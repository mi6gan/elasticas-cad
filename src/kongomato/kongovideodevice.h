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

#ifndef KONGODEVICE_H
#define KONGODEVICE_H
#define GL_GLEXT_PROTOTYPES

#ifdef WITH_SDL
    #include <SDL/SDL.h>
    #include <SDL/SDL_image.h>
#endif
#include <memory.h>
#ifdef WITH_QT4
#include <QtCore/QtCore>
#include <QtGui/QWidget>
#endif
#include "3rd_party/GLee/GLee.h"
#ifdef WITH_QT4
#include <QtOpenGL/QGLWidget>
#include <QtGui/QImage>
#endif

#ifdef  SUPPORT_3DS
#include <lib3ds.h>
//#include <lib3ds/mesh.h>
#endif

#include "kongobase.h"
#include <fstream>
#include <list>
#include <map>
#include <cstdio>
#include <sys/stat.h>
#include<sstream>

namespace Kongomato { namespace VideoDevice{
enum resource_type
{
    empty_resource=0,
    texture_resource=1,
    vertexbuffer_resource=2,
    indexbuffer_resource=3,    
    shader_resource=4,
    font_resource=5,
    submesh_resource=6,
    framebuffer_resource=7
};

enum context_type
{    
    Null_Context=0,
    SDL_Context=1,
    Qt4_Context=2,
    Last_Context=3
};

/*enum resource_content_type
{
    static_resource_content=0,
    dynamic_resource_content=1
};*/

enum bool_parameter
{
   alpha_test_parameter=GL_ALPHA_TEST,
   auto_normal_parameter=GL_AUTO_NORMAL,
   lighting_parameter=GL_LIGHTING,
   cullface_parameter=GL_CULL_FACE,
   color_material_parameter=GL_COLOR_MATERIAL
};

enum uint_parameter
{
   depthfunc_parameter=1,
   clearcolor_parameter=2
};

enum float_parameter
{
   cleardepth_parameter=3
};

enum transformation_type
{
    world_transformation=0,
    view_transformation=1,
    projection_transformation=2,
    world2d_transformation=3
};

enum texture_draw_flags
{
    texture_draw_mirror=0x2,
    texture_draw_flip=0x4,
    texture_draw_none=0x8,
    texture_draw_fill=0x10,
    texture_draw_nopotabstraction=0x20,
};

inline texture_draw_flags operator|(texture_draw_flags a,texture_draw_flags b)
{
    return texture_draw_flags(int(a)|int(b));
}

enum shader_type
{
    vertex_shader=GL_VERTEX_SHADER,
    fragment_shader=GL_FRAGMENT_SHADER
};

enum acceleration_capability_flags
{
    no_acceleration=0x0,
    vertexbuffer_acceleration=0x2,
    framebuffer_acceleration=0x4
};

inline acceleration_capability_flags operator^(acceleration_capability_flags a,acceleration_capability_flags b)
{
    return acceleration_capability_flags(int(a)^int(b));
}

inline acceleration_capability_flags operator|(acceleration_capability_flags a,acceleration_capability_flags b)
{
    return acceleration_capability_flags(int(a)|int(b));
}

inline int next_p2 (int a )
{
  int rval=1;
  while(rval<a) rval<<=1;
  return rval;
}

class Manager;

class DLL_DECLSPEC ResourceFileStream: public Base::IOStream
{
    ResourceFileStream( const char * filename, std::ios_base::openmode mode = std::ios_base::in | std::ios_base::out );
};
//_____________________________________________________________________________________
class DLL_DECLSPEC Resource
{
    friend class VideoDevice::Manager;    
    protected:
        int ref_count;
        std::string resource_name;
        std::string meta_info;
        resource_type type;
    public:        
        Resource(const resource_type & type=empty_resource,const std::string & resource_name="");
        ~Resource();
        const std::string & GetMetaInfo();
        resource_type & GetType();
};

class DLL_DECLSPEC DrawTarget
{    
    friend class Manager;    
   protected:
     Math::Size<int> size;
     virtual void MakeNotCurrent();
     virtual void MakeCurrent();
   public:     
       virtual void Present();
       const Math::Size<int> & GetSize();
};


class Texture;
class DLL_DECLSPEC FrameBuffer:public Resource
{
        friend class Context;
        GLuint gl_id;
        static bool is_EXT;
    public:
        FrameBuffer();
        ~FrameBuffer();
        void Bind();
        void BindTexture(VideoDevice::Texture* texture);
        void Unbind();
};

class DLL_DECLSPEC FrontBuffer: public DrawTarget
{
    friend class Manager;
     virtual void MakeNotCurrent();
     virtual void MakeCurrent();
     virtual void Present();
    public:
     void Update();
};

class DLL_DECLSPEC TextureException: public Base::Exception
{    
};

class Context;
class DLL_DECLSPEC Texture:public DrawTarget,public Resource
{   
        friend class FrameBuffer;
        FrameBuffer* frame_buffer;
        std::vector<Context*> contexts;        
        int last_viewport[4];        
        GLuint gl_id;
        static bool flip_reverse;
        virtual void MakeNotCurrent();
        virtual void MakeCurrent();
        virtual void Present();
        void Initialize(char* image,int width,int height,int px_size,GLuint format);
    protected:
        int real_width,real_height;
        int width,height;
        unsigned int format;        
        void PrivateDraw(const Math::Rectangle<int> & dest=Math::Rectangle<int>(0,0,0,0),const Math::Rectangle<int> & src=Math::Rectangle<int>(0,0,0,0),VideoDevice::texture_draw_flags effect=VideoDevice::texture_draw_none,bool texture_size=false);
        Texture(char* image,int width,int height,int px_size,GLuint format);
    public:
        Texture(const std::string & filename,int width=0,int height=0,Base::Color<float> fill_color=Base::Color<float>());
         ~Texture();
         void Draw(const Math::Rectangle<int> & dest=Math::Rectangle<int>(0,0,0,0),const Math::Rectangle<int> & src=Math::Rectangle<int>(0,0,0,0),VideoDevice::texture_draw_flags effect=VideoDevice::texture_draw_none);
        void Draw(VideoDevice::texture_draw_flags effect);        
        int Width() const;
        int Height() const;
        void Bind(bool filters=true);
        void Unbind();
        //void ConvertToPOT();
};



class DLL_DECLSPEC ElementBuffer
{
    friend class VertexBuffer;
    friend class IndexBuffer;
    GLuint gl_id;
    ElementBuffer(const GLvoid* data,GLsizeiptr size_in_bytes,GLenum target=GL_ARRAY_BUFFER,GLenum usage=GL_STATIC_DRAW);
    ~ElementBuffer();
};

class DLL_DECLSPEC VertexBufferException: public Base::Exception
{
};

class DLL_DECLSPEC VertexBuffer:public Base::VerticesContainer,public Resource
{
        GLuint actual_size;
        friend class SubMesh;
        std::vector<ElementBuffer*> buffers;
        static GLenum VertexAttributeTypeToGLtype(Base::vertex_attribute_type);
        void Synchronize();
        GLenum usage;
    public:
        VertexBuffer(GLenum usage=GL_STATIC_DRAW);
        ~VertexBuffer();
        void operator =(Base::VerticesContainer& v);
        void Bind();
        void Unbind();
        void Draw(GLuint primitive_type=GL_TRIANGLES);
        void disable_vertex_attribute(int id);
        template <class T> Base::ElementsContainer<T>& enable_vertex_attribute(int id,int capacity=0)
        {
            Base::VerticesContainer::enable_vertex_attribute<T>(id,capacity);
        }

