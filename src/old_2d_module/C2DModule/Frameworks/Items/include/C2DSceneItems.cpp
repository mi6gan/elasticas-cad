#include "C2DSceneItems.h"

bool C2DAbstractItem::checkPointer( void    * new_pointer,
                                    void    * old_pointer,
                              const QString & function_name,
                              const QString & point_name )
{
    if ( new_pointer == 0 )
    {
        qWarning() << this->name() << " :: " << function_name
                   << " - trying to set NULL as a " << point_name;
        return false;
    }

    if ( old_pointer == new_pointer )
        return false;

    if ( old_pointer != new_pointer )
        return true;
}

C2DMarker::C2DMarker( const QString  & name,
                      const QColor   & co,
                      C2DLayer       * layer,
                      QGraphicsItem  * parent,
                      QGraphicsScene * scene )
    : C2DTool( name, layer, parent, scene )
{
    this->setColor( co );
    this->value = QList< QVariant >();
}

QRectF C2DMarker::boundingRect() const
{
    return QRectF( this->shape().boundingRect() ).adjusted( -10, -10, 10, 10 );
}

QPainterPath C2DMarker::shape() const
{
    QPainterPath path;

    QList< QVariant > list = this->value.value< QList< QVariant > >();

    if ( !list.isEmpty() )
        path.moveTo( list.at( 0 ).toPointF() );

    if ( list.count() >= 2 )
        for ( int i = 1; i <= list.count() - 1; i++ )
            path.lineTo( list.at( i ).toPointF() );

    qDebug() << path;

    return path;
}

void C2DMarker::drop()
{
    this->value = QList< QVariant >();

    if ( this->isVisible() )
        this->hide();

    this->update();
}

void C2DMarker::setValue( const QVariant & va, bool new_item)
{
    QList< QVariant > list = this->value.value< QList< QVariant > >();

    if ( new_item )
    {
        if ( !this->isVisible() )
            this->show();
        list.append( va );
    }
    else
        list.replace( list.count() - 1, va );

    this->value = list;

    this->update();
}

void C2DMarker::paint( QPainter * painter,
                       const QStyleOptionGraphicsItem * option,
                       QWidget * widget )
{
    painter->setPen( QPen( this->color ) );

    painter->drawPath( this->shape() );
}

C2DSelection::C2DSelection( const QString  & name,
                            const QColor   & co1,
                            const QColor   & co2,
                            C2DLayer       * layer,
                            QGraphicsItem  * parent,
                            QGraphicsScene * scene )
    : C2DTool( name, layer, parent, scene )
{
    this->setColor(  co1 );
    this->setColor2( co2 );
    this->value = QRectF();
    this->color_inverse = false;
}

QRectF C2DSelection::boundingRect() const
{
    return QRectF( this->shape().boundingRect() ).adjusted( -10, -10, 10, 10 );
}

QPainterPath C2DSelection::shape() const
{
    QPainterPath path;

    QRectF rect = this->value.value< QRectF >();

    if ( !rect.isEmpty() )
        path.addRect( rect );

    return path;
}

void C2DSelection::drop()
{
    this->value = QRectF();

    if ( this->isVisible() )
        this->hide();

    this->update();
}

void C2DSelection::setValue( const QVariant & va, bool new_item)
{
    QRectF rect = this->value.value< QRectF >();

    if ( new_item )
    {
        if ( !this->isVisible() )
            this->show();
        rect.setTopLeft( va.toPointF() );
    }
    else
    {
        QPointF tl = rect.topLeft();
        rect = QRectF( tl, va.toPointF() );

        if ( ( va.toPointF().x() - tl.x() ) < 0 )
            this->color_inverse = true;
        else
            this->color_inverse = false;
    }

    this->value = rect;

    this->update();
}

void C2DSelection::paint( QPainter * painter,
                          const QStyleOptionGraphicsItem * option,
                          QWidget * widget )
{
    if ( this->color_inverse )
        painter->setPen( QPen( this->color2 ) );
    else
        painter->setPen( QPen( this->color ) );

    painter->drawPath( this->shape() );
}

QPainterPath Origin::shape() const
{
    QPainterPath Path;

    Path.lineTo( this->origin_stroke_length, 0.0f );
    Path.lineTo( this->origin_stroke_length,
                 this->origin_stroke_length / 25.0f );
    Path.lineTo( this->origin_stroke_length * 1.12f, 0.0f );
    Path.lineTo( this->origin_stroke_length,
                 -this->origin_stroke_length / 25.0f );
    Path.lineTo( this->origin_stroke_length, 0.0f );
    Path.moveTo( 0.0f, 0.0f );
    Path.lineTo( 0.0f, this->origin_stroke_length );
    Path.lineTo( this->origin_stroke_length / 25.0f,
                 this->origin_stroke_length );
    Path.lineTo( 0.0f, this->origin_stroke_length * 1.12f );
    Path.lineTo( -this->origin_stroke_length / 25.0f,
                 this->origin_stroke_length );
    Path.lineTo( 0.0f, this->origin_stroke_length );

    return Path;
}

