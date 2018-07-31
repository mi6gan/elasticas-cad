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

#include "kongobase.h"

namespace Kongomato { namespace Base
{
Exception::Exception(const char* c) throw()
{
    this->cwhat=c;
}

Exception::~Exception() throw()
{
}

const char* Exception::what() const throw()
{
    return this->cwhat.c_str();
}
//________________________________________________________________________________
AbstractElementsContainer::AbstractElementsContainer(int vertex_attribute_id,vertex_attribute_type type)
{
    this->vertex_attribute_id=vertex_attribute_id;
    this->type=type;
}

void AbstractElementsContainer::set_vertex_attribute_type(vertex_attribute_type type)
{
    this->type=type;
}

vertex_attribute_type AbstractElementsContainer::get_vertex_attribute_type() const
{
    return type;
}

void AbstractElementsContainer::set_vertex_attribute_id(int id)
{
    this->vertex_attribute_id=id;
}

int AbstractElementsContainer::get_vertex_attribute_id() const
{
    return this->vertex_attribute_id;
}
AbstractElementsContainer::~AbstractElementsContainer()
{
}
//__________________________________________________________________________________
IndicesContainer::IndicesContainer(index_type current_type)
{
    this->current_type=current_type;
}

void IndicesContainer::set_index_type(index_type type)
{
    if(type==this->current_type) return;
    int size=this->size();
    for(int a=0;a<size;a++)
    {
        if(type==index_16) i16.push_back(i32[a]);
        else i32.push_back(i16[a]);
    }
    this->resize(0);
    this->current_type=type;
    synchronized=false;
}

index_type IndicesContainer::get_index_type() const
{
    return this->current_type;
}

std::size_t IndicesContainer::size() const
{
    if(this->current_type==index_16) return i16.size();
    return i32.size();
}

void IndicesContainer::resize(std::size_t sz)
{
    if(this->current_type==index_16) i16.resize(sz);
    else i32.resize(sz);
    synchronized=false;
}

void IndicesContainer::push_back(unsigned int i)
{
    if(this->current_type==index_16) i16.push_back(i);
    else i32.push_back(i);
    synchronized=false;
}

void IndicesContainer::insert(int to,unsigned int i)
{
    if(this->current_type==index_16) i16.insert(i16.begin()+to,i);
    else i32.insert(i32.begin()+to,i);
    synchronized=false;
}

unsigned int IndicesContainer::get_value(int i) const
{
    if(this->current_type==index_16) return i16[i];
    return i32[i];
}

void IndicesContainer::set_value(int i,unsigned int value)
{
    if(this->current_type==index_16) i16[i]=value;
    else i32[i]=value;
    synchronized=false;
}

const void* IndicesContainer::get_CBuffer_pointer() const
{
    if(this->current_type==index_16) { if(i16.size()>0) return &i16[0]; }
    else  { if(i32.size()>0) return &i32[0]; }
    return NULL;
}

int IndicesContainer::get_CBuffer_size() const
{
    return size()*((4*(current_type==index_32))+(2*(current_type==index_16)));
}

unsigned int IndicesContainer::operator[](int i) const
{
    if(this->current_type==index_16)
    {
        if(i>=i16.size()) throw Exception("unsigned int IndicesContainer::operator[](int i) const exception");
        return i16[i];
    }
    else
    {
        if(i>=i32.size()) throw Exception("unsigned int IndicesContainer::operator[](int i) const exception");
        return i32[i];
    }
}

unsigned int IndicesContainer::operator[](int i)
{
    if(this->current_type==index_16)
    {
        if(i>=i16.size()) throw Exception("unsigned int IndicesContainer::operator[](int i) const exception");
        return i16[i];
    }
    else
    {
        if(i>=i32.size()) throw Exception("unsigned int IndicesContainer::operator[](int i) const exception");
        return i32[i];
    }
}

//___________________________________________________________________________________
int VerticesContainer::get_vertex_attribute_index(int id) const
{
    for(int a=0;a<components.size();a++)
        if(components[a]->get_vertex_attribute_id()==id) return a;
    return -1;
}

void VerticesContainer::disable_all_vertex_attributes()
{
    int size=components.size();
    for(int a=0;a<size;a++) delete components[a];
    components.clear();
    synchronized=false;
}

void VerticesContainer::disable_vertex_attribute(int id)
{
            int index=this->get_vertex_attribute_index(id);
            if(index>=0)
            {
                delete components[index];
                components.erase(components.begin()+index);
                synchronized=false;
            }
}
void VerticesContainer::clear()
{
    for(int a=0;a<components.size();a++) delete components[a];
    components.resize(0);
    synchronized=false;
}

void VerticesContainer::operator =(const VerticesContainer& vc)
{
    this->clear();
    for(int a=0;a<vc.components.size();a++)
        this->components.push_back(vc.components[a]->clone());
    synchronized=false;
}

VerticesContainer::~VerticesContainer()
{
    for(int a=0;a<components.size();a++) delete components[a];
}
//___________________________________________________________________________________
AbstractSubMesh::AbstractSubMesh()
{
    buffers_locked=false;
}

void AbstractSubMesh::LockBuffers(bool lock)
{
    buffers_locked=lock;
    PrivateLockBuffers(lock);
}

void AbstractSubMesh::AddChild(AbstractSubMesh* ns)
{
    children.push_back(ns);
}

const std::vector<AbstractSubMesh*> & AbstractSubMesh::GetChildren()
{
    return children;
}

AbstractSubMesh::~AbstractSubMesh()
{
    int size=children.size();
    for(int a=0;a<size;a++) delete children[a];
}

