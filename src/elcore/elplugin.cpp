#include "elplugin.h"
namespace Elasticas
{

    void Plugin::AddAction(const QString & deprecated,QAction* action,const QString & classname)
    {
        actions.append(QPair<QAction*,QString >(action,classname+":"));
    }

    const QList <QPair<Elasticas::DockDialog*,QString > > & Plugin::dockDialogs()
    {
        return dockdialogs;
    }

    const QList <QPair<Elasticas::Dialog*,QString > > & Plugin::dialogsList()
    {
        return dialogs;
    }

    const QList<QPair<QAction*,QString > > & Plugin::actionsList()
    {
        return actions;
    }

/*
    void Plugin::AddMenu(const QString & menu_name, QWidget* menu)
    {
        this->menus[menu_name]=menu;
    }
*/
    void Plugin::addViewport(QWidget* viewport_widget)
    {
        this->viewports.push_back(viewport_widget);
    }

    void Plugin::AddViewport(QWidget* viewport_widget)
    {
        this->addViewport(viewport_widget);
    }


    void Plugin::addDialog(Elasticas::Dialog* dialog,const QString & toolbar_name)
    {
        dialogs.append(QPair<Elasticas::Dialog*,QString >(dialog,toolbar_name));
    }

    void Plugin::addDockDialog(Elasticas::DockDialog* dialog,const QString & toolbar_name)
    {
        dockdialogs.append(QPair<Elasticas::DockDialog*,QString >(dialog,toolbar_name));
    }

    void Plugin::addQDialog(QDialog* dialog,const QString & toolbar_name,const QString & classname)
    {
        dialogs.append(QPair<Elasticas::Dialog*,QString>(new SimpleDialog(dialog,dialog->windowTitle(),classname),toolbar_name));
    }

    const QList<QWidget*> & Plugin::viewportsList()
    {
        return this->viewports;
    }

    void Plugin::setPluginName(const QString & name)
    {
        this->name=name;
    }

    void Plugin::SetName(const QString & name)
    {
        this->setPluginName(name);
    }

    const QString & Plugin::pluginName()
    {
        return this->name;
    }

    const QString & Plugin::GetName()
    {
        return this->pluginName();
    }

    void Plugin::update()
    {

    }

    void Plugin::Update()
    {
        // qDebug()<<"void Plugin::Update()";
    }
}