void Origin::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    QPen pen( this->origin_color );

    painter->setPen( pen );

    painter->drawPath( this->shape() );
}

PointItem::PointItem( const QString  & name,
                      C2DLayer       * layer,
                      QGraphicsItem  * parent,
                      QGraphicsScene * scene)
    : TypedItem< PointItem >( name, layer, parent, scene )
{
    this->link = 0;
    this->setFlag( ItemIsSelectable );
    this->setFlag( ItemIsMovable );
}

QPainterPath PointItem::shape() const
{
    QPainterPath Path;
    if ( !this->isSelected() )
    {
        Path.moveTo( -2,  2 );
        Path.lineTo(  2, -2 );
        Path.moveTo(  2,  2 );
        Path.lineTo( -2, -2 );
    }
    else
        Path.addRect( QRectF( -2, -2, 4, 4 ) );

    return Path;
}

void PointItem::paint(QPainter * painter,
                      const QStyleOptionGraphicsItem * option,
                      QWidget * widget )
{
    painter->setPen( this->layer()->pen() );

    QPainterPath Path = this->shape();

    if ( option->state & QStyle::State_Selected )
        painter->setBrush( Qt::yellow );

    painter->drawPath( Path );
}

QVariant PointItem::itemChange( GraphicsItemChange change, const QVariant & value )
{
    if ( change == QGraphicsItem::ItemPositionChange )
    {
//        this->parent_item->update();
    }
    return value;
}
///////////////////////////////////lol
PpathItem::PpathItem( const QString  & name,
                      C2DLayer       * layer,
                      QGraphicsItem  * parent,
                      QGraphicsScene * scene)
    : TypedItem< PpathItem >( name, layer, parent, scene )
{
    this->link = 0;
    this->setFlag( ItemIsSelectable );
    this->setFlag( ItemIsMovable );
}

QPointF PpathItem::pointatpersent( double a )
{
    if( a < 0 )
        a = 0;
    if( a > 1 )
        a = 1;
    QPainterPath Path;
    Path = this->shape();
    QPointF b,p = Path.pointAtPercent( a );
    b = Path.pointAtPercent(0);
    if( mirror == 1 )
        p = QPointF( b.x() + ( ( p.x() - b.x() ) * ( -1 ) ), p.y() );

    if(angle!=0)
        p = Unicus::rPoint( p,b,angle );

    return p;
}


QPainterPath PpathItem::shape() const
{
    QPainterPath Path;
    Path = this->ppath_path;
    if ( !this->isSelected() )
    {
  //      Path.moveTo( -2,  2 );
  //      Path.lineTo(  2, -2 );
  //      Path.moveTo(  2,  2 );
  //      Path.lineTo( -2, -2 );
    }
  //  else
  //      Path.addRect( QRectF( -2, -2, 4, 4 ) );

    return Path;
}

QPainterPath PpathItem::myshape( QPointF p,double shag )
{
    QPainterPath Path;
    QPointF delta = pointatpersent(0) - p;
    Path.moveTo( p );
    double l = shape().length();
    double cur_l = 0;
    while( cur_l + shag < l )
    {
        cur_l = cur_l + shag;
        Path.lineTo( pointatpersent( cur_l/l ) - delta );
    }
    Path.lineTo( pointatpersent(1) - delta );
    return Path;
}

void PpathItem::paint(QPainter * painter,
                      const QStyleOptionGraphicsItem * option,
                      QWidget * widget )
{
    painter->setPen( this->layer()->pen() );

    QPainterPath Path = this->shape();

    //if ( option->state & QStyle::State_Selected )
    //    painter->setBrush( Qt::yellow );

    if( mirror == 1 )
    {
        painter->translate( (Path.pointAtPercent(0).x()*2),0 );
        painter->scale( -1, 1 );
    }
    if( mirror == 2 )
        painter->scale( 1, -1 );
    if( mirror == 3 )
        painter->scale( -1, -1 );

    if(angle!=0)
    {
        painter->translate( Path.pointAtPercent(0) - Unicus::rPoint( Path.pointAtPercent(0),QPointF(0,0),angle) );
        painter->rotate( angle );
    }


 //   painter->translate( QPointF( 5.0f,30.0f ) );
    painter->drawPath( Path );

}

QVariant PpathItem::itemChange( GraphicsItemChange change, const QVariant & value )
{
    if ( change == QGraphicsItem::ItemPositionChange )
    {
//        this->parent_item->update();
    }
    return value;
}
///////////////////////////////////lol
ButtonItem::ButtonItem( const QString  & name,
                      C2DLayer       * layer,
                      QGraphicsItem  * parent,
                      QGraphicsScene * scene)
    : TypedItem< ButtonItem >( name, layer, parent, scene )
{
    this->link = 0;
    this->setFlag( ItemIsSelectable );
    this->setFlag( ItemIsMovable );
}

