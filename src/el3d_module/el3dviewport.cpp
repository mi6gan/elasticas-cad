#include "el3dviewport.h"
using namespace Kongomato;
El3dViewport::El3dViewport(Kongomato::VideoDevice::Qt4Context* context,QGLWidget * shareWidget,QWidget * parent):Kongomato::VideoDevice::GLWidget(context,shareWidget,parent)
{
    this->inited=false;
    camera_angle=Kongomato::Math::Vector2D<float>(-M_PI_4,M_PI_4);
    camera_distance=100.0f;
    this->setMouseTracking(true);
    this->lighting=false;
}

void El3dViewport::initScene()
{
    if(!scene) return;
    VideoDevice::Manager* videodevice=VideoDevice::Manager::Instance();
    Scene::SimpleMesh* mesh;
    scene->SetBackgroundColor(Kongomato::Base::Color<double>(0.5f,0.5f,0.5f,0.0f));
    scene->GetLight(0).SetAttenuations(20,0,0);
    videodevice->SetTransform(VideoDevice::projection_transformation,Math::Matrix4x4<float>::PerspectiveView(M_PI/3.0f,4.0f/3.0f,1.0f,100.0f));
    scene->SetCameraTaget(mesh=scene->AddSimpleMesh(""));
    mesh->SetName("MainTarget");
    mesh=scene->AddSimpleMesh("");
    mesh->SetName("MainMask");
}

void El3dViewport::setup()
{
 Kongomato::VideoDevice::Manager* videodevice=Kongomato::VideoDevice::Manager::Instance();
 if(!inited)
 {
    videodevice->SetUintParameter(VideoDevice::depthfunc_parameter,GL_GEQUAL);
    videodevice->SetUintParameter(VideoDevice::clearcolor_parameter,0x888888FF);
    videodevice->SetFloatParameter(VideoDevice::cleardepth_parameter,-1.0f);
    videodevice->SetBoolParameter(VideoDevice::lighting_parameter,true);
    videodevice->SetBoolParameter(VideoDevice::cullface_parameter,false);
    videodevice->SetAspectHValue(3);
    videodevice->SetAspectWValue(4);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_NORMALIZE);
    glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL,GL_SEPARATE_SPECULAR_COLOR);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_MULTISAMPLE);
    //glEnable(GL_CULL_FACE);
    glLineWidth(1.0f);
    if(scene)
    {
        Scene::Light& l1=scene->GetLight(0);
        Scene::Light& l2=scene->GetLight(1);
        // Scene::Light& l3=scene->GetLight(2);
        scene->InitLights();

        l1.Enable();
        l1.SetDirectional(Math::Vector3D<float>(0.25,0.0,0.25));
        l2.Enable();
        l2.SetDirectional(Math::Vector3D<float>(-1,0.0,0.25));
    //    l2.SetDiffuse(Base::Color<float>(1,1,1,0));
    }

    inited=true;


 }
    if(this->lighting) glEnable(GL_LIGHTING);
    else glDisable(GL_LIGHTING);
}

void El3dViewport::paintGL()
{
    using namespace Kongomato;
    if(!scene) return;
    VideoDevice::GLWidget::paintGL();
    VideoDevice::Manager* dev=Kongomato::VideoDevice::Manager::Instance();
    Base::Camera* camera=&scene->GetCamera();
    Scene::Node* camera_target=scene->GetCameraTarget();
   if(camera_target)
   {
       camera_target->Angle().y()=camera_angle.y();
       camera_target->SetPosition(camera_position.x(),camera_position.y(),camera_position.z());
   }
   camera->SetDist(camera_distance);
   camera->SetAngle(camera_angle.x(),0,0);
   this->setup();
   const Base::VideoMode & videomode=dev->GetCurrentContext()->GetVideoMode();
   scene->Draw();
   this->output_matrix=dev->GetViewProjectionMatrix();

   //dev->Clear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   // tx->Draw();
   //dev->Present();
}

void El3dViewport::setScene(Kongomato::Scene::Manager* scene)
{
    this->scene=scene;
    this->initScene();
}

void El3dViewport::rotateCamera(float dx,float dy)
{
    camera_angle.x()+=dx;
    camera_angle.y()+=dy;
}

void El3dViewport::zoomCamera(float step)
{
    camera_distance+=step;
}

void El3dViewport::mouseMoveEvent ( QMouseEvent * event )
{
    last_mouse_pos=event->pos();
    if(!scene) return;
    if((event->buttons()&Qt::RightButton)==Qt::RightButton)
    {
        this->camera_position.y()+=(event->pos().y()-camera_rotate_cursor.y());
        this->updateGL();
    }

    if((event->buttons()&Qt::LeftButton)==Qt::LeftButton)
    {
        //float cameraz=scene->GetCamera().Dist()+100.0f*float(event->pos().y()-camera_rotate_cursor.y())/(this->height());
      //  scene->GetCameraTarget()->Angle().y()+=float(event->pos().x()-camera_rotate_cursor.x())/100.0f;
        camera_angle.y()+=float(event->pos().x()-camera_rotate_cursor.x())/100.0f;

    //mouse wrapping
        if(event->x()<=0)
        {
           camera_rotate_cursor=QPoint(this->width()-2,event->pos().y());
           QCursor::setPos(this->mapToGlobal(camera_rotate_cursor));
           return;
        }
        if(event->x()>=this->width()-1)
        {
           camera_rotate_cursor=QPoint(1,event->pos().y());
           QCursor::setPos(this->mapToGlobal(camera_rotate_cursor));
           return;
        }
        if(event->y()<=0)
        {
           camera_rotate_cursor=QPoint(event->pos().x(),this->height()-2);
           QCursor::setPos(this->mapToGlobal(camera_rotate_cursor));
           return;
        }
        if(event->y()>=this->height()-1)
        {
           camera_rotate_cursor=QPoint(event->pos().x(),1);
           QCursor::setPos(this->mapToGlobal(camera_rotate_cursor));
           return;
        }


 //mouse wrapping
        if(camera_distance>=5.0f)
        {
            camera_distance+=+100.0f*float(event->pos().y()-camera_rotate_cursor.y())/(this->height());
            this->updateGL();
        }
        else camera_distance=5.0f;
    }
    camera_rotate_cursor=event->pos();
}

void El3dViewport::mousePressEvent ( QMouseEvent * event )
{
    camera_rotate_cursor=event->pos();
    this->setCursor(Qt::BlankCursor);
}

void El3dViewport::mouseReleaseEvent ( QMouseEvent * event )
{
    this->unsetCursor();
}

void El3dViewport::wheelEvent(QWheelEvent* event)
{
    //Kongomato::Scene::Manager* scene=Graphics::Instance()->GetScene();
    if(event->delta()!=0)
    {
        Math::Vector3D<float> limup(M_PI_2-0.01f,0,0);
        Math::Vector3D<float> limdown(-M_PI_2+0.01f,0,0);
        double new_cax=camera_angle.x()+float(event->delta())/3000.0f;
        if(new_cax<M_PI_2-0.01f&&new_cax>-M_PI_2+0.01f) camera_angle.x()=new_cax;

        //scene->GetCamera().Rotate(float(event->delta())/3000.0f,0,0,&limup,&limdown);
        this->updateGL();
    }
}

void El3dViewport::updateContent()
{
    this->update();
}

void El3dViewport::setLighting(bool on)
{
    this->lighting=on;
    this->update();
}

