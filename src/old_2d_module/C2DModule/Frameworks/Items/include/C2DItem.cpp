#include "C2DItem.h"

C2DItem::C2DItem() : QGraphicsItemGroup(), C2DExchange()
{
   //d = new DDialog;

//    this->f = new Fabrics( this, this->scene() );
}

void C2DItem::setLayerManager( C2DLayerManager * LM )
{
    this->LM = LM;

    foreach( C2DItem * i, this->children() )
        i->setLayerManager( LM );


}

bool C2DItem::validatePoints()
{
    foreach ( QPointF point, this->P )
    {
        if ( point != point )
                return false;

        if ( ( point.x() >  std::numeric_limits<qreal>::max() ) ||
             ( point.x() < -std::numeric_limits<qreal>::max() ) ||
             ( point.y() >  std::numeric_limits<qreal>::max() ) ||
             ( point.y() < -std::numeric_limits<qreal>::max() ) )
                return false;
    }
    return true;
}

bool C2DItem::validatePointList( int count, QList< QString > points )
{
    if ( points.count() < count )
    {
        qWarning() << this->prefix() << " C2DItem::validatePointList() - count missmatch.";
        return false;
    }

    foreach( QString str, points )
        if ( !this->P.contains( str ) )
        {
            qWarning() << this->prefix() << " C2DItem::validatePointList() has detected point missed.";
            return false;
        }
   // for(int i=0;i<this->scene()->items().count();i++)
   //     this->scene()->removeItem( this->scene()->items().at(i) );
   // for(int i=0;i<paths.count();i++)
   //     scene()->removeItem( paths.at(i) );

    return true;
}

void C2DItem::setFabricsShape()
{
    QPainterPath p;
/*
    foreach ( AbstractItem * i, this->childItems() )
        if ( i->isBorder() &&
             ( ( i->getType() == "Line" ) ||
               ( i->getType() == "Arc" ) ||
               ( i->getType() == "Single Spline" ) ) )
        p->addPath( i->shape() );

    p->closeSubpath();
*/
    p.lineTo( 100.0f, 12.0f );
    p.lineTo( 100.0f, 120.0f );
    p.lineTo( 60.0f, 15.0f );
    p.lineTo( -10.0f, 60.0f );
    p.lineTo( -60.0f, -60.0f );
    p.lineTo( 0.0f, 0.0f );
    this->f->setShape( p );
}

C2DLayer * C2DItem::dashed( bool dashed )
{
    if ( dashed )
        return LM->thick_dashed();
    else
        return LM->thick_solid();
}

C2DItem::~C2DItem()
{
    qDebug() << "Got destructor!";

    this->Items.clear();

    //V.clear();

}

QList< QPair< C2DVariable *, QVariant > > C2DItem::getSheetVariables()
{
    QList< QPair< C2DVariable *, QVariant> > list;

    foreach ( C2DVariable * var, this->variableList() )
    {
        if ( !this->hashContains( var->name() ) )
            qWarning( QString( "Variable %1 missed.").arg( var->name() ).toAscii() );

        list.append( QPair< C2DVariable *, QVariant > ( var, this->V( var->name() ) ) );
    }

    return list;
}



//PointItem * C2DItem::point( C2DSync * Obj, bool f )
//{
//    PointItem * p = NULL;

//    switch ( f )
//    {
//    case ( true ):
//        if ( !Items.contains( Obj->name() ) )
//        {
//            p = new PointItem( P[ Obj->list().at( 0 ) ], Obj->layer(), this, scene() );
//            p->setName( Obj->name() );
//            Items.insert( Obj->name(), p );

//        }
//        else if ( Items.contains( Obj->name() ) )
//        {
//            p = dynamic_cast< PointItem * >( Items.value( Obj->name() ) );
//            p->setPos( P[ Obj->list().at( 0 ) ] );
//        }

