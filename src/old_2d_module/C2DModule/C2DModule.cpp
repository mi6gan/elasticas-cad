#include "C2DModule.h"

Preload::Preload(QWidget *parent)
    : QWidget(parent)
{
    Qt::WindowFlags flags=0;
    Qt::WidgetAttribute attribute;
    flags |= Qt::CustomizeWindowHint;
    flags |= Qt::FramelessWindowHint;
    flags |= Qt::WindowStaysOnTopHint;
    attribute = Qt::WA_TranslucentBackground;
    this->setWindowFlags(flags);
    this->setAttribute(attribute);

    this->setGeometry(0,0,480,360);

    myPixmap = QPixmap(":/Images/Preload.png", "PNG", Qt::ColorOnly);
}

Preload::~Preload()  {  }

 void Preload::SetScreenGeometry(QRect rect)
 {
     screenGeometry=rect;
     this->move( ( screenGeometry.width() - 480 ) / 2, ( screenGeometry.height() - 360 ) / 2 );
     qDebug() << "Screen size: " <<screenGeometry << ";";
 }

void Preload::paintEvent( QPaintEvent * event )
{
    this->SetScreenGeometry( qApp->desktop()->screenGeometry(0) );

    QPainter painter(this);
    const QPointF point(0,0);
    painter.drawPixmap( point, myPixmap );
}

//C2D implementation
C2DModule::C2DModule()
    : QWidget(), Plugin()
{
    this->Initialize();
}

void C2DModule::Initialize()
{
    this->SetName(QObject::trUtf8("2D-конструкция"));

//    this->showPreload();

//    QTimer::singleShot( 20000, this, SLOT( hidePreload() ) );

    this->widget = new C2DWidget;

#if defined( C2D_UNDO )
    View = new QUndoView();
    View->hide();
#endif

    this->setMenus();
}

C2DModule::~C2DModule()
{
    delete this->widget;

#if defined( C2D_UNDO )
    delete View;
#endif
}

void C2DModule::Update()  {  this->widget->view()->UpdateCurrentObject();        }

void C2DModule::showPreload()
{
    p = new Preload;

    p->show();
}

void C2DModule::hidePreload()
{
    p->hide();

    delete p;
}

void C2DModule::setMenus()
{

    QToolBar * dialog_toolbar = new QToolBar( QObject::trUtf8( "Параметры БК" ), this->widget );

    QList< QActionGroup * > group_list = this->widget->kernel()->actions();

    QActionGroup * group = NULL;

    for ( int i = 0; i < group_list.count(); i++ )
    {
        group = group_list.at( i );

        for ( int j = 0; j < group->actions().count(); j++ )
            this->AddAction( group->actions().at( j )->text(),
                             group->actions().at( j ),
                             group->objectName() );
    }
    QList<QPair<Elasticas::DockDialog *,QString> > el_dialogs=this->widget->kernel()->elDialogs();
    QListIterator<QPair<Elasticas::DockDialog *,QString> > i(el_dialogs);

    while(i.hasNext())
    {
        QPair<Elasticas::DockDialog *,QString> pair=i.next();
        this->addDockDialog(pair.first,pair.second);
    }

    //QAction * action = new QAction( QObject::trUtf8( "Вытачки" ), this );


//    this->AddAction( QObject::trUtf8( "Параметры БК" ), action, QString( "StraightSkirt" ),
//                     this->widget->view()->itemDialog( "StraightSkirt" ) );
//    //
//    dialog_toolbar->addAction( QObject::trUtf8( "Вытачки" ),
//                               this->widget->view(), SLOT( itemDialog( "StraightSkirt" ) ) );

//    this->AddMenu( QObject::trUtf8( "Параметры БК" ), dialog_toolbar );


    this->AddViewport( this->widget );
}

extern "C" EXPORTSPEC Elasticas::Plugin * GetPlugin()
{
    C2DModule* c2dmodule=new C2DModule;
    return c2dmodule;
}

