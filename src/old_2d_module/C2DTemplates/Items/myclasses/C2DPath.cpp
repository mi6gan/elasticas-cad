#include "C2DPath.h"
#include "math.h"
QList < QPainterPath > C2DPath::splitpath( int n, double shag )
{
    //n=2;
    int j=1;
    QList < QPainterPath > list;
    if(n<1)
        return list;
    QPainterPath pat;
    double step = (this->path.length()/n);
    if( step < shag )
    {
        shag = step;//0.045
    }
    Unicus::console("step",step);
    double l=0;
    pat.moveTo( this->path.pointAtPercent(0) );
    bool stepend = false;
    Unicus::console("cycle start",l);
    while( l < (this->path.length()) )
    {
        l = l + shag;
        if( l >= this->path.length() )
        {
            l=this->path.length();
            break;
        }
        stepend = false;
        if( l >= (step*j) )
        {
            l = step*j;
            stepend = true;
            //j++;
        }
        Unicus::console("l",l);
        pat.lineTo( this->path.pointAtPercent( l/(this->path.length()) ) );
        if(stepend)
        {
            list.append( pat );
            pat = QPainterPath();
            pat.moveTo(this->path.pointAtPercent(l/(this->path.length()) ));
            j = j + 1;
        }
    }
    pat.lineTo( this->path.pointAtPercent( 1 ) );
    list.append( pat );
    return list;
}
QList < QPainterPath > C2DPath::splitpath2( int n, double start, double period, double shag=3 )
{
    QList < QPainterPath > list;
    if(start<0)
        start = 0;
    if( start>this->path.length() )
        start = 0;
    if( period>this->path.length() )
        period = 0;
    if( start == 0 )
        if( period == 0 )
        {
            list.append( this->path );
            return list;
        }

    start = start/this->path.length();
    period = period/this->path.length();
    list.append( this->takepartofpath( 0, start,shag ) );
    double tmp;
    for( int j=0;j<n-1;j++ )
    {
        tmp = start+( j*period );
        list.append( this->takepartofpath( tmp,period,shag ) );
    }
    list.append( this->takepartofpath( start+( (n-1)*period ),1,shag ) );
    return list;
}
QPainterPath C2DPath::myshape( QPointF p, double l, double shag )
{
    if( ( l > 1 ) || ( l < 0 ) )
        l = 1;

    double x = 1, y = 1;
    if( this->mirror == 1 )
        x = -1;
    else if( this->mirror == 2 )
        y = -1;
    else if( this->mirror == 3 )
    {
        x = -1;
        y = -1;
    }
    QPainterPath Path;
    QPointF tmppoint;
    Path.moveTo( p );
    l = this->path.length() * l;
    double cur_l = 0;
    while( cur_l < l )
    {
        cur_l = cur_l + shag;
        if( cur_l > l )
            cur_l = l;
        tmppoint = this->path.pointAtPercent( cur_l/this->path.length() ) - this->startpoint;
        //Unicus::console( "x",tmppoint.x() );
        //Unicus::console( "y",tmppoint.y() );
        tmppoint = QPointF( tmppoint.x()*x, tmppoint.y()*y );
        if( this->angle != 0 )
            tmppoint = Unicus::rPoint( tmppoint,QPointF(0,0),this->angle );
        Path.lineTo( p + tmppoint );
    }
    return Path;
}
QPainterPath C2DPath::myshapefromstart( double l, double shag )
{
    return myshape( this->startpoint, l, shag );
}
QPainterPath C2DPath::takepartofpath( double start, double length, double shag )
{
    if( start > 1 )
        return QPainterPath();
    QPainterPath Path;
    if( start > 0.9998 )
    {
        Path.moveTo(this->path.pointAtPercent(start-0.0001));
        Path.lineTo(this->path.pointAtPercent(1));
        return Path;
    }
    if( length <= 0 )
    {
        Path.moveTo(this->path.pointAtPercent(start));
        Path.lineTo(this->path.pointAtPercent(start+0.0001));
        //Unicus::console( "PATH.LENGTH !!_!!!_!_!_!", Path.length() );
        //Unicus::console( "PATH.X0     !!_!!!_!_!_!", Path.pointAtPercent(0).x() );
        //Unicus::console( "PATH.X1     !!_!!!_!_!_!", Path.pointAtPercent(1).x() );
        //Unicus::console( "PATH.curX   !!_!!!_!_!_!", Path.currentPosition().x() );
        //Unicus::console( "PATH.curY   !!_!!!_!_!_!", Path.currentPosition().y() );
        //double hi=0;
        //if( Path == QPainterPath() )
        //    hi = 1;
        //Unicus::console( "Path == QPainterPath()_!", hi );


        return Path;
    }


    Path.moveTo( this->path.pointAtPercent(start) );
    double l = length+start;
    if(l>1)
        l=1;
    l = l*this->path.length();
    double cur_l = start*this->path.length();
    while( cur_l < l )
    {
        cur_l = cur_l + shag;
        if( cur_l > l )
            cur_l = l;
        Path.lineTo( this->path.pointAtPercent(cur_l/this->path.length()) );
    }
    return Path;
}