//#if defined(C2D_DEBUG)
//        if ( !Items.contains( Obj->name() + "text" ) )
//            Items.insert( Obj->name() + "text",
//                          new TextItem( Obj->name(),
//                                        P[ Obj->list().at(0) ] + QPointF( 5,-15 ),
//                                        0.0f, Obj->layer(), this, scene()));
//        else
//            dynamic_cast< TextItem * >( Items.value( Obj->name() + "text" ) )->setPos( P[Obj->list().at(0) ] + QPointF( 5,-15 ) );
//#endif
//        break;

//    case ( false ):
//        if ( Items.contains( Obj->name() ) )
//        {
//            p = dynamic_cast< PointItem * >( Items.value( Obj->name() ) );

//            scene()->removeItem( p );
//            Items.remove( Obj->name() );
//            delete p;
//            p = NULL;

//            #if defined(C2D_DEBUG)
//                qDebug()<<"Point: "+Obj->name() +" deleted.";
//            #endif
//        }
//#if defined(C2D_DEBUG)
//        if ( Items.contains( Obj->name() + "text") )
//        {
//            scene()->removeItem( Items.value( Obj->name() + "text" ) );
//            delete Items.value( Obj->name() + "text" );
//            Items.remove( Obj->name() + "text" );
//        }
//#endif
//        break;
//    }
//    return p;
//}

//SignItem * C2DItem::sign( QString Label, QString Point, bool Dual, double angle, bool f)
//{
//    SignItem * s = NULL;
//    switch (f)
//    {
//    case (true):
//        if ( !Items.contains( Label ) )
//        {
//            s = new SignItem( P[ Point ], Dual, angle, LM->CurrentLayer(), this, scene() );
//            Items.insert( Label, s );
//        }
//        else
//        {
//            s = dynamic_cast< SignItem * >( Items.value( Label ) );
//            s->setPos( P[ Point ] );
//        }

//#if defined(C2D_DEBUG)
//        if ( !Items.value( Label + "text" ) )
//            Items.insert( Label + "text",
//                          new TextItem( Label + "text", ( P[ Point ] + QPointF( 5,-15 ) ),
//                                              0.0f, LM->CurrentLayer(), this, scene() ) );
//        else
//            dynamic_cast< TextItem * >( Items.value( Label + "text" ) )->setPos( P[ Point ] + QPointF( 5, -15 ) );
//#endif
//        break;

//    case (false):
//        if ( Items.contains( Label ) )
//        {
//            s = dynamic_cast< SignItem * > ( Items.value( Label ) );
//            scene()->removeItem( s );
//            Items.remove( Label );
//            delete s;
//            s = NULL;

//            #if defined(C2D_DEBUG)
//                qDebug()<< "Sign: "+ Label +" deleted.";
//            #endif
//        }
//#if defined(C2D_DEBUG)
//        if ( Items.contains( Label + "text" ) )
//        {
//            scene()->removeItem( Items.value( Label + "text" ) );
//            delete Items.value( Label + "text" );
//            Items.remove( Label + "text" );
//        }
//#endif
//        break;
//    }

//    return s;
//}

//LineItem * C2DItem::line( C2DSync * Obj, bool f)
//{
//    LineItem * l = NULL;

//    switch ( f )
//    {
//    case (true):
//        if ( !Items.contains( Obj->name() ) )
//        {
//            PointItem * p0 = point( MakeSync( Obj->list().at( 0 ), C2DSync::Point,
//                                              MakeList( Obj->list().at( 0 ) ), Obj->layer() ), f );
//            PointItem * p1 = point( MakeSync( Obj->list().at( 1 ), C2DSync::Point,
//                                              MakeList( Obj->list().at( 1 ) ), Obj->layer() ), f );

//            l = new LineItem( p0, p1, Obj->layer(), this, scene() );
//            l->setName( Obj->name() );

