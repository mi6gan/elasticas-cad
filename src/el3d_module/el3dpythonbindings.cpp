#include "el3dpythonbindings.h"
//_______________________________________________

PyObject* El3dPythonBindings::GetCommonVariableValuef(PyObject *self,PyObject *args)
{
    float value;
    char * var_name;
    if(PyArg_ParseTuple(args,"s",&var_name))
        return Py_BuildValue("f",Elasticas::Core::Instance()->CommonVariables()[var_name].toDouble());
    Py_RETURN_NONE;
}

PyObject* El3dPythonBindings::GetCommonVariableValueb(PyObject *self,PyObject *args)
{
    char * var_name;
    if(PyArg_ParseTuple(args,"s",&var_name))
        return Py_BuildValue("b",Elasticas::Core::Instance()->CommonVariables()[var_name].toBool());
    Py_RETURN_NONE;
}

PyObject* El3dPythonBindings::GetCommonVariableValueI(PyObject *self,PyObject *args)
{
    char * var_name;
    if(PyArg_ParseTuple(args,"s",&var_name))
        return Py_BuildValue("I",Elasticas::Core::Instance()->CommonVariables()[var_name].toInt());
    Py_RETURN_NONE;
}

PyObject* El3dPythonBindings::GetCommonVariableValueS(PyObject *self,PyObject *args)
{
    char * var_name;
    if(PyArg_ParseTuple(args,"s",&var_name))
        return Py_BuildValue("s",(const char*)
                             (const char*)(Elasticas::Core::Instance()->CommonVariables()[var_name].toString().toUtf8()));
    Py_RETURN_NONE;
}

PyObject* El3dPythonBindings::IsCommonVariableSet(PyObject *self,PyObject *args)
{
    char * var_name;
    if(PyArg_ParseTuple(args,"s",&var_name))
        return Py_BuildValue("B",Elasticas::Core::Instance()->CommonVariables().contains(var_name));
    Py_RETURN_NONE;
}

PyObject* El3dPythonBindings::setClassesRelations(PyObject *self,PyObject *args)
{
    char * parent,*child;
    if(PyArg_ParseTuple(args,"ss",&parent,&child)) Elasticas::Core::Instance()->classByName(parent)->addChild(Elasticas::Core::Instance()->classByName(child));
    Py_RETURN_NONE;
}

#ifdef WITH_CARVE
PyObject* El3dPythonBindings::SequencesFromCarvePolyhedron(carve::poly::Polyhedron* ph,PyObject* vertices,PyObject* faces)
{
    int cnt=ph->vertices.size();
    PyObject* lst;
    for(int i=0;i<cnt;i++)
    {
        lst=PyList_New(3);
        for(int j=0;j<3;j++) PyList_SetItem(lst,j,PyFloat_FromDouble(ph->vertices[i].v[j]));
        PyList_Append(vertices,lst);
    }
    cnt=ph->faces.size();
    for(int i=0;i<cnt;i++)
    {
        int n_vertices=ph->faces[i].nVertices();
        for(int a=0;a<n_vertices-2;a++)
        {
            lst=PyList_New(3);
            for(int j=0;j<2;j++) PyList_SetItem(lst,j,PyInt_FromLong(ph->vertexToIndex_fast(ph->faces[i].vertex(a+j))));
            PyList_SetItem(lst,2,PyInt_FromLong(ph->vertexToIndex_fast(ph->faces[i].vertex(n_vertices-1))));
            PyList_Append(faces,lst);
        }
    }
}

carve::poly::Polyhedron* El3dPythonBindings::CarvePolyhedronFromSequences(PyObject *vertices,PyObject *faces)
{
    carve::input::PolyhedronData data;
    int len=PySequence_Length(vertices);
    double x,y,z;
    for(int i=0;i<len;i++)
    {
        x=PyFloat_AsDouble(PySequence_GetItem(PySequence_GetItem(vertices,i),0));
        y=PyFloat_AsDouble(PySequence_GetItem(PySequence_GetItem(vertices,i),1));
        z=PyFloat_AsDouble(PySequence_GetItem(PySequence_GetItem(vertices,i),2));
        data.addVertex(carve::geom::VECTOR(x,y,z));
    }
    len=PySequence_Length(faces);
    long i0,i1,i2;
    for(int i=0;i<len;i++)
    {
        PyObject* poly=PySequence_GetItem(faces,i);
        int len=PySequence_Length(poly);
        if(len>=3)
        {
            i0=PyInt_AsLong(PySequence_GetItem(poly,0));
            i1=PyInt_AsLong(PySequence_GetItem(poly,1));
            i2=PyInt_AsLong(PySequence_GetItem(poly,2));
            if(len==3) data.addFace(i0,i1,i2);
            else data.addFace(i0,i1,i2,PyInt_AsLong(PySequence_GetItem(poly,3)));
        }
        else throw Elasticas::Exception("carve::poly::Polyhedron* El3dPythonBindings::CarvePolyhedronFromSequences(PyObject *vertices,PyObject *faces): unsupported primitive type");
    }
    return data.create();
}