QPainterPath ButtonItem::shape() const
{
    QPainterPath Path;
    Path.moveTo(-2,0);
    Path.lineTo(2,0);
    Path.moveTo(0,2);
    Path.lineTo(0,-2);


    if ( !this->isSelected() )
    {
  //      Path.moveTo( -2,  2 );
  //      Path.lineTo(  2, -2 );
  //      Path.moveTo(  2,  2 );
  //      Path.lineTo( -2, -2 );
    }
  //  else
  //      Path.addRect( QRectF( -2, -2, 4, 4 ) );

    return Path;
}

void ButtonItem::paint(QPainter * painter,
                      const QStyleOptionGraphicsItem * option,
                      QWidget * widget )
{
    painter->setPen( this->layer()->pen() );

    QPainterPath Path = this->shape();

    if ( option->state & QStyle::State_Selected )
        painter->setBrush( Qt::yellow );


 //   painter->translate( QPointF( 5.0f,30.0f ) );
    painter->drawPath( Path );

}

QVariant ButtonItem::itemChange( GraphicsItemChange change, const QVariant & value )
{
    if ( change == QGraphicsItem::ItemPositionChange )
    {
//        this->parent_item->update();
    }
    return value;
}
//////////////////////////////////lol
SignItem::SignItem( const QString  & name,
                    C2DLayer       * layer,
                    QGraphicsItem  * parent,
                    QGraphicsScene * scene)
    : TypedItem< SignItem >( name, layer, parent, scene )
{
    this->color = QColor( 255, 255, 255 );
    this->setFlag( ItemIsSelectable );
    this->setFlag( ItemIsMovable );
}

QPainterPath SignItem::GetShapeByAngle( const bool & dual, const double & angle ) const
{
    QPainterPath Path;
    double a = angle * M_PI / 180.0f;
    QLineF line( QPointF( 1.0f * cos( a ), 1.0f * sin( a ) ),
                 QPointF( 7.0f * cos( a ), 7.0f * sin( a ) ) );

    Path.moveTo( 1, 0 );
    Path.arcTo( QRectF( -1.0f, -1.0f, 2.0f, 2.0f ), 0.0f, 360.0f );
    Path.moveTo( line.p1() );
    Path.lineTo( line.p2() );
    Path.moveTo( line.p2() + 2.0f * ( line.normalVector().unitVector().p2() -
                                      line.normalVector().unitVector().p1() ) );
    Path.lineTo( line.p2() - 2.0f * ( line.normalVector().unitVector().p2() -
                                      line.normalVector().unitVector().p1() ) );
    if ( this->dual )
    {
        line.setPoints( QPointF( -1.0f * cos( this->angle ), -1.0f * sin( this->angle ) ),
                        QPointF( -7.0f * cos( this->angle ), -7.0f * sin( this->angle ) ) );
        Path.moveTo( line.p1() );
        Path.lineTo( line.p2() );
        Path.moveTo( line.p2() + 2.0f * ( line.normalVector().unitVector().p2() -
                                          line.normalVector().unitVector().p1() ) );
        Path.lineTo( line.p2() - 2.0f * ( line.normalVector().unitVector().p2() -
                                          line.normalVector().unitVector().p1() ) );
    }
    return Path;
}

QRectF SignItem::boundingRect() const
{
    return this->GetShapeByAngle( this->dual, this->angle ).boundingRect();
}

QPainterPath SignItem::shape() const
{
    return this->GetShapeByAngle( this->dual, this->angle );
}

void SignItem::paint( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget )
{
    painter->setPen( this->layer()->pen() );

    if ( option->state & QStyle::State_Selected )
        painter->setBrush( Qt::yellow );

    painter->drawPath( this->GetShapeByAngle( this->dual, this->angle ) );
}
//// LOL4

//// LOL4
BadPathItem::BadPathItem( const QString  & name,
                    C2DLayer       * layer,
                    QGraphicsItem  * parent,
                    QGraphicsScene * scene)
    : TypedItem< BadPathItem >( name, layer, parent, scene )
{
    this->color = QColor( 255, 255, 255 );
    this->setFlag( ItemIsSelectable );
    this->setFlag( ItemIsMovable );
}

