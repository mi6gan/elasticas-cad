#include "blouseplot.h"
#define LD(A) 10.0f*V[QString("Blouse:")+A].toDouble()
#define D(A) V[A].toDouble()
#define I(A) V[A].toInt()
#define B(A) V[A].toBool()
#define PP(A) P[A]->pos()

BlousePlot::BlousePlot(QGraphicsScene* scene):Plot(scene)
{
    const QString pnames[]={"1","2","3","4","5","6","7","8","8'","9","9'",
                            "10","10'","11","12","13","13'","13''","13''s","14","15","1-1",
                            "1-1-su","1-2-su","1-2-sb","1-2","15-sb","15",
                            "16","17","18","18d","19","20","21","21r","21d","22",
                            "22'","22r","23","23d","32","32R","32L",
                            "33","100-0","100","100-0","101",
                            "101-0","34s", "34","332","332u","332d",
                            "142","143","144d","144","145","146","147",
                            "144u","352","352d","352u","147","147u","147d",
                            "341","341l","341r", NULL};


    Vertex* v;
    for(int i=0;pnames[i]!=NULL;i++)
    {
        v=new Vertex(this,QPointF());
        //new Label(this,v,pnames[i],true);
        P[pnames[i]]=v;
    }
    new Line(this,P["1"],P["4"]);new Line(this,P["1"],P["5"]);
    new Line(this,P["5"],P["4"]); new Line(this,P["2"],P["7"]);
    new Line(this,P["3"],P["6"]); new Line(this,P["7"],P["8"]);
    new Line(this,P["9"],P["8"]); new Line(this,P["9"],P["10"]);
    new Line(this,P["11"],P["10"]); new Line(this,P["11"],P["13"]);
    new Line(this,P["4"],P["13"]); new Line(this,P["12"],P["3"]);
    new Line(this,P["1"],P["14"]); new Line(this,P["15"],P["14"]);

    new BezierCurve3(this,P["1-1"],P["1-1-su"],P["1-2-sb"],P["1-2"]);
    new BezierCurve3(this,P["1-2"],P["1-2-su"],P["15-sb"],P["15"]);

    new Line(this,P["16"],P["14"]); new Line(this,P["16"],P["8"]);
    new Line(this,P["15"],P["18"]); new Line(this,P["100-0"],P["100"]);
    new Line(this,P["101-0"],P["101"]); new Line(this,P["10"],P["19"]);
    new Line(this,P["11"],P["22"]);

    new Line(this,P["21"],P["20"]); new Line(this,P["22"],P["20"]);
    new Line(this,P["21"],P["23"]); new Line(this,P["13"],P["13'"]);
    new Line(this,P["13'"],P["13''"]);
    new BezierCurve3(this,P["13''"], P["13''s"], P["34s"], P["34"]);
    new Line(this,P["5"],P["34"]); new Line(this,P["32"],P["34"]);
    new Line(this,P["32"],P["9"]); new Line(this,P["32R"],P["9"]);
    new Line(this,P["32L"],P["9"]); new Line(this,P["32R"],P["34"]);
    new Line(this,P["32L"],P["34"]);
    new BezierCurve3(this,P["22"], P["22r"], P["21d"], P["21"]);

    //НАЧАЛО ПРОЙМЫ***************************
    new BezierCurve3(this,P["332"], P["332u"], P["144d"], P["144"]);
    new BezierCurve3(this,P["144"], P["144u"], P["18d"], P["18"]);
    new BezierCurve3(this,P["352"], P["352u"], P["147d"], P["147"]);
    new BezierCurve3(this,P["147"], P["147u"], P["23d"], P["23"]);
    new BezierCurve3(this,P["332"], P["332d"], P["341l"], P["341"]);
    new BezierCurve3(this,P["341"], P["341r"], P["352d"], P["352"]);
    //КОНЕЦ ПРОЙМЫ*****************************

    new Label(this,P["10'"],"10'",true);new Label(this,P["8'"],"8'",true);
    new Label(this,P["341"],"341",true);new Label(this,P["332"],"332",true);
    new Label(this,P["352"],"352",true);new Label(this,P["142"],"142",true);
    new Label(this,P["143"],"143",true);new Label(this,P["144"],"144",true);
    new Label(this,P["9'"],"9'",true);

    LPT1=LPT13=LPT16=LPT18=LPT19=LPT31=LPT39=LPT43=0;
    LPT45_=LPT46=LPT47=LPT61=LPT68=LPTK0=LPTK1=0;
    LPT45=LPT57=30.0f;
}
void BlousePlot::update()
{
    const Elasticas::CommonData & V=Elasticas::Core::Instance()->commonVariables();
    double LT1=LD("T1")+LD("PT1"), LT13=LD("T13")*0.35f+LD("PT13"),
           LT16=LD("T16")+LD("PT16"), LT18=LD("T18")+LD("PT18"),
           LT19=LD("T19")+LD("PT19"), LT31=LD("T31")+LD("PT31"),
           LT39=LD("T39")+LD("PT39"), LT43=LD("T43")+LD("PT43"),
           LT45=LD("T45")+LD("PT45"),
           LT45_=LD("T45'")+LD("PT45'"), LT46=LD("T46")+LD("PT46"),
           LT47=LD("T47")+LD("PT47"), LT57=LD("T57")+LD("PT57"),
           LT61=LD("T36")-LD("T76")+LPT61, LT68=LD("T68")+LD("PT68"),
           LTK0=500.0f+LPTK0, LTK1=500.0f+LPTK1;
    double P100=15.0f,P101=15.0f,P22_=10.0f,P32R=10.0f,P32L=10.0f;

    QLineF line1,line2;
    QPointF p;

    P["1"]->setPos(QPointF(0,0));
    P["2"]->setPos(QPointF(0,0)-QPointF(0,LT39));
    P["3"]->setPos(QPointF(0,0)-QPointF(0,LT43));
    P["4"]->setPos(QPointF(0,0)-QPointF(0,LTK0));
    P["5"]->setPos(PP("4")-QPointF(LD("P5"),0));

    line1.setPoints(PP("5"),PP("1"));
    line2.setPoints(PP("3"),PP("3")-QPointF(1,0));
    line1.intersect(line2,&p);
    P["6"]->setPos(p);
    line2.setPoints(PP("2"),PP("2")-QPointF(1,0));
    line1.intersect(line2,&p);
    P["7"]->setPos(p);
    P["8"]->setPos(PP("7")-QPointF(LT47,0.0f));
    P["10"]->setPos(PP("8")-QPointF(LT57,0.0f));
    P["11"]->setPos(PP("10")-QPointF(LT45,0.0f));
    P["10'"]->setPos(PP("11")+QPointF(LT45_,0.0f));
    P["8'"]->setPos(PP("7")-QPointF(LT47,0.0f));
    P["9"]->setPos(QLineF(PP("10'"),PP("8'")).pointAt(0.5f));
    line1.setPoints(PP("11"),PP("11")+QPointF(0,1));
    line2.setPoints(PP("3"),PP("3")+QPointF(1,0));
    line1.intersect(line2,&p);
    P["12"]->setPos(p);
    line2.setPoints(PP("4"),PP("4")-QPointF(1,0));
    line1.intersect(line2,&p);
    P["13"]->setPos(p);
    P["14"]->setPos(PP("1")-QPointF(LT13,0.0f));
    P["15"]->setPos(PP("14")+QPointF(0.0f,LD("P15")));

    P["1-1"]->setPos(PP("1")-QPointF(QLineF(PP("1"),PP("14")).length()*0.25f,0.0f));
    line1.setPoints(PP("14"),PP("1-1"));
    line2.setPoints(PP("14"),PP("15"));
    line1.setAngle((line1.angle()+line2.angle())/2.0f+180.0f);
    line1.setLength(0.74f*line2.length());
    P["1-2"]->setPos(line1.p2());

    P["1-1-su"]->setPos(PP("1-1")-QPointF(QLineF(PP("14"),PP("1-1")).length()/3.0f,0.0f));
    line1.setPoints(PP("1-2"),PP("15"));
    line2.setPoints(PP("1-1"),PP("1-2"));
    line1.setAngle((line1.angle()+line2.angle())/2.0f);
    line1.setLength(line1.length()*0.3f);
    P["1-2-su"]->setPos(line1.p2());
    line1.setAngle(line1.angle()+180.0f);
    line1.setLength(line2.length()*0.2f);
    P["1-2-sb"]->setPos(line1.p2());
    P["15-sb"]->setPos(QLineF(PP("15"),QLineF(PP("14"),PP("1-2")).pointAt(0.6f)).pointAt(0.2f));
    line1.setPoints(PP("1"),PP("1")-QPointF(1,0));
    line2.setPoints(PP("8"),PP("8")-QPointF(0,1));
    line1.intersect(line2,&p);
    P["16"]->setPos(p);
    P["17"]->setPos(PP("16")-QPointF(0,LD("P17")));
    line1.setPoints(PP("15"),PP("17"));
    line1.setLength(LT31+LD("P18"));
    P["18"]->setPos(line1.p2());

    P["100-0"]->setPos(QLineF(PP("17"),PP("8")).pointAt(0.5f));
    P["100"]->setPos(PP("100-0")-QPointF(P100,0));
    P["101-0"]->setPos(QLineF(PP("17"),PP("8")).pointAt(0.75f));
    P["101"]->setPos(PP("101-0")-QPointF(P101,0.0f));

    P["19"]->setPos(PP("10")+QPointF(0,QLineF(PP("17"),PP("8")).length()+LD("P19")));
    P["20"]->setPos(PP("12")+QPointF(0,LT61-LD("P20")));
    P["21"]->setPos(PP("20")+QPointF(LT13+LD("P21"),0));
    P["22"]->setPos(PP("20")-QPointF(0,LT13+LD("P22")));
    line1.setPoints(PP("20"),PP("10"));
    line1.setLength(LT13+P22_);
    P["22'"]->setPos(line1.p2());
    line1.setPoints(PP("21"),PP("10"));
    double x = QLineF( PP("15"),PP("18") ).length()-LD("P23"),
           R = QLineF( PP("10"),PP("19") ).length(),
           x2 = line1.length(),
           beta = 180/M_PI*acos( (pow(x,2) + pow(x2,2) - pow(R,2))/(2*x*x2) );

    line1.setAngle(line1.angle()-beta);
    line1.setLength(x);
    P["23"]->setPos(line1.p2());


    P["13'"]->setPos(PP("13")-QPointF(0,LD("P13'")));
    P["32"]->setPos(QPointF(PP("9").x(),PP("12").y()));
    P["32L"]->setPos(PP("32")-QPointF(P32L,0));
    P["32R"]->setPos(PP("32")+QPointF(P32R,0));
    P["33"]->setPos(QPointF(PP("9").x(),PP("13").y()));
    line1.setPoints(PP("5"),PP("6"));
    line1.setAngle(line1.angle()-90);
    line1.intersect(QLineF(PP("33"),PP("32")),&p);
    P["34"]->setPos(p);

    ////  Сплайны точка 20
    P["22r"]->setPos(PP("22") + QPointF( QLineF(PP("20"),PP("22")).length()*0.6f,0.0f ));
    line1.setPoints(PP("21"),PP("20"));
    line1.setAngle(line1.angle()-90);
    line1.setLength(QLineF(PP("20"),PP("21")).length()*0.6f);
    P["21d"]->setPos(line1.p2());
    //ПРОЙМА

    line1.setPoints(PP("8'"),PP("10'"));
    P["341"]->setPos(line1.pointAt(0.6f));
    line1.setPoints(PP("341"),PP("8'"));
    P["332"]->setPos(PP("8'")+QPointF(0,line1.length()));
    line1.setPoints(PP("341"),PP("10'"));
    P["352"]->setPos(PP("10'")+QPointF(0,line1.length()));

    line1.setPoints(PP("18"),PP("15"));
    line1.setAngle(line1.angle()+90);
    line1.intersect(QLineF(PP("8'"),PP("332")),&p);
    P["142"]->setPos(p);
    P["143"]->setPos(QLineF(PP("18"),PP("332")).pointAt(0.5));
    P["144"]->setPos(QLineF(PP("143"),PP("142")).pointAt(0.5));
    line1.setLength(QLineF(PP("18"),PP("144")).length()*0.3);
    P["18d"]->setPos(line1.p2());
    line1.setPoints(PP("332"),PP("142"));
    line1.setLength(QLineF(PP("144"),PP("332")).length()*0.3);
    P["332u"]->setPos(line1.p2());
    line1.setPoints(PP("144"),PP("18"));
    line2.setPoints(PP("332"),PP("144"));
    line1.setAngle((line1.angle()+line2.angle())/2);
    line1.setLength(line1.length()*0.4);
    P["144u"]->setPos(line1.p2());
    line1.setAngle(line1.angle()+180);
    line1.setLength(line2.length()*0.4);
    P["144d"]->setPos(line1.p2());

    line1.setPoints(PP("23"),PP("21"));
    line1.setAngle(line1.angle()-90);
    line1.intersect(QLineF(PP("10'"),PP("352")),&p);
    P["145"]->setPos(p);
    P["146"]->setPos(QLineF(PP("23"),PP("352")).pointAt(0.5));
    P["147"]->setPos(QLineF(PP("146"),PP("145")).pointAt(0.5));
    line1.setLength(QLineF(PP("23"),PP("147")).length()*0.3);
    P["23d"]->setPos(line1.p2());
    line1.setPoints(PP("352"),PP("145"));
    line1.setLength(QLineF(PP("147"),PP("352")).length()*0.3);
    P["352u"]->setPos(line1.p2());
    line1.setPoints(PP("147"),PP("23"));
    line2.setPoints(PP("352"),PP("147"));
    line1.setAngle((line1.angle()+line2.angle())/2);
    line1.setLength(line1.length()*0.4);
    P["147u"]->setPos(line1.p2());
    line1.setAngle(line1.angle()+180);
    line1.setLength(line2.length()*0.4);
    P["147d"]->setPos(line1.p2());

    line1.setPoints(PP("10'"),PP("352"));
    P["352d"]->setPos(line1.pointAt(0.5f));
    P["341r"]->setPos(PP("341")-QPointF(line1.length()/2,0));

    line1.setPoints(PP("8'"),PP("332"));
    P["332d"]->setPos(line1.pointAt(0.5f));
    P["341l"]->setPos(PP("341")+QPointF(line1.length()/2,0));
////////////////////////////Tochki nignego splaina
    P["13''"]->setPos( PP("13'") + QPointF( LT46, 0 ));
    line1.setPoints( PP("34"), PP("32L") );
    line1.setAngle(line1.angle()-90.0f);
    line2.setPoints( PP("13''"),PP("34") );
    line1.setLength( line2.length() * 0.2f );
    P["34s"]->setPos(line1.p2());
    line1.setPoints( PP("13''"), PP("13''") + QPointF( 1,0 ) );
    line1.setLength( line2.length() * 0.2f );
    P["13''s"]->setPos(line1.p2());

    //P9 - 9'
        QPainterPath bottomspline;
        bottomspline.moveTo( PP("341") );
        if( PP("9").x() <= PP("341").x() )
            bottomspline.cubicTo( PP("341r"),PP("352d"),PP("352") );
        else
            bottomspline.cubicTo( PP("341l"),PP("332d"),PP("332") );

        P["9'"]->setPos(splinepointonxBlouse( bottomspline, PP("9").x(), 0.5f ));

        /////////Необходимые корректировки =)
        QString key;
        foreach( key, P.keys() )
           P[key]->setPos(QPointF(PP(key).x()*-1,PP(key).y()*-1));



    Plot::update();
}

QPointF BlousePlot::splinepointonxBlouse( QPainterPath spline , double xx,double n)
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
//-----------------------------------
