#ifndef C2DITEM_H
#define C2DITEM_H

#include <math.h>
#include <typeinfo>

#include <QDebug>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItemGroup>

#include "C2DSync.h"
#include "C2DExchange.h"
#include "C2DSceneItems.h"
#include "C2DLayerManager.h"
#include "C2DPropertiesDialog.h"

#include "C2DItemDialog.h"

#include "Unicus/Geometry.h"
#include "Unicus/Intersection.h"
#include "elcore/elbasicdialogs.h"
//#include "cGeometry.h"

#define POINT_NOTE ":note"
class C2DItem: public QGraphicsItemGroup, public C2DExchange
{
public:
    C2DItem();
    ~C2DItem();

    QList< QPair< C2DVariable *, QVariant > > getSheetVariables();

    inline QPointF getViewCenter()      {  return this->P.value( "View:Center", QPointF() );   }
    inline QGraphicsScene *         scene()                    {  return this->item_scene;     }
    inline QList< C2DItemDialog * > dialogs() const            {  return this->item_dialogs;   }
    inline QList< QPair<Elasticas::DockDialog *,QString> > elDialogs() const          {  return this->el_item_dialogs;}
    inline QList< C2DItem * >       children() const           {  return this->item_children;  }
    inline QHash< QString, C2DAbstractItem * > items()         {  return this->Items;          }

    QHash< QString, C2DAbstractItem * > getittems() { return this->Items; };
    inline void setScene( QGraphicsScene *      scene )  {  this->item_scene = scene;          }
    inline void setFabricsVisible( bool       visible )  {  this->f->setVisible( visible );    }
    inline virtual void Update()  { foreach( C2DItem * i, this->children() ) i->Update(); }

    inline QString prefix( bool dots = true )
    {
        return ( dots ) ? ( this->item_prefix + ":" ) : this->item_prefix;
    }

    void setLayerManager( C2DLayerManager * LM );

// LOL

protected:
    PointItem  * point(  C2DSync * Obj, bool f )
    {
        return this->item< PointItem  >( Obj, 1, f );
    }
   // QPainterPath lolpath;
    C2DLayerManager * LM;
    virtual void requiredVariables() {  }
    virtual void setVariables()      {  }
    virtual void UpdatePoints()      {  }
    virtual void DrawOnWidget()      {  }

    bool validatePoints();
    bool validatePointList( int count, QList< QString > points );
    void setFabricsShape();

    inline bool isFabricsVisible()              {  return this->f->isVisible();  }
    inline void setPrefix( const QString & p )  {  this->item_prefix = p;        }

    //    CircleItem       * circle( C2DSync * Obj, bool f );
    //    ArcItem          * arc( C2DSync * Obj, bool f );
    //    TextItem         * text( QString Text, QString Label, double angle, bool f );

    inline void addChildItem( C2DItem * item )       {  this->item_children.append( item );   }
    inline void addDialog( C2DItemDialog * dialog )  {  this->item_dialogs.append( dialog );  }
    inline void addElDialog(Elasticas::DockDialog* dialog,const QString & toolbar_name) {this->el_item_dialogs.append(QPair<Elasticas::DockDialog *,QString>(dialog,toolbar_name) ); }

    C2DLayer * dashed( bool dashed );
    PpathItem * ppath(  C2DSync * Obj, QPainterPath * itempath, double angle, int mirror, bool f )
    {
        PpathItem * pitem;
        if( f == false )
        {
            f = true;
            itempath = new QPainterPath();
        }
       // else if(!itempath)
       //     itempath = new QPainterPath();
        QPainterPath path;
        QPointF deltapoint;
        pitem = this->item< PpathItem  >( Obj, 1, f, itempath );
        if(f==true)
        {
            pitem->mirror = mirror;
            pitem->angle = angle;
            path = pitem->shape();


            deltapoint = pitem->getStartPoint() - path.pointAtPercent(0);
            pitem->calcEnd(Unicus::rPoint( path.pointAtPercent(1),path.pointAtPercent(0),angle )+deltapoint);
            pitem->calcStrt(path.pointAtPercent(0));

            return pitem;
        }
    }
    ButtonItem * button(  C2DSync * Obj, bool f )
    {
        return this->item< ButtonItem   >( Obj, 1, f );
    }
    SignItem   * sign(   C2DSync * Obj, bool f )  {  return this->item< SignItem   >( Obj, 1, f );  }
    CircleItem * circle( C2DSync * Obj, bool f )  {  return this->item< CircleItem >( Obj, 1, f );  }
    LineItem   * line(   C2DSync * Obj, bool f )  {  return this->item< LineItem   >( Obj, 2, f );  }
    SplineItem * spline( C2DSync * Obj, bool f )  {  return this->item< SplineItem >( Obj, 2, f );  }
    ArcItem    * arc(    C2DSync * Obj, bool f )  {  return this->item< ArcItem    >( Obj, 3, f );  }
    DartItem   * dart(   C2DSync * Obj, bool f )  {  return this->item< DartItem   >( Obj, 3, f );  }
    BadPathItem   * badpath(  C2DSync * Obj, bool f )
    {
        return this->item< BadPathItem   >( Obj, 8, f );
    }