QPainterPath BadPathItem::GetShapeByAngle( const bool & dual, const double & angle ) const
{
    QPainterPath Path1,Path2,Path1m,Path2m,edi2,edi1,end;
    QLineF line1,line2;
    QPointF centerp,p1m,p2m,p3m,p5m,p6m,p7m,p0=QPointF(0,0);
    double delta=QLineF(p4,p5).angle()-QLineF(p0,p1).angle(),
           delta2=QLineF(p0,p1).angle()-QLineF(p4,p5).angle() ;

    if(angle==0)
    {
        Path1.moveTo( 0, 0 );
        Path1.cubicTo(  p1, p2, p3 );
        Path2.moveTo( p7 );
        Path2.cubicTo( p6,p5,p4 );
        return Path1;
    }
    centerp = QLineF(p0,p4).pointAt(0.5f);
    p1m = Unicus::rPoint( p1,centerp,180.0f );
    p1m = Unicus::rPoint( p1m,p4,-delta );

    p2m = Unicus::rPoint( p2,centerp,180.0f );
    p2m = Unicus::rPoint( p2m,p4,-delta );

    p3m = Unicus::rPoint( p3,centerp,180.0f );
    p3m = Unicus::rPoint( p3m,p4,-delta );


    p5m = Unicus::rPoint( p5,centerp,180.0f );
    p5m = Unicus::rPoint( p5m,p0,-delta2 );

    p6m = Unicus::rPoint( p6,centerp,180.0f );
    p6m = Unicus::rPoint( p6m,p0,-delta2 );

    p7m = Unicus::rPoint( p7,centerp,180.0f );
    p7m = Unicus::rPoint( p7m,p0,-delta2 );
    Path2m.moveTo(p0);
    Path2m.cubicTo(p5m,p6m,p7m);
    Path1m.moveTo(p4);
    Path1m.cubicTo(p1m,p2m,p3m);


    if(angle>0)
    {
        Path1.moveTo( 0, 0 );
        Path1.cubicTo(  p1, p2, p3 );
        Path2.moveTo( p7 );
        Path2.cubicTo( p6,p5,p4 );

        edi1 = Path2m.simplified();
        edi2 = Path2.simplified();
        end.moveTo(edi1.elementAt(0));
             for(int i=1;i<(edi1.elementCount());i++)
             {
                end.lineTo(edi1.elementAt(i));
                if ( end.length()>= angle )
                    break;
             }
        delta = end.length();
        end.moveTo( 0, 0 );
        end.cubicTo(  p1, p2, p3 );

        double temp = end.length();
        end.moveTo(edi2.elementAt(0));
             for(int i=1;i<(edi2.elementCount());i++)
             {
                 if ( ( end.length()-temp+( QLineF( end.currentPosition(),
                                                    edi2.elementAt(i) ).length() ) )>=
                      (Path2.length() - delta) )
                 {
                    end.lineTo(Path2.pointAtPercent( 1.0f - delta/Path2.length() ));
                    break;
                 }
                 end.lineTo(edi2.elementAt(i));
             }
    }else
    {
        Path1.moveTo( p3 );
        Path1.cubicTo(  p2, p1, p0 );
        Path2.moveTo( p4 );
        Path2.cubicTo( p5,p6,p7 );

        edi1 = Path1m.simplified();
        edi2 = Path1.simplified();

        end.moveTo(edi1.elementAt(0));
             for(int i=1;i<(edi1.elementCount());i++)
             {
                end.lineTo(edi1.elementAt(i));
                if ( end.length()>= -angle )
                    break;
             }
        delta = end.length();
        end.moveTo( p4 );
        end.cubicTo(  p5, p6, p7 );

        double temp = end.length();
        end.moveTo(edi2.elementAt(0));
             for(int i=1;i<(edi2.elementCount());i++)
             {
                 if ( ( end.length()-temp+( QLineF( end.currentPosition(),
                                                    edi2.elementAt(i) ).length() ) )>=
                      (Path1.length() - delta) )
                 {
                    end.lineTo(Path1.pointAtPercent( 1.0f - delta/Path1.length() ));
                    break;
                 }
                 end.lineTo(edi2.elementAt(i));
             }
    }




    return end;
}

QRectF BadPathItem::boundingRect() const
{
    return this->GetShapeByAngle( this->dual, this->angle ).boundingRect();
}

QPainterPath BadPathItem::shape() const
{
    return this->GetShapeByAngle( this->dual, this->angle );
}

void BadPathItem::paint( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget )
{
    painter->setPen( this->layer()->pen() );

    if ( option->state & QStyle::State_Selected )
        painter->setBrush( Qt::yellow );

    painter->drawPath( this->GetShapeByAngle( this->dual, this->angle ) );
}
///TOTEL LOL4end
LineItem::LineItem( const QString  & name,
                    C2DLayer       * layer,
                    QGraphicsItem  * parent,
                    QGraphicsScene * scene )
        :TypedItem< LineItem >( name, layer, parent, scene )
{
    this->start = 0;
    this->end   = 0;
    this->setFlag( ItemIsSelectable );
    this->setFlag( ItemIsMovable );
}

QPointF LineItem::startPoint() const
{
    if ( this->start != 0 )
        return this->start->pos();
    else
        return QPointF( 0.0f, 0.0f );
}

QPointF LineItem::endPoint() const
{
    if ( this->end != 0 )
        return this->end->pos();
    else
        return QPointF( 0.0f, 0.0f );
}

QRectF LineItem::boundingRect() const
{
    return QRectF( QPointF( 0.0f, 0.0f ), this->endPoint() - this->startPoint() )
           .adjusted( -1, -1, 2, 2 );
}


