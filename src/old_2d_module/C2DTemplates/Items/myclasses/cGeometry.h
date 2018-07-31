#include <QPainterPath>
#include "C2DPath.h"
//#include "../../../C2DModule/Frameworks/Items/include/C2DItem.h"
#include "qpair.h"
namespace cGeometry
{
    //QPainterPath simpleSpath;
    QPointF bottompoint( QList <QPointF> point_list );
    QList<QPointF> qpathintersect( QLineF l, QPainterPath path, double shag=1 );
    QLineF qpathintersectbottom( QLineF l, QPainterPath path, double shag=1 );
    double qpintrbtD( QLineF line, QPainterPath path, double shag=1 );
    double qpintrbtE( QLineF line, QPainterPath path, double shag=1 );
    double qpathintersectmaxlength( QLineF line, QPainterPath path, bool min = false ,double shag=0.3 );
    QPointF CircCircUpDown( const QPointF & center1, double R1,
                            const QPointF & center2, double R2,
                            bool Up );
    double degrees360(double d);
    QPainterPath cutaddlengthtopath( QPainterPath path, double l, QPointF anglepoint, bool right=false );
    QPainterPath getpathfromlist( QList<QPainterPath> l );
    QPainterPath GetSign( QPointF startp, double angle=0, double h=5, double width=5 );
    QPainterPath getsmoothpath( QPainterPath path, double start, double end, QList < QPair<double, QPainterPath> > list,double shag=5,QPointF P5=QPointF(0,0) );
    QPainterPath simplesmoothpath( QPainterPath path, double start, double end, double shag );
    QPainterPath partofpath( QPainterPath path, double start, double end, double shag );
    QPainterPath splineon3points( double r, QPointF p1, QPointF p2, QPointF p3,QPointF centerpoint, double k1=0.5f, double k2=0 );
    QPainterPath makedart( QPainterPath path, double strt, double l, double a, double r );
    QPainterPath dart(QPainterPath path,double startbelow1,double angle );
    //QPainterPath makedartFULL( QPainterPath path, double strt, double l, double a, double r );
    QPainterPath spline_on_length_TYPE1( QPointF strt, QPointF strt_p2, QPointF end, QPointF end_p2, double koef, double length );
    QPainterPath arc_round( QPointF center, QPointF start, double end_angle );
    QPointF mirrorpoint( QPointF mypoint, QLineF myline );
    //QPointF splinepointony( QPainterPath spline , double yy,double n);
    //QPointF splinepointonx( QPainterPath spline , double xx,double n);
}



