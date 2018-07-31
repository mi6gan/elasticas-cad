
/***************************************************************************
 *   Copyright (C) 2008 by Michael Boyarov                                 *
 *   mi666gan@gmail.com                                                    *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "kongovideodevice.h"
namespace Kongomato{ namespace VideoDevice{

ResourceFileStream::ResourceFileStream( const char * filename, std::ios_base::openmode mode):Base::IOStream(filename,mode)
{
}
//___________________________________________________________________________________
Resource::Resource(const resource_type & type,const std::string & resource_name)
{
    this->resource_name=resource_name;
    this->type=type;
    this->ref_count=1;
    Manager::Instance()->AddObject(this);
}

Resource::~Resource()
{
    Manager::Instance()->RemoveObject(this);
}

const std::string & Resource::GetMetaInfo()
{
    return meta_info;
}

resource_type & Resource::GetType()
{
    return this->type;
}
//___________________________
void DrawTarget::MakeNotCurrent()
{

}

void DrawTarget::MakeCurrent()
{    
}

void DrawTarget::Present()
{

}

const Math::Size<int> & DrawTarget::GetSize()
{
    return this->size;
}

//___________________________
bool FrameBuffer::is_EXT=false;
FrameBuffer::FrameBuffer():Resource(framebuffer_resource)
{
    if(is_EXT) glGenFramebuffersEXT(1,&gl_id);
    else glGenFramebuffers(1,&gl_id);
}

FrameBuffer::~FrameBuffer()
{
    if(is_EXT) glDeleteFramebuffersEXT(1,&gl_id);
    else glDeleteFramebuffers(1,&gl_id);
}

void FrameBuffer::BindTexture(VideoDevice::Texture* texture)
{
    this->Bind();
    texture->Bind();
    if(is_EXT)
    {
        glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT,GL_COLOR_ATTACHMENT0_EXT,GL_TEXTURE_2D,texture->gl_id,0);
        if(glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT)!=GL_FRAMEBUFFER_COMPLETE_EXT) throw "void FrameBuffer::BindTexture(VideoDevice::Texture* texture)";
    }
    else
    {
        glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,texture->gl_id,0);
        if(glCheckFramebufferStatus(GL_FRAMEBUFFER)!=GL_FRAMEBUFFER_COMPLETE) throw "void FrameBuffer::BindTexture(VideoDevice::Texture* texture)";
    }
    texture->Unbind();
    this->Unbind();

}

void FrameBuffer::Bind()
{
    if(is_EXT) glBindFramebufferEXT(GL_FRAMEBUFFER_EXT,gl_id);
    else glBindFramebuffer(GL_FRAMEBUFFER,gl_id);
}

void FrameBuffer::Unbind()
{
    if(is_EXT) glBindFramebufferEXT(GL_FRAMEBUFFER_EXT,0);
    else glBindFramebuffer(GL_FRAMEBUFFER,0);
}


//___________________________
void FrontBuffer::MakeCurrent()
{    
    VideoDevice::Context* ccon=VideoDevice::Manager::Instance()->GetCurrentContext();
    if(ccon)
    {
        this->Update();
        ccon->SetViewportRectangleBehavior(Context::AspectConsideredVRBehavior,false);
    }
    DrawTarget::MakeCurrent();
}

void FrontBuffer::Update()
{
    VideoDevice::Context* ccon=VideoDevice::Manager::Instance()->GetCurrentContext();
    if(ccon)
    {
        const Base::VideoMode & videomode=ccon->GetVideoMode();
        this->size.width()=videomode.width();
        this->size.height()=videomode.height();
    }
}

void FrontBuffer::MakeNotCurrent()
{
    DrawTarget::MakeNotCurrent();
}

void FrontBuffer::Present()
{
    VideoDevice::Context* ccon=VideoDevice::Manager::Instance()->GetCurrentContext();
    if(ccon)
    {        
        ccon->SwapBuffers();
    }
    DrawTarget::Present();
}
//____________________________
bool Texture::flip_reverse=false;

void Texture::MakeCurrent()
{
    flip_reverse=true;
    VideoDevice::Context* ccon=VideoDevice::Manager::Instance()->GetCurrentContext();
    const Base::VideoMode & videomode=ccon->GetVideoMode();
    if(((Manager::Instance()->GetAccelerationCaps()&framebuffer_acceleration)==framebuffer_acceleration)&&!frame_buffer)
    {
        frame_buffer=new FrameBuffer;
        frame_buffer->BindTexture(this);        
    }
    if(frame_buffer)
    {
        frame_buffer->Bind();
        ccon->SetViewportRectangleBehavior(Context::SimpleVRBehavior);
    }
    else std::cout<<"Can't make texture as current drawing target: no framebuffer support"<<std::endl;
    DrawTarget::MakeCurrent();
}

void Texture::MakeNotCurrent()
{    
    DrawTarget::MakeNotCurrent();
    if(frame_buffer) frame_buffer->Unbind();
    flip_reverse=false;
}

void Texture::Present()
{  
    VideoDevice::Context* ccon=VideoDevice::Manager::Instance()->GetCurrentContext();
    const Base::VideoMode & videomode=ccon->GetVideoMode();
    if(frame_buffer)  DrawTarget::Present();
}

Texture::Texture(char* image,int width,int height,int px_size,GLuint format)
{
    frame_buffer=NULL;
    this->width=width;this->height=height;
    this->Initialize(image,width,height,px_size,format);
}

Texture::Texture(const std::string & filename,int width,int height,Base::Color<float> fill_color):Resource(texture_resource)
{ 
    frame_buffer=NULL;
    if(!width) width=4;
    if(!height) height=4;
    this->width=width;this->height=height;    
    std::ifstream file(filename.c_str());
#ifdef WITH_QT4
    if(Kongomato::VideoDevice::Manager::Instance()->GetCurrentContext()->GetType()==Qt4_Context)
    {
        if(!filename.empty()&&(!file.fail()))
        {
            QImage image(QObject::trUtf8(filename.c_str()));
            int bpp=image.bytesPerLine()/image.width();
            if(bpp==3) this->format=GL_BGR;
            else  this->format=GL_BGRA;
            this->Initialize((char*)image.bits(),image.width(),image.height(),bpp,format);
        }
        else
        {
            QImage image(width,height,QImage::Format_ARGB32);
            image.fill((int(fill_color.r*256)>>24)+(int(fill_color.g*256)>>16)+(int(fill_color.b*256)>>8));
            this->Initialize((char*)image.bits(),image.width(),image.height(),4,GL_RGBA);
        }
    }
    else
#endif
#ifdef WITH_SDL
    {
        SDL_Surface* surface=NULL;
        if(!filename.empty()&&(!file.fail()))
        {            
            surface=IMG_Load(filename.c_str());
            if(!surface) throw VideoDevice::TextureException();
        }
        else
        {
            Uint32 rmask, gmask, bmask, amask;
            #if SDL_BYTEORDER == SDL_BIG_ENDIAN
             rmask = 0xff000000;
             gmask = 0x00ff0000;
             bmask = 0x0000ff00;
             amask = 0x000000ff;
            #else
             rmask = 0x000000ff;
             gmask = 0x0000ff00;
             bmask = 0x00ff0000;
             amask = 0xff000000;
            #endif
            surface=SDL_CreateRGBSurface(SDL_SWSURFACE,width,height,32,rmask,gmask,bmask,amask);
        }
        switch(surface->format->BitsPerPixel)
        {
            case 24: this->format=GL_RGB;break;
            case 32: this->format= GL_RGBA;break;
            default: throw VideoDevice::TextureException();
        }
        SDL_LockSurface(surface);
        this->Initialize((char*)surface->pixels,surface->w,surface->h,surface->format->BitsPerPixel/8,format);
        SDL_UnlockSurface(surface);
        SDL_FreeSurface(surface);
    }
#else
    {}
#endif
    if(!filename.empty()&&(!file.fail()))
    {

        struct stat attributes;
        stat(filename.c_str(),&attributes);
        std::stringstream string_stream;
        // string_stream<<"<resource type="<<int(this->type)<<"  time="<<long(attributes.st_atim.tv_nsec)<<" />";
        std::string new_meta_info=string_stream.str();
        this->meta_info=new_meta_info;        
     }
    if(file.fail()) this->resource_name="";
    else this->resource_name=filename;
}

void Texture::Initialize(char* image,int width,int height,int px_size,GLuint format)
{
        if(!width||!height) throw TextureException();
        char* new_image=NULL;
        this->width=width;this->height=height;
        this->real_width=next_p2(width);this->real_height=next_p2(height);
        this->size.width()=real_width;
        this->size.height()=real_height;
        this->format=format;
        if((this->real_width!=width)||(this->real_height!=height))
        {
         new_image=(char*)malloc(this->real_width*real_height*px_size);
         for(int a=0;a<this->real_height;a++)
         for(int b=0;b<this->real_width;b++)
         {
                if(a<height&&b<width) memcpy(&new_image[px_size*(a*this->real_width+b)],&image[px_size*(a*width+b)],px_size);
                else memset(&new_image[px_size*(a*this->real_width+b)],0,px_size);
         }           
           glGenTextures(1,&gl_id);
           this->Bind();
           glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
           glTexImage2D(GL_TEXTURE_2D, 0, px_size,real_width,real_height, 0,format, GL_UNSIGNED_BYTE, 0);
           this->Unbind();
           Texture* tex=new Texture(new_image,this->real_width,this->real_height,px_size,format);           
           delete new_image;
           VideoDevice::Manager* videodevice=VideoDevice::Manager::Instance();
           VideoDevice::DrawTarget* dt=videodevice->GetCurrentDrawTarget();           
           videodevice->SetCurrentDrawTarget(this);
           tex->Draw(Math::Rectangle<int>(0,
                                          -(real_height*(real_height-height))/height,
                                          real_width+(real_width*(real_width-width))/width,
                                          real_height+(real_height*(real_height-height))/height));
           videodevice->Present();
           videodevice->SetCurrentDrawTarget(dt);
           delete tex;           
        }
        else
        {
            glGenTextures(1,&gl_id);
            glBindTexture(GL_TEXTURE_2D, gl_id);
            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
            glTexImage2D(GL_TEXTURE_2D, 0, px_size,real_width,real_height, 0,format, GL_UNSIGNED_BYTE, image);
            glBindTexture(GL_TEXTURE_2D, 0);
        }
}

int Texture::Width() const
{
    return this->width;
}

int Texture::Height() const
{
    return this->height;
}

void Texture::PrivateDraw(const Math::Rectangle<int> & dest,const Math::Rectangle<int> & src,VideoDevice::texture_draw_flags effect,bool texture_size)
{
    VideoDevice::Manager* dev=VideoDevice::Manager::Instance();
    Math::Matrix4x4<float> final_matrix;
    Math::Rectangle<double> ldest(dest.x(),dest.y(),dest.width(),dest.height());
    Math::Rectangle<double> lsrc(src.x(),src.y(),src.width(),src.height());
    double used_width=this->Width();
    double used_height=this->Height();
    glPushAttrib(GL_ENABLE_BIT|GL_VIEWPORT_BIT|GL_COLOR_BUFFER_BIT);
    glDisable(GL_LIGHTING);
    glDisable(GL_CULL_FACE);
    // glEnable(GL_BLEND);
    // glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    Math::Size<int> size;
    if(!texture_size) size=dev->GetCurrentDrawTarget()->GetSize();
    else size=this->GetSize();    
    glViewport(-size.width(),-size.height(),2*size.width(),2*size.height());
    if((effect&VideoDevice::texture_draw_nopotabstraction)==VideoDevice::texture_draw_nopotabstraction)
    {
        used_width=this->real_width;
        used_height=this->real_height;
    }
    if(lsrc.width()==0.0f) lsrc.width()=used_width;
    if(lsrc.height()==0.0f) lsrc.height()=used_height;
    if(ldest.width()==0.0f) ldest.width()=used_width;
    if(ldest.height()==0.0f) ldest.height()=used_height;
    dev->SetTransform(VideoDevice::world2d_transformation,final_matrix);
    dev->ApplyTransformations(Manager::Matrix2DMode);
    bool mirror=((effect&VideoDevice::texture_draw_mirror)==VideoDevice::texture_draw_mirror);
    bool flip=((effect&VideoDevice::texture_draw_flip)==VideoDevice::texture_draw_flip);    
    if(flip_reverse) flip=!flip;
    ldest.x()=double(ldest.x())/double(size.width());
    ldest.y()=double((size.height()-ldest.height())-ldest.y())/double(size.height());
    ldest.width()=double(ldest.width())/double(size.width());
    ldest.height()=double(ldest.height())/double(size.height());
    this->Bind();
    glBegin(GL_QUADS);
    glTexCoord2f(mirror,flip);glVertex3f(ldest.x(),ldest.y()+ldest.height(),1.0f);
    glTexCoord2f(!mirror,flip);glVertex3f(ldest.x()+ldest.width(),ldest.y()+ldest.height(),1.0f);
    glTexCoord2f(!mirror,!flip);glVertex3f(ldest.x()+ldest.width(),ldest.y(),1.0f);
    glTexCoord2f(mirror,!flip);glVertex3f(ldest.x(),ldest.y(),1.0f);
    glEnd();
    this->Unbind();
    glPopAttrib();
}

void Texture::Draw(VideoDevice::texture_draw_flags effect)
{
    Texture::Draw(Math::Rectangle<int>(0,0,0,0),Math::Rectangle<int>(0,0,0,0),effect);
}

void Texture::Draw(const Math::Rectangle<int> & dest,const Math::Rectangle<int> & src,VideoDevice::texture_draw_flags effect)
{
    this->PrivateDraw(dest,src,effect);
}


void Texture::Bind(bool filters)
{

    glBindTexture(GL_TEXTURE_2D,gl_id);
    if(filters)
    {
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    }
}


void Texture::Unbind()
{
    glBindTexture(GL_TEXTURE_2D,0);
}

Texture::~Texture()
{
    glDeleteTextures(1,&gl_id);
    if(frame_buffer) delete frame_buffer;
}

//________________________________________________________________________________
ElementBuffer::ElementBuffer(const GLvoid* data,GLsizeiptr size_in_bytes,GLenum target,GLenum usage)
{
    gl_id=GL_INVALID_VALUE;
    if((VideoDevice::Manager::Instance()->GetAccelerationCaps()&VideoDevice::vertexbuffer_acceleration)==VideoDevice::vertexbuffer_acceleration)
    {
        glGenBuffers(1,&gl_id);
        glBindBuffer(target,gl_id);
        glBufferData(target,size_in_bytes,data,usage);
        glBindBuffer(target, 0);
    }
}

ElementBuffer::~ElementBuffer()
{
    if((VideoDevice::Manager::Instance()->GetAccelerationCaps()&VideoDevice::vertexbuffer_acceleration)==VideoDevice::vertexbuffer_acceleration) glDeleteBuffers(1,&gl_id);
}

//_______________________________________________________________________________
GLenum VertexBuffer::VertexAttributeTypeToGLtype(Base::vertex_attribute_type type)
{
    switch(type)
    {
        case Base::vertex_attribute_short:
            return GL_SHORT;break;
        case Base::vertex_attribute_unsigned_short:
            return GL_UNSIGNED_SHORT;break;
        case Base::vertex_attribute_int:
            return GL_INT;break;
        case Base::vertex_attribute_unsigned_int:
            return GL_UNSIGNED_INT;break;
        case Base::vertex_attribute_float:
            case Base::vertex_attribute_unsigned_float:
            return GL_FLOAT;break;
        case Base::vertex_attribute_double:
            case Base::vertex_attribute_unsigned_double:
                return GL_DOUBLE;break;
    }
    throw VertexBufferException();
}

VertexBuffer::VertexBuffer(GLenum usage):Resource(vertexbuffer_resource)
{
    this->synchronized=true;
    this->usage=usage;
}

void VertexBuffer::Synchronize()
{
    for(int a=0;a<buffers.size();a++) delete buffers[a];
    buffers.clear();
    actual_size=0;
    for(int a=0;a<this->components.size();a++)
    {
        if(a==0) actual_size=this->components[a]->size();
        else if(this->components[a]->size()<actual_size) actual_size=this->components[a]->size();
        buffers.push_back(new ElementBuffer(components[a]->get_Cbuffer_pointer(),components[a]->get_Cbuffer_size(),GL_ARRAY_BUFFER,this->usage));
    }
    synchronized=true;
}

void VertexBuffer::Bind()
{
    if(!synchronized) this->Synchronize();
    const GLvoid* pointer;
    for(int a=0;a<buffers.size();a++)
    {
                pointer=NULL;
                if(buffers[a]->gl_id!=GL_INVALID_VALUE) glBindBuffer(GL_ARRAY_BUFFER,buffers[a]->gl_id);
                else pointer=this->components[a]->get_Cbuffer_pointer();
                switch(this->components[a]->get_vertex_attribute_id())
                {
                    case Base::vertex_attribute_id_position:
                        glVertexPointer(this->components[a]->get_element_capacity(),
                                            VertexAttributeTypeToGLtype(this->components[a]->get_vertex_attribute_type()),0,pointer);
                        glEnableClientState(GL_VERTEX_ARRAY);
                    break;

                    case Base::vertex_attribute_id_normal:
                        glNormalPointer(VertexAttributeTypeToGLtype(this->components[a]->get_vertex_attribute_type()),0,pointer);
                        glEnableClientState(GL_NORMAL_ARRAY);
                    break;                    

                    case Base::vertex_attribute_id_texture_coordinate:
                        glTexCoordPointer(this->components[a]->get_element_capacity(),
                                            VertexAttributeTypeToGLtype(this->components[a]->get_vertex_attribute_type()),0,pointer);
                        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
                    break;

                    case Base::vertex_attribute_id_color:
                        glColorPointer(this->components[a]->get_element_capacity(),
                                            VertexAttributeTypeToGLtype(this->components[a]->get_vertex_attribute_type()),0,pointer);
                        glEnableClientState(GL_COLOR_ARRAY);
                    break;

                    default:
                        glVertexAttribPointer(this->components[a]->get_vertex_attribute_id(),
                                              this->components[a]->get_element_capacity(),
                                              VertexAttributeTypeToGLtype(this->components[a]->get_vertex_attribute_type()),
                                              GL_FALSE,0,pointer);
                        glEnableVertexAttribArray(this->components[a]->get_vertex_attribute_id());
                    break;
                }
                if(buffers[a]->gl_id!=GL_INVALID_VALUE) glBindBuffer(GL_ARRAY_BUFFER,0);                
    }

}


void VertexBuffer::Unbind()
{
    for(int a=0;a<buffers.size();a++)
    {
        switch(this->components[a]->get_vertex_attribute_id())
        {
            case Base::vertex_attribute_id_position:
                glDisableClientState(GL_VERTEX_ARRAY);
            break;

            case Base::vertex_attribute_id_normal:
                glDisableClientState(GL_NORMAL_ARRAY);
            break;

            case Base::vertex_attribute_id_texture_coordinate:
                glDisableClientState(GL_TEXTURE_COORD_ARRAY);
            break;

            case Base::vertex_attribute_id_color:
                glDisableClientState(GL_COLOR_ARRAY);
            break;

            default:
                glDisableVertexAttribArray(this->components[a]->get_vertex_attribute_id());
            break;
        }
    }
}


void VertexBuffer::Draw(GLuint primitive_type)
{
        Manager::Instance()->ApplyTransformations();
        this->Bind();
        if(this->actual_size>0) glDrawArrays(primitive_type, 0,this->actual_size);
        this->Unbind();
}

VertexBuffer::~VertexBuffer()
{
    for(int a=0;a<buffers.size();a++) delete buffers[a];
}

void VertexBuffer::operator =(Base::VerticesContainer& v)
{
    (*((Base::VerticesContainer*)( this)))=v;        

}

//_______________________________________________________________________________

GLenum IndexBuffer::IndexTypeToGLtype(Base::index_type it)
{
    if(it==Base::index_16) return GL_UNSIGNED_SHORT;
    return GL_UNSIGNED_INT;
}

IndexBuffer::IndexBuffer(GLenum usage):Resource(indexbuffer_resource)
{
    this->usage=usage;
    buffer=NULL;
}

void IndexBuffer::Synchronize()
{
  //  if((VideoDevice::Manager::Instance()->GetAccelerationCaps()&VideoDevice::vertexbuffer_acceleration)!=VideoDevice::vertexbuffer_acceleration) return;
    if(buffer) delete buffer;
    buffer=new ElementBuffer(this->get_CBuffer_pointer(),this->get_CBuffer_size(),GL_ELEMENT_ARRAY_BUFFER,this->usage);
    synchronized=true;
}

void IndexBuffer::Draw(GLuint primitive_type)
{
    if(!this->synchronized) this->Synchronize();
    if(!buffer) return;
    const GLvoid* pointer=NULL;
   if(buffer->gl_id==GL_INVALID_VALUE) pointer=this->get_CBuffer_pointer();
   else  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,buffer->gl_id);
    Manager::Instance()->ApplyTransformations();
    glDrawElements(primitive_type,this->size(),IndexTypeToGLtype(this->current_type),pointer);
    if(buffer->gl_id!=GL_INVALID_VALUE) glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
}


void IndexBuffer::operator =(Base::IndicesContainer& v)
{
    (*(Base::IndicesContainer*)(this))=v;
}

IndexBuffer::~IndexBuffer()
{
    delete buffer;
}
//______________________________________________________________________________________

SubMesh::SubMesh(const std::string & src_filename,bool no_indices):Resource(submesh_resource)
{
    vb=NULL;
    ib=NULL;
    texture=NULL;    
    this->no_indices=no_indices;
    this->src_filename=src_filename;
    this->primitive_type=GL_TRIANGLES;
}

SubMesh::SubMesh(bool no_indices,const std::string & uid):Resource(submesh_resource)
{
    VideoDevice::Manager* device_manager=VideoDevice::Manager::Instance();
    this->no_indices=no_indices;
    vb=new VertexBuffer;
    if(!no_indices) ib=new IndexBuffer;
    else ib=NULL;
    texture=NULL;    
    this->primitive_type=GL_TRIANGLES;
}

void SubMesh::setPrimitiveType(GLuint primitive_type)
{
    this->primitive_type=primitive_type;
}

void SubMesh::LoadFrom3DS(const std::string & file_name,const std::string mesh_name,int xi,int yi,int zi)
{
#ifdef SUPPORT_3DS
    Lib3dsFile* file=lib3ds_file_open(file_name.c_str());
    Lib3dsMesh* mesh=NULL;
    if(file) mesh=file->meshes[lib3ds_file_mesh_by_name(file,mesh_name.c_str())];
    if(mesh)
    {
        this->LockBuffers(true);
        Base::VerticesContainer * vb=this->GetVertices();
        Base::IndicesContainer * ib=this->GetIndices();
        Base::ElementsContainer<float> & position=vb->enable_vertex_attribute<float>(Kongomato::Base::vertex_attribute_id_position,3);
        Base::ElementsContainer<float> & normal=vb->enable_vertex_attribute<float>(Kongomato::Base::vertex_attribute_id_normal,3);
        Base::ElementsContainer<float> & uv=vb->enable_vertex_attribute<float>(Kongomato::Base::vertex_attribute_id_texture_coordinate,2);
        ib->set_index_type(Kongomato::Base::index_16);
        ib->resize(0);
        position.resize(mesh->nvertices);
        normal.resize(mesh->nvertices);
        uv.resize(mesh->nvertices);
        unsigned short index;
        for(int i=0;i<mesh->nfaces;i++)
        {
            for(int j=0;j<3;j++)
            {
                index=mesh->faces[i].index[j];
                (*ib).push_back(index);
                position[index][0]=mesh->vertices[index][xi];
                position[index][1]=mesh->vertices[index][yi];
                position[index][2]=mesh->vertices[index][zi];
                if(index<mesh->nvertices)
                {
                    uv[index][0]=mesh->texcos[index][0];
                    uv[index][1]=1-mesh->texcos[index][1];
                }
                normal[index][0]+=0;//mesh->faces[i].normal[xi];
                normal[index][1]+=0;//mesh->faceL[i].normal[yi];
                normal[index][2]+=0;//mesh->faceL[i].normal[zi];


            }
        }
        this->LockBuffers(false);
        lib3ds_file_free(file);
   }
   else
   {
        if(file) lib3ds_file_free(file);
        std::cout<<"could not load mesh "<<mesh_name<<" from "<<file_name<<std::endl;
   }
#else
    std::cout<<"Won't load mesh "<<mesh_name<<" from "<<file_name<<": complile libkongomato with 3ds support."<<std::endl;
#endif
}

void SubMesh::SaveTo3DS(const std::string & file_name,const std::string mesh_name)
{
#ifdef SUPPORT_3DS
        this->LockBuffers(true);

        Base::VerticesContainer * vb=this->GetVertices();
        Base::IndicesContainer * ib=this->GetIndices();
        Base::ElementsContainer<float> * position=&vb->get_elements_container<float>(Base::vertex_attribute_id_position);
        //Base::ElementsContainer<float> * normal=vb->get_elements_container<float>(Base::vertex_attribute_id_normal);

        Lib3dsFile* file=lib3ds_file_new();
        Lib3dsMesh* mesh=lib3ds_mesh_new(mesh_name.c_str());

        lib3ds_mesh_resize_vertices(mesh,position->size(),true,0);
        lib3ds_mesh_resize_faces(mesh,ib->size()/3);
        for(int a=0;a<mesh->nvertices;a++)
        {
            mesh->vertices[a][0]=(*position)[a][0];
            mesh->vertices[a][2]=(*position)[a][1];
            mesh->vertices[a][1]=(*position)[a][2];
        }

        for(int a=0;a<mesh->nfaces;a++)
            for(int b=0;b<3;b++){ mesh->faces[a].index[b]=(*ib)[a*3+b];  mesh->faces[a].smoothing_group=1; }


        lib3ds_file_insert_mesh(file,mesh,0);
        lib3ds_file_save(file,file_name.c_str());

        lib3ds_file_free(file);

        this->LockBuffers(false);
#else
    std::cout<<"Won't save mesh "<<mesh_name<<" to "<<file_name<<": complile libkongomato with 3ds support."<<std::endl;
#endif
}

Base::IndicesContainer* SubMesh::PrivateGetIndices()
{
    if(!ib&&!no_indices) throw Base::Exception("IndicesContainer* SubMesh::GetIndices() exception");
    return ib;
}

Base::VerticesContainer* SubMesh::PrivateGetVertices()
{
    if(!vb) throw Base::Exception("VerticesContainer* SubMesh::GetVertices() exception");
    return vb;
}

Base::AbstractSubMesh* SubMesh::NewChild()
{
    /*
    char num[10];
    std::string id="";        
    if(!this->descriptor.IsNoId())
    {
        sprintf(num,"%d",(int)this->children.size());
        id=this->descriptor.id.ToString()+num;
    } */
    this->children.push_back(new SubMesh(this->no_indices,""));
    return this->children.back();
}