QPainterPath LineItem::shape() const
{
    QPainterPath Path;

    Path.moveTo( 0.0f, 0.0f );

    Path.lineTo( this->endPoint() - this->startPoint() );

    return Path;
}

QVariant LineItem::itemChange( GraphicsItemChange change, const QVariant & value )
{
    if ( change == QGraphicsItem::ItemSelectedChange )
    {
        if ( value == true )
        {
            qDebug() << "It has become selected" ;
       // start->setFlag(ItemIsSelectable,true);
        //start->setSelected(true);
        //end->setFlag(ItemIsSelectable,true);
        //end->setSelected(true);
         }
        else
        {
            qDebug() << "It has become not selected" ;
            start->setFlag(ItemIsSelectable,false);
            start->setSelected(false);
            end->setFlag(ItemIsSelectable,false);
            end->setSelected(false);
        }
    }
    return value;
}

void LineItem::setStartPoint( PointItem * start )
{
    if ( this->checkPointer( start, this->start,
                             QString( "LineItem::setStartPoint()" ), QString( "start point" ) ) )
    {
        if ( this->start != 0 )
            this->start->dec_d();

        this->start = start;
        this->start->inc_d();
    }
}

void LineItem::setEndPoint( PointItem * end )
{
    if ( this->checkPointer( end, this->end,
                             QString( "LineItem::setEndPoint()" ), QString( "end point" ) ) )
    {
        if ( this->end != 0 )
            this->end->dec_d();

        this->end = end;
        this->end->inc_d();
    }
}

void LineItem::paint( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget )
{
    painter->setPen( this->layer()->pen() );

    if ( option->state & QStyle::State_Selected )
        painter->setPen( Qt::DashLine );

    painter->drawPath( this->shape() );
}

CircleItem::CircleItem( const QString  & name,
                        C2DLayer       * layer,
                        QGraphicsItem  * parent,
                        QGraphicsScene * scene)
    : TypedItem< CircleItem >( name, layer, parent, scene )
{
    this->circle_center = 0;
    this->circle_radius = 0;
}

QPainterPath CircleItem::shape() const
{
    QPainterPath path;

    path.moveTo( this->circle_center->pos() + QPointF( this->circle_radius, 0.0f ) );
    path.arcTo( QRectF( this->circle_center->pos() - QPointF( this->circle_radius,
                                                              this->circle_radius ),
                        this->circle_center->pos() + QPointF( this->circle_radius,
                                                              this->circle_radius ) ), 0.0f, 360.0f );

    return path;
}

QRectF CircleItem::boundingRect() const
{
    return this->shape().boundingRect().adjusted( -1, -1, 1, 1 );
}

void CircleItem::setCenter( PointItem * center )
{
    if ( this->checkPointer( center, this->circle_center,
                             QString( "CircleItem::setCenter()" ), QString( "center point" ) ) )
    {
        if ( this->circle_center != 0 )
            this->circle_center->dec_d();

        this->circle_center = center;
        this->circle_center->inc_d();
    }
}

void CircleItem::setRadius( double radius )
{
    this->circle_radius = radius;
}

void CircleItem::paint( QPainter * painter,
                        const QStyleOptionGraphicsItem * option,
                        QWidget * widget)
{
    painter->setPen( this->layer()->pen() );

    if ( option->state & QStyle::State_Selected )
        painter->setPen( Qt::DashLine );

    painter->drawPath( this->shape() );
}

ArcItem::ArcItem( const QString  & name,
                  C2DLayer       * layer,
                  QGraphicsItem  * parent,
                  QGraphicsScene * scene)
    : TypedItem< ArcItem >( name, layer, parent, scene )
{
    this->arc_center = 0;
    this->arc_start = 0;
    this->arc_end = 0;
}

void ArcItem::setCenter( PointItem * center )
{
    if ( this->checkPointer( center, this->arc_center,
                             QString( "ArcItem::setCenter()" ), QString( "center point" ) ) )
    {
        if ( this->arc_center != 0 )
            this->arc_center->dec_d();

        this->arc_center = center;
        this->arc_center->inc_d();
    }
}

void ArcItem::setStart( PointItem * start )
{
    if ( this->checkPointer( start, this->arc_start,
                             QString( "ArcItem::setStart()" ), QString( "start point" ) ) )
    {
        if ( this->arc_start != 0 )
            this->arc_start->dec_d();

        this->arc_start = start;
        this->arc_start->inc_d();
    }
}

void ArcItem::setEnd( PointItem * end )
{
    if ( this->checkPointer( end, this->arc_end,
                             QString( "ArcItem::setStart()" ), QString( "start point" ) ) )
    {
        if ( this->arc_end != 0 )
            this->arc_end->dec_d();

        this->arc_end = end;
        this->arc_end->inc_d();
    }
}

