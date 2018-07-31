#include "el3dmainwindow.h"

//________________________________________________
El3dMainWindow::El3dMainWindow(Kongomato::Scene::Manager* scene)
{
    using namespace Kongomato;
    this->scene=scene;
    VideoDevice::Manager* videodevice=VideoDevice::Manager::Instance();
    VideoDevice::Qt4Context* context=dynamic_cast<VideoDevice::Qt4Context*>(videodevice->ChangeContext(VideoDevice::Qt4_Context));
    viewport=context->GenerateWidget<El3dViewport>();
    viewport->setScene(scene);
    this->setLayout(new QVBoxLayout);
    toolbar=new QToolBar;
    this->meshes_combobox=new QComboBox;
    this->meshes_combobox->setFixedWidth(150);
    this->model_color_dialog=new QColorDialog;
    QObject::connect(this->meshes_combobox,SIGNAL(currentIndexChanged(int)),this,SLOT(syncMeshProperties()));
    toolbar->addWidget(this->meshes_combobox);
    texture_file_dialog=new QFileDialog;
    texture_file_dialog->setAcceptMode(QFileDialog::AcceptOpen);
    toggle_points_action=toolbar->addAction(QIcon("images/show_vertices.png"),trUtf8("Отображать точки"));
    toggle_grid_action=toolbar->addAction(QIcon("images/show_wireframe.png"),trUtf8("Отображать сетку"));
    toggle_surface_action=toolbar->addAction(QIcon("images/show_solid.png"),trUtf8("Отображать поверхность"));
    toggle_lighting=toolbar->addAction(QIcon("images/show_shading.png"),trUtf8("Включить затенение"));
    show_color_dialog=toolbar->addAction(trUtf8("Цвет"));
    show_texture_dialog=toolbar->addAction(trUtf8("Фактура"));
    toggle_points_action->setCheckable(true);
    toggle_grid_action->setCheckable(true);
    toggle_surface_action->setCheckable(true);
    toggle_lighting->setCheckable(true);
    QObject::connect(toggle_points_action,SIGNAL(toggled(bool)),this,SLOT(toggleMeshProperty(bool)));
    QObject::connect(toggle_grid_action,SIGNAL(toggled(bool)),this,SLOT(toggleMeshProperty(bool)));
    QObject::connect(toggle_surface_action,SIGNAL(toggled(bool)),this,SLOT(toggleMeshProperty(bool)));
    QObject::connect(toggle_lighting,SIGNAL(toggled(bool)),this,SLOT(toggleLighting(bool)));
    QObject::connect(texture_file_dialog,SIGNAL(accepted()),this,SLOT(setCurrentModelTexture()));
    QObject::connect(show_texture_dialog,SIGNAL(triggered()),texture_file_dialog,SLOT(exec()));
    QObject::connect(model_color_dialog,SIGNAL(accepted()),this,SLOT(setCurrentModelColor()));
    QObject::connect(show_color_dialog,SIGNAL(triggered()),model_color_dialog,SLOT(exec()));
    toggle_lighting->setChecked(true);

    this->layout()->addWidget(header=new QLabel(trUtf8("3D-эскиз")));
    header->setMaximumHeight(header->sizeHint().height());
    this->layout()->addWidget(toolbar);
    this->layout()->addWidget(viewport);
    header->setStyleSheet("*{font-weight:bold;}");
}

void El3dMainWindow::clearMeshesList()
{
    this->meshes_combobox->clear();
}

void El3dMainWindow::addMeshToList(const QString & name,int order)
{
    const Elasticas::CommonData & vars=Elasticas::Core::Instance()->commonVariables();
    QString hr_name=vars[name+"Name"].toString();
    if(hr_name.isEmpty()) hr_name=QString(name).remove(":");
    if(order<0)
    {
        this->meshes_combobox->insertItem(0,hr_name,name);
        this->meshes_combobox->setCurrentIndex(0);
    }
    else this->meshes_combobox->addItem(hr_name,name);
}

void El3dMainWindow::updateContent()
{
    viewport->updateContent();
}