void SubMesh::InitializeTexture(const std::string & texture_filename,int w,int h)
{    
    if(!vb||!ib) throw "void SubMesh::InitializeTexture(const std::string & texture_filename) exception";
    VideoDevice::Manager* device_manager=VideoDevice::Manager::Instance();
    if(texture) delete texture;
    texture=new Texture(texture_filename,w,h);
}

VideoDevice::Texture* SubMesh::GetTexture()
{
    return this->texture;
}

SubMesh::~SubMesh()
{
    if(vb) delete vb;
    if(ib) delete ib;
    if(texture) delete texture;
    int size=this->children.size();
    for(int a=0;a<size;a++) delete this->children[a];
}

void SubMesh::PrivateLockBuffers(bool lock)
{
    if(!lock) ComputeBoundingBox();
}

void SubMesh::ComputeBoundingBox()
{
    int a=vb->get_vertex_attribute_index(Base::vertex_attribute_id_position);
    if(a<0) return;
    const Base::ElementsContainer<float>& buffer=vb->get_elements_container<float>(Base::vertex_attribute_id_position);
    int size=buffer.size();
    int capacity=buffer.get_element_capacity();    
    if(capacity>3) capacity=3;
    if(size)
    {
        box_min=buffer[0].ToVector();
        box_max=buffer[0].ToVector();
    }
    for(int a=0;a<size;a++)
     for(int b=0;b<capacity;b++)
     {
        if(box_min[b]>buffer[a][b]) box_min[b]=buffer[a][b];
        if(box_max[b]<buffer[a][b]) box_max[b]=buffer[a][b];
     }
}

