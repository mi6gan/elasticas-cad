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
/*
  Kongomato::Base namespace contains all device independent but graphics related stuff
  */

#ifndef KONGOBASE_H
#define KONGOBASE_H
#include "kongomath.h"
#include <iostream>
#include <string>
#include <typeinfo>
#include <vector>
#include <list>
#include <fstream>

#ifdef WIN32
#ifdef BUILD_DLL
#define DLL_DECLSPEC __declspec(dllexport) 
#else
#define DLL_DECLSPEC __declspec(dllimport)
#endif
#else
#define DLL_DECLSPEC
#endif


namespace Kongomato { namespace Base
{
enum animation_node_type
{
    animation_node_empty=0,
    animation_node_mesh=1,
    animation_node_submesh=2,
    animation_node_joint=3
};

enum index_type
{
    index_16=0,
    index_32=1
};

enum vertex_attribute_type
{
    vertex_attribute_char=0,
    vertex_attribute_unsigned_char=1,
    vertex_attribute_short=2,
    vertex_attribute_unsigned_short=3,
    vertex_attribute_int=4,
    vertex_attribute_unsigned_int=5,
    vertex_attribute_float=6,
    vertex_attribute_unsigned_float=7,
    vertex_attribute_double=8,
    vertex_attribute_unsigned_double=9,
    vertex_attribute_last=10
};

const int vertex_attribute_id_position=-1;
const int vertex_attribute_id_normal=-2;
const int vertex_attribute_id_color=-3;
const int vertex_attribute_id_texture_coordinate=-4;
template<class T> inline bool IsFlagSet(const T & value, const T & flag)
{
    return (value&flag)==flag;
}

template<class T> class Element;

class DLL_DECLSPEC Exception: public std::exception
{
        std::string cwhat;
    public:
        Exception(const char* c="undefined Kongomato exception") throw();
        virtual ~Exception() throw();
        virtual const char* what() const throw();
};

template <class T> class Color
{
    public:
        T r,g,b,a;
        Color<T>(T r=0,T g=0,T b=0,T a=0)
        {
            this->r=r;this->g=g;this->b=b;this->a=a;
        }

};

/*
    This class is designed to be parent of
    Kongomato::Base::ElementsContainer to implement
    set of "elements containers" in one basic container (like std::vector).
    Such is done in Kongomato::Base::VerticesContainer.
    Also type manipulation interface is provided.
*/
class DLL_DECLSPEC AbstractElementsContainer
{
    friend class VerticesContainer;
    int vertex_attribute_id;
    vertex_attribute_type type;
    protected:
    void set_vertex_attribute_type(vertex_attribute_type type);
    void set_vertex_attribute_id(int id);
    public:
    AbstractElementsContainer(int vertex_attribute_id=0,vertex_attribute_type type=vertex_attribute_float);
    virtual ~AbstractElementsContainer();
    vertex_attribute_type get_vertex_attribute_type() const;
    int get_vertex_attribute_id() const;
    virtual int get_Cbuffer_size() const = 0;
    virtual const void* get_Cbuffer_pointer() const = 0;
    virtual int get_element_capacity() const = 0;
    template<class T> static vertex_attribute_type GetVertexAttributeType()
    {
        if(typeid(T)==typeid(float)) return vertex_attribute_float;
        else if(typeid(T)==typeid(double)) return vertex_attribute_double;

        else if(typeid(T)==typeid(unsigned char)) return vertex_attribute_unsigned_char;
        else if(typeid(T)==typeid(char)) return vertex_attribute_char;

        else if(typeid(T)==typeid(unsigned short)) return vertex_attribute_unsigned_short;
        else if(typeid(T)==typeid(short)) return vertex_attribute_short;

        else if(typeid(T)==typeid(unsigned int)) return vertex_attribute_unsigned_int;
        else if(typeid(T)==typeid(int)) return vertex_attribute_int;
        throw Base::Exception("Kongomato::Base::GetVertexAttributeType: unsupported type");
        return vertex_attribute_last;
    }
    virtual std::size_t size() const = 0;
    virtual AbstractElementsContainer* clone() const = 0;
};

/*
    This template class  implements such non-scalar container
   that provides direct C pointer to tightly packed
   list of subelements. In Kongomato::Base::VerticesContainer used to present one vertex attribute array.
   T: any scalar type
   Definitions:
   elements - Determinant but really non-existant vector(std::vector methods overloading and Kongomato::Element class implement this abstraction )
   capacity - size of each element
   subelements - real data vector
*/
template<class T> class ElementsContainer: private std::vector<T>,public AbstractElementsContainer
{

        friend class Element<T>;
        int capacity;
        public:
        int get_element_capacity() const
        {
            return capacity;
        }

        void set_element_capacity(int capacity)
        {
            if(!capacity) throw Base::Exception("ElementsContainer::set_element_capacity: trying to set capacity to zero");
            if(capacity==this->capacity) return;
            std::size_t size=0;
            if(this->capacity!=0) size=this->size();
            this->capacity=capacity;
            this->resize(size);
        }

        std::size_t sizeof_scalar() const
        {
            return sizeof(T);
        }

        std::size_t size() const
        {
            return std::vector<T>::size()/capacity;
        }

        void resize(std::size_t size)
        {
            std::vector<T>::resize(size*capacity);
        }

        void insert(int i,const Math::CommonVector<T> & v)
        {
            if(v.size()!=capacity)
                throw Base::Exception("Kongomato::ElementContainer::insert: non-scalar trying to be inserted is incompatible");
            for(int a=0;a<capacity;a++) std::vector<T>::insert(std::vector<T>::begin()+(i*capacity+a),v[a]);
        }

        void push_back(const Math::CommonVector<T> & v)
        {

            if(v.size()!=capacity)
                throw Base::Exception("Kongomato::ElementContainer::push_back: non-scalar trying to be inserted is incompatible");
                for(int a=0;a<capacity;a++) std::vector<T>::push_back(v[a]);
        }

        int get_Cbuffer_size() const
        {
            return sizeof(T)*std::vector<T>::size();
        }

        const void* get_Cbuffer_pointer() const
        {
            return &(std::vector<T>::operator [](0));
        }

        int get_subelements_count() const
        {
            return std::vector<T>::size();
        }

        T get_subelement(int i) const
        {
            return std::vector<T>::operator[](i);
        }

 /*      const Element<T> operator [] (int a) const
        {
           if(std::vector<T>::size()<=a*capacity) throw Base::Exception("Element<T> Kongomato::ElementContainer::operator [](int a): index out of bounds");
           Element<T> element_helper=Element<T> (this,a);
           return element_helper;
        }*/

        Element<T> operator [] (int a)
        {
           if(std::vector<T>::size()<=a*capacity) throw Base::Exception("Element<T> Kongomato::ElementContainer::operator [](int a): index out of bounds");
           Element<T> element_helper=Element<T> (this,a);
           return element_helper;
        }

        const Element<T> operator [] (int a) const
        {
           if(std::vector<T>::size()<=a*capacity) throw Base::Exception("Element<T> Kongomato::ElementContainer::operator [](int a): index out of bounds");
           Element<T> element_helper=Element<T> ((Kongomato::Base::ElementsContainer<T>*)this,a);
           return element_helper;
        }

        ElementsContainer(int id=0,int capacity=1):AbstractElementsContainer(id,GetVertexAttributeType<T>()),std::vector<T>()
        {
                this->set_element_capacity(capacity);
                this->AbstractElementsContainer::set_vertex_attribute_type(AbstractElementsContainer::GetVertexAttributeType<T>());
        }

        ~ElementsContainer()
        {
        }

        AbstractElementsContainer* clone() const
        {
            ElementsContainer<T>* new_clone=new ElementsContainer<T>();
            (*(new_clone))=(*this);
            return new_clone;
        }
};


/*
    This class implements temporary ElementContainer's element.
*/
template<class T> class Element
{
    friend class ElementsContainer<T>;
    ElementsContainer<T>* owner;
    int index;

    Element<T>(ElementsContainer<T>* owner=NULL,int index=0)
    {
        this->owner=owner;this->index=index;
    }
    public:
    void operator=  (T data)
    {
        if(owner->capacity>0) owner->element[index*owner->capacity]=data;
    }

    void operator= (const Math::CommonVector<T>& data)
    {
        if(data.size()!=owner->capacity) throw Base::Exception("Element::operator =(Math::CommonVector<T>& data) error: invalid right operand");
        for(int a=0;a<owner->capacity;a++)
            owner->std::vector<T>::operator[](index*owner->capacity+a)=data[a];
    }

    T& operator [](int i)
    {
        if(i>owner->capacity) throw Base::Exception("Element::operator [](int i) error: index out of bounds");
        return owner->std::vector<T>::operator[](index*owner->capacity+i);
    }

    T operator [](int i) const
    {
        if(i>owner->capacity) throw Base::Exception("Element::operator [](int i) error: index out of bounds");
        return owner->std::vector<T>::operator[](index*owner->capacity+i);
    }

    const Math::CommonVector<T> ToVector() const
    {
        Math::CommonVector<T> vector_helper(owner->capacity);
        for(int a=0;a<owner->capacity;a++)
            vector_helper[a]=owner->std::vector<T>::operator[](index*owner->capacity+a);
        return vector_helper;
    }

};

class DLL_DECLSPEC IndicesContainer
{
     protected:
        index_type current_type;
        std::vector< unsigned short > i16;
        std::vector< unsigned int > i32;
        bool synchronized;
     public:
        IndicesContainer(index_type current_type=index_16);
        void set_index_type(index_type type);
        index_type get_index_type() const;
        std::size_t size() const;
        void push_back(unsigned int i);
        void insert(int to,unsigned int i);
        void resize(std::size_t sz);
        unsigned int get_value(int i) const;
        void set_value(int i,unsigned int value);
        const void* get_CBuffer_pointer() const;
        int get_CBuffer_size() const;
        unsigned int operator[](int i) const;
        unsigned int operator[](int i);
};

//Non-template container incapsulating list of elements containers.
// Actually designed to be used as device independent
// parent of Kongomato::VertexBuffer class
class DLL_DECLSPEC VerticesContainer
{
    protected:
    std::vector<AbstractElementsContainer*> components;    
    bool synchronized;
    public:
        int get_vertex_attribute_index(int id) const;
        template <class T> ElementsContainer<T>& enable_vertex_attribute(int id,int capacity)
        {
            int index=this->get_vertex_attribute_index(id);
            if(index<0)
            {
                components.push_back((AbstractElementsContainer*)(new ElementsContainer<T>(id,capacity)));
                index=components.size()-1;
            }
            else
                if(AbstractElementsContainer::GetVertexAttributeType<T>()!=components[index]->get_vertex_attribute_type())
                {
                    delete components[index];
                    components[index]=(AbstractElementsContainer*)(new ElementsContainer<T>(id,capacity));
                }
                else
                if(capacity!=0&&(components[index]->get_element_capacity()!=capacity)) ((ElementsContainer<T>*)(components[index]))->set_element_capacity(capacity);
            synchronized=false;
            return *((ElementsContainer<T>*)(components[index]));
        }

