#include "el3d.h"
El3dPlugin::El3dPlugin()
{
    Kongomato::Scene::Manager* scene=new Kongomato::Scene::Manager("El3d scene");
    this->addViewport(mainwindow=new El3dMainWindow(scene));
    QObject::connect(mainwindow,SIGNAL(meshVisiblityChanged(QString,bool)),this,SLOT(meshVisiblityChanged(QString,bool)));
    python_bindings=new El3dPythonBindings(scene);
}

void El3dPlugin::update()
{
        this->mainwindow->setCursor(QCursor(Qt::WaitCursor));
        const Elasticas::CommonData & vars=Elasticas::Core::Instance()->CommonVariables();
        {
            Elasticas::Core::ObjectClass* object,*parent_object;
            mainwindow->clearMeshesList();
            foreach(object,Elasticas::Core::Instance()->objectClasses())
            {
                QString name=object->className();
                try
                {
                    QString pure_classname=QString(name).remove(':');
                    QString parents_list;
                    foreach(parent_object,object->parentsList()) parents_list=parents_list+'\"'+QString(parent_object->className()).remove(":")+'\"'+",";

                    if(object->isEnabled()&&object->isChanged())
                    {
                        python_bindings->ExecuteString("import MeshBuilder\nMeshBuilder.update(name=\""+pure_classname+"\",bearing_models=["+parents_list+"])");
                    }
                    python_bindings->ExecuteString("import MeshBuilder \nMeshBuilder.update(name=\""+pure_classname+"\",visible="+QString().setNum(object->isEnabled())+")");
                }
                catch(const Elasticas::Exception & e)
                {
                    QMessageBox(QMessageBox::Warning,"Error",QString("Oops, something has gone wrong with 3d output scrpits while building \"")+vars["CurrentGarment"].toString()+"\". "+e.what()).exec();
                }
                if(object->isEnabled()) mainwindow->addMeshToList(name,vars[name+"Level"].toInt());
            }
        }
        //model_tool_bar->Update();
        //viewport3d->Update();

    mainwindow->updateContent();
    this->mainwindow->setCursor(QCursor(Qt::ArrowCursor));
}

void El3dPlugin::meshVisiblityChanged(const QString& mesh_name,bool visible)
{
    python_bindings->ExecuteString("import MeshBuilder \nMeshBuilder.update(name=\""+mesh_name+"\",visible="+QString().setNum(visible)+")");
}

Elasticas::Plugin* GetPlugin()
{
    return new El3dPlugin;
}