//            Items.insert( Obj->name(), l );
//            //#if defined(C2D_DEBUG)
//            //    qDebug() << "Line: " + Obj->name();
//            //#endif
//        }
//        else if ( Items.contains( Obj->name() ) )
//        {
//            point( MakeSync( Obj->list().at( 0 ), C2DSync::Point,
//                             MakeList( Obj->list().at( 0 ) ), Obj->layer() ), f );
//            point( MakeSync( Obj->list().at( 1 ), C2DSync::Point,
//                             MakeList( Obj->list().at( 1 ) ), Obj->layer() ),f);

//            l = dynamic_cast< LineItem * >( Items[ Obj->name() ] );
//            l->SetLayer( Obj->layer() );
//        }
//        break;
//    case ( false ):
//        if ( Items.contains( Obj->name() ) )
//        {
//            scene()->removeItem( Items.value( Obj->name() ) );
//            delete Items.value( Obj->name() );
//            Items.remove( Obj->name() );

//#if defined(C2D_DEBUG)
//            qDebug() << "Line: " + Obj->name() +" deleted! Points:" ;
//#endif

//            dynamic_cast< PointItem * >( Items.value(Obj->list().at( 0 ) ) )->dec_d();
//            dynamic_cast< PointItem * >( Items.value(Obj->list().at( 1 ) ) )->dec_d();

//            if ( dynamic_cast< PointItem * >( Items.value( Obj->list().at( 0 ) ) )->depenency() == 0 )
//                point( MakeSync( Obj->list().at( 0 ), C2DSync::Point,
//                                 MakeList( Obj->list().at( 0 ) ), Obj->layer() ), f );
//            if ( dynamic_cast< PointItem * >( Items.value( Obj->list().at( 1 ) ) )->depenency() == 0 )
//                point( MakeSync( Obj->list().at( 1 ), C2DSync::Point,
//                                MakeList( Obj->list().at( 1 ) ), Obj->layer() ), f );

//#if defined( C2D_DEBUG )
//                qDebug() << "Line: " + Obj->name() +" deleted!" ;
//#endif
//        }
//        break;
//    }
//    return l;
//}

//SingleSplineItem * C2DItem::spline( C2DSync * Obj, bool f)
//{
//    SingleSplineItem * s = NULL;

//    switch( f )
//    {
//    case ( true ):
//        //#if defined(C2D_DEBUG)
//        //    qDebug()<<"Spline: "<< Obj->name();
//        //#endif
//        if ( !Items.contains( Obj->name() ) )
//        {
//            PointItem * p0 = point( MakeSync( Obj->list().at( 0 ), C2DSync::Point,
//                                              MakeList( Obj->list().at( 0 ) ), Obj->layer() ),f);
//            PointItem * p1 = point( MakeSync( Obj->list().at( 3 ), C2DSync::Point,
//                                              MakeList( Obj->list().at( 3 ) ), Obj->layer() ),f);
//            s = new SingleSplineItem( p0, P[ Obj->list().at( 1 ) ], P[ Obj->list().at( 2 ) ], p1,
//                                      Obj->layer(), this, scene() );
//            s->setName( Obj->name() );
//            Items.insert( Obj->name(), s );
//        }
//        else
//        {
//            point( MakeSync( Obj->list().at( 0 ), C2DSync::Point,
//                             MakeList( Obj->list().at( 0 ) ), Obj->layer() ),f);
//            point( MakeSync( Obj->list().at( 3 ), C2DSync::Point,
//                             MakeList( Obj->list().at( 3 ) ), Obj->layer() ),f);
//            s = dynamic_cast< SingleSplineItem * >( Items.value( Obj->name() ) );
//            s->SetStartGuide( P[ Obj->list().at( 1 ) ] );
//            s->SetEndGuide( P[ Obj->list().at( 2 ) ] );
//        }
//        break;
//        case (false):
//        if ( Items.contains( Obj->name() ) )
//        {
//            scene()->removeItem( Items.value( Obj->name() ) );
//            delete Items.value( Obj->name() );
//            Items.remove( Obj->name() );