PyObject* El3dPythonBindings::CSGUnion(PyObject *self,PyObject *args)
{
    PyObject* vertices0,*faces0,*vertices1,*faces1,*shared;
    if(PyArg_ParseTuple(args,"OOOO",&vertices0,&faces0,&vertices1,&faces1))
    {
        carve::csg::V2Set shared_edges;
        carve::poly::Polyhedron* ph0=CarvePolyhedronFromSequences(vertices0,faces0);
        carve::poly::Polyhedron* ph1=CarvePolyhedronFromSequences(vertices1,faces1);
        shared=PyList_New(0);
        carve::poly::Polyhedron* ph2=csg->compute(ph0,ph1,carve::csg::CSG::UNION,&shared_edges);
        for(carve::csg::V2Set::iterator it=shared_edges.begin();it!=shared_edges.end();++it)
        {
            PyList_Append(shared,PyInt_FromLong(ph2->vertexToIndex_fast((*it).first)));
            PyList_Append(shared,PyInt_FromLong(ph2->vertexToIndex_fast((*it).second)));
        }
        SequencesFromCarvePolyhedron(ph2,vertices0=PyList_New(0),faces0=PyList_New(0));
        delete ph0; delete ph1; delete ph2;
    }
    return Py_BuildValue("(OOO)",vertices0,faces0,shared);
}

PyObject* El3dPythonBindings::CSGDifference(PyObject *self,PyObject *args)
{
    PyObject* vertices0,*faces0,*vertices1,*faces1,*shared;
    if(PyArg_ParseTuple(args,"OOOO",&vertices0,&faces0,&vertices1,&faces1))
    {
        carve::csg::V2Set shared_edges;
        carve::poly::Polyhedron* ph0=CarvePolyhedronFromSequences(vertices0,faces0);
        carve::poly::Polyhedron* ph1=CarvePolyhedronFromSequences(vertices1,faces1);
        shared=PyList_New(0);
        carve::poly::Polyhedron* ph2;
        //while(true)
        {
        try{
        ph2=csg->compute(ph0,ph1,carve::csg::CSG::A_MINUS_B,&shared_edges);
        //break;
        }
        catch(carve::exception ex)
        {
                std::cout<<ex.str();
                throw ex;
        }
        }

        for(carve::csg::V2Set::iterator it=shared_edges.begin();it!=shared_edges.end();++it)
        {
            PyList_Append(shared,PyInt_FromLong(ph2->vertexToIndex_fast((*it).first)));
            PyList_Append(shared,PyInt_FromLong(ph2->vertexToIndex_fast((*it).second)));
        }
        SequencesFromCarvePolyhedron(ph2,vertices0=PyList_New(0),faces0=PyList_New(0));
        delete ph0; delete ph1; delete ph2;
    }
    return Py_BuildValue("(OOO)",vertices0,faces0,shared);
}

PyObject* El3dPythonBindings::CSGIntersection(PyObject *self,PyObject *args)
{
    PyObject* vertices0,*faces0,*vertices1,*faces1,*shared;
    if(PyArg_ParseTuple(args,"OOOO",&vertices0,&faces0,&vertices1,&faces1))
    {
        carve::csg::V2Set shared_edges;
        carve::poly::Polyhedron* ph0=CarvePolyhedronFromSequences(vertices0,faces0);
        carve::poly::Polyhedron* ph1=CarvePolyhedronFromSequences(vertices1,faces1);
        shared=PyList_New(0);
        carve::poly::Polyhedron* ph2=csg->compute(ph0,ph1,carve::csg::CSG::INTERSECTION,&shared_edges);
        for(carve::csg::V2Set::iterator it=shared_edges.begin();it!=shared_edges.end();++it)
        {
            PyList_Append(shared,PyInt_FromLong(ph2->vertexToIndex_fast((*it).first)));
            PyList_Append(shared,PyInt_FromLong(ph2->vertexToIndex_fast((*it).second)));
        }
        SequencesFromCarvePolyhedron(ph2,vertices0=PyList_New(0),faces0=PyList_New(0));
        delete ph0; delete ph1; delete ph2;
    }
    return Py_BuildValue("(OOO)",vertices0,faces0,shared);
}