bool SubMesh::IsPointIn(const Math::Vector3D<float> & p) const
{
    return true;
}
/*
bool SubMesh::IntersectWithLine(const Math::Vector3D<double> & p1,const Math::Vector3D<double> & p2,Math::Vector3D<double> & out=Math::Vector3D<double>())
{
    if(this->ib)
    {

        if(a<vb->get_vertex_attribute_index(Base::vertex_attribute_id_position)) return false;
        const Base::ElementsContainer<float>& vertices=vb->get_elements_container<float>(Base::vertex_attribute_id_position);
        if(vertices.capacity()<3) return false;
        const Base::IndicesContainer & indices=(*ib);
        int size=indices.size();
        const Math::Matrix4x4<float> & matrix=Manager::Instance()->GetModelViewProjectionMatrix();
        Math::Vector3D<float> pp[3],tp1=p1*matrix,tp2=p2*matrix;

        for(int a=0;a<size;a+=3)
        {
            for(int b=0;b<3;b++)
            {
                pp.x()=vertices[indices[a]][0];
                pp.y()=vertices[indices[a]][1];
                pp.z()=vertices[indices[a]][2];
                pp=matrix*pp;
            }
        }
    }
}
*/
bool SubMesh::IsLineIntersects(const Math::Vector3D<float> & p1,const Math::Vector3D<float> & p2) const
{
    return IsPointIn(p1)||IsPointIn(p2);
}

