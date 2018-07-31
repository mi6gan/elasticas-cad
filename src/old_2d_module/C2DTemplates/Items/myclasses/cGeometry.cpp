#include "cGeometry.h"

QPointF cGeometry::mirrorpoint( QPointF mypoint, QLineF myline)
{
    QLineF myline2(mypoint,mypoint+QPointF(1,0));
    QPointF mypoint2;
    myline2.setAngle(myline.angle()+90.0f);
    myline2.intersect(myline,&mypoint2);
    return Unicus::rPoint(mypoint,mypoint2,180);
}
QPainterPath cGeometry::spline_on_length_TYPE1( QPointF strt, QPointF strt_p2, QPointF end, QPointF end_p2, double koef, double length )
{//Type1 - сплайн по 4-ем точкам с указанным коэфициентом(0.5 - одинаковые. 0.7 значит первая направляющая 0.7 от прироста вторая 0.3) направляющих по длине кривой

    QLineF s_l,e_l;QPainterPath result;
    s_l = QLineF(strt,end);
    double pogreshnost = 0.3,l_max,l_min,add=0,shag=30;
    if( s_l.length()>length+pogreshnost )
    {
        result.moveTo(strt);
        result.lineTo(end);
        return result;
    }

    l_max = length+pogreshnost;
    l_min = length-pogreshnost;

    result.moveTo(strt);
    result.cubicTo( strt_p2,end_p2,end );
    Unicus::console("cycle--LENGTH-acc",result.length());
    if(result.length() < l_min)
        add = 1;
    else if(result.length() > l_max)
        add = -1;
    else
        return result;

    s_l.setPoints(strt,strt_p2);
    e_l.setPoints(end,end_p2);
    int i = 30;
    do
    {

        Unicus::console("cycle--LENGTH-zad",length);
        Unicus::console("cycle--LENGTH-MAX",l_max);
        Unicus::console("cycle--LENGTH-MIN",l_min);
        if(add<0)
        {
            if( s_l.length()==(shag*koef) )
                s_l.setLength(s_l.length()+0.01);
            if(e_l.length()==(shag*(1-koef)))
                e_l.setLength(e_l.length()+0.01);
            s_l.setLength( s_l.length()-(shag*koef) );
            e_l.setLength( e_l.length()-(shag*(1-koef)) );
        }else
        {
            s_l.setLength( s_l.length()+(shag*koef) );
            e_l.setLength( e_l.length()+(shag*(1-koef)) );
        }

        result = QPainterPath();
        result.moveTo(s_l.p1());
        result.cubicTo( s_l.p2(),e_l.p2(),e_l.p1() );
        Unicus::console("cycle--LENGTH-acc",result.length());
        if(add>0)
        {
            if( result.length()>l_max )
            {
                add = -1;
                shag = shag * 0.33;
            }
        }else if(add<0)
            if( result.length()<l_min )
            {
                add = 1;
                shag = shag * 0.33;
            }

        Unicus::console("cycle--shag",shag*add);
        Unicus::console("cycle--i",i);
        i--;
        if(i<0)
            break;
    }while( !((result.length() < l_max)&&(result.length() > l_min) ) );
    return result;
}
QPointF cGeometry::bottompoint( QList <QPointF> point_list )
{
    QPointF tmppoint = QPointF(0,9999),p;
    while( !point_list.isEmpty() )
    {
        p = point_list.takeFirst();
        if(tmppoint.y()>p.y())
            tmppoint = p;
    }
    return tmppoint;
}
QPainterPath cGeometry::splineon3points( double r, QPointF p1, QPointF p2, QPointF p3,QPointF centerpoint , double k1, double k2 )
{
    if( k1 == 0 )
        k1 = 0.5f;
    if( k2 == 0 )
        k2 = k1;
    //if( r>QLineF(p2,p3).length() )
    //    r=QLineF(p2,p3).length();
    QPainterPath result = QPainterPath();
    result.moveTo(p1);
    if(r==0)
    {
        result.lineTo(p2);
        result.lineTo(p3);
        return result;
    }
    QLineF l1,l2,l3;
    l1.setPoints(p2,p1);
    l1.setLength(1);
    l2.setPoints(p2,p3);
    l2.setLength(1);
    l3.setPoints(l1.p2(),l2.p2());

    l1.setAngle(l3.angle()+180);
    l1.setLength(r*k1);
    l2.setPoints( p1,centerpoint );
    l2.setLength( r*k1 );
    result.cubicTo( l2.p2(),l1.p2(),l1.p1() );

    l1.setAngle(l1.angle()+180);
    l1.setLength(r*k2);
    l2.setPoints( p3,centerpoint );
    l2.setLength( r*k2 );
    result.cubicTo( l1.p2(),l2.p2(),l2.p1() );

    return result;
}
int myround(double value)
{
   return (int) floor(value + 0.5);
}
double positiveangle( double angle )
{
    if(angle > 0)
    {
        if(angle > 360)
            angle = angle - ( floor(angle/360)*360 );
        return angle;
    }
    return angle + (360 * ceil(-angle/360));
}
QPainterPath cGeometry::getpathfromlist( QList<QPainterPath> l )
{
    QPainterPath result=l.at(0);
    for( int i = 1; i < l.count();i++ )
        result.connectPath(l.at(i));
    return result;
}
QList<QPointF> cGeometry::qpathintersect( QLineF line, QPainterPath path, double shag )
{
    QList<QPointF> result;
    if( ( path.length() == 0 ) || ( line.length() == 0 ) )
        return result;

    QPointF p1,p2,itsct;
    QLineF line2,tmpline;
    if(shag<=0)
        shag=1;
    double l=0;
    p1 = path.pointAtPercent(0);
    while(l<path.length())
    {
        l=l+shag;
        if(l>path.length())
            l = path.length();
        p2 = path.pointAtPercent( l/path.length() );
        line2.setPoints( p1,p2 );
        if( line.angle() != line2.angle() )
            if( (line.angle()+180)!=line2.angle() )
            {
                line2.intersect( line, &itsct );
                tmpline.setPoints( line2.p1(), itsct );
                if( tmpline.angle() == line2.angle() )
                    if(line2.length()>tmpline.length())
                        result.append( itsct );
            }
        p1 = p2;
    }
    return result;
}
QLineF cGeometry::qpathintersectbottom( QLineF line, QPainterPath path, double shag )
{
    QLineF result=QLineF( QPointF(0,0),QPointF(1,1) );
    if( ( path.length() == 0 ) || ( line.length() == 0 ) )
        return result;
    double miny= 32000;
    QPointF p1,p2,itsct;
    QLineF line2,tmpline;
    if(shag<=0)
        shag=1;

    double l=0,tmpdx,tmpdy;
    p1 = path.pointAtPercent(0);
    bool cycend = false;
    while(l<path.length())
    {
        l=l+shag;
        if(l>path.length())
        {
            l = path.length();
            cycend = true;
        }
        p2 = path.pointAtPercent( l/path.length() );
        line2.setPoints( p1 + QPointF(0.0001,0.0001),p2 + QPointF(0.0002,0.0002) );

        if( line.angle() != line2.angle() )
            if( (line.angle()+180)!=line2.angle() )
            {
                line2.intersect( line, &itsct );
                tmpdx = (itsct.x() - line2.pointAt(0.5).x());
                tmpdy = (itsct.y() - line2.pointAt(0.5).y());

                tmpdx = sqrt( tmpdy*tmpdy + tmpdx*tmpdx );
                if( tmpdx < (line2.length()/2) )
                {
                    if( itsct.y() < miny )
                    {

                        miny = itsct.y();
                        result = QLineF( itsct, QPointF(1,1) );
                        result.setLength( l-(line2.length()/2) );
                        result.setAngle(  path.angleAtPercent( ( result.length()/path.length() ) ) );
                    }
                }

            }
        p1 = p2;
        if(cycend)
            break;
    }
    return result;
}
double cGeometry::qpintrbtD( QLineF line, QPainterPath path, double shag )
{
    double result=0;
    if( ( path.length() == 0 ) || ( line.length() == 0 ) )
        return result;
    double miny= 32000;
    QPointF p1,p2,itsct;
    QLineF line2,tmpline;
    if(shag<=0)
        shag=1;

    double l=0,tmpdx,tmpdy;
    p1 = path.pointAtPercent(0);
    bool cycend = false;
    while(cycend == false)
    {
        l=l+shag;
        if(l>=path.length())
        {
            l = path.length();
            cycend = true;
        }
        p2 = path.pointAtPercent( l/path.length() );
        line2.setPoints( p1 + QPointF(0.0001,0.0001),p2 + QPointF(0.0002,0.0002) );

        if( line.angle() != line2.angle() )
            if( (line.angle()+180)!=line2.angle() )
            {
                line2.intersect( line, &itsct );
                tmpdx = (itsct.x() - line2.pointAt(0.5).x());
                tmpdy = (itsct.y() - line2.pointAt(0.5).y());

                tmpdx = sqrt( tmpdy*tmpdy + tmpdx*tmpdx );
                if( tmpdx <= (line2.length()/2) )
                {
                    //Unicus::console("123456-",miny);

                    if( itsct.y() < miny )
                    {
                        QLineF l1;
                        l1.setPoints( line2.p1(),itsct );
                        //(line2.length()-l1.length())/line2.length()*shag
                        miny = itsct.y();
                        result = (l-shag)+(l1.length())/line2.length()*shag;//shag/2;
                    }
                }
            }
        p1 = p2;
        if(cycend)
            break;
    }
    return result;
}
double cGeometry::qpintrbtE( QLineF line, QPainterPath path, double shag )
{
 //   QLineF line3;
 //   line3.setPoints( path.pointAtPercent(1),path.pointAtPercent(1)+QPointF(100,100) );
 //   line3.setAngle(path.angleAtPercent(1));
 //   path.lineTo(line3.p2());
    double result=0;
    if( ( path.length() == 0 ) || ( line.length() == 0 ) )
        return result;
    double miny= 32000;
    QPointF p1,p2,itsct;
    QLineF line2,tmpline,line3;
    if(shag<=0)
        shag=1;

    double l=0,tmpdx,tmpdy;
    p1 = path.pointAtPercent(0);
    bool cycend = false;
    while(cycend == false)
    {
        l=l+shag;
        if(l>=path.length())
        {
            l = path.length();
            cycend = true;
        }
        p2 = path.pointAtPercent( l/path.length() );
        if(p1 == p2)
            p1 =p1 + QPointF(0.0001,0.0001);
        line2.setPoints( p1 ,p2 );
        line3.setPoints( line2.pointAt(0.5),line2.p1() );
        if( line.angle() != line2.angle() )
            if( (line.angle()+180)!=line2.angle() )
            {
                line2.intersect( line, &itsct );
                if(itsct == line3.p1())
                    return l-shag/2;

                tmpline.setPoints( line3.p1(),itsct );
                if( tmpline.length() <= (line2.length()) )
                {
                    //Unicus::console("FOUNDED  tmpline.length()",tmpline.length());
                    //Unicus::console("FOUNDED  line2.length()",line2.length());

                        QLineF l1;
                        l1.setPoints( line2.p1(),itsct );
                        //(line2.length()-l1.length())/line2.length()*shag
                        miny = itsct.y();
                        result = (l-shag)+(l1.length())/line2.length()*shag;//shag/2;
                        //Unicus::console("FOUNDED  result",result);
                        //Unicus::console("FOUNDED  path.lenth",path.length());
                        if(result>path.length())
                            result = path.length();
                        return result;

                }
            }
        p1 = p2;
        if(cycend)
            break;
    }
    return path.length();
}
double cGeometry::qpathintersectmaxlength( QLineF line, QPainterPath path, bool min, double shag )
{
    double result=-1;
    if( ( path.length() == 0 ) || ( line.length() == 0 ) )
        return result;

    double minx;
    if(min)
        minx = 99000;
    else
        minx = -99000;
    QPointF p1,p2,itsct;
    QLineF line2,tmpline;
    if(shag<=0)
        shag=1;

    double l=0,tmpdx,tmpdy;
    p1 = path.pointAtPercent(0);
    bool cycend = false;
    while(cycend == false)
    {
        l=l+shag;
        if(l>=path.length())
        {
            l = path.length();
            cycend = true;
        }
        p2 = path.pointAtPercent( l/path.length() );
        line2.setPoints( p1 + QPointF(0.0001,0.0001),p2 + QPointF(0.0002,0.0002) );

        if( line.angle() != line2.angle() )
            if( (line.angle()+180)!=line2.angle() )
            {
                line2.intersect( line, &itsct );
                tmpdx = (itsct.x() - line2.pointAt(0.5).x());
                tmpdy = (itsct.y() - line2.pointAt(0.5).y());

                tmpdx = sqrt( tmpdy*tmpdy + tmpdx*tmpdx );
                if( tmpdx <= (line2.length()/2) )
                {
                    //Unicus::console("123456-",miny);
                    if(min)
                    {
                        if( itsct.x()<minx )
                        {
                            result = l;//-shag/2;
                            minx = itsct.x();
                        }
                    }else
                    {
                        if( itsct.x()>minx )
                        {
                            result = l;//-shag/2;
                            minx = itsct.x();
                        }
                    }
                }
            }
        p1 = p2;
        if(cycend)
            break;
    }
    return result;
}
QPointF cGeometry::CircCircUpDown( const QPointF & center1, double R1,
                        const QPointF & center2, double R2,
                        bool Up )
{
    double d = QLineF( center1,center2 ).length();
    if( ( d > R1+R2 ) || ( d < fabs(R1-R2) ) )
        return QPointF(0,0);
    double a = ( pow(R1,2)-pow(R2,2)+pow(d,2) )/(2*d);
    double h = sqrt( pow(R1,2)-pow(a,2) );
    QLineF line = QLineF(center1,center2);
    line.setLength( a );
    QLineF line3,line2 = QLineF(line.p2(),line.p2()+QPointF(1,1));
    line2.setLength( h );
    line3 = line2;
    line2.setAngle( line.angle()-90 );
    line3.setAngle( line.angle()+90 );
    if(!Up)
        if( line2.p2().y()>line3.p2().y() )
            return line3.p2();
        else
            return line2.p2();
    else
        if( line2.p2().y()<line3.p2().y() )
            return line3.p2();
        else
            return line2.p2();
}
QPainterPath cGeometry::GetSign( QPointF startp, double angle, double height, double width )
{
    if(height==0)
        height=1;
    if(width==0)
        width=1;

    angle = angle + 180;
    QLineF line = QLineF(startp,startp+QPointF(1,1));
    line.setAngle(angle+90);
    line.setLength(height);
    QPainterPath result;
    result.moveTo(line.p1());
    result.lineTo(line.p2());
    QLineF line2 = QLineF(line.p2(),line.p1());
    line2.setLength( width/2 );
    line2.setAngle(line2.angle()+90);
    line.setPoints( line2.p2(),line2.p1() );
    line.setLength( width );
    result.moveTo(line.p1());
    result.lineTo(line.p2());
    result.moveTo(line.pointAt(0.5));
    result.lineTo(startp);
    //Unicus::console( "L---ZASECHKA!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!---:",width );
    return result;
}
QPainterPath cGeometry::getsmoothpath( QPainterPath path, double start, double end, QList < QPair<double, QPainterPath> > list, double shag, QPointF P5 )
{
    //double superend = end;
    if(start<0)
        start = -start;
    if(end<0)
        end = -end;
    if(shag <= 0)
        shag = 5;
    end = path.length() - end;
    if( start >= end )
        return QPainterPath();
    QPainterPath result=QPainterPath();
    QPainterPath smooth=QPainterPath();
    smooth = simplesmoothpath( path,start,end,shag );
    //partofpath(path,start,end,shag);

    if(list.count() == 0)
        return smooth;
    else
    {
        //Unicus::console( "EEend",superend );
        double oldlength = path.length();//end - start;
        double newlength = smooth.length();
        //double ko = newlength/oldlength;
        Unicus::console( "WHAT A F*************",newlength );
        double newfirst;
        C2DPath smp = C2DPath(smooth);double newstart = 0;
        result.moveTo( smooth.pointAtPercent(0) );

        for(int i = 0;i<list.count();i++)
        {
            newfirst = list.at(i).first -start;
            if( (newfirst < 0 ) || ( newfirst >= smooth.length() ) )
                break;
            if(newfirst==0)
                newfirst = 0.001;
            //newfirst = list.at(i).first/oldlength*newlength;
            result.connectPath( partofpath( smooth,newstart,newfirst,shag ) );
            if( list.at(i).second.length()>1 )
                result.connectPath( GetSign( result.pointAtPercent(1),
                                             result.angleAtPercent(1)  ) );
            else
            {
                QPointF tmppoint = result.pointAtPercent(1);
                result.lineTo( P5 );
                result.lineTo( tmppoint );
            }
            //smp = C2DPath(list.at(i).second);
            //result.connectPath( list.at(i).second );
            //result.connectPath( smp.myshape( result.pointAtPercent(1),1,1 ) );
            newstart = newfirst;
        }
        result.connectPath( partofpath( smooth,newstart,smooth.length(),shag ) );
    }
    return result;
}
QPainterPath cGeometry::simplesmoothpath( QPainterPath path, double start, double end, double shag )
{

    int PARTS = myround( path.length()/20 );
    if(PARTS<2)
        PARTS = 2;
    double k = 0.3;
    double fulllength=end-start;
    shag = fulllength / PARTS;
    QLineF l1,l2,l3;QPointF p,p2;
    double l;
    double nextdot;
    double angle,l2a,l1a;
    l = start;
    QPainterPath result;
    p = path.pointAtPercent( l/path.length() );
    l1.setPoints( p,p+QPointF(1,1) );
    l1.setAngle( path.angleAtPercent( l/path.length() ) );
    result.moveTo( p );
    for( int i = 0; i < PARTS-1; i++ )
    {
        l = l + shag;
        if( i == (PARTS-2) )
            nextdot = end;
        else
            nextdot = l + shag;

        p = path.pointAtPercent( l/path.length() );
        p2 = path.pointAtPercent( nextdot/path.length() );
        l2 = QLineF( p,p2 );
        l3 = QLineF( p,l1.p1() );
        l3.setLength(l2.length());
        l3.setPoints( l2.p2(),l3.p2() );
        angle = l3.angle();
        l2.setAngle( (angle) );
        l3.setPoints( p,l1.p1() );
        l1.setLength( l3.length()*k );
        l2.setLength( l3.length()*k );
        result.cubicTo( l1.p2(),l2.p2(),l2.p1() );
        l1 = l2;
        l1.setAngle( l1.angle()+180 );
    }
    p = path.pointAtPercent( end/path.length() );
    l2.setPoints( p,p+QPointF(1,1) );
    l2.setAngle( path.angleAtPercent(end/path.length())+180 );
    l3.setPoints( l1.p1(),l2.p1() );
    l1.setLength( l3.length()*k );
    l2.setLength( l3.length()*k );
    result.cubicTo( l1.p2(),l2.p2(),l2.p1() );
    return result;
}
/*
QPainterPath cGeometry::simplesmoothpath( QPainterPath path, double start, double end, double shag )
{
    shag = 4;QLineF l1,l2,l3;QPointF p;
    double l;
    double k = 0.1;
    l = start;
    QPainterPath result;
    p = path.pointAtPercent( l/path.length() );
    l1.setPoints( p,p+QPointF(1,1) );
    l1.setAngle( path.angleAtPercent( l/path.length() ) );
    result.moveTo( p );
    l = l + shag;
    while( l < end )
    {
        p = path.pointAtPercent( l/path.length() );
        l2.setPoints( p,p+QPointF(1,1) );
        l2.setAngle( path.angleAtPercent(l/path.length())+180 );
        l3.setPoints( l1.p1(),l2.p1() );
        l1.setLength( l3.length()*k );
        l2.setLength( l3.length()*k );
        result.cubicTo( l1.p2(),l2.p2(),l2.p1() );
        l1 = l2;
        l1.setAngle( l1.angle()+180 );
        l = l + shag;
        //Unicus::console( "L------:",l );
    }
    p = path.pointAtPercent( end/path.length() );
    l2.setPoints( p,p+QPointF(1,1) );
    l2.setAngle( path.angleAtPercent(end/path.length())+180 );
    l3.setPoints( l1.p1(),l2.p1() );
    l1.setLength( l3.length()*k );
    l2.setLength( l3.length()*k );
    result.cubicTo( l1.p2(),l2.p2(),l2.p1() );
    return result;
}
  */