//            dynamic_cast< PointItem * >( Items.value(Obj->list().at(0) ) )->dec_d();
//            dynamic_cast< PointItem * >( Items.value(Obj->list().at(3) ) )->dec_d();
//            if ( dynamic_cast< PointItem * >( Items.value( Obj->list().at( 0 ) ) )->depenency() == 0 )
//                point( MakeSync( Obj->list().at( 0 ), C2DSync::Point,
//                                 MakeList( Obj->list().at( 0 ) ), Obj->layer() ),f);
//            if ( dynamic_cast< PointItem * >( Items.value( Obj->list().at( 3 ) ) )->depenency() == 0 )
//                point( MakeSync( Obj->list().at( 3 ), C2DSync::Point,
//                                 MakeList( Obj->list().at( 3 ) ), Obj->layer() ),f);
//            #if defined( C2D_DEBUG )
//                qDebug()<<"Spline: "<< Obj->name() <<" deleted;";
//            #endif
//        }
//        break;
//    }
//    return s;
//}

//DartItem * C2DItem::dart( C2DSync *Obj, bool f )
//{
//    DartItem * d = NULL;
//    switch ( f )
//    {
//    case ( true ):
//        //#if defined(C2D_DEBUG)
//        //    qDebug()<<"Dart: "<< Obj->name();
//        //#endif
//        if ( !Items.contains( Obj->name() ) )
//        {
//            PointItem * p0 = point( MakeSync( Obj->list().at( 0 ), C2DSync::Point,
//                                              MakeList( Obj->list().at( 0 ) ), LM->thick_solid() ),f);
//            PointItem * pl = point( MakeSync( Obj->list().at( 1 ), C2DSync::Point,
//                                              MakeList( Obj->list().at( 1 ) ), LM->thick_solid() ),f);
//            PointItem * pr = point( MakeSync( Obj->list().at( 2 ), C2DSync::Point,
//                                              MakeList( Obj->list().at( 2 ) ), LM->thick_solid() ),f);
//            d = new DartItem( p0, pl, pr, Obj->layer(), this, scene() );
//            d->setName( Obj->name() );
//            Items.insert( Obj->name(), d );
//        }
//        else if ( dynamic_cast< DartItem * >( Items.value( Obj->name() ) ) != 0 )
//        {
//            point( MakeSync( Obj->list().at( 0 ), C2DSync::Point,
//                             MakeList( Obj->list().at( 0 ) ), LM->thick_solid() ),f);
//            point( MakeSync( Obj->list().at( 1 ), C2DSync::Point,
//                             MakeList( Obj->list().at( 1 ) ), LM->thick_solid() ),f);
//            point( MakeSync( Obj->list().at( 2 ), C2DSync::Point,
//                             MakeList( Obj->list().at( 2 ) ), LM->thick_solid() ),f);
//            d = dynamic_cast< DartItem * >( Items.value( Obj->name() ) );
//            d->setGuides();
//        }
//        break;
//    case (false):
//        if ( Items.contains( Obj->name() ) )
//        {
//            scene()->removeItem( Items.value( Obj->name() ) );
//            delete Items.value( Obj->name() );
//            Items.remove( Obj->name() );

//            #if defined( C2D_DEBUG )
//                qDebug() << "Dart: " + Obj->name() + " deleted! Points:";
//            #endif

//            dynamic_cast< PointItem * >( Items.value( Obj->list().at( 0 ) ) )->dec_d();
//            dynamic_cast< PointItem * >( Items.value( Obj->list().at( 1 ) ) )->dec_d();
//            dynamic_cast< PointItem * >( Items.value( Obj->list().at( 2 ) ) )->dec_d();
//            if ( dynamic_cast< PointItem * >( Items.value( Obj->list().at( 0 ) ) )->depenency() == 0 )
//                point( MakeSync( Obj->list().at( 0 ), C2DSync::Point,
//                                 MakeList( Obj->list().at( 0 ) ), LM->thick_solid() ), f );
//            if ( dynamic_cast< PointItem * >( Items.value( Obj->list().at( 1 ) ) )->depenency() == 0 )
//                point( MakeSync( Obj->list().at( 1 ), C2DSync::Point,
//                                 MakeList( Obj->list().at( 1 ) ), LM->thick_solid() ), f );
//            if ( dynamic_cast< PointItem * >( Items.value( Obj->list().at( 2 ) ) )->depenency() == 0 )
//                point( MakeSync( Obj->list().at( 2 ), C2DSync::Point,
//                                 MakeList( Obj->list().at( 2 ) ), LM->thick_solid() ), f );
//            #if defined( C2D_DEBUG )
//                qDebug()<<"Dart: " + Obj->name() +" deleted!" ;
//            #endif
//        }
//        break;
//    }
//    return d;
//}