        void disable_vertex_attribute(int id);
        void disable_all_vertex_attributes();

        template <class T> ElementsContainer<T> & get_elements_container(int id)
        {
            int a=this->get_vertex_attribute_index(id);
            if(a<0) throw Base::Exception("ElementsContainer::get_elements_container(int id) : trying to get access to disabled attribute");
                else if(AbstractElementsContainer::GetVertexAttributeType<T>()!=components[a]->get_vertex_attribute_type())
                        throw Base::Exception("ElementsContainer::get_elements_container(int id) : invalid template function type for this attribute");
            synchronized=false;
            return *((ElementsContainer<T>*)components[a]);
        }

        template <class T> const ElementsContainer<T> & get_elements_container(int id) const
        {
            int a=this->get_vertex_attribute_index(id);
            if(a<0) throw Base::Exception("ElementsContainer::get_elements_container(int id) : trying to get access to disabled attribute");
                else if(AbstractElementsContainer::GetVertexAttributeType<T>()!=components[a]->get_vertex_attribute_type())
                        throw Base::Exception("ElementsContainer::get_elements_container(int id) : invalid template function type for this attribute");
            return *((ElementsContainer<T>*)components[a]);
        }

        void clear();
        void operator =(const VerticesContainer& vc);
        ~VerticesContainer();
};


/*
 */
class DLL_DECLSPEC AbstractSubMesh
{
    bool buffers_locked;
   protected:
    std::vector<AbstractSubMesh*> children;
    void AddChild(AbstractSubMesh* ns);
    virtual IndicesContainer* PrivateGetIndices()=0;
    virtual VerticesContainer* PrivateGetVertices()=0;
    virtual void PrivateLockBuffers(bool lock)=0;
   public:
    virtual const Math::Vector3D<float> & GetBoundingBoxMin()=0;
    virtual const Math::Vector3D<float> & GetBoundingBoxMax()=0;
    IndicesContainer* GetIndices();
    VerticesContainer* GetVertices();
    AbstractSubMesh();
    void LockBuffers(bool lock);
    virtual void InitializeTexture(const std::string & texture_filename,int w=0,int h=0)=0;
    virtual bool IsPointIn(const Math::Vector3D<float> & p) const=0;
    virtual bool IsPointIn(const Math::Vector2D<float> & p,const Math::Matrix4x4<float> & trans) const=0;
    virtual AbstractSubMesh* NewChild()=0;
    const std::vector<AbstractSubMesh*> & GetChildren();
    virtual ~AbstractSubMesh();    
};

/*
  3-Dimensional object with three basics:
  position,angle and size.

*/

class DLL_DECLSPEC GeometricObject
{
protected:
        Math::Vector3D<float> position,angle,size;
        Math::Matrix4x4<float> helper_matrix;
        bool own_axis;
 public:
        GeometricObject( Math::Vector3D<float>& position, Math::Vector3D<float>& angle, Math::Vector3D<float>& size);
        GeometricObject(float posx=0,float posy=0,float posz=0,float anglex=0,float angley=0,float anglez=0,float sizex=1,float sizey=1,float sizez=1);
        Math::Vector3D<float> & Position();
        Math::Vector3D<float> & Angle();
        Math::Vector3D<float> & Size();
        const Math::Vector3D<float> & Position() const;
        const Math::Vector3D<float> & Angle() const;
        const Math::Vector3D<float> & Size() const;
        void Rotate(const Math::Vector3D<float>& d,Math::Vector3D<float>* limup=NULL,Math::Vector3D<float>* limdown=NULL);
        void Move(const Math::Vector3D<float>& d);
        void Scale(const Math::Vector3D<float>& d);
        virtual void Rotate(float x,float y,float z,Math::Vector3D<float>* limup=NULL,Math::Vector3D<float>* limdown=NULL);
        virtual void Move(float x,float y,float z);
        virtual void Scale(float x,float y,float z);
        Math::Matrix4x4<float> GetMatrix() const;
        void SetAngle(float x,float y,float z,bool isx=true,bool isy=true,bool isz=true);
        void SetPosition(float x,float y,float z,bool isx=true,bool isy=true,bool isz=true);
        void SetSize(float x,float y,float z,bool isx=true,bool isy=true,bool isz=true);
};

class DLL_DECLSPEC Camera:protected GeometricObject
{
    float dist;
    Math::Vector3D<float> helper_vector;
    void ComputeEye();
   public:
    Camera();
    Camera(const Math::Vector3D<float>& at,const Math::Vector3D<float>& up,float dist);
    void SetAt(float atx,float aty,float atz);
    void SetUp(float upx,float upy,float upz);
    void SetAngle(float x,float y,float z);
    void SetDist(float dist);
    const Math::Vector3D<float> & Angle() const;
    const Math::Vector3D<float>& At() const;
    const Math::Vector3D<float>& Up() const;
    float Dist() const;
    Math::Vector3D<float> & Angle();
    Math::Vector3D<float>& At();
    Math::Vector3D<float>& Up();
    float & Dist();
    Math::Matrix4x4<float> GetMatrix();
    void Move(float d);
    void Rotate(float x,float y,float z,Math::Vector3D<float>* limup=0,Math::Vector3D<float>* limdown=0);
};

/*
  No comment )
 */

class DLL_DECLSPEC VideoMode
{
        int _width,_height,_bpp;
        bool _fullscreen,_doublebuffer;
        public:
        VideoMode(int width=800,int height=600,bool doublebuffer=true,bool fullscreen=true,int bpp=32);        
        int & width();
        int & height();
        int & bpp();
        bool & fullscreen();
        bool & doublebuffer();
        int width() const;
        int height() const;
        int bpp() const;
        bool fullscreen() const;
        bool doublebuffer() const;
};

class DLL_DECLSPEC UidGenerator
{
        std::vector< Math::Range<char> > alphabet;
        std::string last_generated;
        int GetContainingAlphabet(char alpha);
    public:
        UidGenerator(const Math::Range<char>& primary_alphabet=Math::Range<char>('A','Z'));
        void ExtendAlphabet(const Math::Range<char>& additional_alphabet);
        void SetAlphabet(const Math::Range<char>& primary_alphabet);
        const std::string & GenerateNext();
        void Reload(const std::string & first="");
};

class DLL_DECLSPEC IOStream:public virtual std::fstream
{
    protected:
    IOStream( const char * filename, std::ios_base::openmode mode = std::ios_base::in | std::ios_base::out );
    ~IOStream();
};



}}

std::ostream & operator<<(std::ostream& out,const Kongomato::Base::VideoMode& videomode);
#endif
