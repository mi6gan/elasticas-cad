#ifndef C2DDRESS_H
#define C2DDRESS_H

#include <math.h>
#include "myclasses/cGeometry.h"
//#include "myclasses\C2DPath.h"
#include "myclasses/DressGorlovina.h"
#include "myclasses/DressCollar.h"
#include "myclasses/DressGLine.h"
#include "myclasses/DressVorotDialog.h"
#include "myclasses/DressVorotDecor.h"
#include "myclasses/SleeveElDialog.h"
#include "../../C2DModule/Frameworks/Items/include/C2DItem.h"
#include "C2DDressDialog.h"
#include "C2DDressTableDialog.h"
#include "myclasses/DressEquidistant.h"
#include "myclasses/DressGathers.h"

class NewDressDialog: public Elasticas::DockDialog
{
public:
    NewDressDialog();
    virtual void apply();
};

class C2DDress : public C2DItem
{
public:
    C2DDress();
    DressCollar * collar;
    DressVorotDialog * VorotDialog;
    DressVorotDecor * VorotDecor;
    DressEquidistant * equidistant;
    DressGathers * gathers;
    DressGLine * gline;
    DressGorlovina * dress_gorlovina;
    SleeveElDialog * elsleeve;
    double sleevewidth;

    int ifg;
    bool simple;
    int vorotnik_type;
   void Update();
protected:
    void drawpath( QString s, QPainterPath path,bool draw, C2DLayer * L );
    void drawline( QString name, QString p1, QString p2, bool draw, C2DLayer * L );
    void requiredVariables();
  //  void getVariables();
    void setVariables();
    void UpdatePoints();
    void DrawOnWidget();
    /*SLEEVE*/
    void SleeveUpdate();
    void SleeverequiredVariables();
    void SleevesetVariables();
    void SleeveUpdatePoints();
    void SleeveDrawOnWidget();
    /*COLLAR*/
    void CollarGetValues();
    void CollarGetDsgn();
    void MakeCollar();
    void DrawCollar( bool is_collar );
    void celno_collar();
    QPainterPath gethightline( QPointF p1, double a1, double H2, QPainterPath path, double a2, int add=0 );
    QPainterPath makedartsdraw( QPainterPath path, QString d1, QString d2,QString count, bool draw );
    QList< QPainterPath > makedart( QPainterPath path, QString s, int k );
    QList< QPainterPath > Gathers( QList< QPainterPath > items, bool lev, double * sign1, double * sign2 );
    QPointF GetUpPointOnBottomLines( QLineF leftline, QLineF rightline, double h, double a=0 );
    QPainterPath GetUpLineOnBottomLine( QPointF strt, QPainterPath lineDWN, QLineF l1, QLineF l2,bool first = false );
    QPainterPath partofline( QLineF l1, double llength,QPainterPath pth1,double start,int parts=3 );
    QList< QPainterPath > gettoptines(QPainterPath p1path,QPainterPath p2path,
                                      QPainterPath p3path,QPainterPath p4path);
    QList< QPainterPath > getdecor( QPainterPath up,QPainterPath down, double * sign1,double * sign2, bool spinka=true,
                    bool lev=false );
    void drawdecor( QString name, QPointF p, QList< QPainterPath > items, bool draw, double angle = 0,double signpos = -1,double signpos2 = -1 );
    QLineF resize_collar( QPainterPath lineUP, QPainterPath lineDWN, int N,
                           double deltau,double deltad, QLineF lineSTRT );
    QLineF resize_collar_right( QPainterPath lineUP, QPainterPath lineDWN, int N,
                           double deltau,double deltad, QLineF lineSTRT );
    QLineF resize_collar_botfirst( QPainterPath lineUP, QPainterPath lineDWN, int N,
                           double deltau,double deltad, QLineF lineSTRT );
    QLineF resize_collar2( QPainterPath lineUP, QPainterPath lineDWN, int N,
                           double deltau,double deltad, QLineF lineSTRT );
    void draw_collar_part( QString s );
    void col_conners_changing_conditions();
    double col_con_leftH,col_con_rightH,col_con_uX,col_con_dX;
    QPainterPath addvorotpathplus( QPainterPath path,QPainterPath path1, bool oneside = false, bool right=false );
    QPainterPath splineaboutYl(  QLineF first, QLineF second, double K1, double K2, double lengh, double pogr=3 );
    /*COLLAR_END*/
    void NewGorlovina(); //горловина с учетом gorlovinabalance
    void NewProima(); // Пройма с учетом proimabalance
    //void NewGorlovinaClasp();//горловина под застежку переделанная.
    void takegpoints();
    void NewGorlovinaBalance();
    void signP( QString name, QPointF p1,double angle, bool dual, bool draw );
    QPointF claspwidthlimit( QPainterPath path, QLineF line );
    QList< C2DPath > path_balance( C2DPath cp1, C2DPath cp2,
                                   double balance, double shag=0.5, double a1=0,double a2=0 );
    QList< QPainterPath > splitPath( QPainterPath path, double balance, double shag );
    QPainterPath g_splinemaker( QPointF p1, QPointF p2, double angle1, double angle2,
                                double length1, double length2=0 );

