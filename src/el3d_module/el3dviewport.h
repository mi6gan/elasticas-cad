#ifndef EL3DVIEWPORT_H
#define EL3DVIEWPORT_H
#include <QtGui>
#include "kongovideodevice.h"
#include "kongoscene.h"
class El3dViewport:public Kongomato::VideoDevice::GLWidget
{
    Q_OBJECT
    bool inited;
    Kongomato::Math::Vector2D<float> camera_angle;
    Kongomato::Math::Vector3D<float> camera_position;
    double camera_distance;
    QPoint last_mouse_pos;
    QPoint camera_rotate_cursor;
    Kongomato::Scene::Manager* scene;
    Kongomato::Math::CommonMatrix<float> output_matrix;
    bool lighting;
    virtual void paintGL();
    virtual void mouseMoveEvent ( QMouseEvent * event );
    virtual void mousePressEvent ( QMouseEvent * event );
    virtual void mouseReleaseEvent ( QMouseEvent * event );
    virtual void wheelEvent(QWheelEvent* event);
    void rotateCamera(float dx,float dy);
    void zoomCamera(float step);
    void setup();
    void initScene();
public:
    El3dViewport(Kongomato::VideoDevice::Qt4Context* context,QGLWidget * shareWidget=0,QWidget * parent=0);
    void setScene(Kongomato::Scene::Manager* scene);
    void updateContent();
    void setLighting(bool on);
};
#endif
