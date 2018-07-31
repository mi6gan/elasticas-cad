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

#ifndef KONGOSCENE_H
#define KONGOSCENE_H
#include "kongovideodevice.h"
#include "kongofileformat.h"
#include "kongosprite.h"
#include <map>
#include <list>

namespace Kongomato { namespace Scene {
enum node_type
{
    abstract_node=0x0,
    simple_mesh_node=0x1,
    mesh_node=0x2,
    colored_line_node=0x3
};

enum mesh_draw_flags
{
    mesh_draw_none=0x0,
    mesh_draw_solid=0x1,
    mesh_draw_wireframe=0x2,
    mesh_draw_points=0x4
};

enum MeshInitialFigure { MeshInitialFigure,SphereMeshInitialFigure };



inline mesh_draw_flags operator|(const mesh_draw_flags a,const mesh_draw_flags b)
{
    return mesh_draw_flags(int(a)|int(b));
}

inline void operator|=(mesh_draw_flags & a,const mesh_draw_flags & b)
{
    a=mesh_draw_flags(int(a)|int(b));
}


inline mesh_draw_flags operator~(const mesh_draw_flags & a)
{
    return mesh_draw_flags(~int(a));
}

inline mesh_draw_flags operator&(const mesh_draw_flags a,const mesh_draw_flags b)
{
    return mesh_draw_flags(int(a)&int(b));
}


inline void operator&=(mesh_draw_flags & a,const mesh_draw_flags & b)
{
    a=mesh_draw_flags(int(a)&int(b));
}

inline mesh_draw_flags operator^(const mesh_draw_flags & a,const mesh_draw_flags & b)
{
    return mesh_draw_flags(int(a)^int(b));
}

inline void operator^=(mesh_draw_flags & a,const mesh_draw_flags & b)
{
    a=mesh_draw_flags(int(a)^int(b));
}

class Manager;

class DLL_DECLSPEC  Node: public Base::GeometricObject
{
    friend class Manager;
    std::string name;
    node_type type;
   protected:
    std::vector<Scene::Node*> children;
    Scene::Node* parent;
    bool visible;    
    virtual void PrivateDraw()=0;
    virtual ~Node();
    Node(const node_type & type=abstract_node);
    void PushChild(Scene::Node* child);
   public:
    void SetParent(Scene::Node* parent);
    void SetName(const std::string & str);
    const std::string & GetName() const;
    virtual void SetVisiblity(bool visible=true);
    virtual bool IsPointIn(const Math::Vector3D<float> & p) const;
    bool IsVisible() const;
    void Hide();
    void Show();
    void Draw();    
};




class DLL_DECLSPEC CommonMesh
{
    friend class Manager;
   protected:
    VideoDevice::SubMesh * root;
    mesh_draw_flags draw_flags;
    virtual void PrivateDraw();
    CommonMesh();
   public:
    void SetDrawFlags(mesh_draw_flags a=mesh_draw_solid);
    mesh_draw_flags GetDrawFlags();
    virtual bool IsPointIn(const Math::Vector3D<float> & p) const;
    bool ScreenPointToSurfacePoint(const Math::Vector2D<float> & inp,Math::Vector3D<float> & outp1,const Math::Matrix4x4<float> & matrix,VideoDevice::Context* context=NULL);
    VideoDevice::SubMesh* GetSubMesh(int submesh_id);
    VideoDevice::SubMesh* AddSubMesh();
    int GetSubMeshesCount();
};
//_____________________________________________________________

class DLL_DECLSPEC SimpleMesh:public CommonMesh,public Node
{
    friend class Manager;
    SimpleMesh(const std::string & src_filename="");
    ~SimpleMesh();
    Base::AbstractSubMesh* submesh;
   public:    
    Base::VerticesContainer * GetVertices();
    Base::IndicesContainer * GetIndices();
    void LockBuffers(bool lock);
    void InitializeTexture(const std::string & tx_src_filename);
    void SetTexture(std::string & tx_src_filename);
    void SetTexture(int w,int h);    
    const Math::Vector3D<float> & GetBoundingBoxMin();
    const Math::Vector3D<float> & GetBoundingBoxMax();
    VideoDevice::Texture* GetTexture();
    void PrivateDraw();
};

class DLL_DECLSPEC Mesh:public CommonMesh,public Node
{
    friend class Manager;
    Mesh(const std::string & src_filename="");
   virtual ~Mesh();
   public:
    void PrivateDraw();
};


class DLL_DECLSPEC ColoredLine
{
     Base::Color<float> color;
     Math::Vector3D<float> p1;
     Math::Vector3D<float> p2;
    public:
     ColoredLine(const Math::Vector3D<float>& p1,const Math::Vector3D<float>& p2,const Base::Color<float> & color=Base::Color<float>());
     Math::Vector3D<float> & GetP1();
     Math::Vector3D<float> & GetP2();
     Base::Color<float> & GetColor();
};

class DLL_DECLSPEC ColoredLinesGroup:public Node
{
    friend class Manager;
    float width;
    std::vector<ColoredLine> lines;
    Math::Vector3D<float> normal;
    ColoredLinesGroup();
   public:
    void AddLine(const ColoredLine & line);    
    void SetLine(int i,const ColoredLine & line);
    void SetNormal(const Math::Vector3D<float>& n);
    void SetWidth(float width);
    void Clear();
    void PrivateDraw();
};





class DLL_DECLSPEC Light
{
        friend class Manager;
        float exponent,cutoff,constant_attenuation,linear_attenuation,quadratic_attenuation;
        Base::Color<float> ambient,diffuse,specular;
        Math::Vector4D<float> position;
        Math::Vector3D<float> direction;
        int index;
        static int GetLightFlag(int id);
        Light();
        ~Light();
        void SetLightIndex(int index=0);
       public:
        void SetAmbient(const Base::Color<float> & color=Base::Color<float>(0,0,0,1));
        void SetDiffuse(const Base::Color<float> & color=Base::Color<float>(0,0,0,1));
        void SetSpecular(const Base::Color<float> & color=Base::Color<float>(0,0,0,1));
        void SetSpot(const Math::Vector3D<float> & pos=Math::Vector3D<float>(0,0,1),
                     const Math::Vector3D<float> & dir=Math::Vector3D<float>(0,0,-1),
                     float expon=0,
                     float cutoff=180
                     );
        void SetDirectional(const Math::Vector3D<float> & dir=Math::Vector3D<float>(0,0,1));
        void SetAttenuations(float cons=1,float lin=0,float quad=0);
        void Enable(bool enable=true);
        void Synchronize();

};

class DLL_DECLSPEC Manager
{
    friend class Node;
    std::string name;
    Base::Camera camera;
    Node* camera_target;
    std::vector<Node*>  objects;
    Light lights[GL_MAX_LIGHTS];
    Kongomato::Base::Color<double> back_color;
    //Land* landscape;    
 public:
    const std::string & GetName();
    void InitLights(); //temp
    Manager(const std::string & name);
    Base::Camera & GetCamera();
    void SetCameraTaget(Scene::Node* m);
    Scene::Node* GetCameraTarget();
    Node* GetFirstByName(const std::string & name);
    void Draw();
    int GetMaxLights();
    Light & GetLight(int index=0);
    std::vector<Scene::Node*> & GetNodesList();
    SimpleMesh* AddSimpleMesh(const std::string & src_filename);
    Mesh* AddMesh(const std::string & src_filename);
    ColoredLinesGroup* AddColoredLinesGroup();
    void RemoveNode(Node* node);
    void SetBackgroundColor(const Kongomato::Base::Color<double> & color);


    //void SetLandscape(Land* landscape);

};

} }

#endif // KONGOSCENEMANAGER_H