bool SubMesh::ScreenPointToSurfacePoint(const Math::Vector2D<float> & screen_inp,Math::Vector3D<float> & outp1,const Math::CommonMatrix<float> & matrix,VideoDevice::Context* context)
{    
    if(this->ib)
    {

        Kongomato::VideoDevice::Manager* device=Kongomato::VideoDevice::Manager::Instance();
        const Math::Rectangle<int> & vr=context->GetViewportRectangle();        
        std::cout<<screen_inp<<" "<<matrix<<" "<<vr<<std::endl;        
        int total_i=this->ib->size();
        const Base::ElementsContainer<float>& vertices=this->vb->get_elements_container<float>(Base::vertex_attribute_id_position);
        Math::Vector4D<float> trans_vertices[4];
        Math::CommonMatrix<float> inv_matrix=matrix.Inversion();
        Math::Vector2D<float> inp(float(2.0f*screen_inp.x()-2.0f*vr.x()-vr.width())/float(vr.width()),
                                   float(2.0f*(vr.height()-screen_inp.y())-2.0f*vr.y()-vr.height())/float(vr.height()));
        std::cout<<"screen_inp="<<screen_inp<<std::endl;
        std::cout<<"inp="<<inp<<std::endl;

        float min_x;

        for(int a=0;a<total_i;a+=3)
        {            
            for(int b=0;b<3;b++)
            {
                Math::CommonVector<float> vertex=vertices[(*this->ib)[a+b]].ToVector();
                vertex.push_back(1.0f);                
                trans_vertices[b]=vertex*matrix;
                trans_vertices[b].x()/=trans_vertices[b].w();
                trans_vertices[b].y()/=trans_vertices[b].w();
                trans_vertices[b].z()/=trans_vertices[b].w();
                if(!b) min_x=trans_vertices[b].x();
                else if(trans_vertices[b].x()<min_x) min_x=trans_vertices[b].x();
                std::cout<<trans_vertices[b]<<std::endl;
            }
            float line_length=fabs(min_x-inp.x());
            bool intersected=false;
            int c=0;
            for(int b=0;b<3;b++)
            {
                    if(b==2) c=0; else c=b+1;
                    float x0=trans_vertices[b].x(),x1=trans_vertices[c].x();
                    float y0=trans_vertices[b].y(),y1=trans_vertices[c].y();
                    float y=inp.y(),x=(x0*y1-x1*y0+(x1-x0)*y)/(y1-y0);                    
                    float expected_line_length=fabs(x-min_x)+fabs(x-inp.x());
                    std::cout<<"expected="<<expected_line_length<<" actual="<<line_length<<std::endl;
                    if(expected_line_length>=line_length-0.0005&&expected_line_length<=line_length+0.0005)
                        if(intersected)
                        {
                            intersected=false;
                            break;
                        }
                        else intersected=true;
           }
            if(intersected)
            {
                outp1=trans_vertices[0];
                return true;                
                float x0=trans_vertices[0].x(),x1=trans_vertices[1].x(),x2=trans_vertices[2].x();
                float y0=trans_vertices[0].y(),y1=trans_vertices[1].y(),y2=trans_vertices[2].y();
                float z0=trans_vertices[0].z(),z1=trans_vertices[1].z(),z2=trans_vertices[2].z();
                float x=inp.x(),y=inp.y();
                float z=(((x0-x)*y1+(x-x1)*y0+(x1-x0)*y)*z2+((x-x0)*y2+(x2-x)*y0+(x0-x2)*y)*z1+((x1-x)*y2+(x-x2)*y1+(x2-x1)*y)*z0)/((x1-x0)*y2+(x0-x2)*y1+(x2-x1)*y0);                
                std::cout<<"intersected"<<std::endl;
          //      std::cout<<Math::Vector3D<float>(x,y,z)<<std::endl;
                // trans_vertices[0].w()
                outp1=Math::Vector4D<float>(x,y,z,trans_vertices[0].w())*inv_matrix;
         //       std::cout<<(Math::Vector4D<float>(x,y,z,trans_vertices[0].w())*inv_matrix)<<std::endl;
                return true;
            }
        }
    }
    int ccount=children.size();
    for(int a=0;a<ccount;a++) if(dynamic_cast<SubMesh*>(children[a])->ScreenPointToSurfacePoint(screen_inp,outp1,matrix,context)) return true;
    return false;
}
/*
bool SubMesh::IntersectByLine(Math::Vector3D<float> & inp1,Math::Vector3D<float> & inp2,Math::Vector3D<float> & outp1)
{

}
*/

