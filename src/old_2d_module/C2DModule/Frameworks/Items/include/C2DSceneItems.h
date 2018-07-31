#ifndef C2DSCENEITEMS_H
#define C2DSCENEITEMS_H

#include <math.h>
#include <limits>
#include <typeinfo>

#include <QPen>
#include <QDebug>
#include <QStyle>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsPathItem>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsSceneHoverEvent>

#include "C2DSync.h"
#include "C2DLayer.h"

#include "Unicus/Geometry.h"

#define ABSTRACT_ITEM        QGraphicsItem::UserType + 1
#define TOOL_ITEM            QGraphicsItem::UserType + 2
#define ORIGIN_ITEM          QGraphicsItem::UserType + 5
#define POINT_ITEM           QGraphicsItem::UserType + 10
#define SIGN_ITEM            QGraphicsItem::UserType + 11
#define LINE_ITEM            QGraphicsItem::UserType + 15
#define CIRCLE_ITEM          QGraphicsItem::UserType + 20
#define ARC_ITEM             QGraphicsItem::UserType + 25
#define SPLINE_ITEM          QGraphicsItem::UserType + 30
#define MULTISPLINE_ITEM     QGraphicsItem::UserType + 31
#define DART_ITEM            QGraphicsItem::UserType + 32
#define VENT_ITEM            QGraphicsItem::UserType + 33
#define TEXT_ITEM            QGraphicsItem::UserType + 40
#define FABRICS_ITEM         QGraphicsItem::UserType + 100
#define BADPATH_ITEM            QGraphicsItem::UserType + 150
#define PPATH_ITEM           QGraphicsItem::UserType + 151
#define BUTTON_ITEM           QGraphicsItem::UserType + 152

class C2DAbstractItem: public QGraphicsPathItem
{

public:
    C2DAbstractItem( const QString & name, C2DLayer * layer,
                     QGraphicsItem * parent = 0, QGraphicsScene * scene = 0 )
                         : QGraphicsPathItem( parent, scene ),
                           item_name( name ),
                           item_layer( layer )  {  }

    virtual ~C2DAbstractItem()  {  }

    enum { Type = ABSTRACT_ITEM };

    virtual       int              type()               = 0;
    virtual       QRectF           boundingRect() const = 0;
    virtual       QPainterPath     shape()        const = 0;
    virtual const std::type_info & GetType()            = 0;

    inline Border * getBorder()                   {  return   this->b;  }
    inline void     setBorder( Border * border )  {  this->b = border;  }
    inline void     setSelected( bool selected )  {  QGraphicsItem::setSelected( selected );  }

    QString  & name()      {  return this->item_name;         }
    C2DLayer * layer()     {  return this->item_layer;        }
    qreal      length()    {  return this->shape().length();  }

    QString getType()
    {
        QString str;
        switch ( this->type() )
        {
            case ( ABSTRACT_ITEM )    : str = QString( "Abstract_item" );        break;
            case ( TOOL_ITEM )        : str = QString( "Tool" );                 break;
            case ( ORIGIN_ITEM )      : str = QString( "Coordinate Axis" );      break;
            case ( POINT_ITEM )       : str = QString( "Point" );                break;
            case ( SIGN_ITEM )        : str = QString( "Sign" );                 break;
            case ( LINE_ITEM )        : str = QString( "Line" );                 break;
            case ( CIRCLE_ITEM )      : str = QString( "Circle" );               break;
            case ( ARC_ITEM )         : str = QString( "Arc" );                  break;
            case ( SPLINE_ITEM )      : str = QString( "Single Spline" );        break;
            case ( MULTISPLINE_ITEM ) : str = QString( "Spline" );               break;
            case ( DART_ITEM )        : str = QString( "Dart" );                 break;
            case ( VENT_ITEM )        : str = QString( "Vent" );                 break;
            case ( TEXT_ITEM )        : str = QString( "Text" );                 break;
            case ( FABRICS_ITEM )     : str = QString( "Fabrics" );              break;
            case ( BADPATH_ITEM )        : str = QString( "BadPath" );                 break;
            case ( PPATH_ITEM )       : str = QString( "Ppath" );                break;
            case ( BUTTON_ITEM )      : str = QString( "Button" );               break;
            default                   : str = QString( "Undefined" );            break;
        }
        return str;
    }

protected:
    bool checkPointer( void    * new_pointer,
                       void    * old_pointer,
                 const QString & function_name,
                 const QString & point_name     );

private:
    QString    item_name;
    C2DLayer * item_layer;
    Border * b;
};

