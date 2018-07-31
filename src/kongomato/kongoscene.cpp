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

#include "kongoscene.h"
namespace Kongomato { namespace Scene {
//____________________________________________________________

Node::Node(const node_type & type)
{
    this->type=type;
    this->visible=true;this->name="";
    this->parent=NULL;
}

void Node::SetParent(Scene::Node* parent)
{
    this->parent=parent;
    parent->children.push_back(this);
}

void Node::PushChild(Scene::Node* child)
{
    child->SetParent(this);
}

Node::~Node()
{    
}

void Node::SetName(const std::string & str)
{
    this->name=str;
}

const std::string & Node::GetName() const
{
    return name;
}

void Node::SetVisiblity(bool visible)
{
    this->visible=visible;
}

bool Node::IsPointIn(const Math::Vector3D<float> & p) const
{
    return false;
}

bool Node::IsVisible() const
{
    return visible;
}

void Node::Hide()
{
    this->visible=false;
}

void Node::Show()
{
    this->visible=true;
}

void Node::Draw()
{
    if(!this->visible) return;
    Math::Matrix4x4<float> matrix;
    VideoDevice::Manager* device_manager=VideoDevice::Manager::Instance();
    device_manager->GetTransform(VideoDevice::world_transformation,matrix);
    device_manager->AddTransform(VideoDevice::world_transformation,this->GetMatrix());
    device_manager->ApplyTransformations();
    this->PrivateDraw();
    int size=children.size();
    for(int a=0;a<size;a++) children[a]->Draw();
    device_manager->SetTransform(VideoDevice::world_transformation,matrix);
}
//____________________________________________________________
CommonMesh::CommonMesh()
{    
    SetDrawFlags();
}

mesh_draw_flags CommonMesh::GetDrawFlags()
{
    return draw_flags;
}

void CommonMesh::SetDrawFlags(mesh_draw_flags a)
{
    draw_flags=a;
}

void CommonMesh::PrivateDraw()
{
        glPushAttrib(GL_ENABLE_BIT|GL_POLYGON_BIT);
        if((draw_flags&mesh_draw_solid)==mesh_draw_solid) root->Draw();
        glDisable(GL_LIGHTING);
        glDisable(GL_TEXTURE_2D);
        if((draw_flags&mesh_draw_wireframe)==mesh_draw_wireframe)
        {
            glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
            root->Draw();
        }
        if((draw_flags&mesh_draw_points)==mesh_draw_points)
        {
            glPointSize(3);
            glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
            glDisable(GL_LIGHTING);
            root->Draw();
        }
        glPopAttrib();
}

bool CommonMesh::IsPointIn(const Math::Vector3D<float> & p) const
{
    const std::vector<Base::AbstractSubMesh*> & children=root->GetChildren();
    int size=children.size();

    for(int a=0;a<size;a++) if(children[a]->IsPointIn(p)) return true;
    return false;
}

bool CommonMesh::ScreenPointToSurfacePoint(const Math::Vector2D<float> & inp,Math::Vector3D<float> & outp1,const Math::Matrix4x4<float> & matrix,VideoDevice::Context* context)
{
    Kongomato::VideoDevice::Manager* device=Kongomato::VideoDevice::Manager::Instance();
    if(!context) context=device->GetCurrentContext();
    if(!context) return false;
    return root->ScreenPointToSurfacePoint(inp,outp1,matrix,context);
}

VideoDevice::SubMesh* CommonMesh::GetSubMesh(int submesh_id)
{
    int count=this->root->GetChildren().size();
    if(submesh_id>=count) throw Base::Exception("VideoDevice::SubMesh* CommonMesh::GetSubMesh(int submesh_id)");
    return (VideoDevice::SubMesh*)this->root->GetChildren()[submesh_id];
}

VideoDevice::SubMesh* CommonMesh::AddSubMesh()
{
    return ((VideoDevice::SubMesh*)root->NewChild());
}

int CommonMesh::GetSubMeshesCount()
{
    return root->GetChildren().size();
}

//_____________________________________________________________
SimpleMesh::SimpleMesh(const std::string & src_filename):Node(simple_mesh_node)
{
    VideoDevice::Manager* device_manager=VideoDevice::Manager::Instance();
    root=new VideoDevice::SubMesh(std::string(""),false);
   if(!root->GetChildren().size()) submesh=root->NewChild();
   else  submesh=root->GetChildren()[0];
    if(!src_filename.empty())
        FileFormat::Xfm3::Load(src_filename,submesh,true);
    else
    {
     //   switch(initial_figure)
        {
    //        case SphereMeshInitialFigure:
            //
   //         break;
        }
    }
}

SimpleMesh::~SimpleMesh()
{
    delete root;
}

Base::VerticesContainer * SimpleMesh::GetVertices()
{
    return submesh->GetVertices();
}

Base::IndicesContainer * SimpleMesh::GetIndices()
{
    return submesh->GetIndices();
}

void SimpleMesh::LockBuffers(bool lock)
{
    submesh->LockBuffers(lock);
}

const Math::Vector3D<float> & SimpleMesh::GetBoundingBoxMax()
{
    dynamic_cast<VideoDevice::SubMesh*>(submesh)->ComputeBoundingBox();
    return submesh->GetBoundingBoxMax();
}

const Math::Vector3D<float> & SimpleMesh::GetBoundingBoxMin()
{
    dynamic_cast<VideoDevice::SubMesh*>(submesh)->ComputeBoundingBox();
    return submesh->GetBoundingBoxMin();
}

void SimpleMesh::InitializeTexture(const std::string & tx_src_filename)
{    
    submesh->InitializeTexture(tx_src_filename);
}

void SimpleMesh::SetTexture(std::string & tx_src_filename)
{
    dynamic_cast<VideoDevice::SubMesh*>(submesh)->InitializeTexture(tx_src_filename);
}

void SimpleMesh::SetTexture(int w,int h)
{    
    dynamic_cast<VideoDevice::SubMesh*>(submesh)->InitializeTexture("",w,h);
}

VideoDevice::Texture* SimpleMesh::GetTexture()
{
    return dynamic_cast<VideoDevice::SubMesh*>(submesh)->GetTexture();
}

void SimpleMesh::PrivateDraw()
{    
    CommonMesh::PrivateDraw();
}

//____________________________________________________________
ColoredLine::ColoredLine(const Math::Vector3D<float>& p1,const Math::Vector3D<float>& p2,const Base::Color<float> & color)
{
    this->color=color;this->p1=p1;this->p2=p2;
}

Math::Vector3D<float> & ColoredLine::GetP1()
{
    return p1;
}

Math::Vector3D<float> & ColoredLine::GetP2()
{
    return p2;
}

Base::Color<float> & ColoredLine::GetColor()
{
    return color;
}
//_____________________________________________________________
ColoredLinesGroup::ColoredLinesGroup():Node(colored_line_node)
{
    this->width=1.0f;
}

void ColoredLinesGroup::AddLine(const ColoredLine & line)
{
    lines.push_back(line);
}

void ColoredLinesGroup::SetLine(int i,const ColoredLine & line)
{
    lines[i]=line;
}

void ColoredLinesGroup::SetNormal(const Math::Vector3D<float>& n)
{
    this->normal=n;
}

void ColoredLinesGroup::SetWidth(float width)
{
    this->width=width;
}

void ColoredLinesGroup::Clear()
{
    lines.clear();
}

void ColoredLinesGroup::PrivateDraw()
{
    int size=lines.size();
    VideoDevice::Manager* device_manager=VideoDevice::Manager::Instance();
    bool color_material=device_manager->GetBoolParameter(VideoDevice::color_material_parameter);
    bool lighting=device_manager->GetBoolParameter(VideoDevice::lighting_parameter);

    if(!color_material) device_manager->SetBoolParameter(VideoDevice::color_material_parameter,true);
    if(lighting) device_manager->SetBoolParameter(VideoDevice::lighting_parameter,false);
    GLfloat last_width;
    glGetFloatv(GL_LINE_WIDTH,&last_width);
    glLineWidth(this->width);
    glBegin(GL_LINES);    
    for(int a=0;a<size;a++)
    {
        glColor4fv((const GLfloat*)(&lines[a].GetColor()));
        glNormal3fv((const GLfloat*)(normal.data()));
        glVertex3fv((const GLfloat*)(&(lines[a].GetP1()[0])));
        glColor4fv((const GLfloat*)(&lines[a].GetColor()));
        glNormal3fv((const GLfloat*)(normal.data()));
        glVertex3fv((const GLfloat*)(&(lines[a].GetP2()[0])));
    }
    glEnd();    
    glLineWidth(last_width);
    glColor4f(1,1,1,1);    
    if(!color_material) device_manager->SetBoolParameter(VideoDevice::color_material_parameter,false);
    if(lighting) device_manager->SetBoolParameter(VideoDevice::lighting_parameter,true);
}
//_____________________________________________________________
Mesh::Mesh(const std::string & src_filename):Node(mesh_node)
{
    VideoDevice::Manager* device_manager=VideoDevice::Manager::Instance();    
    root=new VideoDevice::SubMesh(src_filename,false);
    root->NewChild();

}

Mesh::~Mesh()
{
        delete root;
}

void Mesh::PrivateDraw()
{
   CommonMesh::PrivateDraw();
}
//_____________________________________________________


int Light::GetLightFlag(int id)
{
        if(id==0) return GL_LIGHT0;
        if(id==1) return GL_LIGHT1;
        if(id==2) return GL_LIGHT2;
        if(id==3) return GL_LIGHT3;
        if(id==4) return GL_LIGHT4;
        if(id==5) return GL_LIGHT5;
        if(id==6) return GL_LIGHT6;
        if(id==7) return GL_LIGHT7;
        return GL_MAX_LIGHTS-1;
}
Light::Light()        
{
    index=0;
}

Light::~Light()
{
    this->Enable(false);
}

void Light::SetLightIndex(int index)
{
    this->index=index;
}



void Light::SetAmbient(const Base::Color<float> & color)
{
    ambient=color;
    glLightfv(GetLightFlag(index),GL_AMBIENT,(GLfloat*)&color);
}

void Light::SetDiffuse(const Base::Color<float> & color)
{
    diffuse=color;
    glLightfv(GetLightFlag(index),GL_DIFFUSE,(GLfloat*)&color);
}

void Light::SetSpecular(const Base::Color<float> & color)
{
    specular=color;
    glLightfv(GetLightFlag(index),GL_SPECULAR,(GLfloat*)&color);
}

void Light::SetSpot(const Math::Vector3D<float>& pos,const Math::Vector3D<float> & dir,float expon,float cutoff)
{
    Math::Vector4D<float> real_pos(pos.x(),pos.y(),pos.z(),1);
    this->position=real_pos;
    this->direction=dir;
    this->exponent=expon;
    this->cutoff=cutoff;
    glLightfv(GetLightFlag(index),GL_POSITION,&real_pos(0));
    glLightfv(GetLightFlag(index),GL_SPOT_DIRECTION,&dir(0));
    glLightfv(GetLightFlag(index),GL_SPOT_EXPONENT,&expon);
    glLightfv(GetLightFlag(index),GL_SPOT_CUTOFF,&cutoff);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Light::SetDirectional(const Math::Vector3D<float> & dir)
{
    Math::Vector4D<float> real_pos(dir.x(),dir.y(),dir.z(),0);
    this->position=real_pos;
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glLightfv(GetLightFlag(index),GL_POSITION,&real_pos(0));
}

void Light::SetAttenuations(float cons,float lin,float quad)
{
    constant_attenuation=cons;linear_attenuation=lin;quadratic_attenuation=quad;
    glLightfv(GetLightFlag(index),GL_CONSTANT_ATTENUATION,&cons);
    glLightfv(GetLightFlag(index),GL_LINEAR_ATTENUATION,&lin);
    glLightfv(GetLightFlag(index),GL_LINEAR_ATTENUATION,&quad);
}

void Light::Enable(bool enable)
{
        if(enable) glEnable(GetLightFlag(index));
        else glDisable(GetLightFlag(index));
}

void Light::Synchronize()
{
    glLightfv(GetLightFlag(index),GL_AMBIENT,(GLfloat*)&ambient);
    glLightfv(GetLightFlag(index),GL_DIFFUSE,(GLfloat*)&diffuse);
    glLightfv(GetLightFlag(index),GL_SPECULAR,(GLfloat*)&specular);
    glLightfv(GetLightFlag(index),GL_POSITION,&position(0));
    glLightfv(GetLightFlag(index),GL_SPOT_DIRECTION,&direction(0));
    glLightfv(GetLightFlag(index),GL_SPOT_CUTOFF,&cutoff);
    glLightfv(GetLightFlag(index),GL_SPOT_EXPONENT,&exponent);
    glLightfv(GetLightFlag(index),GL_CONSTANT_ATTENUATION,&constant_attenuation);
    glLightfv(GetLightFlag(index),GL_LINEAR_ATTENUATION,&linear_attenuation);
    glLightfv(GetLightFlag(index),GL_LINEAR_ATTENUATION,&quadratic_attenuation);
}
//_____________________________________________________
Manager::Manager(const std::string & n)
{    
    camera_target=NULL;      
    camera.SetAt(0,0,0);
    camera.SetUp(0,1,0);
    camera.SetDist(100);
    camera.SetAngle(-M_PI/4.0f+0.2f,0,0);    
    InitLights();    
    //landscape=NULL;    
}

const std::string & Manager::GetName()
{
    return this->name;
}

void Manager::InitLights() //temp
{
    if(GL_MAX_LIGHTS>0)
    {
        for(int a=0;a<8;a++)
        {
            lights[a].SetLightIndex(a);
            lights[a].Enable(a==0);
        }

        lights[0].SetDirectional(Math::Vector3D<float>(0,0,1));
        lights[0].SetDiffuse(Base::Color<float>(1,1,1,0));
    }

}

Light & Manager::GetLight(int index)
{
        if(index>=GL_MAX_LIGHTS) throw Base::Exception("SceneManager::GetLight(int index)");
        return lights[index];
}

void Manager::Draw()
{    
    VideoDevice::Manager* device_manager=VideoDevice::Manager::Instance();
    device_manager->SetClearColor(back_color.r,back_color.g,back_color.b,back_color.a);
   device_manager->Clear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    if(camera_target)
    {       
       camera.At()=camera_target->Position();
       camera.Angle().y()=camera_target->Angle().y();
    }
    device_manager->SetTransform(VideoDevice::view_transformation,camera.GetMatrix());
    int size=objects.size();
   for(int a=0 ; a <size; a++) if(!objects[a]->parent) objects[a]->Draw();

/*
   device_manager->Clear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   TwoDimensional::PrimitivesPlotter::BeginDraw(GL_LINES);
   glVertex2f(-1.0f,-1.0f);
   glVertex2f(1.0f,1.0f);
   TwoDimensional::PrimitivesPlotter::EndDraw();*/




 /* if(landscape)
   {
       Device::Instance()->SetBoolAttribute(GL_LIGHTING,false);
       landscape->Draw();
       Device::Instance()->SetBoolAttribute(GL_LIGHTING,true);
   }*/

   device_manager->Present();

}

Base::Camera& Manager::GetCamera()
{
    return camera;
}

void Manager::SetCameraTaget(Scene::Node* t)
{   
   camera_target=t;   
}

Scene::Node* Manager::GetCameraTarget()
{
    return camera_target;
}

Node* Manager::GetFirstByName(const std::string & name)
{
    int size=objects.size();
    for(int a=0;a<size;a++)
        if(name==objects[a]->GetName()) return objects[a];
    return NULL;
    //throw Base::Exception("Node* Manager::GetFirstByName(const std::string & name): not found");
}

std::vector<Scene::Node*> & Manager::GetNodesList()
{
    return this->objects;
}

SimpleMesh* Manager::AddSimpleMesh(const std::string & src_filename)
{    
    SimpleMesh* sm=new SimpleMesh(src_filename);
    objects.push_back(sm);
    return sm;
}

Mesh* Manager::AddMesh(const std::string & src_filename)
{
    Mesh* m=new Mesh(src_filename);
    objects.push_back(m);
    return m;
}

ColoredLinesGroup* Manager::AddColoredLinesGroup()
{
    ColoredLinesGroup* clg=new ColoredLinesGroup;
    objects.push_back(clg);
    return clg;
}

void Manager::RemoveNode(Node* node)
{
    int size=0;
    for(int a=0;a<size;a++)
        if(node==objects[a])
        {
            objects.erase(objects.begin()+a);
            a--;
        }
    delete node;
}

void Manager::SetBackgroundColor(const Kongomato::Base::Color<double> & color)
{
    this->back_color=color;
}

} }
