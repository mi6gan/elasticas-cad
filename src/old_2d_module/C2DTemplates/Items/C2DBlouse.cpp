#include "C2DBlouse.h"
//#include "myclasses/cGeometry.h"
C2DBlouse::C2DBlouse() : C2DItem()
{
    this->setPrefix( QString( "Blouse" ) );
    this->requiredVariables();
    this->addDialog( new C2DBlouseDialog( QObject::trUtf8( "Блузка" ), this->prefix(), QObject::trUtf8( "Параметры БК" ),
                     QPair< QString, double> ( QObject::trUtf8( "см" ), 10.0f ), NULL ) );
}

void C2DBlouse::Update()
{
    this->setVariables();
    this->UpdatePoints();
    this->DrawOnWidget();

}

void C2DBlouse::requiredVariables()
{
    this->addVariable( C2DVariable::set( "PTx", this->prefix()+"PTx",
                       "Not described", C2DVariable::Unitless, C2DVariable::General, 0.0f, 0.01f ) );
    this->addVariable( C2DVariable::set( "PTy", this->prefix()+"PTy", "Not describedd",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 0.01f  ) );
///////ПОЛУЧЕНИЕ ГЛОБАЛЬНЫХ ПАРАМЕТРОВ
    this->addVariable( C2DVariable::set( "T1", this->prefix()+"T1", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "T16", this->prefix()+"T16", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "T18", this->prefix()+"T18", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "T19", this->prefix()+"T19", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "T31", this->prefix()+"T31", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "T68", this->prefix()+"T68", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "T39", this->prefix()+"T39", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "T43", this->prefix()+"T43", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "T46", this->prefix()+"T46", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "T13", this->prefix()+"T13", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "T47", this->prefix()+"T47", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "T57", this->prefix()+"T57", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "T45", this->prefix()+"T45", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "T45'", this->prefix()+"T45", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 10.0f ) );


    this->addVariable( C2DVariable::set( "T36", this->prefix()+"T36", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "T76", this->prefix()+"T76", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 10.0f ) );
///////ПОЛУЧЕНИЕ ПРИБАВОК ИЗ ДИАЛОГА
    this->addVariable( C2DVariable::set( "PT1", this->prefix()+"PT1", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "PT16", this->prefix()+"PT16", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "PT18", this->prefix()+"PT18", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "PT19", this->prefix()+"PT19", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "PT31", this->prefix()+"PT31", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "PT39", this->prefix()+"PT39", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "PT43", this->prefix()+"PT43", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "PT46", this->prefix()+"PT46", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "PTK0", this->prefix()+"PTK0", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "PTK1", this->prefix()+"PTK1", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "PT13", this->prefix()+"PT13", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "PT61", this->prefix()+"PT61", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "PT47", this->prefix()+"PT47", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "PT57", this->prefix()+"PT57", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "PT68", this->prefix()+"PT68", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "PT45", this->prefix()+"PT45", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "PT45'", this->prefix()+"PT45'", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 10.0f ) );
///////ПОЛУЧЕНИЕ ПЕРЕМЕННЫХ ИЗ ДИАЛОГА
    this->addVariable( C2DVariable::set( "P5", this->prefix()+"P5", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "P15", this->prefix()+"P15", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "P17", this->prefix()+"P17", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "P18", this->prefix()+"P18", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "P19", this->prefix()+"P19", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "P20", this->prefix()+"P20", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "P21", this->prefix()+"P21", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "P22", this->prefix()+"P22", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "P23", this->prefix()+"P23", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "P13'", this->prefix()+"P13'", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 10.0f ) );
}

