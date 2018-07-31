#ifndef C2DKERNEL_H
#define C2DKERNEL_H

#include <QDir>
#include <QHash>
#include <QDebug>
#include <QObject>
#include <QLibrary>
#include <QToolBar>
#include <QMessageBox>
#include <QFileDialog>
#include <QHashIterator>
#include <QCoreApplication>

#include "Frameworks/Items/include/C2DItemDialog.h"
#include "Frameworks/Items/include/C2DItem.h"
#include "Frameworks/Items/include/C2DLibrary.h"
#include "Frameworks/Items/include/C2DManager.h"
#include "Frameworks/Items/include/C2DVariable.h"
#include "C2DCommon.h"
#include "C2DPlugin.h"

#define LIBRARIES_PATH QString( "lib" )

class C2DKernel : public QObject
{

    Q_OBJECT

public:
    C2DKernel();
    ~C2DKernel();

    void saveSheet( const QString & name, QList< QPair< C2DVariable *, QVariant > > list );
    void exportDXF( const QString & name, C2DItem * item );

    inline QHash< QString, C2DItem * > importItems()  {  return this->kernel_items;  }

    QList< QActionGroup * >  actions();
    QList<QPair<Elasticas::DockDialog *,QString> > elDialogs();
    QList< QToolBar * > toolbars();

public slots:

protected:

private:
    void init();

    QLibrary Liblink;

    bool eventFilter( QObject * obj, QEvent * e );

    C2DCommon * kernel_common_dialog;

    QHash< QString, C2DItem * >       kernel_items;
    QHash< QString, C2DPlugin * >     kernel_plugins;
    QHash< QString, C2DManager * >    kernel_managers;
    QHash< QString, C2DLibrary * >    kernel_libraries;
    QHash< QString, C2DItemDialog * > kernel_item_dialogs;

};

#endif //C2DKernel
