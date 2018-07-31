#include "Geometry.h"

namespace Unicus
{

    const QPointF rPoint( const QPointF &point, const QPointF &center, double angle )
    {
        // Angle [ deg ]
        
        QPointF T1( point.x() - center.x(), point.y() - center.y() );
        return QPointF( Unicus::e10( center.x() + T1.x() * cos( angle * M_PI / 180.0f )
                                     + T1.y() * ( -sin( angle * M_PI / 180.0f ) ) ),
                        Unicus::e10( center.y() + T1.x() * sin( angle * M_PI / 180.0f )
                                     + T1.y() * cos( angle * M_PI / 180.0f ) ) );
    }

    const QLineF rLine( const QLineF & line, const QPointF & center, double angle)
    {
        // Angle [ deg ]
        return QLineF( rPoint( line.p1(), center , angle ), rPoint( line.p2(), center , angle ) );
    }

    double normalizeAngle( double angle )
    {
        while ( abs( angle ) >= 360.0f )
            angle = Unicus::normalizeAngle( ( angle > 0.0f ? ( angle - 360.0f ) : ( angle + 360.0f ) ) );

        if ( ( 180.1f <= angle ) && ( angle < 360.0f ) )
            return ( angle - 360.0f );
        else
        {
            if ( ( -360.0f <= angle ) && ( angle <= -180.1f ) )
                return ( angle + 360.0f );
            else
                return angle;
        }

    }

    double angleOx( const QLineF & line )
    {
        QLineF l( QPointF( 0.0f, 0.0f ), QPointF( 1.0f, 0.0f ) );
        return Unicus::normalizeAngle( Unicus::e10( line.angleTo( l ) ) );
    }

    const QLineF uNormal( QLineF line, bool right_pair )
    {
        double k;
        if ( right_pair ) 
            k =  1;
        else 
            k = -1;

        line = Unicus::rLine( line, line.p1(), k * 90.0f );

        QLineF l;
        l.setP2( QPointF( Unicus::e10( line.dx() ),
                          Unicus::e10( line.dy() ) ) );
        l.setP1( QPointF( 0.0f, 0.0f ) );

        return l;
    }

    double dPointPoint( const QPointF & point1, const QPointF & point2 )
    {
        return Unicus::e10( sqrt( pow( point1.x() - point2.x(), 2.0f )
                                  + pow( point1.y() - point2.y(), 2.0f ) ) );
    }

    QPointF PointOnRay(const QPointF & center, double angle, double ray_length)
    {
        return QPointF( Unicus::e10( center.x() + ray_length * cos( angle * M_PI / 180.0f ) ),
                        Unicus::e10( center.y() + ray_length * sin( angle * M_PI / 180.0f ) ) );
    }

    QLineF sGuides(const QPointF & center, double offset, double angle)
    {
        return QLineF( Unicus::PointOnRay( center, angle, offset ),
                       Unicus::PointOnRay( center, angle, -offset ) );
    }

    const QVector<QPointF> ArcToBezier( const QPointF & start, const QPointF & end, const QPointF & center )
    {
        QVector<QPointF> P;

        double theta = Unicus::angleOx( QLineF( center, end ) )
                       - Unicus::angleOx( QLineF( center, start ) );
        //double alpha = Unicus::angleOx( QLineF( center, start ) );

        QPointF arc_center = center; //Unicus::rPoint( start, center, theta / 2.0f );

        double ax = start.x() - arc_center.x();
        double ay = start.y() - arc_center.y();

        double bx = end.x() - arc_center.x();
        double by = end.y() - arc_center.y();

        double q1 = pow( ax, 2.0f ) +  pow( ay, 2.0f );
        double q2 = q1 + ax * bx + ay * by;

        double k = ( 4.0f / 3.0f ) * ( pow( 2.0f * q1 * q2, 0.5f ) - q2 ) / ( ax * by - ay * bx );
        P.push_back( start );

        P.push_back( QPointF( arc_center.x() + start.x() - k * start.y(),
                              arc_center.y() + start.y() - k * start.x() ) );
        P.push_back( QPointF( arc_center.x() + end.x()   - k * end.y(),
                              arc_center.y() + end.y()   - k * end.x() ) );
        P.push_back( end );
        P.push_back( arc_center );

        qDebug() << "Ax: " << ax;
        qDebug() << "Ay: " << ay;
        qDebug() << "Bx: " << bx;
        qDebug() << "By: " << by;
        qDebug() << "Q1: " << q1;
        qDebug() << "Q2: " << q2;
        qDebug() << "k: " << k;
        return P;

    }

