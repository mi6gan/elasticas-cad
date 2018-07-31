/**  \file elplugin.h
  *  \author M. S. Boyarov
  */
#ifndef ELPLUGIN_H
#define ELPLUGIN_H
#include <QDebug>
#include <QLibrary>
#include <QToolBar>
#include <QVector>
#include <QHash>
#include "elbasicdialogs.h"
#ifdef Q_WS_WIN
#define EXPORTSPEC __declspec(dllexport)
#else
#define EXPORTSPEC
#endif
namespace Elasticas
{
    /** Provides interface for creating own plugins to embed it into El3D System.  Here are such functions as adding
     *  new dialogs and viewport widgets into El3D System main window and also update method that purposed to provide ablility
     *  for reacting when system's states change.
    */
    class DLL_DECLSPEC Plugin
    {        
        // QVector<QPair<QAction*, Dialog*> > actions;
        QList<QWidget*> viewports;
        QList<QPair<Elasticas::DockDialog*,QString > > dockdialogs;
        QList<QPair<Elasticas::Dialog*,QString > > dialogs;
        QList<QPair<QAction*,QString > > actions;
        QHash<const QAction*, QString> garment_type_dependent_actions;
     protected:
        QString name;
        QSet<QString> garment_names;
     public:

        const QList <QPair<Elasticas::DockDialog*,QString > > & dockDialogs();
        const QList <QPair<Elasticas::Dialog*,QString > > & dialogsList();
        const QList<QPair<QAction*,QString > > & actionsList();
        const QList<QWidget*> & viewportsList();

          /**
           Adds action (tool button) to menu identified by name.
           \warning this method is deprecated, use Plugin:addDialog() instead.
           \param menu_name menu name,
           \param action action to add,
           \param garment_type_value name of garment type for which the action is active,
           \param  dialog dialog for garment parameters dock widget.
        */
        void AddAction(const QString & deprecated,QAction* action,const QString & classname);

        /**
          Adds widget to main window viewport area.
          \param viewport_widget widget to add.
        */
        void addViewport(QWidget* viewport_widget);

        /**
          \warining this method is deprecated, use Plugin:addViewport() instead.
        */
        void AddViewport(QWidget* viewport_widget);

        /**
          Adds basic dialog into toolbar tab of main menu.
          \param dialog dialog to add
          \param toolbar_name name of toolbar tab
        */
        void addDialog(Elasticas::Dialog* dialog,const QString & toolbar_name);

        /**
          Adds special dockable dialog into toolbar tab of main menu.
          \param dialog dialog to add
          \param toolbar_name name of toolbar tab
        */
        void addDockDialog(Elasticas::DockDialog* dialog,const QString & toolbar_name);

        /**
          Adds QDialog into toolbar tab of main menu.
          \param dialog QDialog dialog to add
          \param toolbar_name name of toolbar tab
        */
        void addQDialog(QDialog* dialog,const QString & toolbar_name,const QString & classname="");


        void setPluginName(const QString & name);

        /**
          \warining this method is deprecated, use  Plugin::setPluginName() instead.
        */
        void SetName(const QString & name);

        const QString & pluginName();

        /**
          \warining this method is deprecated, use  Plugin::pluginName() instead.
        */
        const QString & GetName();

        /**
           Called by Elasticas::Dialog::apply() method or when current active Core::ObjectClass ("object class") is switched. Implement your own Core::update() if needed.
          \see Elasticas::Core::objectClasses(), Elasticas::Core::CommonVariables(), Elasticas::Dialog::commonValue()
        */
        virtual void update();

        /**
          \warining this method is deprecated, use  Plugin::update() instead.
        */
        virtual void Update();
    };
}

#endif // ELPLUGIN_H