void ArcItem::updateDependencies()
{
    if ( this->arc_center && this->arc_start && this->arc_end )
    {
        this->arc_radius      = QLineF( QPointF( 0.0f, 0.0f ),
                                        this->arc_start->pos() - this->arc_center->pos() ).length();
        this->arc_angle_start = QLineF( QPointF( 0.0f, 0.0f ),
                                        this->arc_start->pos() - this->arc_center->pos() ).angle();
        this->arc_angle_end   = QLineF( QPointF( 0.0f, 0.0f ),
                                        this->arc_end->pos() - this->arc_center->pos() ).angle() -
                                this->arc_angle_start;

        if ( this->arc_angle_end >= 180.0f )
            this->arc_angle_end = -( 360.0f - this->arc_angle_end );
        if ( this->arc_angle_end <= -180.0f )
            this->arc_angle_end = ( 360.0f + this->arc_angle_end );
    }
}

QRectF ArcItem::boundingRect() const
{
    return this->shape().boundingRect().adjusted( -1, -1, 1, 1 );
}

QPainterPath ArcItem::shape() const
{
    QPainterPath Path;

    if ( this->arc_center && this->arc_start && this->arc_end )
    {
        Path.moveTo( this->arc_start->pos() - this->arc_center->pos() );
        Path.arcTo( QRectF( QPointF( -this->arc_radius, this->arc_radius ),
                            QSizeF(  2.0f * this->arc_radius, 2.0f * this->arc_radius ) ),
                    this->arc_angle_start, this->arc_angle_end );

//        Path.addRect( QRectF( QPointF( -this->arc_radius, this->arc_radius ),
//                              QSizeF(  2.0f * this->arc_radius, 2.0f * this->arc_radius ) ) );
    }

//    qDebug() << "Arc::pos()      : " << this->pos();
//    qDebug() << "Arc::shape()    : " << Path;
//    qDebug() << "Arc::arc_center : " << this->arc_center;
//    qDebug() << "Arc::arc_start  : " << this->arc_start;
//    qDebug() << "Arc::arc_end    : " << this->arc_end;
//    qDebug() << "Arc::arc_radius : " << this->arc_radius;
//    qDebug() << "Arc::arc_angle_start : " << this->arc_angle_start;
//    qDebug() << "Arc::arc_angle_end   : " << this->arc_angle_end;

    return Path;
}

void ArcItem::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget )
{
    this->updateDependencies();

    if ( option->state & QStyle::State_Selected )
        painter->setPen( Qt::DashLine );

    painter->setPen( this->layer()->pen() );

    painter->drawPath( this->shape() );
}

SplineItem::SplineItem( const QString        & name,
                              C2DLayer       * layer ,
                              QGraphicsItem  * parent,
                              QGraphicsScene * scene )
    : TypedItem< SplineItem >( name, layer, parent, scene )
{
    this->spline_start = 0;
    this->spline_end   = 0;
    this->startGuide   = QPointF( 0.0f, 0.0f );
    this->endGuide     = QPointF( 0.0f, 0.0f );
    this->start_factor = 1.0f;
    this->end_factor   = 1.0f;
}

void SplineItem::setStart( PointItem     * start,
                           const QPointF & start_guide,
                           double          start_factor )
{
    if ( this->checkPointer( start, this->spline_start,
                             QString( "SingleSplineItem::setStart()" ), QString( "start point" ) ) )
    {
        if ( this->spline_start != 0 )
            this->spline_start->dec_d();

        this->spline_start = start;
        this->spline_start->inc_d();
    }

    this->startGuide = start_guide;

    this->start_factor = start_factor;

    this->setGuides();
}

void SplineItem::setEnd( PointItem     * end,
                         const QPointF & end_guide,
                         double          end_factor )
{
    if ( this->checkPointer( end, this->spline_end,
                             QString( "SingleSplineItem::setEnd()" ), QString( "end point" ) ) )
    {
        if ( this->spline_end != 0 )
            this->spline_end->dec_d();

        this->spline_end = end;
        this->spline_end->inc_d();
    }

    this->endGuide = end_guide;

    this->end_factor = end_factor;

    this->setGuides();
}

QPainterPath SplineItem::shape() const
{
    QPainterPath Path;

    Path.moveTo( 0.0f, 0.0f );

    if ( ( this->spline_start != 0 ) && ( this->spline_end != 0 ) )
        Path.cubicTo( StartGuide.pointAt( this->start_factor ) - this->spline_start->pos(),
                      EndGuide.pointAt( this->end_factor )     - this->spline_start->pos(),
                      this->spline_end->pos() - this->spline_start->pos() );

    return Path;
}

QRectF SplineItem::boundingRect() const
{
    return this->shape().controlPointRect().adjusted( -1, -1, 1, 1 );
}

void SplineItem::paint( QPainter * painter,
                        const QStyleOptionGraphicsItem * option,
                        QWidget * widget)
{
    painter->setPen( this->layer()->pen() );

    if ( option->state & QStyle::State_Selected )
        painter->setPen( Qt::DashLine );

    painter->drawPath( this->shape() );
}