    //double l_dart_angle=0, r_dart_angle=0;

    QPainterPath make_dialog_gorlovina( QPainterPath * path, QString const str );//Горловинка с несколькими точками

    QHash< QString, C2DPath > cpath;
    double gorl, gorlm, gorr, gorrm, cut, zipper,gangleS,gangleP,gangleSm,ganglePm, colclasptype;
    QPointF gorlo_dialog[];
    int gorlo_count;
    bool vorot_planka_b,vorot_planka_sign, vorot_add,Gmirropath_right,Gmirropath_left;
    double vorot_planka_sign_double,vorot_planka_sign_angle;
    double collar_clasp_gl,collar_clasp_gr;
    QPainterPath collar_topline,collar_bottomline,wide_collar_up,wide_collar_down;
    //QPainterPath collar_add_top_left,collar_add_top_right,collar_add_down_left,collar_add_down_right;
    QPainterPath coners( QPointF p, double a=10, double b=10, double cl=0, double ct=0, double a1=0, double a2=0, double a3=0, int N=0, QPainterPath linepath=QPainterPath(),QLineF lineH=QLineF() );
    QPainterPath findC2Dpathpart( QPointF p );
    QPainterPath vorotnik,vorotnikdecor;
    QLineF Zeroguidelineofpath( QPainterPath p );
    bool drawqpathqlist( QString name, QList <QPainterPath> list,bool mirror, QPointF mp );
private:
    void checkgathersvalues( double lup, QString A1, QString B1, QString C1, QString N, double GType );

    QPainterPath dpath1,dpath2;
    bool is_vorotdecor;
    QPainterPath clasp_sign3_path;
    QPainterPath clasp_sign4_path;
    double clasp_sign3_start;
    double clasp_sign4_start;
    QPainterPath proima[5];
    QPointF sleevestartpoint;
    double sleeve_VOK;
};
class collarpart
{
    public:
    collarpart( double len=0, double N=0, double du=0, double dd=0,double full = 0 )
    {
        length = len;
        Num = N;
        dup = du;
        ddwn = dd;
        ful = full;
        y1=0;
        y2=0;
        cos1=0;
        cos2=0;
    }
    double l(){ return length; }
    double du(){ return dup; }
    double dd(){ return ddwn; }
    double N(){ return Num; }
    double f(){ return ful; }
    double k(){ return this->length/this->ful; }
    void changel( double d )
    {
        this->length = this->length + d;
    }
    void changef( double d )
    {
        this->ful = this->ful + d;
    }
    double y1,y2,cos1,cos2;
private:
    double length, dup, ddwn, Num,ful;


};

#endif // C2DDRESS_H