PyObject* El3dPythonBindings::CSGSlice(PyObject *self,PyObject *args)
{
    PyObject* vertices0,*faces0,*vertices1,*faces1,*shared;
    PyObject* a_vertices=PyList_New(0),*b_vertices=PyList_New(0);
    PyObject* a_faces=PyList_New(0),*b_faces=PyList_New(0);
    if(PyArg_ParseTuple(args,"OOOO",&vertices0,&faces0,&vertices1,&faces1))
    {
        carve::csg::V2Set shared_edges;
        std::list<carve::poly::Polyhedron*> a_sliced,b_sliced;
        carve::poly::Polyhedron* ph0=CarvePolyhedronFromSequences(vertices0,faces0);
        carve::poly::Polyhedron* ph1=CarvePolyhedronFromSequences(vertices1,faces1);
        shared=PyList_New(0);
        csg->slice(ph0,ph1,a_sliced,b_sliced);
        /*,&shared_edges);
        for(carve::csg::V2Set::iterator it=shared_edges.begin();it!=shared_edges.end();++it)
        {
            PyList_Append(shared,PyInt_FromLong(ph2->vertexToIndex_fast((*it).first)));
            PyList_Append(shared,PyInt_FromLong(ph2->vertexToIndex_fast((*it).second)));
        }*/
        for(std::list<carve::poly::Polyhedron*>::iterator it=a_sliced.begin();it!=a_sliced.end();++it)
        {
            SequencesFromCarvePolyhedron(*it,vertices0=PyList_New(0),faces0=PyList_New(0));
            PyList_Append(a_vertices,vertices0);
            PyList_Append(a_faces,faces0);
            delete *it;
        }
        for(std::list<carve::poly::Polyhedron*>::iterator it=b_sliced.begin();it!=b_sliced.end();++it)
        {
            SequencesFromCarvePolyhedron(*it,vertices0=PyList_New(0),faces0=PyList_New(0));
            PyList_Append(b_vertices,vertices0);
            PyList_Append(b_faces,faces0);
            delete *it;
        }
    }
    return Py_BuildValue("(OOOO)",a_vertices,a_faces,b_vertices,b_faces);
}

#endif

PyObject* El3dPythonBindings::ModelClearTexture( PyObject *self,PyObject *args)
{
    ModelClass* _self=(ModelClass*)self;
    unsigned int color;
    if(PyArg_ParseTuple(args,"I",&color))
    {
        Kongomato::VideoDevice::Manager* dev=Kongomato::VideoDevice::Manager::Instance();
        VideoDevice::DrawTarget* last_draw_target=dev->GetCurrentDrawTarget();
        dev->SetCurrentDrawTarget(_self->node->GetSubMesh(0)->GetTexture());
        dev->SetUintParameter(VideoDevice::clearcolor_parameter,color);
        dev->Clear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        dev->Present();
        dev->SetCurrentDrawTarget(last_draw_target);
    }
    Py_RETURN_NONE;
}

PyObject* El3dPythonBindings::ModelBeginDrawOnTexture(PyObject *self,PyObject *args)
{
    ModelClass* _self=(ModelClass*)self;
    Kongomato::VideoDevice::Manager* dev=Kongomato::VideoDevice::Manager::Instance();
    VideoDevice::DrawTarget* last_draw_target=dev->GetCurrentDrawTarget();
    dev->SetCurrentDrawTarget(_self->node->GetSubMesh(0)->GetTexture());
    Py_RETURN_NONE;
}

PyObject* El3dPythonBindings::ModelEndDrawOnTexture(PyObject *self,PyObject *args)
{
    ModelClass* _self=(ModelClass*)self;
    Kongomato::VideoDevice::Manager* dev=Kongomato::VideoDevice::Manager::Instance();
    dev->Present();
    dev->SetCurrentDrawTarget(last_draw_target);
    Py_RETURN_NONE;
}

PyObject* El3dPythonBindings::ModelAddSubMesh(PyObject *self,PyObject *args)
{
    ModelClass* _self=(ModelClass*)self;
    _self->node->AddSubMesh();
    Py_BuildValue("I",_self->node->GetSubMeshesCount()-1);
    Py_RETURN_NONE;
}

PyObject* El3dPythonBindings::DrawPolyline(PyObject *self,PyObject *args)
{
    PyObject *array,*sub,*element;
    float coord[]={0.0f,0.0f};
    float line_width=1.0f;
    int len1=0;
    if(PyArg_ParseTuple(args,"O|f",&array,&line_width))
    {
            Kongomato::TwoDimensional::PrimitivesPlotter::BeginDraw(GL_LINE_STRIP);
            GLfloat last_width;
            glGetFloatv(GL_LINE_WIDTH,&last_width);
            glEnable(GL_BLEND);
            glLineWidth(line_width);
            if(PySequence_Check(array)) len1=PySequence_Length(array);
             for(int a=0;a<len1;a++)
             {
                 if(PySequence_Check(sub=PySequence_GetItem(array,a)))
                 {
                     if(PySequence_Length(sub)>=2)
                     {
                         for(int b=0;b<2;b++)
                         {
                          if(PyNumber_Check(element=PySequence_GetItem(sub,b)))
                           {
                             PyObject* n=PyNumber_Float(element);
                             coord[b]=PyFloat_AsDouble(n);
                             Py_XDECREF(n);
                           }
                           Py_XDECREF(element);
                         }
                     }
                      glVertex2f(coord[0],coord[1]);
                 }
                 Py_XDECREF(sub);
             }
             glLineWidth(last_width);
             glDisable(GL_BLEND);
             Kongomato::TwoDimensional::PrimitivesPlotter::EndDraw();
    }
    Py_RETURN_NONE;
}