    int    LI( const QString & name )  {  return this->item_hash.value( name ).value< int >   ();  }
    bool   LB( const QString & name )  {  return this->item_hash.value( name ).value< bool >  ();  }
    double LD( const QString & name )  {  return this->item_hash.value( name ).value< double >();  }
    QVariant & H( const QString & name )  {  return this->item_hash[ name ];                       }

    Fabrics * f;

    QHash< QString, QPointF >           P;
    QHash< QString, C2DAbstractItem * > Items;
 //   QGraphicsItem * mypaths1;
 //   QGraphicsItem * mypaths2;

private:

    template < class T > T * item( C2DSync * Obj, int points, bool f , QPainterPath * itempath = new QPainterPath());

    QString                    item_prefix;
    QGraphicsScene *           item_scene;
    QList< C2DItem * >         item_children;
    QList< C2DItemDialog * >   item_dialogs;
    QList< QPair<Elasticas::DockDialog *,QString> >  el_item_dialogs;
    QHash< QString, QVariant > item_hash;

};



template < class T > T * C2DItem::item( C2DSync * Obj, int points, bool f, QPainterPath * itempath )
{
    //qDebug() << "C2DItem::item() - start;";

    C2DAbstractItem * i = 0;
    TextItem        * t = 0;
    T               * r = 0;

    PointItem * p[ points ];

    C2DSync::Type type  = Obj->type();

    switch ( f )
    {
    case ( true ) :
    if ( this->validatePointList( points, Obj->list() ) )
    {
        if ( !this->Items.contains( Obj->name() ) )
            {
                this->Items.insert( Obj->name(),
                                    new T( Obj->name(), Obj->layer(), this, this->scene() ) );

                i = this->Items.value( Obj->name() );

                r = dynamic_cast< T * >( i );

                switch ( type )
                {
                    case ( C2DSync::Point ) :
                    qDebug() << "C2DItem::item( Point, true ) : new;";

                    if ( r )
                    {
                        r->setPos( P[ Obj->list().at( 0 ) ] );

                        #if defined( C2D_DEBUG )
                            if ( !this->Items.contains( Obj->name() + POINT_NOTE ) )
                            {
                                t = new TextItem( Obj->name(), Obj->layer(), this, this->scene() );
                                t->setText( Obj->name() );
                                t->setPos( P[ Obj->list().at( 0 ) ] + QPointF( 5.0f, -15.0f ) );
                                t->setAngle( 0.0f );

                                this->Items.insert( Obj->name() + POINT_NOTE, t );
                            }
                            else
                                dynamic_cast< TextItem * >
                                        ( this->Items.value( Obj->name() + POINT_NOTE ) )
                                        ->setPos( P[Obj->list().at( 0 ) ] + QPointF( 5.0f, -15.0f ) );
                        #endif
                    }
                    else
                        qWarning() << this->prefix()
                                   << "C2DItem::item() - item of type \"C2DSync::Point\""
                                   << "with name " << Obj->name()
                                   << "not found after instantiation.";
                    break;
 ///////////////////////////////////////////////////lol
                        case ( C2DSync::Ppath ) :
                        qDebug() << "C2DItem::item( PPoint, true ) : new;";

                        if ( r )
                        {
                            r->setPos( P[ Obj->list().at( 0 ) ] - itempath->pointAtPercent(0) );
                            //r->setPos( P[ Obj->list().at( 0 ) ] );
                            dynamic_cast< PpathItem * >( i )->setStartPoint( P[ Obj->list().at( 0 ) ] );
                            dynamic_cast< PpathItem * >( i )->setPath( itempath );

                            #if defined( C2D_DEBUG )
                            //    if ( !this->Items.contains( Obj->name() + POINT_NOTE ) )
                            //    {
                            //        t = new TextItem( Obj->name(), Obj->layer(), this, this->scene() );
                            //        t->setText( Obj->name() );
                            //        t->setPos( P[ Obj->list().at( 0 ) ] + QPointF( 5.0f, -15.0f ) );
                            //        t->setAngle( 0.0f );

                            //        this->Items.insert( Obj->name() + POINT_NOTE, t );
                            //    }
                            //    else
                            //        dynamic_cast< TextItem * >
                            //                ( this->Items.value( Obj->name() + POINT_NOTE ) )
                            //                ->setPos( P[Obj->list().at( 0 ) ] + QPointF( 5.0f, -15.0f ) );
                            #endif
                        }
                        else
                            qWarning() << this->prefix()
                                       << "C2DItem::item() - item of type \"C2DSync::PPoint\""
                                       << "with name " << Obj->name()
                                       << "not found after instantiation.";
                        break;
                        ///////////////////////////////////////////////////lol
                        case ( C2DSync::Button ) :
                        qDebug() << "C2DItem::item( PPoint, true ) : new;";

                        if ( r )
                        {
                           r->setPos( P[ Obj->list().at( 0 ) ] );
                        }
                        else
                            qWarning() << this->prefix()
                                       << "C2DItem::item() - item of type \"C2DSync::PPoint\""
                                       << "with name " << Obj->name()
                                       << "not found after instantiation.";
                        break;
//////////////////////////////////////////////////lol
                case ( C2DSync::Sign ) :
                    qDebug() << "C2DItem::item( Sign, true ) : new;";

                    if ( dynamic_cast< SignItem * >( i ) )
                    {
                        dynamic_cast< SignItem * >( i )->setPos( P[ Obj->list().at( 0 ) ] );
                        dynamic_cast< SignItem * >( i )->setDual( Obj->property< bool >( SYNC_SIGN_DUAL ) );
                        dynamic_cast< SignItem * >( i )->setAngle( Obj->property< double >( SYNC_SIGN_ANGLE ) );

                        #if defined( C2D_DEBUG )
                            if ( !this->Items.contains( Obj->name() + POINT_NOTE ) )
                            {
                                t = new TextItem( Obj->name(), Obj->layer(), this, scene() );
                                t->setText( Obj->name() );
                                t->setPos( P[ Obj->list().at( 0 ) ] + QPointF( 5.0f, -15.0f ) );
                                t->setAngle( 0.0f );

                                this->Items.insert( Obj->name() + POINT_NOTE, t );
                            }
                            else
                                dynamic_cast< TextItem * >
                                        ( this->Items.value( Obj->name() + POINT_NOTE ) )
                                        ->setPos( P[Obj->list().at( 0 ) ] + QPointF( 5.0f, -15.0f ) );
                        #endif
                    }
                    else
                        qWarning() << this->prefix()
                                   << "C2DItem::item() - item of type \"C2DSync::Sign\""
                                   << "with name " << Obj->name()
                                   << "not found after instantiation.";
                    break;

                /*****LOL***/
                case ( C2DSync::BadPath ) :
                    if ( dynamic_cast< BadPathItem * >( i ) )
                    {
                        dynamic_cast< BadPathItem * >( i )->setPos( P[ Obj->list().at( 0 ) ] );
                        dynamic_cast< BadPathItem * >( i )->setPoints( P[ Obj->list().at( 0 ) ],
                                                                    P[ Obj->list().at( 1 ) ],
                                                                    P[ Obj->list().at( 2 ) ],
                                                                    P[ Obj->list().at( 3 ) ],
                                                                    P[ Obj->list().at( 4 ) ],
                                                                    P[ Obj->list().at( 5 ) ],
                                                                    P[ Obj->list().at( 6 ) ],
                                                                    P[ Obj->list().at( 7 ) ] );

                        dynamic_cast< BadPathItem * >( i )->setDual( Obj->property< bool >( SYNC_BADPATH_DUAL ) );
                        dynamic_cast< BadPathItem * >( i )->setAngle( Obj->property< double >( SYNC_BADPATH_ANGLE ) );

                        #if defined( C2D_DEBUG )
                            if ( !this->Items.contains( Obj->name() + POINT_NOTE ) )
                            {
                                t = new TextItem( Obj->name(), Obj->layer(), this, scene() );
                                t->setText( Obj->name() );
                                t->setPos( P[ Obj->list().at( 0 ) ] + QPointF( 5.0f, -15.0f ) );
                                t->setAngle( 0.0f );

                                this->Items.insert( Obj->name() + POINT_NOTE, t );
                            }
                            else
                                dynamic_cast< TextItem * >
                                        ( this->Items.value( Obj->name() + POINT_NOTE ) )
                                        ->setPos( P[Obj->list().at( 0 ) ] + QPointF( 5.0f, -15.0f ) );
                        #endif
                    }
                    else
                        qWarning() << this->prefix()
                                   << "C2DItem::item() - item of type \"C2DSync::Sign\""
                                   << "with name " << Obj->name()
                                   << "not found after instantiation.";
                    break;
                /****LOLend***/
                case ( C2DSync::Circle ) :
                    qDebug() << "C2DItem::item( Circle, true ) : new;";

                    p[ 0 ] = this->point( Sync( attr( SYNC_NAME, Obj->list().at( 0 ) ),
                                                attr( SYNC_TYPE, C2DSync::Point ),
                                                attr( SYNC_LIST, MakeList( Obj->list().at( 0 ) ) ),
                                                Obj->layer() ), f );

                    if ( !p[ 0 ] )
                    {
                        qWarning() << this->prefix()
                                   << "C2DItem::item() - item of type \"C2DSync::Circle\""
                                   << "with name " << Obj->name() << ": "
                                   << "no valid points";
                    }
                    else
                    {
                        dynamic_cast< CircleItem * >( i )->setPos( P[ Obj->list().at( 0 ) ] );
                        dynamic_cast< CircleItem * >( i )->setCenter( p[ 0 ] );
                        dynamic_cast< CircleItem * >( i )->setRadius( Obj->property< double >( SYNC_RADIUS ) );

                        qDebug() << "Circle center : " << p[ 0 ];
                        qDebug() << "Circle radius : " << Obj->property< double >( SYNC_RADIUS );
                    }
                    break;
                case ( C2DSync::Line ) :
                    qDebug() << "C2DItem::item( Line, true ) : new;";

                    p[ 0 ] = this->point( Sync( attr( SYNC_NAME, Obj->list().at( 0 ) ),
                                                attr( SYNC_TYPE, C2DSync::Point ),
                                                attr( SYNC_LIST, MakeList( Obj->list().at( 0 ) ) ),
                                                Obj->layer() ), f );
                    p[ 1 ] = this->point( Sync( attr( SYNC_NAME, Obj->list().at( 1 ) ),
                                                attr( SYNC_TYPE, C2DSync::Point ),
                                                attr( SYNC_LIST, MakeList( Obj->list().at( 1 ) ) ),
                                                Obj->layer() ), f );

                    if ( !p[ 0 ] && !p[ 1 ] )
                    {
                        qWarning() << this->prefix()
                                   << "C2DItem::item() - item of type \"C2DSync::Line\""
                                   << "with name " << Obj->name() << ": "
                                   << "no valid points";
                    }
                    else
                    {
                        dynamic_cast< LineItem * >( i )->setPos( p[ 0 ]->pos() );
                        dynamic_cast< LineItem * >( i )->setStartPoint( p[ 0 ] );
                        dynamic_cast< LineItem * >( i )->setEndPoint( p[ 1 ] );
                    }
                    break;
                case ( C2DSync::Arc ) :
                    qDebug() << "C2DItem::item( Arc, true ) : new;";

                    p[ 0 ] = this->point( Sync( attr( SYNC_NAME, Obj->list().at( 0 ) ),
                                                attr( SYNC_TYPE, C2DSync::Point ),
                                                attr( SYNC_LIST, MakeList( Obj->list().at( 0 ) ) ),
                                                Obj->layer() ), f );
                    p[ 1 ] = this->point( Sync( attr( SYNC_NAME, Obj->list().at( 1 ) ),
                                                attr( SYNC_TYPE, C2DSync::Point ),
                                                attr( SYNC_LIST, MakeList( Obj->list().at( 1 ) ) ),
                                                Obj->layer() ), f );
                    p[ 2 ] = this->point( Sync( attr( SYNC_NAME, Obj->list().at( 2 ) ),
                                                attr( SYNC_TYPE, C2DSync::Point ),
                                                attr( SYNC_LIST, MakeList( Obj->list().at( 2 ) ) ),
                                                Obj->layer() ), f );

                    if ( !p[ 0 ] && !p[ 1 ] && !p[ 2 ] )
                    {
                        qWarning() << this->prefix()
                                   << "C2DItem::item() - item of type \"C2DSync::Arc\""
                                   << "with name " << Obj->name() << ": "
                                   << "no valid points";
                    }
                    else
                    {
                        dynamic_cast< ArcItem * >( i )->setPos( P[ Obj->list().at( 0 ) ] );
                        dynamic_cast< ArcItem * >( i )->setCenter( p[ 0 ] );
                        dynamic_cast< ArcItem * >( i )->setStart( p[ 1 ] );
                        dynamic_cast< ArcItem * >( i )->setEnd( p[ 2 ] );
                    }
                    break;
                case ( C2DSync::Spline ) :
                    qDebug() << "C2DItem::item( Spline, true ) : new;";

                    p[ 0 ] = this->point( Sync( attr( SYNC_NAME, Obj->list().at( 0 ) ),
                                                attr( SYNC_TYPE, C2DSync::Point ),
                                                attr( SYNC_LIST, MakeList( Obj->list().at( 0 ) ) ),
                                                Obj->layer() ), f );
                    p[ 1 ] = this->point( Sync( attr( SYNC_NAME, Obj->list().at( 3 ) ),
                                                attr( SYNC_TYPE, C2DSync::Point ),
                                                attr( SYNC_LIST, MakeList( Obj->list().at( 3 ) ) ),
                                                Obj->layer() ), f );

                    if ( !p[ 0 ] && !p[ 1 ] )
                    {
                        qWarning() << this->prefix()
                                   << "C2DItem::item() - item of type \"C2DSync::Spline\""
                                   << "with name " << Obj->name() << ": "
                                   << "no valid points";
                    }
                    else
                    {
                        dynamic_cast< SplineItem * >( i )->setPos(   p[ 0 ]->pos() );
                        dynamic_cast< SplineItem * >( i )->setStart( p[ 0 ], P[ Obj->list().at( 1 ) ] );
                        dynamic_cast< SplineItem * >( i )->setEnd(   p[ 1 ], P[ Obj->list().at( 2 ) ] );
                    }

                    break;
                case ( C2DSync::Dart ) :
                    qDebug() << "C2DItem::item( Dart, true ) : new;";

                    p[ 0 ] = this->point( Sync( attr( SYNC_NAME, Obj->list().at( 0 ) ),
                                                attr( SYNC_TYPE, C2DSync::Point ),
                                                attr( SYNC_LIST, MakeList( Obj->list().at( 0 ) ) ),
                                                Obj->layer() ), f );
                    p[ 1 ] = this->point( Sync( attr( SYNC_NAME, Obj->list().at( 1 ) ),
                                                attr( SYNC_TYPE, C2DSync::Point ),
                                                attr( SYNC_LIST, MakeList( Obj->list().at( 1 ) ) ),
                                                Obj->layer() ), f );
                    p[ 2 ] = this->point( Sync( attr( SYNC_NAME, Obj->list().at( 2 ) ),
                                                attr( SYNC_TYPE, C2DSync::Point ),
                                                attr( SYNC_LIST, MakeList( Obj->list().at( 2 ) ) ),
                                                Obj->layer() ), f );

                    if ( !p[ 0 ] && !p[ 1 ] && !p[ 2 ] )
                    {
                        qWarning() << this->prefix()
                                   << "C2DItem::item() - item of type \"C2DSync::Dart\""
                                   << "with name " << Obj->name() << ": "
                                   << "no valid points";
                    }
                    else
                    {
                        dynamic_cast< DartItem * >( i )->setPos( p[ 0 ]->pos() );
                        dynamic_cast< DartItem * >( i )->setP0( p[ 0 ] );
                        dynamic_cast< DartItem * >( i )->setPL( p[ 1 ] );
                        dynamic_cast< DartItem * >( i )->setPR( p[ 2 ] );
                    }

                    break;
                }

                this->Items.insert( Obj->name(), r );
            }
            else
            if ( this->Items.contains( Obj->name() ) )
            {
                i = this->Items.value( Obj->name() );

                r = dynamic_cast< T * >( i );

                if ( r )
                    switch ( type )
                    {
                    case ( C2DSync::Point ) :

                        qDebug() << "C2DItem::item( Point, true ) : update;";

                        dynamic_cast< PointItem * >( i )->setPos( P[ Obj->list().at( 0 ) ] );

                        #if defined( C2D_DEBUG )
                            if ( this->Items.contains( Obj->name() + POINT_NOTE ) )
                                this->Items.value( Obj->name() + POINT_NOTE )->setPos(
                                        P[ Obj->list().at( 0 ) ] + QPointF( 5.0f, -15.0f ) );
                        #endif

                        break;
                    case ( C2DSync::Sign ) :
                        qDebug() << "C2DItem::item( Sign, true ) : update;";

                        dynamic_cast< SignItem * >( i )->setPos( P[ Obj->list().at( 0 ) ] );
                        dynamic_cast< SignItem * >( i )->setDual( Obj->property< bool >( SYNC_SIGN_DUAL ) );
                        dynamic_cast< SignItem * >( i )->setAngle( Obj->property< double >( SYNC_SIGN_ANGLE ) );
                        break;
///////////////////////////////////////////lol
                    case ( C2DSync::Ppath ) :

                        qDebug() << "C2DItem::item( PPoint, true ) : update;";

                        dynamic_cast< PpathItem * >( i )->setPos( P[ Obj->list().at( 0 ) ] - itempath->pointAtPercent(0) );
                        //dynamic_cast< PpathItem * >( i )->setPos( P[ Obj->list().at( 0 ) ] );
                        dynamic_cast< PpathItem * >( i )->setStartPoint( P[ Obj->list().at( 0 ) ] );
                        dynamic_cast< PpathItem * >( i )->setPath( itempath );

                        #if defined( C2D_DEBUG )
                        //    if ( this->Items.contains( Obj->name() + POINT_NOTE ) )
                        //        this->Items.value( Obj->name() + POINT_NOTE )->setPos(
                        //                P[ Obj->list().at( 0 ) ] + QPointF( 5.0f, -15.0f ) );
                        #endif

                        break;
///////////////////////////////////////////lol
                    case ( C2DSync::Button ) :

                        qDebug() << "C2DItem::item( PPoint, true ) : update;";

                        dynamic_cast< ButtonItem * >( i )->setPos( P[ Obj->list().at( 0 ) ] );


                        break;
///////////////////////////////////////////lol
                    /***LOL2***/
                    case ( C2DSync::BadPath ) :
                        qDebug() << "C2DItem::item( Sign, true ) : update;";

                        dynamic_cast< BadPathItem * >( i )->setPos( P[ Obj->list().at( 0 ) ] );
                        dynamic_cast< BadPathItem * >( i )->setPoints( P[ Obj->list().at( 0 ) ],
                                                                    P[ Obj->list().at( 1 ) ],
                                                                    P[ Obj->list().at( 2 ) ],
                                                                    P[ Obj->list().at( 3 ) ],
                                                                    P[ Obj->list().at( 4 ) ],
                                                                    P[ Obj->list().at( 5 ) ],
                                                                    P[ Obj->list().at( 6 ) ],
                                                                    P[ Obj->list().at( 7 ) ] );
                        dynamic_cast< BadPathItem * >( i )->setDual( Obj->property< bool >( SYNC_BADPATH_DUAL ) );
                        dynamic_cast< BadPathItem * >( i )->setAngle( Obj->property< double >( SYNC_BADPATH_ANGLE ) );
                        break;
                    /***LOL2end***/
                    case ( C2DSync::Circle ) :
                        qDebug() << "C2DItem::item( Circle, true ) : update;";

                        p[ 0 ] = this->point( Sync( attr( SYNC_NAME, Obj->list().at( 0 ) ),
                                                    attr( SYNC_TYPE, C2DSync::Point ),
                                                    attr( SYNC_LIST, MakeList( Obj->list().at( 0 ) ) ),
                                                    Obj->layer() ), f );

                        if ( p[ 0 ] )
                            dynamic_cast< CircleItem * >( i )->setCenter( p[ 0 ] );

                        dynamic_cast< CircleItem * >( i )->setRadius( Obj->property< double >( SYNC_RADIUS ) );

                        dynamic_cast< CircleItem * >( i )->update( i->boundingRect() );
                        break;
                    case ( C2DSync::Line ) :
                        qDebug() << "C2DItem::item( Line, true ) : update;";

                        p[ 0 ] = this->point( Sync( attr( SYNC_NAME, Obj->list().at( 0 ) ),
                                                    attr( SYNC_TYPE, C2DSync::Point ),
                                                    attr( SYNC_LIST, MakeList( Obj->list().at( 0 ) ) ),
                                                    Obj->layer() ), f );
                        p[ 1 ] = this->point( Sync( attr( SYNC_NAME, Obj->list().at( 1 ) ),
                                                    attr( SYNC_TYPE, C2DSync::Point ),
                                                    attr( SYNC_LIST, MakeList( Obj->list().at( 1 ) ) ),
                                                    Obj->layer() ), f );

                        if ( !p[ 0 ] && !p[ 1 ] )
                        {
                            qWarning() << this->prefix()
                                       << "C2DItem::item() - item of type \"C2DSync::Line\""
                                       << "with name " << Obj->name() << ": "
                                       << "no valid points";
                        }
                        else
                        {
                            dynamic_cast< LineItem * >( i )->setPos( p[ 0 ]->pos() );
                            dynamic_cast< LineItem * >( i )->setStartPoint( p[ 0 ] );
                            dynamic_cast< LineItem * >( i )->setEndPoint( p[ 1 ] );
                        }

                        dynamic_cast< LineItem * >( i )->update( i->boundingRect() );

                        break;
                    case ( C2DSync::Arc ) :
                        qDebug() << "C2DItem::item( Arc, true ) : update;";

                        p[ 0 ] = this->point( Sync( attr( SYNC_NAME, Obj->list().at( 0 ) ),
                                                    attr( SYNC_TYPE, C2DSync::Point ),
                                                    attr( SYNC_LIST, MakeList( Obj->list().at( 0 ) ) ),
                                                    Obj->layer() ), f );
                        p[ 1 ] = this->point( Sync( attr( SYNC_NAME, Obj->list().at( 1 ) ),
                                                    attr( SYNC_TYPE, C2DSync::Point ),
                                                    attr( SYNC_LIST, MakeList( Obj->list().at( 1 ) ) ),
                                                    Obj->layer() ), f );
                        p[ 2 ] = this->point( Sync( attr( SYNC_NAME, Obj->list().at( 2 ) ),
                                                    attr( SYNC_TYPE, C2DSync::Point ),
                                                    attr( SYNC_LIST, MakeList( Obj->list().at( 2 ) ) ),
                                                    Obj->layer() ), f );

                        if ( !p[ 0 ] && !p[ 1 ] && !p[ 2 ] )
                        {
                            qWarning() << this->prefix()
                                       << "C2DItem::item() - item of type \"C2DSync::Arc\""
                                       << "with name " << Obj->name() << ": "
                                       << "no valid points";
                        }
                        else
                        {
                            dynamic_cast< ArcItem * >( i )->setPos( p[ 0 ]->pos() );
                            dynamic_cast< ArcItem * >( i )->setCenter( p[ 0 ] );
                            dynamic_cast< ArcItem * >( i )->setStart( p[ 1 ] );
                            dynamic_cast< ArcItem * >( i )->setEnd( p[ 2 ] );
                        }

                        break;
                    case ( C2DSync::Spline ) :
                        qDebug() << "C2DItem::item( Spline, true ) : update;";

                        p[ 0 ] = this->point( Sync( attr( SYNC_NAME, Obj->list().at( 0 ) ),
                                                    attr( SYNC_TYPE, C2DSync::Point ),
                                                    attr( SYNC_LIST, MakeList( Obj->list().at( 0 ) ) ),
                                                    Obj->layer() ), f );
                        p[ 1 ] = this->point( Sync( attr( SYNC_NAME, Obj->list().at( 3 ) ),
                                                    attr( SYNC_TYPE, C2DSync::Point ),
                                                    attr( SYNC_LIST, MakeList( Obj->list().at( 3 ) ) ),
                                                    Obj->layer() ), f );

                        if ( !p[ 0 ] && !p[ 1 ] )
                        {
                            qWarning() << this->prefix()
                                       << "C2DItem::item() - item of type \"C2DSync::Spline\""
                                       << "with name " << Obj->name() << ": "
                                       << "no valid points";
                        }
                        else
                        {
                            dynamic_cast< SplineItem * >( i )->setPos( p[ 0 ]->pos() );
                            dynamic_cast< SplineItem * >( i )->setStart( p[ 0 ], P[ Obj->list().at( 1 ) ] );
                            dynamic_cast< SplineItem * >( i )->setEnd( p[ 1 ], P[ Obj->list().at( 2 ) ] );
                        }

                        dynamic_cast< SplineItem * >( i )->update( i->boundingRect() );

                        break;
                    case ( C2DSync::Dart ) :
                        qDebug() << "C2DItem::item( Dart, true ) : update;";

                        p[ 0 ] = this->point( Sync( attr( SYNC_NAME, Obj->list().at( 0 ) ),
                                                    attr( SYNC_TYPE, C2DSync::Point ),
                                                    attr( SYNC_LIST, MakeList( Obj->list().at( 0 ) ) ),
                                                    Obj->layer() ), f );
                        p[ 1 ] = this->point( Sync( attr( SYNC_NAME, Obj->list().at( 1 ) ),
                                                    attr( SYNC_TYPE, C2DSync::Point ),
                                                    attr( SYNC_LIST, MakeList( Obj->list().at( 1 ) ) ),
                                                    Obj->layer() ), f );
                        p[ 2 ] = this->point( Sync( attr( SYNC_NAME, Obj->list().at( 2 ) ),
                                                    attr( SYNC_TYPE, C2DSync::Point ),
                                                    attr( SYNC_LIST, MakeList( Obj->list().at( 2 ) ) ),
                                                    Obj->layer() ), f );

                        if ( !p[ 0 ] && !p[ 1 ] && !p[ 2 ] )
                        {
                            qWarning() << this->prefix()
                                       << "C2DItem::item() - item of type \"C2DSync::Dart\""
                                       << "with name " << Obj->name() << ": "
                                       << "no valid points";
                        }
                        else
                        {
                            dynamic_cast< DartItem * >( i )->setPos( p[ 0 ]->pos() );
                            dynamic_cast< DartItem * >( i )->setP0( p[ 0 ] );
                            dynamic_cast< DartItem * >( i )->setPL( p[ 1 ] );
                            dynamic_cast< DartItem * >( i )->setPR( p[ 2 ] );
                        }

                        dynamic_cast< DartItem * >( i )->update( i->boundingRect() );

                        break;
                    }
            }
        }
        break;
        case ( false ) :
            if ( this->Items.contains( Obj->name() ) )
            {
                i = this->Items.value( Obj->name() );

                if ( ( type != C2DSync::Point ) && ( type != C2DSync::Sign ) )
                {
                    this->scene()->removeItem( i );

                    delete i;

                    this->Items.remove( Obj->name() );
                }
                else
                {
                    if ( dynamic_cast< PointItem * >( i ) )
                    {
                        #if defined( C2D_DEBUG )
                            if ( ( dynamic_cast< PointItem * >( i )->depenency() == 0 ) &&
                                 this->Items.contains( Obj->name() + POINT_NOTE ) )
                            {
                                 this->scene()->removeItem(
                                         this->Items.value( Obj->name() + POINT_NOTE ) );
                                 delete this->Items.value( Obj->name() + POINT_NOTE );
                                 this->Items.remove( Obj->name() + POINT_NOTE );
                            }
                        #endif
                    }

                    if ( dynamic_cast< SignItem * >( i ) )
                    {
                        #if defined( C2D_DEBUG )
                            if ( this->Items.contains( Obj->name() ) )
                            {
                                 this->scene()->removeItem(
                                         this->Items.value( Obj->name() ) );
                                 delete this->Items.value( Obj->name() );
                                 this->Items.remove( Obj->name() );
                            }
                        #endif
                    }
                }

                if ( ( type != C2DSync::Point ) && ( type != C2DSync::Sign ) )
                    for ( int i = 0; i < points; i++ )
                    {
                        if ( this->Items.contains( Obj->list().at( i ) ) )
                        {
                            p[ i ] = dynamic_cast< PointItem * >
                                 ( this->Items.value( Obj->list().at( i ) ) );
                        }
                        else
                            p[ i ] = 0;

                        if ( p[ i ] )
                        {
                            p[ i ]->dec_d();

                            qDebug() << Obj->list().at( i ) << " : " << p[ i ]->depenency();

                            this->point( Sync( attr( SYNC_NAME, Obj->list().at( i ) ),
                                               attr( SYNC_TYPE, C2DSync::Point ),
                                               attr( SYNC_LIST, MakeList( Obj->list().at( i ) ) ),
                                               Obj->layer() ), f );
                        }
                    }
                }
            break;
        }

    //qDebug() << "C2DItem::item() - end;";
    if ( !r )
    {
        qWarning() << this->prefix() << " " << Obj->name() << " C2DItem::item() returns NULL.";
        return 0;
    }
    else
        return r;
};

#endif // C2DITEM_H