//ArcItem * C2DItem::arc( C2DSync * Obj, bool f )
//{
//    ArcItem * a;
//    switch ( f )
//    {
//    case ( true ):
//          #if defined(C2D_DEBUG)
//            qDebug() << "Arc: "<< Obj->name();
//          #endif
//        if ( !Items.contains( Obj->name() ) )
//        {
//            PointItem * p0 = point( MakeSync( Obj->list().at( 0 ), C2DSync::Point,
//                                              MakeList( Obj->list().at( 0 ) ), LM->thick_solid() ), f );
//            PointItem * pl = point( MakeSync( Obj->list().at( 1 ), C2DSync::Point,
//                                              MakeList( Obj->list().at( 1 ) ), LM->thick_solid() ), f );
//            PointItem * pr = point( MakeSync( Obj->list().at( 2 ), C2DSync::Point,
//                                              MakeList( Obj->list().at( 2 ) ), LM->thick_solid() ),f);
//            a = new ArcItem( p0, pl, pr, Obj->layer(), this, scene() );
//            a->setName( Obj->name() );
//            Items.insert( Obj->name(), a );
//        }
//        else if ( dynamic_cast< ArcItem * >(Items.value( Obj->name() )) != 0 )
//        {
//            #if defined(C2D_DEBUG)
//                qDebug()<<"Update: " << Obj->name() ;
//            #endif
//            point( MakeSync( Obj->list().at( 0 ), C2DSync::Point,
//                             MakeList( Obj->list().at( 0 ) ), LM->thick_solid() ), f );
//            point( MakeSync( Obj->list().at( 1 ), C2DSync::Point,
//                             MakeList( Obj->list().at( 1 ) ), LM->thick_solid() ), f );
//            point( MakeSync( Obj->list().at( 2 ), C2DSync::Point,
//                             MakeList( Obj->list().at( 2 ) ), LM->thick_solid() ), f );
//            a = dynamic_cast< ArcItem * >( Items.value( Obj->name() ) );
//            a->updateDependencies();
//            #if defined(C2D_DEBUG)
//                qDebug()<<"Update: ok";
//            #endif
//        }
//        break;
//    case ( false ):
//        if ( Items.contains( Obj->name() ) )
//        {
//            scene()->removeItem( Items.value( Obj->name() ) );
//            delete Items.value( Obj->name() );
//            Items.remove( Obj->name() );
//            #if defined( C2D_DEBUG )
//                qDebug()<<"Arc: " + Obj->name() +" deleted! Points:" ;
//            #endif
//            dynamic_cast< PointItem * >( Items.value( Obj->list().at( 0 ) ) )->dec_d();
//            dynamic_cast< PointItem * >( Items.value( Obj->list().at( 1 ) ) )->dec_d();
//            dynamic_cast< PointItem * >( Items.value( Obj->list().at( 2 ) ) )->dec_d();
//            if ( dynamic_cast< PointItem * >( Items.value( Obj->list().at( 0 ) ) )->depenency() == 0 )
//                point( MakeSync( Obj->list().at( 0 ), C2DSync::Point,
//                                 MakeList( Obj->list().at( 0 ) ), LM->thick_solid() ), f );
//            if ( dynamic_cast< PointItem * >( Items.value( Obj->list().at( 1 ) ) )->depenency() == 0 )
//                point( MakeSync( Obj->list().at( 1 ), C2DSync::Point,
//                                 MakeList( Obj->list().at( 1 ) ), LM->thick_solid() ), f );
//            if ( dynamic_cast< PointItem * >( Items.value( Obj->list().at( 2 ) ) )->depenency() == 0 )
//                point( MakeSync( Obj->list().at( 2 ), C2DSync::Point,
//                                 MakeList( Obj->list().at( 2 ) ), LM->thick_solid() ), f );
//            #if defined( C2D_DEBUG )
//                qDebug()<<"Arc: " + Obj->name() +" deleted!" ;
//            #endif
//        }
//        break;
//    }
//    return a;
//}