        template <class T> Base::ElementsContainer<T> & get_elements_container(int id)
        {
            return Base::VerticesContainer::get_elements_container<T>(id);
        }

        template <class T> const Base::ElementsContainer<T> & get_elements_container(int id) const
        {
            return Base::VerticesContainer::get_elements_container<T>(id);
        }

};

class DLL_DECLSPEC IndexBufferException: public Base::Exception
{
};


class DLL_DECLSPEC  IndexBuffer:public Base::IndicesContainer,public Resource
{
        ElementBuffer* buffer;
        static GLenum IndexTypeToGLtype(Base::index_type it);
        void Synchronize();
        GLenum usage;
    public:
        IndexBuffer(GLenum usage=GL_STATIC_DRAW);
        ~IndexBuffer();
        void operator =(Base::IndicesContainer& v);        
        void Draw(GLuint primitive_type=GL_TRIANGLES);
};

class DLL_DECLSPEC SubMesh:public Base::AbstractSubMesh,public Resource
{    
    bool no_indices;
    std::string src_filename;
    Math::Vector3D<float> box_max,box_min;
    VideoDevice::VertexBuffer* vb;
    VideoDevice::IndexBuffer* ib;
    VideoDevice::Texture* texture;
    GLuint primitive_type;
    Base::IndicesContainer* PrivateGetIndices();
    Base::VerticesContainer* PrivateGetVertices();
    virtual void PrivateLockBuffers(bool lock);
   public:
    SubMesh(const std::string & src_filename="",bool no_indices=false);
    SubMesh(bool no_indices,const std::string & uid="");
    void setPrimitiveType(GLuint primitive_type);
    void LoadFrom3DS(const std::string & file_name,const std::string mesh_name,int xi=0,int yi=2,int zi=1);
    void SaveTo3DS(const std::string & file_name,const std::string mesh_name);
    ~SubMesh();
    void ComputeBoundingBox();
    virtual const Math::Vector3D<float> & GetBoundingBoxMin();
    virtual const Math::Vector3D<float> & GetBoundingBoxMax();
    virtual bool IsPointIn(const Math::Vector3D<float> & p) const;
    virtual bool IsPointIn(const Math::Vector2D<float> & p,const Math::Matrix4x4<float> & trans) const;
   // bool IntersectWithLine(const Math::Vector3D<double> & p1,const Math::Vector3D<double> & p2,Math::Vector3D<double> & out=Math::Vector3D<double>());
    virtual bool IsLineIntersects(const Math::Vector3D<float> & p1,const Math::Vector3D<float> & p2) const;
    bool ScreenPointToSurfacePoint(const Math::Vector2D<float> & inp,Math::Vector3D<float> & outp1,const Math::CommonMatrix<float> & matrix,VideoDevice::Context* context); // every context must have it's own matrix
    Base::AbstractSubMesh* NewChild();
    void InitializeTexture(const std::string & texture_filename,int w=4,int h=4);
    VideoDevice::Texture* GetTexture();
    void Draw();
};


class DLL_DECLSPEC Context
{
    friend class Manager;
    friend class FrontBuffer;
    bool glee_inited;
   public:    
    enum ViewportRectangleBehavior {  SimpleVRBehavior=0x0,AspectConsideredVRBehavior=0x2};
   protected:
    ViewportRectangleBehavior vr_behavior;
    Base::VideoMode videomode;
    Math::Rectangle<int> viewport_rectangle;
    context_type type;
    virtual void MakeCurrent();
    virtual void MakeNotCurrent();
    virtual void SwapBuffers();
    Context(const context_type & ct=Null_Context);
   public:
    const context_type & GetType();    
    void RestoreViewportRectangle();
    void Resize(int w,int h,bool activate=true);
    const Context::ViewportRectangleBehavior & GetViewportRectangleBehavior();
    //void SetViewportRectangle(const Math::Rectangle<int> & vr=Math::Rectangle<int>(0,0,0,0),bool activate=true);
    const Math::Rectangle<int> & GetViewportRectangle();
    void SetViewportRectangleBehavior(const ViewportRectangleBehavior & vr,bool activate=true);
    void SetVideoMode(const Base::VideoMode & videomode,bool activate=true);
    const Base::VideoMode & GetVideoMode() const;    
    virtual ~Context();
};

inline Context::ViewportRectangleBehavior operator & (const Context::ViewportRectangleBehavior & v1,const Context::ViewportRectangleBehavior & v2)
{
    return Context::ViewportRectangleBehavior(int(v1)&int(v2));
}

inline Context::ViewportRectangleBehavior operator | (const Context::ViewportRectangleBehavior & v1,const Context::ViewportRectangleBehavior & v2)
{
    return Context::ViewportRectangleBehavior(int(v1)|int(v2));
}

#ifdef WITH_SDL
class DLL_DECLSPEC SDLContext:public Context
{
    friend class Manager;
    virtual void MakeCurrent();
    virtual void MakeNotCurrent();
    void SwapBuffers();
    SDLContext();
   public:    
    ~SDLContext();
};
#endif

#ifdef WITH_QT4


class Qt4Context;

class DLL_DECLSPEC GLWidget:public QGLWidget
{
    Q_OBJECT
   protected:
    Qt4Context* context;
    friend class Qt4Context;
     GLWidget(Qt4Context* context,const QGLWidget * shareWidget=0,QWidget * parent = 0);
     void paintGL();
    signals:
     void repaintGL();
     void mouseMoveEvent ( QMouseEvent * event );
     void mousePressEvent ( QMouseEvent * event );
     void mouseReleaseEvent ( QMouseEvent * event );
     void wheelEvent(QWheelEvent* event);
};

class DLL_DECLSPEC Qt4Context:public Context
{
 protected:   
    QGLFormat format;
    GLWidget* share_widget;
    friend class Manager;    
    QList<GLWidget*> gl_widgets;
    Qt4Context();
public:        
    template <class WidgetType> WidgetType * GenerateWidget()
    {
        WidgetType* ret=new WidgetType(this,this->share_widget);
        gl_widgets.push_back(ret);
        return ret;
    }
    virtual void MakeCurrent();
    void SetCurrentWidget(GLWidget* widget);
    QGLWidget * GenerateWidget();

};
#endif

class DLL_DECLSPEC Shader: public Resource
{        
    public:
        Shader(const std::string & path_to_filename);
};

class DLL_DECLSPEC Manager
{        
        static Manager* self;
        friend class Resource;
        std::list<Resource*> objects;
        std::map<resource_type,std::list<Resource*> > objects_by_type;
        std::map<context_type,Context*> contexts;
        VideoDevice::acceleration_capability_flags capability_flags;
        Manager();
        ~Manager();
        Math::Rectangle<int> clip_rect;
        Texture* blankpng;
        Math::Matrix4x4<float> matrix[4];
        Math::Matrix4x4<float> modelviewprojection_matrix;
        Math::Matrix4x4<float> viewprojection_matrix;
        bool modelviewprojection_changed;
        bool viewprojection_changed;
        static std::ostream* log;        
        VideoDevice::Context* current_context;
        VideoDevice::Context* empty_context;
        VideoDevice::DrawTarget* current_drawing_target;
        Math::Vector2D<int> aspect;
        FrontBuffer* front_buffer;
        void AddObject(Resource* object);
        void RemoveObject(Resource* object);
       public:
        enum MatrixMode {Matrix2DMode,Matrix3DMode};
        static Manager* Instance();
        static void Destroy();
        void Clear(GLbitfield target);
        void Present();
        VideoDevice::DrawTarget* GetCurrentDrawTarget();
        void SetCurrentDrawTarget(VideoDevice::DrawTarget* target=NULL);
        Context * ChangeContext(const context_type & ct,const Base::VideoMode & videomode=Base::VideoMode(0,0,0,0,0));        
        void RemoveContext(VideoDevice::Context* context);        
        Context * GetCurrentContext();
        void SetAccelerationCaps(VideoDevice::acceleration_capability_flags=vertexbuffer_acceleration);
        acceleration_capability_flags GetAccelerationCaps();
        void SetBoolParameter(VideoDevice::bool_parameter p,bool value);
        void SetUintParameter(VideoDevice::uint_parameter p,unsigned int value);
        void SetFloatParameter(VideoDevice::float_parameter p,float value);
        bool GetBoolParameter(VideoDevice::bool_parameter p);        
        unsigned int GetUintParameter(Kongomato::VideoDevice::uint_parameter p);        
        float GetFloatParameter(VideoDevice::float_parameter p);
        FrontBuffer* GetFrontBuffer();
        void SetClearColor(double r,double g,double b,double a);
        Resource* GetResourceByName(const std::string & name,const resource_type & type=empty_resource);
        Texture* GetTextureByPath(const std::string & path);
        void RemoveManagedResource(Resource* resource);