template < class T > class TypedItem : public C2DAbstractItem
{
 public:
     TypedItem( const QString & name, C2DLayer * layer,
                QGraphicsItem * parent = 0, QGraphicsScene * scene = 0 )
                    : C2DAbstractItem( name, layer, parent, scene )  {  }
     inline const std::type_info & GetType()  { return typeid( T ); }
};

class PointItem;
class LineItem;
class ArcItem;

class C2DTool : public TypedItem< C2DTool >
{
public:
    enum { Type = TOOL_ITEM };
    C2DTool( const QString & name,
             C2DLayer * layer = 0,
             QGraphicsItem * parent = 0,
             QGraphicsScene * scene = 0 )
        : TypedItem< C2DTool >( name, layer, parent, scene )  {  }
    virtual ~C2DTool()  {  }

   QRectF boundingRect() const = 0;
   QPainterPath  shape() const = 0;

    int type()  { return this->Type; }

    virtual void drop() = 0;
    //?
    inline  void setColor( const QColor & color )  { this->color = color; }

    virtual void setValue( const QVariant & va, bool reset = false ) = 0;

protected:
    virtual void paint( QPainter * painter, const QStyleOptionGraphicsItem * option,
                        QWidget * widget = 0 ) = 0;

    QVariant value;
    QColor   color;
private:

};

class C2DMarker : public C2DTool
{
public:
    C2DMarker( const QString & name, const QColor & co, C2DLayer * layer,
            QGraphicsItem * parent, QGraphicsScene * scene );
   ~C2DMarker()  {  }

    QRectF boundingRect() const;
    QPainterPath  shape() const;

    void drop();

protected:
    void setValue( const QVariant & va, bool new_item = false );
    void paint( QPainter * painter, const QStyleOptionGraphicsItem * option,
                QWidget * widget = 0 );

private:
};

class C2DSelection : public C2DTool
{
public:
    C2DSelection( const QString & name, const QColor & co1, const QColor & co2, C2DLayer * layer,
               QGraphicsItem * parent, QGraphicsScene * scene );
   ~C2DSelection()  {  }

    QRectF boundingRect() const;
    QPainterPath  shape() const;

    void drop();

    inline void setColor2( const QColor & color )  { this->color2 = color; }

protected:
    void setValue( const QVariant & va, bool resize = false );
    void paint( QPainter * painter, const QStyleOptionGraphicsItem * option,
                QWidget * widget = 0 );

private:
    bool color_inverse;
    QColor color2;
};

class Origin : public TypedItem< Origin >
{

public:
    enum { Type = ORIGIN_ITEM };

    Origin( C2DLayer * layer = 0, QGraphicsItem * parent = 0, QGraphicsScene * scene = 0 )
        : TypedItem< Origin >( QString( "Global Origin" ), layer, parent, scene )
    {
        this->origin_color = QColor( 000, 253, 024 );
        this->origin_stroke_length = 100;
    }

    inline int type()  {  return this->Type;  }
    inline QRectF boundingRect() const
    {
        return QRectF( -this->origin_stroke_length / 25,
                       -this->origin_stroke_length / 25,
                        this->origin_stroke_length * 1.12f,
                        this->origin_stroke_length * 1.12f );
    }

    QPainterPath shape() const;

protected:
    void paint( QPainter * painter,
                const QStyleOptionGraphicsItem * option,
                QWidget * widget = 0 );

private:
    int    origin_stroke_length;
    QColor origin_color;
};

class PointItem: public TypedItem< PointItem >
{
public:
    enum { Type = POINT_ITEM };

    PointItem( const QString   & name,
               C2DLayer        * layer,
               QGraphicsItem   * parent = 0,
               QGraphicsScene  * scene  = 0 );

    inline int  type()  {  return this->Type;  }

    inline       void  inc_d()     { this->link++;      }
    inline       void  dec_d()     { this->link--;      }
    inline const int & depenency() { return this->link; }

    QPainterPath  shape()        const;
    inline QRectF boundingRect() const  {  return this->shape().boundingRect().adjusted( 1, 1, 1, 1 );  }


protected:
    void paint( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0 );

    QVariant itemChange( GraphicsItemChange change, const QVariant & value );

private:
    int link;

};
////////////////////////////////////////////////////lol
class PpathItem: public TypedItem< PpathItem >
{
public:
    enum { Type = PPATH_ITEM };

    PpathItem( const QString   & name,
               C2DLayer        * layer,
               QGraphicsItem   * parent = 0,
               QGraphicsScene  * scene  = 0 );