PyObject* El3dPythonBindings::DrawTexture(PyObject *self,PyObject *args)
{
    char* file_name;
    Math::Rectangle<int> rect;
    if(PyArg_ParseTuple(args,"s|(iiii)",&file_name,&rect.x(),&rect.y(),&rect.width(),&rect.height()))
    {
        VideoDevice::Texture* tx=VideoDevice::Manager::Instance()->GetTextureByPath(file_name);
        tx->Draw(rect);
    }
    Py_RETURN_NONE;
}

PyObject* El3dPythonBindings::TextureSize( PyObject *self,PyObject *args)
{
    char* file_name;
    int w=0,h=0;
    if(PyArg_ParseTuple(args,"s",&file_name))
    {
        VideoDevice::Texture* tx= VideoDevice::Manager::Instance()->GetTextureByPath(file_name);
        w=VideoDevice::next_p2(tx->Width());
        h=VideoDevice::next_p2(tx->Height());
    }
    return Py_BuildValue("(ii)",w,h);
}

PyObject* El3dPythonBindings::ModelNew(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    ModelClass* self=(ModelClass*)PyType_GenericNew(type,args,kwds);
    char* file_name=NULL,*mesh_name=NULL;
   if(PyArg_ParseTuple(args,"s|s",&mesh_name,&file_name))
   self->node=dynamic_cast<Scene::Mesh*>( static_scene->GetFirstByName(mesh_name));
   if(!self->node)
   {
       self->node=static_scene->AddMesh("");
       self->node->SetName(mesh_name);
   }
   if(file_name) self->node->GetSubMesh(0)->LoadFrom3DS(file_name,mesh_name);
   return (PyObject*)self;
}

void El3dPythonBindings::ModelDel( PyObject *self)
{
    //static_scene->RemoveNode(((ModelClass*)(self))->node);
}

PyObject* El3dPythonBindings::ModelLoadFrom3DS(PyObject *self,PyObject *args)
{
    ModelClass* _self=(ModelClass*)self;
    char* file_name=NULL,*node_name=NULL;
    if(PyArg_ParseTuple(args,"s|s",&file_name,&node_name))
    {
        if(node_name) _self->node->GetSubMesh(0)->LoadFrom3DS(file_name,node_name);
        else _self->node->GetSubMesh(0)->LoadFrom3DS(file_name,_self->node->GetName());
    }
    Py_RETURN_NONE;
}

PyObject* El3dPythonBindings::ModelRotate( PyObject *self,PyObject *args)
{

        ModelClass* _self=(ModelClass*)self;
        float x,y,z;
        if(PyArg_ParseTuple(args,"(fff)",&x,&y,&z)) _self->node->Rotate(x,y,z);
        Py_RETURN_NONE;
}

PyObject* El3dPythonBindings::ModelScale( PyObject *self,PyObject *args)
{
        ModelClass* _self=(ModelClass*)self;
        float x,y,z;
        if(PyArg_ParseTuple(args,"(fff)",&x,&y,&z)) _self->node->Scale(x,y,z);
        Py_RETURN_NONE;
}

PyObject* El3dPythonBindings::ModelSetVisiblity( PyObject *self,PyObject *args)
{
    ModelClass* _self=(ModelClass*)self;
    bool visible;
    if(PyArg_ParseTuple(args,"b",&visible)) _self->node->SetVisiblity(visible);
    Py_RETURN_NONE;
}


PyObject* El3dPythonBindings::ModelSetAngle( PyObject *self,PyObject *args)
{
        ModelClass* _self=(ModelClass*)self;
        float x,y,z;
        unsigned char isx=1,isy=1,isz=1;
        if(PyArg_ParseTuple(args,"(fff)|(bbb)",&x,&y,&z,&isx,&isy,&isz))
            _self->node->SetAngle(x,y,z,isx,isy,isz);
        Py_RETURN_NONE;
}

PyObject* El3dPythonBindings::ModelSetPosition( PyObject *self,PyObject *args)
{
        ModelClass* _self=(ModelClass*)self;
        float x,y,z;
        unsigned char isx=1,isy=1,isz=1;
        if(PyArg_ParseTuple(args,"(fff)|(bbb)",&x,&y,&z,&isx,&isy,&isz))
            _self->node->SetPosition(x,y,z,isx,isy,isz);
        Py_RETURN_NONE;
}