        void SetTransform(Kongomato::VideoDevice::transformation_type t,const Math::Matrix4x4<float>& m);                
        const Math::Matrix4x4<float> & GetViewProjectionMatrix();
        const Math::Matrix4x4<float> & GetModelViewProjectionMatrix();
        const Math::Matrix4x4<float> & GetTransform(Kongomato::VideoDevice::transformation_type t);
        void GetTransform(VideoDevice::transformation_type t,Math::Matrix4x4<float>& m);
        void AddTransform(VideoDevice::transformation_type t,const Math::Matrix4x4<float>& m);
        void ApplyTransformations(Manager::MatrixMode matrix_mode=Matrix3DMode);
        Math::Vector3D<float> FromScreenToWorld(int x,int y);

        const Math::Vector2D<int> & GetAspect();
        int GetAspectWValue();
        int GetAspectHValue();
        void SetAspect(const Math::Vector2D<int> & aspect);
        void SetAspectWValue(int w);
        void SetAspectHValue(int h);

        static void SetLogStream(std::ostream* s);
        static std::ostream & GetLogStream();

        void SetClipRectangle(Math::Rectangle<int> clip_rect);
        Math::Rectangle<int> GetClipRectangle();
        bool IsTextureBlank(Texture* t);

};


}}
#endif