    inline int  type()  {  return this->Type;  }
    inline void setPath(  QPainterPath * p  ){    this->ppath_path = *p;   }
    inline void setStartPoint(  QPointF p  ){    this->startpoint = p;   }
    inline void calcEnd(  QPointF p  ){    this->end = p;   }
    inline void calcStrt(  QPointF p  ){    this->strt = p;   }
    inline QPointF getEnd() { return this->end; }
    inline QPointF getStrt() { return this->strt; }
    inline QPointF getStartPoint() { return this->startpoint; }


    inline       void  inc_d()     { this->link++;      }
    inline       void  dec_d()     { this->link--;      }
    inline const int & depenency() { return this->link; }

    QPointF pointatpersent( double a );
    QPainterPath  shape()        const;
    QPainterPath  myshape(QPointF start_point, double shag = 5 );
    QPainterPath  myshape_fromstart( double shag=5 )
    {
        return this->myshape( this->getStartPoint(), shag ) ;
    };
    inline QRectF boundingRect() const  {  return this->shape().boundingRect().adjusted( 1, 1, 1, 1 );  }

    int mirror;
    double angle;
protected:
    void paint( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0 );

    QVariant itemChange( GraphicsItemChange change, const QVariant & value );

private:
    int link;
    QPainterPath ppath_path;
    QPointF startpoint,strt,end;

};
/////////////////////////////////////////////////////lol
class ButtonItem: public TypedItem< ButtonItem >
{
public:
    enum { Type = BUTTON_ITEM };

    ButtonItem( const QString   & name,
               C2DLayer        * layer,
               QGraphicsItem   * parent = 0,
               QGraphicsScene  * scene  = 0 );

    inline int  type()  {  return this->Type;  }

    inline       void  inc_d()     { this->link++;      }
    inline       void  dec_d()     { this->link--;      }
    inline const int & depenency() { return this->link; }

    QPainterPath  shape()        const;
    inline QRectF boundingRect() const  {  return this->shape().boundingRect().adjusted( 1, 1, 1, 1 );  }

protected:
    void paint( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0 );

    QVariant itemChange( GraphicsItemChange change, const QVariant & value );

private:
    int link;
};
/////////////////////////////////////////////////////lol

class SignItem: public TypedItem< SignItem >
{
public:
    enum { Type = SIGN_ITEM };

    SignItem( const QString  & name,
              C2DLayer       * layer ,
              QGraphicsItem  * parent = 0,
              QGraphicsScene * scene  = 0 );

    inline int  type()                    {  return this->Type;    }
    inline void setDual(  bool   dual  )  {  this->dual = dual;    }
    inline void setAngle( double angle )  {  this->angle = angle;  }

    QRectF boundingRect() const;
    QPainterPath shape() const;
    QPainterPath GetShapeByAngle( const bool & dual, const double & angle ) const;

protected:
    void paint( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0 );

private:
    bool dual;
    double angle;
    QColor color;
};
///////*LOL3
///////
class BadPathItem: public TypedItem< BadPathItem >
{
public:
    enum { Type = BADPATH_ITEM };

    BadPathItem( const QString  & name,
              C2DLayer       * layer ,
              QGraphicsItem  * parent = 0,
              QGraphicsScene * scene  = 0 );

    inline int  type()                    {  return this->Type;    }
    inline void setDual(  bool   dual  )  {  this->dual = dual;    }
    inline void setPoints(  QPointF p0,QPointF p1,QPointF p2,QPointF p3,QPointF p4,
                            QPointF p5,QPointF p6,QPointF p7  ){    this->p1 = p1-p0;
                                                                    this->p2 = p2-p0;
                                                                    this->p3 = p3-p0;
                                                                    this->p4 = p4-p0;
                                                                    this->p5 = p5-p0;
                                                                    this->p6 = p6-p0;
                                                                    this->p7 = p7-p0;}
    inline void setAngle( double angle )  {  this->angle = angle;  }

    QRectF boundingRect() const;
    QPainterPath shape() const;
    QPainterPath GetShapeByAngle( const bool & dual, const double & angle ) const;

protected:
    void paint( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0 );

private:
    QPointF p1,p2,p3,p4,p5,p6,p7;
    bool dual;
    double angle;
    QColor color;
};

/*********LOL3end***/
class LineItem: public TypedItem< LineItem >
{
public:
    enum { Type = LINE_ITEM };