bool SubMesh::IsPointIn(const Math::Vector2D<float> & p,const Math::Matrix4x4<float> & trans) const
{
    //const Math::Matrix4x4<float> & mvp_matrix=Manager::Instance()->GetModelViewProjectionMatrix();
    //Math::Vector3D<float> tr_box_min=mvp_matrix*box_min,tr_box_max=mvp_matrix*box_max;
    //for(int a=0;a<8;a++)
    //return p.x()>box_min.x()&&p.y()>box_min.y()&&box_min.z();
    return true;
}

const Math::Vector3D<float> & SubMesh::GetBoundingBoxMin()
{
    return box_min;
}

const Math::Vector3D<float> & SubMesh::GetBoundingBoxMax()
{
    return box_max;
}

void SubMesh::Draw()
{
    if(vb)
    {
        if(texture) texture->Bind(true);
        if(no_indices) vb->Draw(this->primitive_type);
        else
        {
            if(!ib) throw "void SubMesh::Draw() exception";
            vb->Bind();
            ib->Draw(this->primitive_type);
            vb->Unbind();
        }
        if(texture) texture->Unbind();
    }
    for(int a=0;a<children.size();a++) dynamic_cast<SubMesh*>(children[a])->Draw();
}
//_____________________________________________________________________________
void Context::MakeCurrent()
{
    if(!glee_inited)
    {
    Manager* device=Manager::Instance();
    std::ostream & log_stream=VideoDevice::Manager::Instance()->GetLogStream();
    GLeeInit();
    log_stream<<"checking for GL_ARB_vertex_buffer_object...";
    if(GLEE_ARB_vertex_buffer_object) log_stream<<"OK"<<std::endl;
    else
    {
        device->SetAccelerationCaps(device->GetAccelerationCaps()^vertexbuffer_acceleration);
        log_stream<<"missing"<<std::endl;
    }
    log_stream<<"checking for GL_ARB_vertex_blend...";
    if(GLEE_ARB_vertex_blend) log_stream<<"OK"<<std::endl;
    else log_stream<<"missing"<<std::endl;
    log_stream<<"checking for GL_ARB_vertex_program...";
    if(GLEE_ARB_vertex_program) log_stream<<"OK"<<std::endl;
    else log_stream<<"missing"<<std::endl;
    log_stream<<"checking for GL_ARB_framebuffer_object...";
    if(GLEE_ARB_framebuffer_object)
    {
       device->SetAccelerationCaps(device->GetAccelerationCaps()|framebuffer_acceleration);
        log_stream<<"OK"<<std::endl;
    }
    else
    {
        log_stream<<"missing"<<std::endl;
        log_stream<<"checking for GL_EXT_framebuffer_object...";
        if(GLEE_EXT_framebuffer_object)
        {
           device->SetAccelerationCaps(device->GetAccelerationCaps()|framebuffer_acceleration);
           FrameBuffer::is_EXT=true;
            log_stream<<"OK"<<std::endl;
        }
        else log_stream<<"missing"<<std::endl;
    }
 /*   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);*/
   /* glEnable(GL_CULL_FACE);
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);*/
    glee_inited=true;
 }



}