QPainterPath cGeometry::arc_round( QPointF center, QPointF start, double end_angle )
{
    if((center==start)||(end_angle == 0))
        return QPainterPath();
    QPainterPath result;
    result.moveTo(start);
    QLineF l1;
    l1 = QLineF(center,start);
    result.arcTo(QRectF( center + QPointF(-l1.length(),-l1.length() ),center+QPointF( l1.length(),l1.length() ) ) ,l1.angle(),end_angle );
    return result;
}

QPainterPath cGeometry::partofpath( QPainterPath path, double start, double end, double shag )
{
    if(end > path.length())
        end = path.length();
    QPainterPath result;
    result.moveTo( path.pointAtPercent( start/path.length() ) );
    start = start + shag;
    while( start < end )
    {
        result.lineTo( path.pointAtPercent( start/path.length() ) );
        start = start + shag;
    }
    result.lineTo( path.pointAtPercent( end/path.length() ) );
    return result;
}
QPainterPath cGeometry::makedart( QPainterPath path, double strt, double l, double a, double r )
{
    QPointF p1,p2;
    QLineF l1,l2;
    strt = strt/path.length();
    p1 = path.pointAtPercent( strt );
    a = path.angleAtPercent( strt ) - 90 + a;
    l1.setPoints( p1,p1+QPointF(1,1) );
    l1.setAngle(a);
    l1.setLength(l);

    double angle;
    angle = 2*180/M_PI*asin( r/(2*l) );
    p2 = Unicus::rPoint( l1.p2(),p1,-angle );
    l2.setPoints(p1,p2);

    path = dart( path,strt,angle );
    return path;
}
QPainterPath cGeometry::dart( QPainterPath path, double start, double angle)
{
    C2DPath cp1;
    QPainterPath result;
    cp1 = C2DPath(path);
    result = cp1.takepartofpath(0,start);
    cp1 = C2DPath( cp1.takepartofpath(start,1),angle );
    result.connectPath( cp1.myshape( result.pointAtPercent(1) )  );
    return result;
}
QPainterPath cGeometry::cutaddlengthtopath( QPainterPath path, double l, QPointF anglepoint, bool right )
{
    if( l == 0)
        return path;
    else if( l > 0 )
    {
        QLineF l1;
        l1.setPoints( path.pointAtPercent(1),anglepoint );
        if(right)
            l1.setAngle( l1.angle() - 90 );
        else
            l1.setAngle( l1.angle() + 90 );
        l1.setLength(l);
        path.lineTo(l1.p2());
        return path;
    }
    else if( l < 0 )
    {
        if( path.length()<=-l )
            l = -path.length()+0.1;
        C2DPath cdpath = C2DPath(path);
        return cdpath.myshapefromstart( (path.length()+l)/path.length() );
    }
}
double cGeometry::degrees360(double d)
{
    if(d<-280)
        d = d + 360;
    else if(d>280)
        d = d - 360;
    return d;
}