    LineItem( const QString  & name,
              C2DLayer       * Layer,
              QGraphicsItem  * parent = 0,
              QGraphicsScene * scene  = 0 );

    inline int    type()                 {  return this->Type;          }

    QPointF      startPoint()   const;
    QPointF      endPoint()     const;
    QRectF       boundingRect() const;
    QPainterPath shape()        const;

    void setStartPoint( PointItem * start );
    void setEndPoint(   PointItem * end   );

    inline QVariant angle()
    {
        return QVariant( Unicus::angleOx( QLineF( this->start->pos(), this->end->pos() ) ) );
    }

protected:
    void paint( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0 );

    QVariant itemChange( GraphicsItemChange change, const QVariant & value );

private:
    PointItem * start, * end;

};

class CircleItem: public TypedItem< CircleItem >
{
public:
    enum { Type = CIRCLE_ITEM };

    CircleItem( const QString  & name,
                C2DLayer       * layer,
                QGraphicsItem  * parent = 0,
                QGraphicsScene * scene  = 0 );

    inline int type()  {  return this->Type;  }

    QRectF boundingRect() const;
    QPainterPath shape() const;

    void setCenter( PointItem * center );
    void setRadius( double radius );

    inline QVariant getRadius()  {  return QVariant( this->circle_radius );  }

protected:
    void paint( QPainter *painter, const QStyleOptionGraphicsItem *option,
                QWidget *widget = 0 );

private:
    PointItem * circle_center;
    double circle_radius;
};

class ArcItem: public TypedItem< ArcItem >
{
public:
    enum { Type = ARC_ITEM };

    ArcItem( const QString  & name,
             C2DLayer       * Layer,
             QGraphicsItem  * parent = 0,
             QGraphicsScene * scene  = 0 );

    void setCenter( PointItem * center );
    void setStart(  PointItem * start  );
    void setEnd(    PointItem * end    );

    inline PointItem * center()  {  return this->arc_center;  }
    inline PointItem * start()   {  return this->arc_start;   }
    inline PointItem * end()     {  return this->arc_end;     }

    inline int      type()       {  return this->Type;                }
    inline QVariant getRadius()  {  return QVariant( this->arc_radius );  }

    QRectF boundingRect() const;
    QPainterPath shape() const;


    inline QVariant startAngle()
    {
        return QVariant( Unicus::angleOx( QLineF( this->arc_center->pos(), this->arc_start->pos() ) ) );
    }

    inline QVariant arcAngle()
    {
        return QVariant( Unicus::angleOx( QLineF( this->arc_center->pos(), this->arc_end->pos() ) )
                         - this->startAngle().toDouble() );
    }

    void updateDependencies();

protected:
    void paint( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0 );

private:
    PointItem * arc_center, * arc_start, * arc_end;
    double arc_radius, arc_angle_start, arc_angle_end;
};

class SplineItem: public TypedItem< SplineItem >
{
public:
    enum { Type = SPLINE_ITEM };

    SplineItem( const QString        & name,
                      C2DLayer       * layer,
                      QGraphicsItem  * parent = 0,
                      QGraphicsScene * scene  = 0 );

    inline int type()  {  return this->Type;  }
    inline void setStartGuideFactor( double f = 1.0f )  {  this->start_factor = f;      }
    inline void setEndGuideFactor( double f = 1.0f )    {  this->end_factor   = f;      }

    void setStart( PointItem * start, const QPointF & start_guide, double start_factor = 1.0f );
    void setEnd(   PointItem * end,   const QPointF & end_guide,   double end_factor   = 1.0f );

    inline PointItem * start()  { return this->spline_start;  }
    inline PointItem * end()    { return this->spline_end;    }

    QRectF boundingRect() const;
    QPainterPath  shape() const;

protected:
    void paint( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0 );

private:
    void setGuides();

    double start_factor, end_factor;
    PointItem * spline_start, * spline_end;
    QPointF startGuide, endGuide;
    QLineF StartGuide, EndGuide;

};

class DartItem : public TypedItem< DartItem >
{
public:
    enum { Type = DART_ITEM };

    DartItem( const QString  & name,
              C2DLayer       * layer ,
              QGraphicsItem  * parent = 0,
              QGraphicsScene * scene  = 0 );

    inline int type()                            {  return this->Type;             }
    inline void setLeftVisible( bool visible )   {  this->leftVisible = visible;   }
    inline void setRightVisible( bool visible )  {  this->rightVisible = visible;  }