PyObject* El3dPythonBindings::ModelSetSize(PyObject *self,PyObject *args)
{
        ModelClass* _self=(ModelClass*)self;
        float x,y,z;
        unsigned char isx=1,isy=1,isz=1;
        if(PyArg_ParseTuple(args,"(fff)|(bbb)",&x,&y,&z,&isx,&isy,&isz))
            _self->node->SetSize(x,y,z,isx,isy,isz);
        Py_RETURN_NONE;
}

PyObject* El3dPythonBindings::ModelSetTexture( PyObject *self,PyObject *args)
{
    char* filename;
    ModelClass* _self=(ModelClass*)self;
    int i=0;
    if(PyArg_ParseTuple(args,"s|i",&filename,&i)) _self->node->GetSubMesh(i)->InitializeTexture(QString(filename).toLocal8Bit().data());

    Py_RETURN_NONE;
}

PyObject* El3dPythonBindings::ModelInitTexture( PyObject *self,PyObject *args)
{
    ModelClass* _self=(ModelClass*)self;
    int w,h,i=0;
    if(!_self->node->GetSubMesh(0)->GetTexture())
        if(PyArg_ParseTuple(args,"ii|i",&w,&h,&i)) _self->node->GetSubMesh(i)->InitializeTexture("",w,h);
    Py_RETURN_NONE;
}

PyObject* El3dPythonBindings::ModelSetViewMode( PyObject *self,PyObject *args)
{
    ModelClass* _self=(ModelClass*)self;
    int i0,i1;
    if(PyArg_ParseTuple(args,"ii",&i0,&i1))
    {
        Kongomato::Scene::mesh_draw_flags draw_flag;
        if(i0==0) draw_flag=Kongomato::Scene::mesh_draw_points;
        else if(i0==1) draw_flag=Kongomato::Scene::mesh_draw_wireframe;
        else if(i0==2) draw_flag=Kongomato::Scene::mesh_draw_solid;
        if(i1) _self->node->SetDrawFlags(_self->node->GetDrawFlags()|draw_flag);
        else _self->node->SetDrawFlags(_self->node->GetDrawFlags()&(~draw_flag));
    }
    Py_RETURN_NONE;
}