//CircleItem * C2DItem::circle( C2DSync * Obj, bool f )
//{
//    CircleItem * c;
//    switch ( f )
//    {
//    case ( true ):
//        #if defined( C2D_DEBUG )
//            qDebug()<< "Circle: "<< Obj->name();
//        #endif
//        if ( !Items.contains( Obj->name() ) )
//        {
//            PointItem * p0 = point( MakeSync( Obj->list().at( 0 ), C2DSync::Point,
//                                              MakeList( Obj->list().at( 0 ) ), LM->thick_solid() ), f );
//            c = new CircleItem( p0, Obj->radius(), Obj->layer(), this, scene() );
//            Items.insert( Obj->name(), c );
//        }
//        else if ( dynamic_cast< CircleItem * >( Items.value( Obj->name() ) ) != 0 )
//        {
//            #if defined( C2D_DEBUG )
//                qDebug()<<"Update: ";
//            #endif
//            point( MakeSync( Obj->list().at( 0 ), C2DSync::Point,
//                             MakeList( Obj->list().at( 0 ) ), LM->thick_solid() ), f );
//            c = dynamic_cast< CircleItem * >( Items.value( Obj->name() ) );
//            #if defined(C2D_DEBUG)
//                qDebug()<<"Update: ok";
//            #endif
//        }
//        break;
//    case (false):
//        if ( Items.contains( Obj->name() ) )
//        {
//            scene()->removeItem( Items.value( Obj->name() ) );
//            delete Items.value( Obj->name() );
//            Items.remove( Obj->name() );
//            #if defined( C2D_DEBUG )
//                qDebug()<<"Circle: " + Obj->name() +" deleted! Points:" ;
//            #endif
//            dynamic_cast< PointItem * >( Items.value( Obj->list().at( 0 ) ) )->dec_d();
//            if ( dynamic_cast< PointItem * >( Items.value( Obj->list().at( 0 ) ) )->depenency() == 0 )
//                point( MakeSync( Obj->list().at( 0 ), C2DSync::Point,
//                               MakeList( Obj->list().at( 0 ) ), LM->thick_solid() ), f );
//            #if defined( C2D_DEBUG )
//                qDebug()<<"Circle: " + Obj->name() +" deleted!" ;
//            #endif
//        }
//        break;
//    }
//    return c;
//}

//TextItem * C2DItem::text(QString Text, QString Label, double angle, bool f )
//{
//    TextItem * t;
//    switch ( f )
//    {
//    case ( true ):
//        if ( !Items.contains( Label ) )
//        {
//            t = new TextItem( Text, P[ Label ], angle, LM->CurrentLayer(), this, scene() );
//            Items.insert( Label, t );
//        }
//        else
//        {
//            t = dynamic_cast< TextItem * >( Items.value( Label ) );
//            t->setPos( P[ Label ] );
//        }
////#if defined(C2D_DEBUG)
//    //qDebug()<<"Text: " + Label;
////#endif
//        break;
//    case (false):
//        if ( Items.contains( Label ) )
//        {
//            scene()->removeItem( Items.value( Label ) );
//            delete Items.value( Label );
//            Items.remove( Label );

//#if defined( C2D_DEBUG )
//    qDebug()<<"Text: " + Label +" deleted!" ;
//#endif
//     }
//        break;
//    }
//    return t;
//}