    inline const QPointF & connectLeft()  const  {  return this->ConnectionLeft;   }
    inline const QPointF & connectRight() const  {  return this->ConnectionRight;  }

    inline void   setKK( double KK )  {  this->kk = KK; this->setGuides();  }
    inline double getSpread()         {  return this->spread;               }
    inline double getHeight()         {  return this->height;               }

    void setP0( PointItem * p0 );
    void setPR( PointItem * pr );
    void setPL( PointItem * pl );

    inline QPainterPath leftSplineShape()   {  return this->leftSpline->shape();   }
    inline QPainterPath rightSplineShape()  {  return this->rightSpline->shape();  }

    QRectF       boundingRect() const;
    QPainterPath shape() const;
    void         setGuides();

protected:
    void paint( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0 );

private:
    SplineItem * leftSpline, * rightSpline;
    bool leftVisible, rightVisible;

    PointItem * P0, * Pl, * Pr, * Tc, * D1, * D2, * D3, * D4;
    QPointF ConnectionLeft,ConnectionRight;
    QPointF BottomGuide, LeftGuide, RightGuide;
    double spread, height;
    double kb, kl, kr, kk, cl, cr;
};

class TextItem: public TypedItem< TextItem >
{
public:
    enum { Type = TEXT_ITEM };

    TextItem( const QString  & name,
              C2DLayer       * layer,
              QGraphicsItem  * parent = 0,
              QGraphicsScene  * scene  = 0 );

    inline int type()  {  return this->Type;  }

    inline QPainterPath shape()  const  {  return this->path();                                          }
    inline QRectF boundingRect() const  {  return this->path().boundingRect().adjusted( -1, -1, 1, 1 );  }

    void setText( const QString & text );

    inline void setAngle( double angle )  {  this->item_angle = angle; this->rotate( -angle );  }
    inline double angle() const           {  return this->item_angle;                           }

protected:
    void paint( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0 );

private:
    QString item_text;
    QFont   item_font;
    double  item_angle;
};

class VentItem : public TypedItem< VentItem >
{
public:
    enum { Type = VENT_ITEM } ;
    VentItem( const QString  & name,
              PointItem      * p0,
              PointItem      * p1,
              PointItem      * p2,
              C2DLayer       * Layer ,
              QGraphicsItem  * parent = 0,
              QGraphicsScene * scene  = 0 );

    inline int type()  { return this->Type;  }

    QRectF boundingRect() const;
    QPainterPath shape() const;

protected:
    void paint( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0 );

private:
    C2DLayer * l;
    PointItem * P0, * Pl, * Pr;
};

class MultiSplineItem : public TypedItem< MultiSplineItem >
{
public:
    enum { Type = MULTISPLINE_ITEM };

    MultiSplineItem( const QString       & name,
                QList<PointItem * >   points,
                C2DLayer            * layer,
                QGraphicsItem       * parent = 0,
                QGraphicsScene      * scene  = 0 );

    inline int type()  { return this->Type;  }

    QRectF boundingRect() const;
    QPainterPath shape() const;

    const QPointF & connectStart() const;
    const QPointF & connectEnd() const;
    void setPoints( QList< PointItem * > points );

    void setGuides();

    QPainterPath splineShape();

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget = 0);

private:
    QList< PointItem * > p;

    C2DLayer * l;

    QPointF ConnectionStart, ConnectionEnd;
    QPointF BottomGuide, LeftGuide, RightGuide;
    double spread, height;
    double kb, kl, kr, kk;
};

class Fabrics : public TypedItem< Fabrics >
{
public:
    enum { Type = FABRICS_ITEM };

    Fabrics( const QString  & name,
             C2DLayer       * layer,
             QGraphicsItem  * parent = 0,
             QGraphicsScene * scene  = 0 );

    inline int type()  {  return this->Type;  }

    QPainterPath shape() const   {  return this->s;                                              }
    QRectF boundingRect() const  {  return this->s.controlPointRect().adjusted( -1, -1, 1, 1 );  }

    inline void setPixmap( QPixmap pixmap )     {  this->p = pixmap;  }
    inline void setShape( QPainterPath shape )  {  this->s = shape;   }

protected:
    void paint( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0 );

private:
    QPixmap p;
    QPainterPath s;
};

/*
class SupportingPoints
{
public:
    enum SupportType { Point, Line, Circle, Arc, Spline };
    SupportingPoints(QString Name,SupportType Type) { }
protected:
private:
    SupportType Type;
    QString Name;
    C2DLayer * Layer;

};
*/
#endif // C2DSCENEITEMS_H
