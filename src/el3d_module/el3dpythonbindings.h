#ifndef EL3DPYTHONBINDINGS_H
#define EL3DPYTHONBINDINGS_H
#include <Python.h>
#include "elcore/elcore.h"
#include <QString>
#include <QDir>
#include <QDebug>
#include <kongoscene.h>
#ifdef SUPPORT_CARVE
    #include "carve/poly.hpp"
    #include "carve/input.hpp"
    #include "carve/csg.hpp"
#endif
using namespace Kongomato;
class El3dPythonBindings:public QObject
{
    static PyTypeObject model_type;
    static PyTypeObject coloredpolyline_type;
    Kongomato::Scene::Manager* scene;
    static Kongomato::Scene::Manager* static_scene;
#ifdef SUPPORT_CARVE
    static carve::csg::CSG* csg;
#endif
    typedef struct
    {
        PyObject_HEAD
        Scene::Mesh* node;
    } ModelClass;

    typedef struct
    {
        PyObject_HEAD
        Scene::ColoredLinesGroup* node;
    } ColoredPolyline;

    template<class NodeClass> static PyObject* ModelSetParent( PyObject *self,PyObject *args)
    {
        char* node_name;
        NodeClass* _self=(NodeClass*)self;
        if(PyArg_ParseTuple(args,"s",&node_name))
        {
            _self->node->SetParent(static_scene->GetFirstByName(node_name));
        }
        Py_RETURN_NONE;
    }
    static PyObject* GetCommonVariableValueb(PyObject *self,PyObject *args);
    static PyObject* GetCommonVariableValuef(PyObject *self,PyObject *args);
    static PyObject* GetCommonVariableValueI(PyObject *self,PyObject *args);
    static PyObject* GetCommonVariableValueS(PyObject *self,PyObject *args);
    static PyObject* IsCommonVariableSet(PyObject *self,PyObject *args);
    static PyObject* setClassesRelations(PyObject *self,PyObject *args);

#ifdef SUPPORT_CARVE 
    static PyObject* SequencesFromCarvePolyhedron(carve::poly::Polyhedron* ph,PyObject* vertices,PyObject* faces);
    static carve::poly::Polyhedron* CarvePolyhedronFromSequences(PyObject *vertices,PyObject *faces);
    static PyObject* CSGUnion(PyObject *self,PyObject *args);
    static PyObject* CSGDifference(PyObject *self,PyObject *args);
    static PyObject* CSGIntersection(PyObject *self,PyObject *args);
    static PyObject* CSGSlice(PyObject *self,PyObject *args);
#endif

    static PyObject* DrawPolyline( PyObject *self,PyObject *args);
    static PyObject* DrawTexture( PyObject *self,PyObject *args);
    static PyObject* TextureSize( PyObject *self,PyObject *args);

    static PyObject* ModelNew(PyTypeObject *type, PyObject *args, PyObject *kwds);
    static void ModelDel(PyObject *self);
    static PyObject* ModelLoadFrom3DS(PyObject *self,PyObject *args);
    static PyObject* ModelRotate( PyObject *self,PyObject *args);
    static PyObject* ModelScale( PyObject *self,PyObject *args);
    static PyObject* ModelSetVisiblity( PyObject *self,PyObject *args);
    static PyObject* ModelClearTexture( PyObject *self,PyObject *args);
    static PyObject* ModelBeginDrawOnTexture(PyObject *self,PyObject *args);
    static PyObject* ModelEndDrawOnTexture(PyObject *self,PyObject *args);
    static PyObject* ModelAddSubMesh(PyObject *self,PyObject *args);
    static PyObject* ModelSetAngle( PyObject *self,PyObject *args);
    static PyObject* ModelSetSize( PyObject *self,PyObject *args);
    static PyObject* ModelSetPosition( PyObject *self,PyObject *args);
    static PyObject* ModelSetSurface( PyObject *self,PyObject *args);
    static PyObject* ModelSetViewMode( PyObject *self,PyObject *args);
    static PyObject* ModelSetTexture( PyObject *self,PyObject *args);
    static PyObject* ModelInitTexture( PyObject *self,PyObject *args);
    static PyObject* ModelAngle( PyObject *self,PyObject *args);
    static PyObject* ModelSize( PyObject *self,PyObject *args);
    static PyObject* ModelPosition( PyObject *self,PyObject *args);
    static PyObject* ModelSaveTo3DS( PyObject *self,PyObject *args);
    static PyObject* ModelClear( PyObject *self,PyObject *args);

    static PyObject* ColoredPolylineNew(PyTypeObject *type, PyObject *args, PyObject *kwds);
    static PyObject* ColoredPolylineSetVisiblity( PyObject *self,PyObject *args);
    static PyObject* ColoredPolylineAddLine(PyObject *self, PyObject *args);
    static PyObject* ColoredPolylineSetNormal(PyObject *self, PyObject *args);
    static PyObject* ColoredPolylineClear(PyObject *self, PyObject *args);
    static PyObject* ColoredPolylineSetWidth(PyObject *self, PyObject *args);

    static VideoDevice::DrawTarget* last_draw_target;
    void PreExec(const QString & scripts_path);
    void PostExec();
    static void InitModule();
   public:
    El3dPythonBindings(Kongomato::Scene::Manager *);
    ~El3dPythonBindings();
    void ExecuteFile(const QString & filen,const QString & scripts_path="./scripts");
    void ExecuteString(const QString & filen,const QString & scripts_path="./scripts");

    //

};
#endif // EL3DPYTHONBINDINGS_H

