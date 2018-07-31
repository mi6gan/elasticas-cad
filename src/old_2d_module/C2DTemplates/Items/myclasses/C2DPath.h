#include <QPainterPath>
#include "../../../C2DModule/Frameworks/Items/include/C2DItem.h"
class C2DPath
{
public:
    C2DPath( QPainterPath p = QPainterPath(), double a = 0, int mir = 0 )
    {
        this->path = p;
        this->angle = a;
        this->mirror = mir;
        if( this->path.length() != 0 )
            this->startpoint = this->path.pointAtPercent(0);
        else
            this->startpoint = QPointF(0,0);
    }
    QPainterPath myshape( QPointF p, double l = 1, double shag = 1 );
    QPainterPath myshapefromstart( double l = 1, double shag = 1 );
    QPainterPath takepartofpath( double start, double length, double shag=1 );
    QPainterPath shape(){ return this->path; }
    QPainterPath * pointer(){ return &path; }
    QList < QPainterPath > splitpath( int n, double shag = 1 );
    QList < QPainterPath > splitpath2( int n, double start, double period, double shag );
    void toReversed(){ this->path = this->path.toReversed();
                       this->startpoint = this->path.pointAtPercent(0); }
    double length(){ return this->path.length(); }
    void setAngle( double a ){ this->angle = a; }
    void setMirror( int a=0 ){ this->mirror = a; }
    double getangle(){ return this->angle; }

private:
    QPainterPath path;
    double angle;
    int mirror;
    QPointF startpoint;
};