void SplineItem::setGuides()
{
    if ( ( this->spline_start != 0 ) && ( this->spline_end != 0 ) )
    {
        this->StartGuide = QLineF( this->spline_start->pos(), startGuide );
        this->EndGuide   = QLineF( this->spline_end->pos(),   endGuide );
    }
}

DartItem::DartItem( const QString  & name,
                    C2DLayer       * layer ,
                    QGraphicsItem  * parent,
                    QGraphicsScene * scene )
    : TypedItem< DartItem >( name, layer, parent, scene )
{
    this->setFlag( ItemIsSelectable );
    this->setFlag( ItemIsMovable );

    this->kb = 0.1f;
    this->kl = 1.0f;
    this->kr = 1.0f;
    this->kk = 10.0f;
    this->cl = 3.0f;
    this->cr = 3.0f;

    this->Tc = new PointItem( QString( "%1 : %2" )
                              .arg( this->name() )
                              .arg( QString( "top center point." ) ),
                              this->layer(), this, scene );
    #if defined( C2D_DEBUG )
        this->D1 = new PointItem( QString( "%1 : %2" )
                                  .arg( this->name() )
                                  .arg( QString( "left guide debug point." ) ),
                                  this->layer(), this, scene );
        this->D2 = new PointItem( QString( "%1 : %2" )
                                  .arg( this->name() )
                                  .arg( QString( "right guide debug point." ) ),
                                  this->layer(), this, scene );
        this->D3 = new PointItem( QString( "%1 : %2" )
                                  .arg( this->name() )
                                  .arg( QString( "left connection debug point." ) ),
                                  this->layer(), this, scene );
        this->D4 = new PointItem( QString( "%1 : %2" )
                                 .arg( this->name() )
                                 .arg( QString( "right connection debug point." ) ),
                                 this->layer(), this, scene );
    #endif

    this->Pl = new PointItem( QString( "%1 : %2" )
                              .arg( this->name() )
                              .arg( QString( "left top point." ) ),
                              this->layer(), this, scene );
    this->Pr = new PointItem( QString( "%1 : %2" )
                              .arg( this->name() )
                              .arg( QString( "right top point." ) ),
                              this->layer(), this, scene );
    this->P0 = new PointItem( QString( "%1 : %2" )
                              .arg( this->name() )
                              .arg( QString( "bottom point." ) ),
                              this->layer(), this, scene );

    this->leftSpline = new SplineItem( QString( "%1 : %2" )
                                       .arg( this->name() )
                                       .arg( QString( "left spline." ) ),
                                       this->layer(), this, scene );

    this->rightSpline = new SplineItem( QString( "%1 : %2" )
                                        .arg( this->name() )
                                        .arg( QString( "right spline." ) ),
                                        this->layer(), this, scene );


    this->leftSpline->setStart( this->P0, QPointF( 0.0f, 0.0f ) );
    this->leftSpline->setEnd( this->Pl, QPointF( 0.0f, 0.0f ) );
    this->leftSpline->setVisible( false );
    this->leftVisible = true;

    this->rightSpline->setStart( this->P0, QPointF( 0.0f, 0.0f ) );
    this->rightSpline->setEnd( this->Pr, QPointF( 0.0f, 0.0f ) );
    this->rightSpline->setVisible( false );
    this->rightVisible = true;
}

void DartItem::setP0( PointItem * p0 )
{
    if ( this->checkPointer( p0, this->P0,
                             QString( "DartItem::setP0()" ), QString( "bottom point" ) ) )
    {
        if ( this->P0 != 0 )
            this->P0->dec_d();

        this->P0 = p0;
        this->P0->inc_d();
    }

    this->setGuides();

    this->leftSpline->setStart( p0, this->BottomGuide );
    this->rightSpline->setStart( p0, this->BottomGuide );
}

void DartItem::setPR( PointItem * pr )
{
    if ( this->checkPointer( pr, this->Pr,
                             QString( "DartItem::setPR()" ), QString( "top right point" ) ) )
    {
        if ( this->Pr != 0 )
            this->Pr->dec_d();

        this->Pr = pr;
        this->Pr->inc_d();
    }

    this->setGuides();

    this->rightSpline->setEnd( pr, this->RightGuide );
}

void DartItem::setPL( PointItem * pl )
{
    if ( this->checkPointer( pl, this->Pl,
                             QString( "DartItem::setPL()" ), QString( "top left point" ) ) )
    {
        if ( this->Pl != 0 )
            this->Pl->dec_d();

        this->Pl = pl;
        this->Pl->inc_d();
    }

    this->setGuides();

    this->leftSpline->setEnd( pl, this->LeftGuide );
}