void C2DBlouse::setVariables()
{
    H( "Tx" ) = 1.0f + D( "PTx" );
    H( "Ty" ) = 1.0f + D( "PTy" );

////// ОБРАБОТКА ПРИБАВОК ГЛОБАЛЬНЫХ ЗНАЧЕНИЙ
    H( "LPT1" ) = 0.0f;
    H( "LPT13" ) = 0.0f;
    H( "LPT16" ) = 0.0f;
    H( "LPT18" ) = 0.0f;
    H( "LPT19" ) = 0.0f;
    H( "LPT31" ) = 0.0f;
    H( "LPT39" ) = 0.0f;
    H( "LPT43" ) = 0.0f;
    H( "LPT45" ) = 30.0f;
    H( "LPT45'" ) = 0.0f;
    H( "LPT46" ) = 0.0f;
    H( "LPT47" ) = 0.0f;
    H( "LPT57" ) = 30.0f;
    H( "LPT61" ) = 0.0f;
    H( "LPT68" ) = 0.0f;

    H( "LPTK0" ) = 0.0f;
    H( "LPTK1" ) = 0.0f;

////// ОБРАБОТКА ГЛОБАЛЬНЫХ ЗНАЧЕНИЙ
    H( "LT1" ) = D( "T1" ) + D("PT1");
    H( "LT13" ) = D( "T13" )*0.35f+D("PT13");
    H( "LT16" ) = D( "T16" ) + D("PT16");
    H( "LT18" ) = D( "T18" ) + D("PT18");
    H( "LT19" ) = D( "T19" ) + D("PT19");
    H( "LT31" ) = D( "T31" ) + D("PT31");
    H( "LT39" ) = D( "T39" ) + D("PT39");
    H( "LT43" ) = D( "T43" ) + D("PT43");
    H( "LT45" ) = D( "T45" ) + D("PT45");
    H( "LT45'" ) = D( "T45'" ) + LD("LPT45'");
    H( "LT46" ) = D( "T46" ) + D("PT46");
    H( "LT47" ) = D( "T47" ) + D("PT47");
    H( "LT57" ) = D( "T57" ) + D("PT57");
    H( "LT61" ) = D( "T36" ) - D( "T76" ) + LD("LPT61");
    H( "LT68" ) = D( "T68" ) + D("PT68");

    H( "LTK0" ) = 500.0f + LD("LPTK0");
    H( "LTK1" ) = 500.0f + LD("LPTK1");

///// ПЕРЕМЕННЫЕ
    H( "P5" ) = D("P5");// 20.0f;
    H( "P15" ) = D("P15");
    H( "P17" ) = D("P17");
    H( "P18" ) = D("P18");
    H( "P100" ) = 15.0f;
    H( "P101" ) = 15.0f;
    H( "P19" ) = D("P19");
    H( "P20" ) = D("P20");
    H( "P21" ) = D("P21");
    H( "P22" ) = D("P22");
    H( "P22'" ) = 10.0f;
    H( "P23" ) = D("P23");

    H( "P13'" ) = D("P13'");
    H( "P32L" ) = 10.0f;
    H( "P32R" ) = D("P32L");
}