PyObject* El3dPythonBindings::ModelSetSurface( PyObject *self,PyObject *args)
{
    PyObject* v,*t,*uv=NULL,*n=NULL,*col=NULL,*array,*sub,*element;
    float coord[]={0.0f,0.0f,0.0f};
    float tcoord[]={0.0f,0.0f};
    int ind[]={0,0,0,0};
    ModelClass* _self=(ModelClass*)self;
    int len1=0;
    int mesh_id=0;
    if(PyArg_ParseTuple(args,"OO|O|O|O",&v,&t,&uv,&n,&col))
    {
            VideoDevice::SubMesh* mesh=_self->node->GetSubMesh(mesh_id);
            mesh->LockBuffers(true);
            Base::VerticesContainer * vb=mesh->GetVertices();
            Base::IndicesContainer * ib=mesh->GetIndices();
            vb->disable_all_vertex_attributes();
            Base::ElementsContainer<float> * position=&vb->enable_vertex_attribute<float>(Base::vertex_attribute_id_position,3);
            Base::ElementsContainer<float> * texture=NULL,*normal=NULL,*color=NULL;
            if(uv) texture=&vb->enable_vertex_attribute<float>(Base::vertex_attribute_id_texture_coordinate,2);
            if(n) normal=&vb->enable_vertex_attribute<float>(Base::vertex_attribute_id_normal,3);
            if(col) color=&vb->enable_vertex_attribute<float>(Base::vertex_attribute_id_color,3);

            ib->set_index_type(Base::index_16);
            for(int i=0;i<2+(uv!=NULL)+(n!=NULL)+(col!=NULL);i++)
            {
            if(i==0) array=v;
            else if(i==1) array=t;
            else if(i==2) array=uv;
            else if(i==3) array=n;
            else if(i==4) array=col;
            if(PySequence_Check(array))
            {
             len1=PySequence_Length(array);
             for(int a=0;a<len1;a++)
                 if(PySequence_Check(sub=PySequence_GetItem(array,a)))
                 {
                     if(PySequence_Length(sub)>=2)
                     {
                        if(i==0)
                        {
                         for(int b=0;b<3;b++)
                         {
                          if(PyNumber_Check(element=PySequence_GetItem(sub,b)))
                           {
                             PyObject* n=PyNumber_Float(element);
                             coord[b]=PyFloat_AsDouble(n);
                             Py_XDECREF(n);
                           }
                           Py_XDECREF(element);
                         }
                         position->push_back(Math::Vector3D<float>(coord[0],coord[1],coord[2]));
                        }
                        else
                        if(i==1)
                        {
                            int len2=PySequence_Length(sub);
                            for(int b=0;b<len2;b++)
                            {
                               if(PyNumber_Check(element=PySequence_GetItem(sub,b)))
                               {
                                PyObject* n=PyNumber_Int(element);
                                ind[b]=PyInt_AsLong(n);
                                Py_XDECREF(n);
                               }
                               Py_XDECREF(element);
                             }
                             ib->push_back(ind[0]);
                             ib->push_back(ind[1]);
                             ib->push_back(ind[2]);
                             if(len2>3)
                             {
                                 ib->push_back(ind[3]);
                                 mesh->setPrimitiveType(GL_QUADS);
                             }
                             else mesh->setPrimitiveType(GL_TRIANGLES);

                        }
                        else
                        if(i==2)
                        {
                         for(int b=0;b<2;b++)
                         {
                          if(PyNumber_Check(element=PySequence_GetItem(sub,b)))
                           {
                             PyObject* n=PyNumber_Float(element);
                             tcoord[b]=PyFloat_AsDouble(n);
                             Py_XDECREF(n);
                           }
                           Py_XDECREF(element);
                         }
                         texture->push_back(Math::Vector2D<float>(tcoord[0],tcoord[1]));
                        }
                        else
                        if( i==3)
                        {
                         for(int b=0;b<3;b++)
                         {
                          if(PyNumber_Check(element=PySequence_GetItem(sub,b)))
                           {
                             PyObject* n=PyNumber_Float(element);
                             coord[b]=PyFloat_AsDouble(n);
                             Py_XDECREF(n);
                           }
                           Py_XDECREF(element);
                         }
                         normal->push_back(Math::Vector3D<float>(coord[0],coord[1],coord[2]));
                        }
                        else
                        if( i==4)
                        {
                         for(int b=0;b<3;b++)
                         {
                          if(PyNumber_Check(element=PySequence_GetItem(sub,b)))
                           {
                             PyObject* c=PyNumber_Float(element);
                             coord[b]=PyFloat_AsDouble(c);
                             Py_XDECREF(c);
                           }
                           Py_XDECREF(element);
                         }
                         color->push_back(Math::Vector3D<float>(coord[0],coord[1],coord[2]));
                        }
                     }
                     Py_XDECREF(sub);
                  }
             if(i==2&&!len1) { vb->disable_vertex_attribute(Base::vertex_attribute_id_texture_coordinate);}
             if(i==3&&!len1) { vb->disable_vertex_attribute(Base::vertex_attribute_id_normal);}
             if(i==4&&!len1) { vb->disable_vertex_attribute(Base::vertex_attribute_id_color);}
            }
            }
            mesh->LockBuffers(false);
    }
    Py_RETURN_NONE;
}

PyObject* El3dPythonBindings::ModelAngle( PyObject *self,PyObject *args)
{
        ModelClass* _self=(ModelClass*)self;
        Math::Vector3D<float> & res=_self->node->Angle();
        float x,y,z;
        unsigned char isx=1,isy=1,isz=1;
        return Py_BuildValue("(fff)",res.x(),res.y(),res.z());
}

PyObject* El3dPythonBindings::ModelSize( PyObject *self,PyObject *args)
{
        ModelClass* _self=(ModelClass*)self;
        Math::Vector3D<float> & res=_self->node->Size();
        float x,y,z;
        unsigned char isx=1,isy=1,isz=1;
        return Py_BuildValue("(fff)",res.x(),res.y(),res.z());
}

PyObject* El3dPythonBindings::ModelPosition( PyObject *self,PyObject *args)
{
        ModelClass* _self=(ModelClass*)self;
        Math::Vector3D<float> & res=_self->node->Position();
        float x,y,z;
        unsigned char isx=1,isy=1,isz=1;
        return Py_BuildValue("(fff)",res.x(),res.y(),res.z());
}


PyObject* El3dPythonBindings::ModelSaveTo3DS( PyObject *self,PyObject *args)
{
    const char* file_name;
    if(PyArg_ParseTuple(args,"s",&file_name))
    {
        ModelClass* _self=(ModelClass*)self;
        _self->node->GetSubMesh(0)->SaveTo3DS(file_name,_self->node->GetName());
    }
    Py_RETURN_NONE;
}


PyObject* El3dPythonBindings::ModelClear( PyObject *self,PyObject *args)
{
    int i=0;
    if(PyArg_ParseTuple(args,"|i",&i))
    {
        ModelClass* _self=(ModelClass*)self;
        _self->node->GetSubMesh(i)->LockBuffers(true);
        _self->node->GetSubMesh(i)->GetVertices()->disable_all_vertex_attributes();
        _self->node->GetSubMesh(i)->GetIndices()->resize(0);
        _self->node->GetSubMesh(i)->LockBuffers(false);
    }
    Py_RETURN_NONE;
}