void Context::MakeNotCurrent()
{

}

const Math::Rectangle<int> & Context::GetViewportRectangle()
{
    Manager* dev=Manager::Instance();
    if(dev->GetCurrentDrawTarget())
    {
        const Math::Size<int> & dt_size=dev->GetCurrentDrawTarget()->GetSize();
        int width=dt_size.width(),height=dt_size.height();
        if(Base::IsFlagSet<>(vr_behavior,AspectConsideredVRBehavior))
        {
            int aw=dev->GetAspectWValue(),ah=dev->GetAspectHValue();
            int ph=(width*ah)/aw,h=height;
            int pw=(height*aw)/ah,w=width;
            if(ph>=h) viewport_rectangle=Math::Rectangle<int>(0,(h-ph)/2,w,ph);
            else viewport_rectangle=Math::Rectangle<int>((w-pw)/2,0,pw,h);
        }
        else viewport_rectangle=Math::Rectangle<int>(0,0,width,height);
    }
    return this->viewport_rectangle;
}

void Context::RestoreViewportRectangle()
{
    Manager* dev=Manager::Instance();
    if(dev->GetCurrentContext()!=this) throw Base::Exception("void Context::RestoreViewportRectangle()");
    if(!dev->GetCurrentDrawTarget()) return;
    const Math::Rectangle<int> & r=this->GetViewportRectangle();
    glViewport(r.x(),r.y(),r.width(),r.height());
}

void Context::SwapBuffers()
{

}

const context_type & Context::GetType()
{
    return this->type;
}

Context::Context(const context_type & ct)
{
    this->type=ct;
    this->videomode=videomode;
    this->vr_behavior=AspectConsideredVRBehavior;
    this->glee_inited=false;
}

void Context::Resize(int w,int h,bool activate)
{
    videomode.width()=w;videomode.height()=h;
    if(activate&&Manager::Instance()->GetCurrentContext()==this) this->RestoreViewportRectangle();
}

const Context::ViewportRectangleBehavior & Context::GetViewportRectangleBehavior()
{
    return vr_behavior;
}

void Context::SetViewportRectangleBehavior(const ViewportRectangleBehavior & vr,bool activate)
{
    vr_behavior=vr;
    if(activate&&Manager::Instance()->GetCurrentContext()==this) this->RestoreViewportRectangle();
}

