#ifndef EL3DMAINWINDOW_H
#define EL3DMAINWINDOW_H
#include "el3dviewport.h"
#include "elcore/elcore.h"
class El3dMainWindow : public QFrame
{
    Q_OBJECT
    QColorDialog* model_color_dialog;
    QToolBar* toolbar;
    QLabel * header;
    El3dViewport* viewport;
    QAction* toggle_points_action,*toggle_grid_action,*toggle_surface_action,*toggle_lighting,*show_color_dialog,*show_texture_dialog;
    QComboBox* meshes_combobox;
    Kongomato::Scene::Manager* scene;
    QFileDialog* texture_file_dialog;
public:
    El3dMainWindow(Kongomato::Scene::Manager* scene);
    void clearMeshesList();
    void addMeshToList(const QString & name,int order=0);
    void updateContent();
    Kongomato::Scene::Mesh* currentMesh();
private slots:
    void toggleMeshProperty(bool on);
    void toggleLighting(bool on);
    void syncMeshProperties();
    void setCurrentModelColor();
    void setCurrentModelTexture();
signals:
    void meshVisiblityChanged(const QString& mesh_name,bool visible);


};

#endif // EL3DMAINWINDOW_H