PyObject* El3dPythonBindings::ColoredPolylineNew(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    ColoredPolyline* self=(ColoredPolyline*)PyType_GenericNew(type,args,kwds);
    char* group_name;
    if(PyArg_ParseTuple(args,"s",&group_name))
    {
        self->node=dynamic_cast<Scene::ColoredLinesGroup*>(static_scene->GetFirstByName(group_name));
        if(!self->node)
        {
            self->node=static_scene->AddColoredLinesGroup();
            self->node->SetName(group_name);
        }
    }
    return (PyObject*)self;
}

PyObject* El3dPythonBindings::ColoredPolylineSetVisiblity( PyObject *self,PyObject *args)
{
    ColoredPolyline* _self=(ColoredPolyline*)self;
    bool visible;
    if(PyArg_ParseTuple(args,"b",&visible)) _self->node->SetVisiblity(visible);
    Py_RETURN_NONE;
}

PyObject* El3dPythonBindings::ColoredPolylineAddLine(PyObject *self, PyObject *args)
{
    ColoredPolyline* _self=(ColoredPolyline*)self;
    float a1,a2,a3,b1,b2,b3,c1,c2,c3;
    if(PyArg_ParseTuple(args,"(fff)(fff)|(fff)",&a1,&a2,&a3,&b1,&b2,&b3,&c1,&c2,&c3))
    {
        _self->node->AddLine(Scene::ColoredLine(Math::Vector3D<float>(a1,a2,a3),Math::Vector3D<float>(b1,b2,b3),Base::Color<float>(c1,c2,c3)));
    }
    Py_RETURN_NONE;
}

PyObject* El3dPythonBindings::ColoredPolylineSetNormal(PyObject *self, PyObject *args)
{
    ColoredPolyline* _self=(ColoredPolyline*)self;
    float a1,a2,a3;
    if(PyArg_ParseTuple(args,"(fff)",&a1,&a2,&a3))
    {
        _self->node->SetNormal(Math::Vector3D<float>(a1,a2,a3));
    }
    Py_RETURN_NONE;
}

PyObject* El3dPythonBindings::ColoredPolylineClear(PyObject *self, PyObject *args)
{
    ColoredPolyline* _self=(ColoredPolyline*)self;
    _self->node->Clear();
    Py_RETURN_NONE;
}

PyObject* El3dPythonBindings::ColoredPolylineSetWidth(PyObject *self, PyObject *args)
{
    ColoredPolyline* _self=(ColoredPolyline*)self;
    float width;
    if(PyArg_ParseTuple(args,"f",&width))
    {
        _self->node->SetWidth(width);
    }
    Py_RETURN_NONE;
}