    double Scalar( const QLineF & v1, const QLineF & v2 )
    {
        return ( v1.dx() * v2.dx() + v1.dy() * v2.dy() );
    }
    QPointF circline( QLineF line1 , QPointF centr, double r, bool right )
    {
        QPointF p,p2;
        QLineF line2 = QLineF( centr, centr + QPointF(0,1) );
        line2.setAngle(line1.angle()+90.0f);
        line1.intersect( line2,&p );
        if(p==centr)
        {
            line2.setAngle(line1.angle());
            line2.setLength(r);
            p = line2.p2();
            line2.setAngle(line2.angle()+180);
            p2 = line2.p2();
        }else if( QLineF(centr,p).length()>r )
        {
            return QPointF(0,0);
        }else if( QLineF(centr,p).length()==r )
        {
            return p;
        }else if ( QLineF(centr,p).length()<r )
        {
            line2.setPoints( p,centr );

            line2.setLength(sqrt( abs( pow(r,2)-pow(line2.length(),2)) ));
            line2.setAngle(line2.angle()+90);
            p = line2.p2();
            line2.setAngle(line2.angle()+180);
            p2 = line2.p2();
        }
        if(p.x()>p2.x())
        {
            if(right)
                return p;
            else
                return p2;
        }else if(p.x()<p2.x())
        {
            if(right)
                return p2;
            else
                return p;
        }else if(p.x()==p2.x())
        {
            if(p.y()>p2.y())
            {
                if(right)
                    return p;
                else
                    return p2;
            }else
            {
                if(right)
                    return p2;
                else
                    return p;
            }
        }
    }


}




/*
QPointF C2DStraightSkirt::CircInter(double R1, double R2, double h)
{
    //Returns deltas for intersection point of two equal circles
    //situated one strong above other
    QPointF Point(0,0);
    double k=((R1*R1-R2*R2-h*h)/(2*h*R2));
    Point.setY(h+k*R2);
    Point.setX(R2*sqrt(1-k*k));
    return Point;
}

QLineF  C2DStraightSkirt::CircIntersection(QPointF P1, QPointF P2, double R)
{
    //Returns intersection points of two circles with radius equal to R
    QLineF V=QLineF(P1,P2).unitVector().normalVector();
    double k1=P1.x()+(P2.x()-P1.x())/2;
    double k2=P1.y()+(P2.y()-P1.y())/2;
    double sina=QLineF(P1,P2).length()/(2*R);
    V.setLength(R*sqrt( 1- pow(sina,2)));

    if ((k2+V.dy())<= (k2-V.dy()))
    {
        P1.setX(k1-V.dx());
        P1.setY(k2-V.dy());
        P2.setX(k1+V.dx());
        P2.setY(k2+V.dy());
    }
    else
    {
        P1.setX(k1+V.dx());
        P1.setY(k2+V.dy());
        P2.setX(k1-V.dx());
        P2.setY(k2-V.dy());
    }
    return QLineF(P1,P2);
}


QLineF  C2DStraightSkirt::LineCircIntersection(QLineF Line1, QPointF P1,  double R)
{
    //Returns intercection point of circle (P1,R) & line P1
    //which is closer to Line1 start point
    Line1.setLength(1);
    double a=(pow(Line1.dx(),2)+pow(Line1.dy(),2));
    double b=2*(Line1.dx()*(Line1.x1()-P1.x())+Line1.dy()*(Line1.y1()-P1.y()));
    double c=(pow(Line1.x1()-P1.x(),2)+pow(Line1.y1()-P1.y(),2)-pow(R,2));
    double D=sqrt(pow(b,2)-4*a*c);
    P1.setX((-b+D)/2/a);
    P1.setY((-b-D)/2/a);
    Line1.setLength(P1.y());
    return Line1;
}
*/