void Context::SetVideoMode(const Base::VideoMode & videomode,bool activate)
{
    this->videomode=videomode;
    if(activate&&Manager::Instance()->GetCurrentContext()==this) this->RestoreViewportRectangle();

}

const Base::VideoMode & Context::GetVideoMode() const
{
    return videomode;
}



Context::~Context()
{
    Manager* videodevice=Manager::Instance();
    //if(videodevice->GetCurrentContext()==this) videodevice->SetNullContext();

}
//_____________________________________________________________________________
#ifdef WITH_SDL
SDLContext::SDLContext():Context(SDL_Context)
{
/*        this->SetClipRectangle(Math::Rectangle<int>(0,0,0,0));
        this->empty_context=new NullContext(Base::VideoMode(320,200,true,true,32));
        this->current_drawing_target=this->front_buffer=new FrontBuffer;*/
}

void SDLContext::MakeNotCurrent()
{
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
}

void SDLContext::MakeCurrent()
{
    std::ostream & log_stream=Manager::Instance()->GetLogStream();
    log_stream<<"SDL:Initializing video device..."<<std::endl;
    if(SDL_Init(SDL_INIT_VIDEO)<0) log_stream<<"failed"<<std::endl;
    else log_stream<<"OK"<<std::endl;
   SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 5);
   SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 5);
   SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 5);
   SDL_GL_SetAttribute( SDL_GL_ALPHA_SIZE, 5);
   SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, videomode.doublebuffer());
   SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE,1);
   SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS,1);
   SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES,4);
   if(SDL_SetVideoMode(videomode.width(),videomode.height(), videomode.bpp(),SDL_SWSURFACE|SDL_ANYFORMAT|SDL_OPENGL | (SDL_FULLSCREEN*(videomode.fullscreen())))<0)
   throw Base::Exception("SDLContext::PrivateMakeCurrent() exception");
   Context::MakeCurrent();
}

void SDLContext::SwapBuffers()
{    
    SDL_GL_SwapBuffers();
    Context::SwapBuffers();
}

SDLContext::~SDLContext()
{
}
#endif
//______________________________________________________________________________
#ifdef WITH_QT4

//_______________________________________________________________________________

GLWidget::GLWidget(Qt4Context* context,const QGLWidget * shareWidget,QWidget * parent):QGLWidget(parent,shareWidget)
{
    this->context=context;
}

void GLWidget::paintGL()
{
    this->context->SetCurrentWidget(this);
    this->repaintGL();
}

Qt4Context::Qt4Context():Context(Qt4_Context)
{
    format=QGLFormat(QGL::FormatOptions(QGL::DoubleBuffer|QGL::Rgba|QGL::StencilBuffer|QGL::SampleBuffers));
    format.setRedBufferSize(5);
    format.setGreenBufferSize(5);
    format.setBlueBufferSize(5);
    format.setStencilBufferSize(1);
    format.setSampleBuffers (true);
    format.setSamples(4);    
    share_widget=new GLWidget(this);
  //  share_widget->setFormat(format);
   // share_widget->show();
   // share_widget->hide();
    this->SetCurrentWidget(share_widget);    
    share_widget->makeCurrent();
    this->MakeCurrent();
}

void Qt4Context::SetCurrentWidget(GLWidget* widget)
{
   this->Resize(widget->width(),widget->height(),false);
   if(Manager::Instance()->GetCurrentContext()==this)
   {
    Manager::Instance()->GetFrontBuffer()->Update();
    this->RestoreViewportRectangle();
   }
}

void Qt4Context::MakeCurrent()
{
        Context::MakeCurrent();
}

#endif
//_____________________________________________________________________________

Manager::Manager()
{    
        self=this;
        aspect.x()=1;aspect.y()=1;
        current_context=new Context;
        capability_flags=vertexbuffer_acceleration;
        modelviewprojection_changed=true;
        viewprojection_changed=true;
        this->current_drawing_target=NULL;
        this->front_buffer=NULL;
        objects.push_back(new Resource);
}

void Manager::AddObject(Resource* object)
{
    this->objects.push_back(object);
    this->objects_by_type[object->GetType()].push_back(object);
}

void Manager::RemoveObject(Resource* object)
{
    objects_by_type[object->GetType()].remove(object);
    objects.remove(object);
}

Resource* Manager::GetResourceByName(const std::string & name,const resource_type & type)
{
    if(type==empty_resource)
    {        
        for(std::list<Resource*>::iterator it=objects.begin();it!=objects.end();it++)
            if((*it)->resource_name==name) return  *it;
    }
    else
    {
        std::list<Resource*> & objects_list=objects_by_type[type];
        for(std::list<Resource*>::iterator it=objects_list.begin();it!=objects_list.end();it++)
            if((*it)->resource_name==name) return  *it;
    }
    return NULL;
}

Texture* Manager::GetTextureByPath(const std::string & path)
{
    std::list<Resource*>  & objects=objects_by_type[texture_resource];
    for(std::list<Resource*>::iterator it=objects.begin();it!=objects.end();it++) if((*it)->resource_name==path)
    {
        return  static_cast<Texture*>(*it);
    }
    return new Texture(path);
}

void Manager::RemoveManagedResource(Resource* resource)
{
    resource->ref_count--;
    if(!resource->ref_count) delete resource;
}

Math::Vector3D<float> Manager::FromScreenToWorld(int x,int y)
{
        //Matrix4x4<float> mat=matrix[device_transform_projection]*matrix[device_transform_view];
        return Math::Vector3D<float>();
}


Manager* Manager::Instance()
{
        if(!self)   self=new Manager();
	return self;
}

Context * Manager::ChangeContext(const context_type & ct,const Base::VideoMode & videomode)
{    
            int count=contexts.size();
            Context* context;
            if(contexts.find(ct)== contexts.end())
            {
                switch(ct)
                {
                    case Null_Context: contexts[ct]=new Context; break;
#ifdef WITH_SDL
                    case SDL_Context: contexts[ct]=new SDLContext; break;
#endif
#ifdef WITH_QT4
                    case Qt4_Context:contexts[ct]=new Qt4Context; break;
#endif
                }
            }
            context=contexts[ct];            
            if(this->current_context) this->current_context->MakeNotCurrent();            
            this->current_context=context;            
            if(videomode.width()||videomode.height()) this->current_context->SetVideoMode(videomode);
            this->current_context->MakeCurrent();            
            this->current_context->RestoreViewportRectangle();            
            this->SetCurrentDrawTarget(this->current_drawing_target);            
            //std::cout<<"Context * Manager::ChangeContext(const context_type & ct,const Base::VideoMode & videomode): "<<(ct==Qt4_Context)<<","<<int(context);
            return context;
}