void C2DBlouse::UpdatePoints()
{
    QLineF unitX = QLineF( QPointF( 0.0f, 0.0f ), QPointF( 1.0f, 0.0f ) );
    QLineF line1,line2;
    QPointF p;

    P["P0"] = QPointF( 0.0f, 0.0f );
    P["1"] = P["P0"];
    P["2"] = P["1"] - QPointF(0.0f,LD("LT39"));
    P["3"] = P["1"] - QPointF(0.0f,LD("LT43"));
    P["4"] = P["1"] - QPointF(0.0f,LD("LTK0"));
    P["5"] = P["4"] - QPointF(LD("P5"),0.0f);

    line1.setPoints(P["5"],P["1"]);
    line2.setPoints(P["3"],P["3"]-QPointF(1,0));
    line1.intersect(line2,&p);
    P["6"] = p;
    line2.setPoints(P["2"],P["2"]-QPointF(1,0));
    line1.intersect(line2,&p);
    P["7"] = p;
    P["8"] = P["7"] - QPointF(LD("LT47"),0.0f);
    //P["9"] = P["8"] - QPointF(2.0f/3.0f*(LD("LT57")),0.0f);
    P["10"] = P["8"] - QPointF((LD("LT57")),0.0f);
    P["11"] = P["10"] - QPointF((LD("LT45")),0.0f);
    P["10'"] = P["11"] + QPointF( LD("LT45'"),0.0f );
    P["8'"] = P["7"] - QPointF( LD("LT47"),0.0f );
    P["9"] = QLineF(P["10'"],P["8'"]).pointAt(0.5f);
    line1.setPoints(P["11"],P["11"]+QPointF(0,1));
    line2.setPoints(P["3"],P["3"]-QPointF(1,0));
    line1.intersect(line2,&p);
    P["12"] = p;
    line2.setPoints(P["4"],P["4"]-QPointF(1,0));
    line1.intersect(line2,&p);
    P["13"] = p;
    P["14"] = P["1"] - QPointF(LD("LT13"),0.0f);
    P["15"] = P["14"] + QPointF(0.0f,LD("P15"));

    P["1-1"]=P["1"]-QPointF( QLineF(P["1"],P["14"]).length()*0.25,0.0f );
    line1.setPoints(P["14"],P["1-1"]);
    line2.setPoints(P["14"],P["15"]);
    line1.setAngle((line1.angle()+line2.angle())/2+180.0f);
    line1.setLength(0.74*line2.length());
    P["1-2"]=line1.p2();

    P["1-1-su"] = P["1-1"] - QPointF( QLineF( P["14"], P["1-1"] ).length() / 3, 0.0f );
    line1.setPoints(P["1-2"],P["15"]);
    line2.setPoints(P["1-1"],P["1-2"]);
    line1.setAngle((line1.angle()+line2.angle())/2);
    line1.setLength(line1.length()*0.3);
    P["1-2-su"] = line1.p2();
    line1.setAngle(line1.angle()+180);
    line1.setLength(line2.length()*0.2);
    P["1-2-sb"] = line1.p2();
    P["15-sb"] = QLineF( P["15"], QLineF( P["14"], P["1-2"] ).pointAt( 0.6f ) )
                        .pointAt( 0.2f );

    line1.setPoints(P["1"],P["1"]-QPointF(1,0));
    line2.setPoints(P["8"],P["8"]+QPointF(0,1));
    line1.intersect(line2,&p);
    P["16"]=p;
    P["17"]=P["16"]-QPointF(0,LD("P17"));
    line1.setPoints(P["15"],P["17"]);
    line1.setLength(LD("LT31")+LD("P18"));
    P["18"]=line1.p2();

    P["100-0"]=QLineF(P["17"],P["8"]).pointAt(0.5);
    P["100"]=P["100-0"]-QPointF(LD("P100"),0);
    P["101-0"]=QLineF(P["17"],P["8"]).pointAt(0.75);
    P["101"]=P["101-0"]-QPointF(LD("P101"),0);

    P["19"]=P["10"]+QPointF(0,QLineF(P["17"],P["8"]).length()+LD("P19"));
    P["20"]=P["12"]+QPointF(0,LD("LT61")-LD("P20"));
    P["21"]=P["20"]+QPointF(LD("LT13")+LD("P21"),0);
    P["22"]=P["20"]-QPointF(0,LD("LT13")+LD("P22"));
    line1.setPoints(P["20"],P["10"]);
    line1.setLength(LD("LT13")+LD("P22'"));
    P["22'"]=line1.p2();
    line1.setPoints(P["21"],P["10"]);
    double x = QLineF( P["15"],P["18"] ).length()-LD("P23"),
           R = QLineF( P["10"],P["19"] ).length(),
           x2 = line1.length(),
           beta = 180/M_PI*acos( (pow(x,2) + pow(x2,2) - pow(R,2))/(2*x*x2) );

    line1.setAngle(line1.angle()-beta);
    line1.setLength(x);
    P["23"]=line1.p2();


    P["13'"]=P["13"]-QPointF(0,LD("P13'"));
    P["32"]=QPointF(P["9"].x(),P["12"].y());
    P["32L"]=P["32"]-QPointF(LD("P32L"),0);
    P["32R"]=P["32"]+QPointF(LD("P32R"),0);
    P["33"]=QPointF(P["9"].x(),P["13"].y());
    line1.setPoints(P["5"],P["6"]);
    line1.setAngle(line1.angle()-90);
    line1.intersect(QLineF(P["33"],P["32"]),&p);
    P["34"]=p;

    ////  Сплайны точка 20
    P["22r"] = P["22"] + QPointF( QLineF(P["20"],P["22"]).length()*0.6f,0.0f );
    line1.setPoints(P["21"],P["20"]);
    line1.setAngle(line1.angle()-90);
    line1.setLength(QLineF(P["20"],P["21"]).length()*0.6f);
    P["21d"] = line1.p2();
    //ПРОЙМА

    line1.setPoints(P["8'"],P["10'"]);
    P["341"] = line1.pointAt(0.6f);
    line1.setPoints(P["341"],P["8'"]);
    P["332"]=P["8'"]+QPointF(0,line1.length());
    line1.setPoints(P["341"],P["10'"]);
    P["352"]=P["10'"]+QPointF(0,line1.length());

    line1.setPoints(P["18"],P["15"]);
    line1.setAngle(line1.angle()+90);
    line1.intersect(QLineF(P["8'"],P["332"]),&p);
    P["142"]=p;
    P["143"]=QLineF(P["18"],P["332"]).pointAt(0.5);
    P["144"]=QLineF(P["143"],P["142"]).pointAt(0.5);
    line1.setLength(QLineF(P["18"],P["144"]).length()*0.3);
    P["18d"]=line1.p2();
    line1.setPoints(P["332"],P["142"]);
    line1.setLength(QLineF(P["144"],P["332"]).length()*0.3);
    P["332u"]=line1.p2();
    line1.setPoints(P["144"],P["18"]);
    line2.setPoints(P["332"],P["144"]);
    line1.setAngle((line1.angle()+line2.angle())/2);
    line1.setLength(line1.length()*0.4);
    P["144u"]=line1.p2();
    line1.setAngle(line1.angle()+180);
    line1.setLength(line2.length()*0.4);
    P["144d"]=line1.p2();

    line1.setPoints(P["23"],P["21"]);
    line1.setAngle(line1.angle()-90);
    line1.intersect(QLineF(P["10'"],P["352"]),&p);
    P["145"]=p;
    P["146"]=QLineF(P["23"],P["352"]).pointAt(0.5);
    P["147"]=QLineF(P["146"],P["145"]).pointAt(0.5);
    line1.setLength(QLineF(P["23"],P["147"]).length()*0.3);
    P["23d"]=line1.p2();
    line1.setPoints(P["352"],P["145"]);
    line1.setLength(QLineF(P["147"],P["352"]).length()*0.3);
    P["352u"]=line1.p2();
    line1.setPoints(P["147"],P["23"]);
    line2.setPoints(P["352"],P["147"]);
    line1.setAngle((line1.angle()+line2.angle())/2);
    line1.setLength(line1.length()*0.4);
    P["147u"]=line1.p2();
    line1.setAngle(line1.angle()+180);
    line1.setLength(line2.length()*0.4);
    P["147d"]=line1.p2();

    line1.setPoints(P["10'"],P["352"]);
    P["352d"]=line1.pointAt(0.5f);
    P["341r"]=P["341"]-QPointF(line1.length()/2,0);

    line1.setPoints(P["8'"],P["332"]);
    P["332d"]=line1.pointAt(0.5f);
    P["341l"]=P["341"]+QPointF(line1.length()/2,0);
////////////////////////////Tochki nignego splaina
    P["13''"] = P["13'"] + QPointF( LD("LT46"), 0 );
    line1.setPoints( P["34"], P["32L"] );
    line1.setAngle(line1.angle()-90.0f);
    line2.setPoints( P["13''"],P["34"] );
    line1.setLength( line2.length() * 0.2f );
    P["34s"] =line1.p2();
    line1.setPoints( P["13''"], P["13''"] + QPointF( 1,0 ) );
    line1.setLength( line2.length() * 0.2f );
    P["13''s"]=line1.p2();
    //P9 - 9'
        QPainterPath bottomspline;
        bottomspline.moveTo( P["341"] );
        if( P["9"].x() <= P["341"].x() )
            bottomspline.cubicTo( P["341r"],P["352d"],P["352"] );
        else
            bottomspline.cubicTo( P["341l"],P["332d"],P["332"] );

        P["9'"] = Unicus::splinepointonx( bottomspline, P["9"].x(), 0.5f );

        /////////Необходимые корректировки =)
        QString key;
        foreach( key, P.keys() )
           P[key]=QPointF(P[key].x()*-1,P[key].y());
}