void El3dPythonBindings::InitModule()
{
   //Module Initialization
   static PyMethodDef methods[]=
   {
        {"GetCommonVariableValuef",GetCommonVariableValuef,METH_VARARGS,NULL},
        {"GetCommonVariableValueb",GetCommonVariableValueb,METH_VARARGS,NULL},
        {"GetCommonVariableValueI",GetCommonVariableValueI,METH_VARARGS,NULL},
        {"GetCommonVariableValueS",GetCommonVariableValueS,METH_VARARGS,NULL},
        {"IsCommonVariableSet",IsCommonVariableSet,METH_VARARGS,NULL},
        {"setClassesRelations",setClassesRelations,METH_VARARGS,NULL},
        {"DrawPolyline",DrawPolyline,METH_VARARGS,NULL},
        {"DrawTexture",DrawTexture,METH_VARARGS,NULL},
        {"TextureSize",TextureSize,METH_VARARGS,NULL},
        {"CSGUnion",CSGUnion,METH_VARARGS,NULL},
        {"CSGDifference",CSGDifference,METH_VARARGS,NULL},
        {"CSGIntersection",CSGIntersection,METH_VARARGS,NULL},
        {"CSGSlice",CSGSlice,METH_VARARGS,NULL},
        {NULL}
   };

   //class Model
   static PyMethodDef model_methods[]=
   {
       {"Rotate",ModelRotate,METH_VARARGS,NULL},
       {"Scale",ModelScale,METH_VARARGS,NULL},
       {"SetAngle",ModelSetAngle,METH_VARARGS,NULL},
       {"SetSize",ModelSetSize,METH_VARARGS,NULL},
       {"SetPosition",ModelSetPosition,METH_VARARGS,NULL},
       {"SetVisiblity",ModelSetVisiblity,METH_VARARGS,NULL},
       {"SetViewMode",ModelSetViewMode,METH_VARARGS,NULL},
       {"Angle",ModelAngle,METH_VARARGS,NULL},
       {"Size",ModelSize,METH_VARARGS,NULL},
       {"Position",ModelPosition,METH_VARARGS,NULL},
       {"Clear",ModelClear,METH_VARARGS,NULL},
       {"SetSurface",ModelSetSurface,METH_VARARGS,NULL},
       {"SetTexture",ModelSetTexture,METH_VARARGS,NULL},
       {"InitTexture",ModelInitTexture,METH_VARARGS,NULL},
        {"ClearTexture",ModelInitTexture,METH_VARARGS,NULL},
       {"SetParent",ModelSetParent<ModelClass>,METH_VARARGS,NULL},
       {"BeginDrawOnTexture",ModelBeginDrawOnTexture,METH_VARARGS,NULL},
       {"EndDrawOnTexture",ModelEndDrawOnTexture,METH_VARARGS,NULL},
       {"AddSubMesh",ModelAddSubMesh,METH_VARARGS,NULL},
       {"SaveTo3DS",ModelSaveTo3DS,METH_VARARGS,NULL},
       {"LoadFrom3DS",ModelLoadFrom3DS,METH_VARARGS,NULL},
       {NULL}
   };
   memset(&model_type,0,sizeof(model_type));
   model_type.tp_name="PyEl3d.Model";
   model_type.tp_basicsize=sizeof(ModelClass);
   model_type.tp_flags=Py_TPFLAGS_DEFAULT;
   model_type.tp_new=ModelNew;
   model_type.tp_dealloc=ModelDel;
   model_type.tp_methods=model_methods;
   PyType_Ready(&model_type);

   //class ColoredPolyline
   static PyMethodDef coloredpolyline_methods[]=
   {
       {"AddLine",ColoredPolylineAddLine,METH_VARARGS,NULL},
       {"Clear",ColoredPolylineClear,METH_VARARGS,NULL},
       {"SetWidth",ColoredPolylineSetWidth,METH_VARARGS,NULL},
       {"SetVisiblity",ColoredPolylineSetVisiblity,METH_VARARGS,NULL},
       {"SetNormal",ColoredPolylineSetNormal,METH_VARARGS,NULL},
       {"SetParent",ModelSetParent<ColoredPolyline>,METH_VARARGS,NULL},
       {NULL}
   };

   memset(&coloredpolyline_type,0,sizeof(coloredpolyline_methods));
   coloredpolyline_type.tp_name="PyEl3d.ColoredPolyline";
   coloredpolyline_type.tp_basicsize=sizeof(ColoredPolyline);
   coloredpolyline_type.tp_flags=Py_TPFLAGS_DEFAULT;
   coloredpolyline_type.tp_new=ColoredPolylineNew;
   coloredpolyline_type.tp_methods=coloredpolyline_methods;
   PyType_Ready(&coloredpolyline_type);

   PyObject* module=Py_InitModule("PyEl3d",methods);
   PyModule_AddObject(module,"Model",(PyObject *)&model_type);
   PyModule_AddObject(module,"ColoredPolyline",(PyObject *)&coloredpolyline_type);
}

El3dPythonBindings::El3dPythonBindings(Kongomato::Scene::Manager * scene)
{
   assert(scene);
   Py_Initialize();
   El3dPythonBindings::InitModule();
   this->scene=scene;
   csg=new carve::csg::CSG;
}

El3dPythonBindings::~El3dPythonBindings()
{
    Py_Finalize();
}

void El3dPythonBindings::ExecuteFile(const QString & filen,const QString & scripts_path)
{
        PreExec(scripts_path);
        FILE* f=fopen (filen.toLocal8Bit().data(),"r");
        if(!f) throw Elasticas::Exception("Read the console output for details");
        PyRun_SimpleFile(f,"r");
        fclose(f);
        PostExec();
}

void El3dPythonBindings::ExecuteString(const QString & str,const QString & scripts_path)
{
        PreExec(scripts_path);
        if(PyRun_SimpleString(str.toLocal8Bit().data())!=0) throw  Elasticas::Exception("Read the console output for details");
        PostExec();
}

void El3dPythonBindings::PreExec(const QString & scripts_path)
{
        El3dPythonBindings::static_scene=this->scene;
        if(PyRun_SimpleString(("import sys\nif '"+QDir::currentPath()+"/"+scripts_path+"' not in sys.path: sys.path.append('"+QDir::currentPath()+"/"+scripts_path+"')\n").toLocal8Bit().data())!=0)
            throw Elasticas::Exception("Read the console output for details");
}

void El3dPythonBindings::PostExec()
{
        PyGC_Collect();
}

VideoDevice::DrawTarget* El3dPythonBindings::last_draw_target=NULL;
Kongomato::Scene::Manager* El3dPythonBindings::static_scene=NULL;
carve::csg::CSG* El3dPythonBindings::csg=NULL;
PyTypeObject El3dPythonBindings::model_type;
PyTypeObject El3dPythonBindings::coloredpolyline_type;