Context * Manager::GetCurrentContext()
{
    if(!this->current_context)
    {
        #ifdef WITH_SDL
            return this->ChangeContext(SDL_Context);
        #elif WITH_QT4
            return this->ChangeContext(Qt4_Context);
        #else
            return this->ChangeContext(Null_Context);
        #endif
    }
    return this->current_context;
}

VideoDevice::DrawTarget* Manager::GetCurrentDrawTarget()
{
    return this->current_drawing_target;
}

void Manager::SetCurrentDrawTarget(VideoDevice::DrawTarget* target)
{
    if(!current_context) throw "void Manager::SetCurrentDrawTarget(VideoDevice::DrawTarget* target)";
    if(!target)
    {
        if(!front_buffer) front_buffer=new FrontBuffer;
        target=front_buffer;
    }        
    if(current_drawing_target) current_drawing_target->MakeNotCurrent();            
    this->current_drawing_target=target;
    target->MakeCurrent();              
}

void Manager::SetAccelerationCaps(acceleration_capability_flags caps)
{
        this->capability_flags=caps;
}

acceleration_capability_flags Manager::GetAccelerationCaps()
{
        return capability_flags;
}

void Manager::SetBoolParameter(Kongomato::VideoDevice::bool_parameter p,bool value)
{
        if(value) glEnable((GLenum)p);
        else glDisable((GLenum)p);
}

void Manager::SetUintParameter(Kongomato::VideoDevice::uint_parameter p,unsigned int value)
{
        switch(p)
	{
                case Kongomato::VideoDevice::depthfunc_parameter:
			 glDepthFunc(value);
			break;
                case Kongomato::VideoDevice::clearcolor_parameter:
                        glClearColor(double((value&0xFF000000)>>24)/255.0f,
                                     double((value&0x00FF0000)>>16)/255.0f,
                                     double((value&0x0000FF00)>>8)/255.0f,
                                     double(value&0x000000FF)/255.0f);
			break;

	}
}

void Manager::SetFloatParameter(Kongomato::VideoDevice::float_parameter p,float value)
{
        switch(p)
        {
                case cleardepth_parameter:
                        glClearDepth(value);
                        break;
        }
}

void Manager::SetClearColor(double r,double g,double b,double a)
{
    glClearColor(r,g,b,a);
}

const Math::Vector2D<int> & Manager::GetAspect()
{
    return aspect;
}

int Manager::GetAspectWValue()
{
    return aspect.x();
}

int Manager::GetAspectHValue()
{
    return aspect.y();
}


void Manager::SetAspectWValue(int w)
{
    aspect.x()=w;
}

void Manager::SetAspectHValue(int h)
{
    aspect.y()=h;
}

void Manager::SetAspect(const Math::Vector2D<int> & aspect)
{
    this->aspect=aspect;
}

bool Manager::GetBoolParameter(Kongomato::VideoDevice::bool_parameter p)
{
	bool r;
        glGetBooleanv((GLenum)p,(GLboolean*)&r);
	return r;
}

unsigned int Manager::GetUintParameter(Kongomato::VideoDevice::uint_parameter p)
{
        int r;
        glGetIntegerv((GLenum)p,(GLint*)&r);
	return r;
}

float Manager::GetFloatParameter(Kongomato::VideoDevice::float_parameter p)
{
        float r;
        glGetFloatv((GLenum)p,(GLfloat*)&r);
        return r;
}

FrontBuffer* Manager::GetFrontBuffer()
{
    return this->front_buffer;
}

Manager::~Manager()
{
        this->GetLogStream()<<"closing video device..."<<std::endl;
	self=NULL;
        #ifdef WITH_SDL
	SDL_Quit();
        #endif
        this->GetLogStream()<<"OK"<<std::endl;
}

void Manager::Destroy()
{
	delete self;
	self=NULL;
}


void Manager::SetTransform(Kongomato::VideoDevice::transformation_type t,const Math::Matrix4x4<float>& m)
{    
        matrix[(int)t]=m;
        modelviewprojection_changed=true;
        viewprojection_changed=true;
}

void Manager::AddTransform(Kongomato::VideoDevice::transformation_type t,const Math::Matrix4x4<float>& m)
{
        matrix[(int)t]=m*matrix[(int)t];
        modelviewprojection_changed=true;
        viewprojection_changed=true;
}

const Math::Matrix4x4<float> & Manager::GetTransform(Kongomato::VideoDevice::transformation_type t)
{
    return matrix[(int)t];
}

void Manager::GetTransform(Kongomato::VideoDevice::transformation_type t,Math::Matrix4x4<float>& m)
{
        m=matrix[(int)t];
}

const Math::Matrix4x4<float> & Manager::GetModelViewProjectionMatrix()
{
    if(modelviewprojection_changed)
    {
        modelviewprojection_matrix=(matrix[(int)VideoDevice::world_transformation]*
                                   matrix[(int)VideoDevice::view_transformation]*
                                   matrix[(int)VideoDevice::projection_transformation]);
        modelviewprojection_changed=false;
    }
    return modelviewprojection_matrix;
}

const Math::Matrix4x4<float> & Manager::GetViewProjectionMatrix()
{
    if(viewprojection_changed)
    {
        viewprojection_matrix=(matrix[(int)VideoDevice::view_transformation]*
                                   matrix[(int)VideoDevice::projection_transformation]);
        viewprojection_changed=false;
    }
    return viewprojection_matrix;
}

void Manager::ApplyTransformations(Manager::MatrixMode matrix_mode)
{
    if(matrix_mode==Manager::Matrix3DMode)
    {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
        glMultMatrixf((GLfloat*)(&matrix[(int)projection_transformation](0,0)));
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
        glMultMatrixf((GLfloat*)&matrix[(int)view_transformation](0,0));
        glMultMatrixf((GLfloat*)&matrix[(int)world_transformation](0,0));
    }
    else if(matrix_mode==Manager::Matrix2DMode)
    {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glMatrixMode(GL_MODELVIEW);
        glLoadMatrixf((GLfloat*)&matrix[(int)world2d_transformation](0,0));
    }


}

bool Manager::IsTextureBlank(Texture* t)
{
	return t==blankpng;
}

void Manager::Clear(GLbitfield target)
{
	glClear(target);
}

void Manager::Present()
{
    if(current_drawing_target)    current_drawing_target->Present();
}

void Manager::SetClipRectangle(Math::Rectangle<int> clip_rect)
{        
	this->clip_rect=clip_rect;
}

Math::Rectangle<int> Manager::GetClipRectangle()
{
	return clip_rect;
}

void Manager::SetLogStream(std::ostream * s)
{
    log=s;
}

 std::ostream & Manager::GetLogStream()
 {
     return *log;
 }

Manager* Manager::self=NULL;

std::ostream* Manager::log=&std::cout;

//______________________________________________________________________


}}