void C2DBlouse::DrawOnWidget()
{

    Unicus::console("T13",LD("LT13"));
    this->line( Sync( attr( SYNC_NAME, QString( "1-4" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "1","4" ) ),
                      LM->thick_solid() ), true );
    this->line( Sync( attr( SYNC_NAME, QString( "1-5" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "1","5" ) ),
                      LM->thick_solid() ), true );
    this->line( Sync( attr( SYNC_NAME, QString( "5-4" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "5","4" ) ),
                      LM->thick_solid() ), true );
    this->line( Sync( attr( SYNC_NAME, QString( "2-7" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "2","7" ) ),
                      LM->thick_solid() ), true );
    this->line( Sync( attr( SYNC_NAME, QString( "3-6" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "3","6" ) ),
                      LM->thick_solid() ), true );
    this->line( Sync( attr( SYNC_NAME, QString( "7-8" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "7","8" ) ),
                      LM->thick_solid() ), true );
    this->line( Sync( attr( SYNC_NAME, QString( "9-8" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "9","8" ) ),
                      LM->thick_solid() ), true );
    this->line( Sync( attr( SYNC_NAME, QString( "9-10" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "9","10" ) ),
                      LM->thick_solid() ), true );
    this->line( Sync( attr( SYNC_NAME, QString( "11-10" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "11","10" ) ),
                      LM->thick_solid() ), true );
    this->line( Sync( attr( SYNC_NAME, QString( "11-13" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "11","13" ) ),
                      LM->thick_solid() ), true );
    this->line( Sync( attr( SYNC_NAME, QString( "4-13" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "4","13" ) ),
                      LM->thick_solid() ), true );
    this->line( Sync( attr( SYNC_NAME, QString( "12-3" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "12","3" ) ),
                      LM->thick_solid() ), true );
    this->line( Sync( attr( SYNC_NAME, QString( "1-14" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "1","14" ) ),
                      LM->thick_solid() ), true );
    this->line( Sync( attr( SYNC_NAME, QString( "15-14" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "15","14" ) ),
                      LM->thick_solid() ), true );

    this->spline( Sync( attr( SYNC_NAME,  QString( "S1-1-1-2" ) ),
                        attr( SYNC_TYPE, C2DSync::Spline ),
                        attr( SYNC_LIST, MakeList( "1-1", "1-1-su", "1-2-sb", "1-2" ) ),
                        LM->thick_solid() ), true );
    this->spline( Sync( attr( SYNC_NAME,  QString( "S1-2-15" ) ),
                        attr( SYNC_TYPE, C2DSync::Spline ),
                        attr( SYNC_LIST, MakeList( "1-2", "1-2-su", "15-sb", "15" ) ),
                        LM->thick_solid() ), true );

    this->line( Sync( attr( SYNC_NAME, QString( "16-14" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "16","14" ) ),
                      LM->thick_solid() ), true );
    this->line( Sync( attr( SYNC_NAME, QString( "16-8" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "16","8" ) ),
                      LM->thick_solid() ), true );
    this->line( Sync( attr( SYNC_NAME, QString( "15-18" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "15","18" ) ),
                      LM->thick_solid() ), true );
    this->line( Sync( attr( SYNC_NAME, QString( "100-0-100" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "100-0","100" ) ),
                      LM->thick_solid() ), true );
    this->line( Sync( attr( SYNC_NAME, QString( "101-0-101" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "101-0","101" ) ),
                      LM->thick_solid() ), true );
    this->line( Sync( attr( SYNC_NAME, QString( "10-19" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "10","19" ) ),
                      LM->thick_solid() ), true );
    this->line( Sync( attr( SYNC_NAME, QString( "11-22" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "11","22" ) ),
                      LM->thick_solid() ), true );

    this->line( Sync( attr( SYNC_NAME, QString( "21-20" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "21","20" ) ),
                      LM->thick_solid() ), true );
    this->line( Sync( attr( SYNC_NAME, QString( "22-20" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "22","20" ) ),
                      LM->thick_solid() ), true );
    this->line( Sync( attr( SYNC_NAME, QString( "21-23" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "21","23" ) ),
                      LM->thick_solid() ), true );

    this->line( Sync( attr( SYNC_NAME, QString( "13-13'" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "13","13'" ) ),
                      LM->thick_solid() ), true );
    this->line( Sync( attr( SYNC_NAME, QString( "13'-13''" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "13'","13''" ) ),
                      LM->thick_solid() ), true );
    this->spline( Sync( attr( SYNC_NAME,  QString( "S1-13''-34" ) ),
                        attr( SYNC_TYPE, C2DSync::Spline ),
                        attr( SYNC_LIST, MakeList( "13''", "13''s", "34s", "34" ) ),
                        LM->thick_solid() ), true );
    this->line( Sync( attr( SYNC_NAME, QString( "5-34" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "5","34" ) ),
                      LM->thick_solid() ), true );
    this->line( Sync( attr( SYNC_NAME, QString( "32-34" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "32","34" ) ),
                      LM->thick_solid() ), true );
    this->line( Sync( attr( SYNC_NAME, QString( "32-9" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "32","9'" ) ),
                      LM->thick_solid() ), true );
    this->line( Sync( attr( SYNC_NAME, QString( "32R-9" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "32R","9'" ) ),
                      LM->thick_solid() ), true );
    this->line( Sync( attr( SYNC_NAME, QString( "32L-9" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "32L","9'" ) ),
                      LM->thick_solid() ), true );
    this->line( Sync( attr( SYNC_NAME, QString( "32R-34" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "32R","34" ) ),
                      LM->thick_solid() ), true );
    this->line( Sync( attr( SYNC_NAME, QString( "32L-34" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "32L","34" ) ),
                      LM->thick_solid() ), true );

    this->spline( Sync( attr( SYNC_NAME,  QString( "S22-21" ) ),
                        attr( SYNC_TYPE, C2DSync::Spline ),
                        attr( SYNC_LIST, MakeList( "22", "22r", "21d", "21" ) ),
                        LM->thick_solid() ), true );
/*НАЧАЛО ПРОЙМЫ***************************/
    this->spline( Sync( attr( SYNC_NAME,  QString( "S332-144" ) ),
                        attr( SYNC_TYPE, C2DSync::Spline ),
                        attr( SYNC_LIST, MakeList( "332", "332u", "144d", "144" ) ),
                        LM->thick_solid() ), true );
    this->spline( Sync( attr( SYNC_NAME,  QString( "S144-18" ) ),
                        attr( SYNC_TYPE, C2DSync::Spline ),
                        attr( SYNC_LIST, MakeList( "144", "144u", "18d", "18" ) ),
                        LM->thick_solid() ), true );
    this->spline( Sync( attr( SYNC_NAME,  QString( "S352-147" ) ),
                        attr( SYNC_TYPE, C2DSync::Spline ),
                        attr( SYNC_LIST, MakeList( "352", "352u", "147d", "147" ) ),
                        LM->thick_solid() ), true );
    this->spline( Sync( attr( SYNC_NAME,  QString( "S147-23" ) ),
                        attr( SYNC_TYPE, C2DSync::Spline ),
                        attr( SYNC_LIST, MakeList( "147", "147u", "23d", "23" ) ),
                        LM->thick_solid() ), true );
    this->spline( Sync( attr( SYNC_NAME,  QString( "S332-341" ) ),
                        attr( SYNC_TYPE, C2DSync::Spline ),
                        attr( SYNC_LIST, MakeList( "332", "332d", "341l", "341" ) ),
                        LM->thick_solid() ), true );
    this->spline( Sync( attr( SYNC_NAME,  QString( "S341-352" ) ),
                        attr( SYNC_TYPE, C2DSync::Spline ),
                        attr( SYNC_LIST, MakeList( "341", "341r", "352d", "352" ) ),
                        LM->thick_solid() ), true );
/*КОНЕЦ ПРОЙМЫ*****************************/

    this->point( Sync( attr( SYNC_NAME, QString( "10'" ) ),
                      attr( SYNC_TYPE, C2DSync::Point ),
                      attr( SYNC_LIST, MakeList( "10'" ) ),
                      LM->thick_solid() ), true );
    this->point( Sync( attr( SYNC_NAME, QString( "8'" ) ),
                      attr( SYNC_TYPE, C2DSync::Point ),
                      attr( SYNC_LIST, MakeList( "8'" ) ),
                      LM->thick_solid() ), true );
    this->point( Sync( attr( SYNC_NAME, QString( "341" ) ),
                      attr( SYNC_TYPE, C2DSync::Point ),
                      attr( SYNC_LIST, MakeList( "341" ) ),
                      LM->thick_solid() ), true );
    this->point( Sync( attr( SYNC_NAME, QString( "332" ) ),
                      attr( SYNC_TYPE, C2DSync::Point ),
                      attr( SYNC_LIST, MakeList( "332" ) ),
                      LM->thick_solid() ), true );
    this->point( Sync( attr( SYNC_NAME, QString( "352" ) ),
                      attr( SYNC_TYPE, C2DSync::Point ),
                      attr( SYNC_LIST, MakeList( "352" ) ),
                      LM->thick_solid() ), true );
    this->point( Sync( attr( SYNC_NAME, QString( "142" ) ),
                      attr( SYNC_TYPE, C2DSync::Point ),
                      attr( SYNC_LIST, MakeList( "142" ) ),
                      LM->thick_solid() ), true );
    this->point( Sync( attr( SYNC_NAME, QString( "143" ) ),
                      attr( SYNC_TYPE, C2DSync::Point ),
                      attr( SYNC_LIST, MakeList( "143" ) ),
                      LM->thick_solid() ), true );
    this->point( Sync( attr( SYNC_NAME, QString( "144" ) ),
                      attr( SYNC_TYPE, C2DSync::Point ),
                      attr( SYNC_LIST, MakeList( "144" ) ),
                      LM->thick_solid() ), true );

    this->point( Sync( attr( SYNC_NAME, QString( "9'" ) ),
                      attr( SYNC_TYPE, C2DSync::Point ),
                      attr( SYNC_LIST, MakeList( "9'" ) ),
                      LM->thick_solid() ), true );


}
