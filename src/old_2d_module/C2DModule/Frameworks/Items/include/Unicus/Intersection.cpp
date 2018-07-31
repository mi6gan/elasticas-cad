#include "Intersection.h"
#include "QPainterPath"
namespace Unicus
{
    QPointF splinepointony( QPainterPath spline , double yy,double n)
    {
        double shag,persent=0.5f;

        if (spline.pointAtPercent(0).y()>spline.pointAtPercent(1).y())
            shag = -0.5f;
        else
            shag = 0.5f;


        for ( int i = 1; i < 200; i = i + 1 )
        {
            if ((  (spline.pointAtPercent( persent ).y() - yy)  <=  n)&&
                    (  (spline.pointAtPercent( persent ).y() - yy)  >=  -n))
            {
                return spline.pointAtPercent( persent );
            }
            shag = shag/2;

            if ( spline.pointAtPercent( persent ).y() <  yy)
            {
                persent = persent + shag;
            }
           else
            {
                persent = persent - shag;
            }


          //  qDebug()<< "persent = " <<persent<<"Ys "<<spline.pointAtPercent( persent ).y()<<"Y"<< yy<< shag<<" cycle N"<<i ;
        }
        return spline.pointAtPercent( persent );
    }
    QPointF splinepointonx( QPainterPath spline , double xx,double n )
    {
        double shag,persent=0.5f;

        if (spline.pointAtPercent(0).x()>spline.pointAtPercent(1).x())
            shag = -0.5f;
        else
            shag = 0.5f;


        for ( int i = 1; i < 200; i = i + 1 )
        {
            if ((  (spline.pointAtPercent( persent ).x() - xx)  <=  n)&&
                    (  (spline.pointAtPercent( persent ).x() - xx)  >=  -n))
            {
                return spline.pointAtPercent( persent );
            }
            shag = shag/2;

            if ( spline.pointAtPercent( persent ).x() <  xx)
            {
                persent = persent + shag;
            }
           else
            {
                persent = persent - shag;
            }

          //  qDebug()<< "persent = " <<persent<<"Ys "<<spline.pointAtPercent( persent ).y()<<"Y"<< yy<< shag<<" cycle N"<<i ;
        }
        return spline.pointAtPercent( persent );
    }


    const QPointF CircCirc( const QPointF & center1, double R1,
                            const QPointF & center2, double R2,
                            bool right )
    {
        bool DeZero = false;
        bool DbZero = false;

        double dx = center2.x() - center1.x();
        double dy = center2.y() - center1.y();

        if ( dy != 0 ) // dy != 0
        {
            double t1 = ( center1.x() - center2.x() ) / ( center2.y() - center1.y() );
            double t2 = ( pow ( R1, 2 ) - pow ( R2, 2 ) +
                          pow( center2.x(), 2 ) - pow( center1.x(), 2 ) +
                          pow( center2.y(), 2 ) - pow( center1.y(), 2 )
                          ) / ( 2 * ( center2.y() - center1.y() ) );

            double a = 1 + pow( t1, 2 );
            double b = 2 * ( t1 * ( t2 - center1.y() ) - center1.x() );
            double c = pow( t2 - center1.y(), 2 ) + pow( center1.x(), 2 ) - pow( R1, 2 );

            double D = pow( b, 2.0f ) - 4.0f * a * c;

            if ( D < 0.0f )
            {
                DbZero = true;
                Unicus::console( "Unicus::CircCirc", "Discriminant is below Zero!" );
                return QPointF( -1, -1 );
            }
            else if ( D == 0.0f )
            {
                DeZero = true;
                double x = ( -b ) / ( 2.0f * a );
                double y = t1 * x + t2;
                Unicus::console( "Unicus::CircCirc", "Discriminant is equal to Zero! Direction ( Right/Left ) ignored" );

                return QPointF( Unicus::e10( x ), Unicus::e10( y ) );
            }
            else
            {
                Unicus::console( "Unicus::CircCirc", "Discriminant is above zero" );

                double SrD = pow( ( D ), 0.5f );
                double  x1 = ( ( -b ) + SrD ) / ( 2.0f * a );
                double  x2 = ( ( -b ) - SrD ) / ( 2.0f * a );

                double y1 = t1 * x1 + t2;
                double y2 = t1 * x2 + t2;

                QLineF l  = QLineF( QPointF( center1.x(), center1.y() ),
                                    QPointF( center2.x(), center2.y() ) );
                QLineF l1 = QLineF( QPointF( center1.x(), center1.y() ),
                                    QPointF( Unicus::e10( x1 ), Unicus::e10( y1 ) ) );
                QLineF l2 = QLineF( QPointF( center1.x(), center1.y() ),
                                    QPointF( Unicus::e10( x2 ), Unicus::e10( y2 ) ) );

                qDebug() << "L1 : " << l1;
                qDebug() << "L2 : " << l2;

                double a1 = l1.angleTo( l );
                if ( abs( a1 ) > 180.0f && a1 >= 0.0f ) a1 = a1 - 360.0f;
                if ( abs( a1 ) > 180.0f && a1 <= 0.0f ) a1 = a1 + 360.0f;
                double a2 = l2.angleTo( l );
                if ( abs( a2 ) > 180.0f && a2 >= 0.0f ) a2 = a2 - 360.0f;
                if ( abs( a2 ) > 180.0f && a2 <= 0.0f ) a2 = a2 + 360.0f;

#if defined( C2D_DEBUG )
                Unicus::console( "center1 - x", center1.x() );
                Unicus::console( "center1 - y", center1.y() );
                Unicus::console( "R1", R1 );
                Unicus::console( "center2 - x", center2.x() );
                Unicus::console( "center2 - y", center2.y() );
                Unicus::console( "R2", R2 );

                Unicus::console( "t1", t1 );
                Unicus::console( "t2", t2 );

                Unicus::console( "a", a );
                Unicus::console( "b", b );
                Unicus::console( "c", c );
                Unicus::console( "SrD", SrD );


                Unicus::console( "p1 - x", x1 );
                Unicus::console( "p1 - y", y1 );

                Unicus::console( "p2 - x", x2 );
                Unicus::console( "p2 - y", y2 );



                Unicus::console( "a1", a1 );
                Unicus::console( "a2", a2 );
#endif
                if ( right )
                {
                    if ( a1 <= a2 )
                        return l1.p2();
                    else
                        return l2.p2();
                }
                else
                    if ( a1 >= a2 )
                        return l1.p2();
                else
                    return l2.p2();
            }
        }
    else // dy == 0
    {
            // (x-x1)^2 + y^2 = R1^2
            // (x-x2)^2 + y^2 = R2^2
            //  y^2 = R1^2 - (x-x1)^2
            // (x-x2)^2 - (x-x1)^2 = R2^2 - R1^2
            //
            // x^2 - 2*x*x2 + x2^2 - x^2 + 2*x*x1 - x1^2 = R2^2 - R1^2
            // 2*x*(x1-x2) = R2^2 - R1^2 + x1^2 - x2^2

        double xx = ( pow( R2, 2 ) - pow( R1, 2 ) + pow( center1.x(), 2 ) - pow( center2.x(), 2 ) ) /
                    ( 2 * ( center1.x() - center2.x() ) );
            // y = sqrt ( R1^2 - (xx-x1)^2 )
        double yy = pow( pow( R1, 2 ) - pow( xx - center1.x(), 2 ), 0.5f );

        Unicus::console( "Unicus::CircCirc", "dy == 0, direction (Right/Left) ignored" );
        return QPointF( Unicus::e10( xx ), Unicus::e10( yy ) );
    }
}


}
