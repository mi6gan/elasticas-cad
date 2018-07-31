#include "C2DKernel.h"

C2DKernel::C2DKernel()
{
    foreach( C2DManager * p, this->kernel_managers )
        p->installEventFilter( this );

    this->kernel_common_dialog = new C2DCommon;

    this->init();
}

C2DKernel::~C2DKernel()
{
#if defined( Q_WS_WIN )
    if ( this->Liblink.isLoaded() )
        this->Liblink.unload();
#endif
}


void C2DKernel::saveSheet( const QString & name, QList< QPair< C2DVariable *, QVariant > > list )
{
    //using namespace Export;

    if ( list.count() == 0 )
        return;


    qWarning( QString( "%1%2" )
              .arg( "\nCannot detect whether Q_WS_WIN is defined. " )
              .arg( "\nExport to MS Word 'doc' format is possible only for MS Windows.\n" )
              .toAscii() );

    QMessageBox::warning( NULL, QObject::trUtf8( "Данная функция не доступна для вашей ОС" ),
                          QString( "%1%2")
                          .arg( "\nCannot detect whether Q_WS_WIN is defined. " )
                          .arg( "\nExport to MS Word 'doc' format is possible only for MS Windows.\n" )
                          .toAscii(), QMessageBox::Ok );


}

void C2DKernel::exportDXF( const QString & name, C2DItem * item )
{
    if ( !item )
        return;
    qWarning( QString( "Данная функция недоступна в данной сборке программы." ).toAscii() );

    qWarning( QString( "%1%2" )
              .arg( "\nCannot detect whether C2D_DXF is defined." )
              .arg( "\nExport to AutoCAD 'dxf' format is not possible.\n" )
              .toAscii() );

    QMessageBox::warning( NULL, QObject::trUtf8( "Данная функция недоступна в данной сборке программы." ),
                          QString( "%1%2")
                          .arg( "\nCannot detect whether C2D_DXF is defined." )
                          .arg( "\nExport to AutoCAD 'dxf' format is not possible.\n" )
                          .toAscii(), QMessageBox::Ok );
}

QList< QActionGroup * > C2DKernel::actions()
{
    QList< QAction * >       list_actions;
    QList< QActionGroup * >  list_groups;

    QAction       * action      = NULL;
    QActionGroup  * group       = NULL;
    C2DItemDialog * item_dialog = NULL;

    //Dialogs
    QHashIterator< QString, C2DItem * > i( this->kernel_items );

    while( i.hasNext() )
    {
        i.next();


        list_actions.clear();

        group = new QActionGroup( this );
        group->setObjectName( i.value()->prefix( false ) );

        for ( int j = 0; j < i.value()->dialogs().count(); j++ )
        {
            item_dialog = i.value()->dialogs().at( j );

            action = new QAction( item_dialog->objectName(), this );
            action->setData( item_dialog->tab() );

            QObject::connect( action, SIGNAL( triggered() ), item_dialog, SLOT( show() ) );
            QObject::connect( kernel_common_dialog, SIGNAL( state( bool ) ),
                              item_dialog, SLOT( kernelBusy( bool ) ) );
            QObject::connect( item_dialog, SIGNAL( transmitData( QHash< QString, QVariant > ) ),
                              kernel_common_dialog, SLOT( writeData( QHash< QString, QVariant > ) ) );

            qDebug() << "Dialog name: "  << action->text();
            qDebug() << "Tab name: "     << action->data().toString();
            qDebug() << "Garment type: " << group->objectName();

            item_dialog->startup();

            list_actions.append( action );
        }

        foreach( QAction * a, list_actions )
            group->addAction( a );

        list_groups.append( group );
    }

    return list_groups;
}

QList<QPair<Elasticas::DockDialog *,QString> > C2DKernel::elDialogs()
{
    QList<QPair<Elasticas::DockDialog *,QString> > el_dialogs;
    QHashIterator< QString, C2DItem * > i( this->kernel_items );
    while( i.hasNext() )
    {
        i.next();
       el_dialogs.append(i.value()->elDialogs());
    }
    return el_dialogs;
}

QList< QToolBar * > C2DKernel::toolbars()
{
    QList< QToolBar * > list;

    return list;
}

void C2DKernel::init()
{
    //The kernel will load libraries at startup.

    //Library directory
    QDir dir( QString( "%1/%2" )
              .arg( qApp->applicationDirPath() )
              .arg( LIBRARIES_PATH ) );

    C2DLibrary * lib;

    QDir path = QDir( QString( "%1/%2" )
                      .arg( QDir::currentPath() )
                      .arg( QString( "items" ) ) );

    qDebug() << "Current path to load libraries: " << path.absolutePath().toAscii();

    QStringList list;

    #if defined( Q_WS_WIN )
        list << QString( "*.dll" );
    #elif defined( Q_WS_X11 )
        list << QString( "*.so"  );
    #endif

    path.setNameFilters( list );

    qDebug() << "Libraries in folder: " << path.entryList();

    for ( int i = 0; i < path.entryList().count(); i++ )
    {
        this->kernel_items.clear();

        QFile file;

        file.setFileName( QString( "%1/%2" )
                          .arg( path.absolutePath() )
                          .arg( path.entryList().at( i ) ) );

        qDebug() << "Current library: " << file.fileName().toAscii();

        Liblink.setFileName( file.fileName() );
        Liblink.load();

        if ( Liblink.isLoaded() )
        {
            typedef C2DLibrary * ( *c ) ();
            c cl = (c) Liblink.resolve( "library" );
            if ( cl )
            {
                lib = cl();
                qDebug() << "Library: " << lib->name() << " - loaded.";

                this->kernel_libraries.insert( lib->name(), lib );
            }
        }
        else
        {
            lib = NULL;
            std::cout <<   "Library - " << Liblink.fileName().toStdString()
                      << "\nLoading failed with the reason:" << std::endl;
            std::cout << QObject::trUtf8( Liblink.errorString().toAscii() ).toStdString().c_str();
        }
    }

    foreach( C2DLibrary * l, this->kernel_libraries )
    {
        QList< C2DItem * > list = l->items();

        for ( int i = 0; i < list.count(); i++ )
        {
            qWarning() << list.at( i )->prefix( false );

            this->kernel_items.insert( list.at( i )->prefix( false ), list.at( i ) );
        }
    }

    qDebug() << "Kernel items: " << this->kernel_items;
}

bool C2DKernel::eventFilter( QObject * obj, QEvent * e )
{
    // Handles child events here
    return QObject::eventFilter( obj, e );
}