 IndicesContainer* AbstractSubMesh::GetIndices()
 {
     if(!buffers_locked) throw Base::Exception("IndicesContainer* AbstractSubMesh::GetIndices() exception");
     return PrivateGetIndices();
 }
 VerticesContainer* AbstractSubMesh::GetVertices()
 {
     if(!buffers_locked) throw Base::Exception("VerticesContainer* AbstractSubMesh::GetVertices() exception");
     return PrivateGetVertices();
 }


//___________________________________________________________________________________

GeometricObject::GeometricObject( Math::Vector3D<float>& position, Math::Vector3D<float>& angle, Math::Vector3D<float>& size)
{
    this->position=position;
    this->angle=angle;
    this->size=size;
    own_axis=true;
}

GeometricObject::GeometricObject(float posx,float posy,float posz,float anglex,float angley,float anglez,float sizex,float sizey,float sizez)
{
    position.x()=posx;position.y()=posy;position.z()=posz;
    angle.x()=anglex;angle.y()=angley;angle.z()=anglez;
    size.x()=sizex;size.y()=sizey;size.z()=sizez;
}

void GeometricObject::Rotate(const Math::Vector3D<float>& d,Math::Vector3D<float>* limup,Math::Vector3D<float>* limdown)
{
    GeometricObject::Rotate(d.x(),d.y(),d.z(),limup,limdown);
}

void GeometricObject::Scale(const Math::Vector3D<float> & d)
{
    GeometricObject::Scale(d[0],d[1],d[2]);
}

void GeometricObject::Move(const Math::Vector3D<float> & d)
{
    GeometricObject::Move(d[0],d[1],d[2]);
}

void GeometricObject::Rotate(float x,float y,float z,Math::Vector3D<float>* limup,Math::Vector3D<float>* limdown)
{
        if(limup)
        {
                if(angle.x()+x>=limup->x()) {angle.x()=limup->x();x=0;}
                if(angle.y()+y>=limup->y()) {angle.y()=limup->y();y=0;}
                if(angle.z()+z>=limup->z()) {angle.z()=limup->z();z=0;}
        }
        if(limdown)
        {
                if(angle.x()+x<=limdown->x()) {angle.x()=limdown->x();x=0;}
                if(angle.y()+y<=limdown->y()) {angle.y()=limdown->y();y=0;}
                if(angle.z()+z<=limdown->z()) {angle.z()=limdown->z();z=0;}
        }
        angle.x()+=x;
        angle.y()+=y;
        angle.z()+=z;
}

void GeometricObject::Scale(float x,float y,float z){size.x()+=x;size.y()+=y;size.z()+=z;}

void GeometricObject::Move(float x,float y,float z)
{
        if(own_axis)
        {
            position.x()+=(x*cos(-angle.y())+z*sin(-angle.y()));
            position.y()+=y;
            position.z()+=(x*sin(angle.y())+z*cos(angle.y()));
        }
        else
        {
            position.x()+=x;
            position.y()+=y;
            position.z()+=z;
        }
}

void GeometricObject::SetAngle(float x,float y,float z,bool isx,bool isy,bool isz)
{
        if(isx) this->angle.x()=x;
        if(isy) this->angle.y()=y;
        if(isz) this->angle.z()=z;
}

void GeometricObject::SetPosition(float x,float y,float z,bool isx,bool isy,bool isz)
{
        if(isx) this->position.x()=x;
        if(isy) this->position.y()=y;
        if(isz) this->position.z()=z;
}

void GeometricObject::SetSize(float x,float y,float z,bool isx,bool isy,bool isz)
{
        if(isx) this->size.x()=x;
        if(isy) this->size.y()=y;
        if(isz) this->size.z()=z;
}

Math::Vector3D<float> & GeometricObject::Angle()
{
        return angle;
}

Math::Vector3D<float> & GeometricObject::Size()
{
        return size;
}

Math::Vector3D<float> & GeometricObject::Position()
{
        return position;
}

const Math::Vector3D<float> & GeometricObject::Position() const
{
    return position;
}

const Math::Vector3D<float> & GeometricObject::Angle() const
{
    return angle;
}

const Math::Vector3D<float> & GeometricObject::Size() const
{
    return size;
}


Math::Matrix4x4<float> GeometricObject::GetMatrix() const
{
        Math::Matrix4x4<float> helper_matrix=Math::Matrix4x4<float>::YawPitchRoll(angle.y(),angle.x(),angle.z())*
                        Math::Matrix4x4<float>::Scale(size)*
                        Math::Matrix4x4<float>::Translation(position);
        return helper_matrix;
}
//____________________________________________________________
void Camera::SetAt(float atx,float aty,float atz)
{
    At().x()=atx;At().y()=aty;At().z()=atz;
}

void Camera::SetUp(float upx,float upy,float upz)
{
    Up().x()=upx;Up().y()=upy;Up().z()=upz;
}

void Camera::SetDist(float dist)
{
    this->dist=dist;
}

void Camera::SetAngle(float x,float y,float z)
{
    GeometricObject::SetAngle(x,y,z);
}

Camera::Camera()
{
    own_axis=false;
    SetAt(0,0,0);
    SetUp(0,1,0);
    SetDist(100);
}

Camera::Camera(const Math::Vector3D<float>& at,const Math::Vector3D<float>& up,float dist)
{
    own_axis=false;
    At()=at;Up()=up;this->dist=dist;
}

void Camera::Move(float d)
{
   dist+=d;
}

Math::Vector3D<float> & Camera::Angle()
{
    return GeometricObject::Angle();
}

Math::Vector3D<float> & Camera::At()
{
    return GeometricObject::Position();
}

Math::Vector3D<float> & Camera::Up()
{
    return GeometricObject::Size();
}

float & Camera::Dist()
{
    return dist;
}

const Math::Vector3D<float> & Camera::Angle() const
{
    return GeometricObject::Angle();
}

const Math::Vector3D<float>& Camera::At() const
{
    return GeometricObject::Position();
}

const Math::Vector3D<float>& Camera::Up() const
{
    return GeometricObject::Size();
}

float Camera::Dist() const
{
    return dist;
}


void Camera::ComputeEye()
{

    Math::Matrix4x4<float> p_mat;
    helper_vector.x()=0.0f;
    helper_vector.y()=0.0f;
    helper_vector.z()=dist;
    p_mat=(p_mat*
          Math::Matrix4x4<float>::Translation(helper_vector)*
          Math::Matrix4x4<float>::YawPitchRoll(angle.y(),angle.x(),angle.z()));

    helper_vector.x()=At().x()+p_mat(3,0);
    helper_vector.y()=At().y()+p_mat(3,1);
    helper_vector.z()=At().z()+p_mat(3,2);
}


Math::Matrix4x4<float> Camera::GetMatrix()
{
                ComputeEye();
                return Math::Matrix4x4<float>::LookAtView(helper_vector,At(),Up());
}

void Camera::Rotate(float x,float y,float z,Math::Vector3D<float>* limup,Math::Vector3D<float>* limdown)
{
    GeometricObject::Rotate(x,y,z,limup,limdown);
}

//____________________________________________________________-
VideoMode::VideoMode(int width,int height,bool doublebuffer,bool fullscreen,int bpp)
{
    _width=width;_height=height;_fullscreen=fullscreen;_doublebuffer=doublebuffer;_bpp=bpp;
}
int & VideoMode::width()
{
    return _width;
}

int & VideoMode::height()
{
    return _height;
}

int & VideoMode::bpp()
{
    return _bpp;
}

bool & VideoMode::fullscreen()
{
    return _fullscreen;
}

bool & VideoMode::doublebuffer()
{
    return _doublebuffer;
}

int VideoMode::width() const
{
    return _width;
}

int VideoMode::height() const
{
    return _height;
}

int VideoMode::bpp() const
{
    return _bpp;
}

bool VideoMode::fullscreen() const
{
    return _fullscreen;
}

bool VideoMode::doublebuffer() const
{
    return _doublebuffer;
}

//_______________________________________________________________________


UidGenerator::UidGenerator(const Math::Range<char>& primary_alphabet)
{
    this->SetAlphabet(primary_alphabet);
}

int UidGenerator::GetContainingAlphabet(char alpha)
{
    int size=alphabet.size();
    for(int a=0;a<size;a++)
    {
        if(alphabet[a].contains(alpha)) return a;
    }
    return -1;
}

const std::string & UidGenerator::GenerateNext()
{
 int end=last_generated.length();
 int begin=0;
 int alphabet_id=0;
 int prev_alphabet_id=0;
 int alpha_size=alphabet.size()-1;
 for(int i=end-1;i>=begin;i--)
 {
     alphabet_id=GetContainingAlphabet(last_generated[i]+1);
     prev_alphabet_id=GetContainingAlphabet(last_generated[i]);

     if(prev_alphabet_id==alpha_size&&alphabet_id<0)
     {
         last_generated[i]=alphabet[0].left();
         if(i==0)
         {
             last_generated=last_generated+alphabet[0].left();
             break;
         }
     }
     else if(alphabet_id<0)
     {
         last_generated[i]=alphabet[prev_alphabet_id+1].left();
         break;
     }
     else
     {
         last_generated[i]=last_generated[i]+1;
         break;
     }
 } 
 return last_generated;
}

void UidGenerator::ExtendAlphabet(const Math::Range<char>& additional_alphabet)
{
    alphabet.push_back(additional_alphabet);
    this->Reload();
}


void UidGenerator::SetAlphabet(const Math::Range<char> & primary_alphabet)
{
    alphabet.resize(1,primary_alphabet);
    this->Reload();
}

void UidGenerator::Reload(const std::string & first)
{
    if(alphabet.size()&&(!first.length()))
    {
        last_generated=alphabet[0].left();
        return;
    }
    last_generated=first;

}
//________________________________________________________________________________
IOStream::IOStream(const char * filename, std::ios_base::openmode mode):std::fstream(filename,mode)
{

}

IOStream::~IOStream()
{
}



}}


//__________________________________________________________________________________
std::ostream & operator<<(std::ostream& out,const Kongomato::Base::VideoMode& videomode)
{
    return out<<"videomode( width="<<videomode.width()<<" height="<<videomode.height()<<
            " bpp="<<videomode.bpp()<<" fullscreen="<<videomode.fullscreen()<<
            " doublebuffer="<<videomode.doublebuffer()<<" )";
}