void DartItem::setGuides()
{
    if ( ( this->P0 != 0 ) && ( this->Pl != 0 ) && ( this->Pr != 0 ) )
        if ( ( this->P0->pos() != this->Pl->pos() ) &&
             ( this->P0->pos() != this->Pr->pos() ) &&
             ( this->Pl->pos() != this->Pr->pos() ) )
    {
        //To do : relative origin
        QLineF l1( ( this->Pl->pos() + this->Pr->pos() ) / 2.0f - this->P0->pos(),
                   QPointF( 0.0f, 0.0f ) );

        QLineF l2 = QLineF( this->Pl->pos(), this->Pr->pos() );
        QLineF ll = QLineF( this->Pl->pos(), this->P0->pos() );
        QLineF lr = QLineF( this->Pr->pos(), this->P0->pos() );

        this->height = l1.length();
        this->spread = l2.length();

        QLineF lln = QLineF( ll.pointAt( 0.5f ),
                            Unicus::uNormal( ll, true ).translated( ll.pointAt( 0.5f ) ).p2() );
        QLineF lrn = QLineF( lr.pointAt( 0.5f ),
                           Unicus::uNormal( lr, false ).translated( lr.pointAt( 0.5f ) ).p2() );

        lln.setLength( kk * 2.0f );
        lrn.setLength( kk * 2.0f );

        //To do : global origin
        this->Tc->setPos( l1.p1() );

        this->BottomGuide = this->P0->pos() + l1.pointAt( 1 - kb );
        this->LeftGuide   = QLineF( Pl->pos(), lln.p2() ).pointAt( kl );
        this->RightGuide  = QLineF( Pr->pos(), lrn.p2() ).pointAt( kr );

        this->leftSpline->setStart( this->leftSpline->start(), this->BottomGuide );
        this->leftSpline->setEnd(   this->leftSpline->end(),   this->LeftGuide   );
        this->leftVisible = true;

        this->rightSpline->setStart( this->rightSpline->start(), this->BottomGuide );
        this->rightSpline->setEnd(   this->rightSpline->end(),   this->RightGuide  );
        this->rightVisible = true;

        QLineF cll = QLineF( this->Pl->pos(),
                             Unicus::rPoint( this->LeftGuide,  this->Pl->pos(), 270.0f ) );
        QLineF clr = QLineF( this->Pr->pos(),
                             Unicus::rPoint( this->RightGuide, this->Pr->pos(), -270.0f ) );

        cll.setLength( cl );
        clr.setLength( cr );

        this->ConnectionLeft  = cll.p2();
        this->ConnectionRight = clr.p2();

    #if defined( C2D_DEBUG )
        this->D1->setPos( this->LeftGuide  - this->P0->pos() );
        this->D2->setPos( this->RightGuide - this->P0->pos() );
        this->D3->setPos( this->ConnectionLeft  - this->P0->pos() );
        this->D4->setPos( this->ConnectionRight - this->P0->pos() );
    #endif

        this->leftSpline->update();
        this->rightSpline->update();
    }
}

QRectF DartItem::boundingRect() const
{
    return this->shape().controlPointRect().adjusted( -1, -1, 1, 1 );
}

QPainterPath DartItem::shape() const
{
    QPainterPath path;

    if ( this->leftVisible )
        path.addPath( this->leftSpline->shape() );

    if ( this->rightVisible )
        path.addPath( this->rightSpline->shape() );

    return path;
}

void DartItem::paint(QPainter * painter,
                     const QStyleOptionGraphicsItem * option,
                     QWidget * widget)
{
    painter->setPen( this->layer()->pen() );

    if ( option->state & QStyle::State_Selected )
        painter->setPen( Qt::DashLine );

    painter->drawPath( this->shape() );
}

VentItem::VentItem( const QString  & name,
                    PointItem      * p0,
                    PointItem      * p1,
                    PointItem      * p2,
                    C2DLayer       * layer,
                    QGraphicsItem  * parent,
                    QGraphicsScene * scene )
    : TypedItem< VentItem >( name, layer, parent, scene )
{

}

QRectF VentItem::boundingRect() const
{

}

QPainterPath VentItem::shape() const
{

}

void VentItem::paint( QPainter * painter,
                      const QStyleOptionGraphicsItem * option,
                      QWidget * widget )
{

}

TextItem::TextItem( const QString  & name,
                    C2DLayer       * layer,
                    QGraphicsItem  * parent,
                    QGraphicsScene * scene )
    : TypedItem< TextItem >( name, layer, parent, scene )
{
    this->item_font = QFont( "Calibri", 15, 1, false );

    this->setMatrix( QMatrix( 1, 0, 0, -1, 0, 0 ) );
}

void TextItem::setText( const QString & text )
{
    this->item_text = text;

    QPainterPath Path;

    Path.addText( QPointF(), this->item_font, this->item_text );

    this->setPath( Path );
}

void TextItem::paint( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget )
{
    painter->setPen( this->layer()->pen() );

    painter->drawText( QPoint(), this->item_text );
}

Fabrics::Fabrics( const QString  & name,
                  C2DLayer       * layer,
                  QGraphicsItem  * parent,
                  QGraphicsScene * scene )
    : TypedItem< Fabrics >( name, layer, parent, scene )
{

}

void Fabrics::paint( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget )
{
    painter->setBrush( QBrush( this->p ) );

    painter->drawPath( this->s );
}