Kongomato::Scene::Mesh* El3dMainWindow::currentMesh()
{
    if(meshes_combobox->currentIndex()<0) return NULL;
    QString mesh_name=meshes_combobox->itemData(meshes_combobox->currentIndex()).toString().remove(":");
    return dynamic_cast<Kongomato::Scene::Mesh*>(this->scene->GetFirstByName(mesh_name.toStdString()));
}

void El3dMainWindow::toggleMeshProperty(bool on)
{
    Kongomato::Scene::Mesh* mesh=this->currentMesh();
    if(mesh)
    {
        QAction* action=dynamic_cast<QAction*>(QObject::sender());
        Kongomato::Scene::mesh_draw_flags draw_flags=mesh->GetDrawFlags();
        if(action==toggle_points_action)
        {
            if(on) mesh->SetDrawFlags(draw_flags|Kongomato::Scene::mesh_draw_points);
            else  mesh->SetDrawFlags(draw_flags&(~Kongomato::Scene::mesh_draw_points));
        }
        else if(action==toggle_grid_action)
        {
            if(on) mesh->SetDrawFlags(draw_flags|Kongomato::Scene::mesh_draw_wireframe);
            else  mesh->SetDrawFlags(draw_flags&(~Kongomato::Scene::mesh_draw_wireframe));
        }
        else if(action==toggle_surface_action)
        {
            if(on) mesh->SetDrawFlags(draw_flags|Kongomato::Scene::mesh_draw_solid);
            else  mesh->SetDrawFlags(draw_flags&(~Kongomato::Scene::mesh_draw_solid));
        }
        this->meshVisiblityChanged(mesh->GetName().c_str(),mesh->GetDrawFlags()!=Kongomato::Scene::mesh_draw_none);
    }
    this->updateContent();
}

void El3dMainWindow::toggleLighting(bool on)
{
    viewport->setLighting(on);
}

void El3dMainWindow::syncMeshProperties()
{
    if(meshes_combobox->currentIndex()<0) return;
    QString mesh_name=meshes_combobox->itemData(meshes_combobox->currentIndex()).toString().remove(":");
    Kongomato::Scene::Mesh* mesh=dynamic_cast<Kongomato::Scene::Mesh*>(this->scene->GetFirstByName(mesh_name.toStdString()));
    toggle_points_action->setEnabled(mesh!=NULL);
    toggle_grid_action->setEnabled(mesh!=NULL);
    toggle_surface_action->setEnabled(mesh!=NULL);
    if(mesh)
    {
        toggle_points_action->setChecked((mesh->GetDrawFlags()&Kongomato::Scene::mesh_draw_points)==Kongomato::Scene::mesh_draw_points);
        toggle_grid_action->setChecked((mesh->GetDrawFlags()&Kongomato::Scene::mesh_draw_wireframe)==Kongomato::Scene::mesh_draw_wireframe);
        toggle_surface_action->setChecked((mesh->GetDrawFlags()&Kongomato::Scene::mesh_draw_solid)==Kongomato::Scene::mesh_draw_solid);
    }
}

void El3dMainWindow::setCurrentModelColor()
{
    Kongomato::Scene::Mesh* mesh=this->currentMesh();
    Kongomato::Scene::Mesh* sleeve_mesh=dynamic_cast<Kongomato::Scene::Mesh*>(this->scene->GetFirstByName("Sleeve"));
    if(mesh)
    {
        QPixmap pixmap(8,8);
        //qDebug()<<model_color_dialog->currentColor();
        pixmap.fill(model_color_dialog->currentColor());

        pixmap.save("images/temp.png");
        mesh->GetSubMesh(0)->InitializeTexture("images/temp.png");
        if(sleeve_mesh) sleeve_mesh->GetSubMesh(0)->InitializeTexture("images/temp.png");

    }
}

void El3dMainWindow::setCurrentModelTexture()
{
    Kongomato::Scene::Mesh* mesh=this->currentMesh();
    Kongomato::Scene::Mesh* sleeve_mesh=dynamic_cast<Kongomato::Scene::Mesh*>(this->scene->GetFirstByName("Sleeve"));
    if(mesh) mesh->GetSubMesh(0)->InitializeTexture(texture_file_dialog->selectedFiles().first().toStdString());
    if(sleeve_mesh) sleeve_mesh->GetSubMesh(0)->InitializeTexture(texture_file_dialog->selectedFiles().first().toStdString());

}


