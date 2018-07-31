#ifndef ELMAINUIWIDGET_H
#define ELMAINUIWIDGET_H
#include <QTabWidget>
#include <QLibrary>
#include <QToolBar>
#include <QAction>
#include <QMenu>
#include <QDockWidget>
#include <QComboBox>
#include <QMap>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMainWindow>
#include <QDir>
#include <QDebug>
#include <QLabel>
#include <QVector>
#include <QPair>
#include <QResizeEvent>
#include <QMetaClassInfo>
#include <QMessageBox>
#include "dialogs/fakeskirtdialog.h"
#include "dialogs/elstraightskirtdialogs.h"
#include "dialogs/elflaredskirtdialogs.h"
#include "dialogs/eltulipskirtdialogs.h"
#include "dialogs/eldressdialogs.h"
#include "dialogs/elpantsdialog.h"
#include "dialogs/eljacketdialogs.h"
#include "dialogs/elblousedialogs.h"
#include "dialogs/elrpdialogs.h"
#include "dialogs/dressdialog.h"
#include "dialogs/skirtdialog.h"
#include "elcore/elplugin.h"
namespace Elasticas
{
    class MainWindow: public QMainWindow
    {
        Q_OBJECT
        class ViewportsWidget:public QWidget
        {
            QList<QWidget*> viewports;
            virtual void resizeEvent(QResizeEvent *);
            virtual QSize sizeHint() const;
        public:
            void alignViewports(int width=-1);
            ViewportsWidget();
            void addViewport(QWidget* viewport);

        } *central_widget;
        QTabWidget* tab_menu;
        QList<QToolBar*> tabs;
        QHash<QAction*,QString> tab_actions_classnames;
        QList<QString> tabs_names;
        QList<Elasticas::Plugin*> plugins;
        QComboBox* main_classes_combobox;
        QComboBox* classes_combobox;
        QDockWidget* dialog_dock_widget;
        QPushButton* save_button,*load_button;
        QFileDialog* save_dialog,*load_dialog;
        QString current_classname;

        QPushButton* fake_button1,*fake_button2;

        int gender;
        int addTabIfNotExist(const QString & tab_name);
        void addDialog(Elasticas::Dialog* dialog,const QString & toolbar_name);
        void addDockDialog(Elasticas::DockDialog* dialog,const QString & toolbar_name);
        void addWidgetToToolbar(QWidget* widget,const QString & toolbar_name,const QString & classname="");
        void updateTabMenu();
        void updateMainClassesList();
        void loadPlugins();
        void setupDependencies();
    public:
        MainWindow();
    public slots:
        void updatePlugins();
        void updateAll();
        void updateClassesList();
        void saveLoadDialogAccepted();


        void fakeButton12();
    };
}

#endif // ELMAINUIWIDGET_H
