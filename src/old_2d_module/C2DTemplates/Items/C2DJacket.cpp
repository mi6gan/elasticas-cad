#include "C2DJacket.h"
C2DJacket::C2DJacket() : C2DItem()
{
    this->setPrefix( QString( "Jacket" ) );
    this->requiredVariables();
    this->addDialog( new C2DJacketDialog( QObject::trUtf8( "Пиджак" ), this->prefix(), QObject::trUtf8( "Параметры БК" ),
                     QPair< QString, double> ( QObject::trUtf8( "см" ), 10.0f ), NULL ) );
    rotatebeta =0;
}

void C2DJacket::Update()
{
    this->setVariables();
    this->UpdatePoints();
    this->DrawOnWidget();

}


void C2DJacket::requiredVariables()
{
    variables << "T7" << "T12" << "T13" << "T14" << "T15" << "T18" << "T19" << "T25" << "T26"
              << "T34" << "T35" << "T36" << "T38" << "T39" << "T40" << "T44" << "T45" << "T46" << "T47" << "T57" ;
    Unicus::console("qQstring",variables.count());
    for ( int i = 0; i < variables.count(); i++ )
    {
        this->addVariable( C2DVariable::set( variables[i], this->prefix()+variables[i],
                       "Not described", C2DVariable::Metrics, C2DVariable::General, 1000.0f, 10.0f ) );
        this->addVariable( C2DVariable::set( "P"+variables[i], this->prefix()+"P"+variables[i],
                       "Not described", C2DVariable::Metrics, C2DVariable::General, 0.0f, 10.0f ) );
    }

    this->addVariable( C2DVariable::set( "PTx", this->prefix()+"PTx",
                       "Not described", C2DVariable::Unitless, C2DVariable::General, 0.0f, 0.01f ) );
    this->addVariable( C2DVariable::set( "PTy", this->prefix()+"PTy", "Not describedd",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 0.01f  ) );

    ///////ПОЛУЧЕНИЕ ПЕРЕМЕННЫХ ИЗ ДИАЛОГА
        this->addVariable( C2DVariable::set( "P14", this->prefix()+"P14", "Not described", C2DVariable::Metrics,
                           C2DVariable::General, 1000.0f, 10.0f ) );
        this->addVariable( C2DVariable::set( "P16", this->prefix()+"P16", "Not described", C2DVariable::Metrics,
                           C2DVariable::General, 1000.0f, 10.0f ) );
        this->addVariable( C2DVariable::set( "P97", this->prefix()+"P97", "Not described", C2DVariable::Metrics,
                           C2DVariable::General, 1000.0f, 10.0f ) );
        this->addVariable( C2DVariable::set( "P161", this->prefix()+"P161", "Not described", C2DVariable::Metrics,
                           C2DVariable::General, 1000.0f, 10.0f ) );
        this->addVariable( C2DVariable::set( "P331", this->prefix()+"P331", "Not described", C2DVariable::Metrics,
                           C2DVariable::General, 1000.0f, 10.0f ) );
        this->addVariable( C2DVariable::set( "P341", this->prefix()+"P341", "Not described", C2DVariable::Metrics,
                           C2DVariable::General, 1000.0f, 10.0f ) );
        this->addVariable( C2DVariable::set( "P332", this->prefix()+"P332", "Not described", C2DVariable::Metrics,
                           C2DVariable::General, 1000.0f, 10.0f ) );
        this->addVariable( C2DVariable::set( "P346", this->prefix()+"P346", "Not described", C2DVariable::Metrics,
                           C2DVariable::General, 1000.0f, 0.01f ) );
        this->addVariable( C2DVariable::set( "P352", this->prefix()+"P352", "Not described", C2DVariable::Metrics,
                           C2DVariable::General, 1000.0f, 10.0f ) );
        this->addVariable( C2DVariable::set( "P411", this->prefix()+"P411", "Not described", C2DVariable::Metrics,
                           C2DVariable::General, 1000.0f, 10.0f ) );
        this->addVariable( C2DVariable::set( "P511", this->prefix()+"P511", "Not described", C2DVariable::Metrics,
                           C2DVariable::General, 1000.0f, 10.0f ) );
        this->addVariable( C2DVariable::set( "P911", this->prefix()+"P911", "Not described", C2DVariable::Metrics,
                           C2DVariable::General, 1000.0f, 10.0f ) );
        this->addVariable( C2DVariable::set( "P122-1", this->prefix()+"P122-1", "Not described", C2DVariable::Metrics,
                           C2DVariable::General, 1000.0f, 1.0f ) );
}

void C2DJacket::setVariables()
{
    H( "Tx" ) = 1.0f + D( "PTx" );
    H( "Ty" ) = 1.0f + D( "PTy" );


////// ОБРАБОТКА ГЛОБАЛЬНЫХ ЗНАЧЕНИЙ
    H( "LT7" )  = D( "T7" ) +  D( "PT7" );
    H( "LT12" ) = D( "T12" ) + D( "PT12" );
    H( "LT13" ) = D( "T13" ) + D( "PT13" );
    H( "LT14" ) = D( "T14" ) + D( "PT14" );
    H( "LT15" ) = D( "T15" ) + D( "PT15" );
    H( "LT18" ) = D( "T18" ) + D( "PT18" );
    H( "LT19" ) = D( "T19" ) + D( "PT19" );
    H( "LT25" ) = D( "T25" ) + D( "PT25" );
    H( "LT26" ) = D( "T26" ) + D( "PT26" );
    H( "LT34" ) = D( "T34" ) + D( "PT34" );
    H( "LT35" ) = D( "T35" ) + D( "PT35" );
    H( "LT36" ) = D( "T36" ) + D( "PT36" );
    H( "LT38" ) = D( "T38" ) + D( "PT38" );
    H( "LT39" ) = D( "T39" ) + D( "PT39" );
    H( "LT40" ) = D( "T40" ) + D( "PT40" );
    H( "LT44" ) = D( "T44" ) + D( "PT44" );
    H( "LT45" ) = D( "T45" ) + D( "PT45" );
    H( "LT46" ) = D( "T46" ) + D( "PT46" );
    H( "LT47" ) = D( "T47" ) + D( "PT47" );
    H( "LT57" ) = D( "T57" ) + D( "PT57" );
/////////////////////////////////////////////////////////////////////
   // H( "LTK0" ) = 500.0f + LD("LPTK0");
   // H( "LTK1" ) = 500.0f + LD("LPTK1");

    Unicus::console( "}}}}}}}}}", LD( "LT57" ) );
///// ПЕРЕМЕННЫЕ
    H( "P14" ) = D( "P14" );
    H( "P16" ) = D( "P16" );
    H( "P97" ) = D( "P97" );
    H( "P161" ) = D( "P161" );
    H( "P331" ) = D( "P331" );
   // H( "P351" ) = 20.0f;
    H( "P341" ) = D( "P341" );
   // H( "P341-1" ) = 0.0f;
    H( "P332" ) = D( "P332" );
   // H( "P342" ) = 10.0f;
    H( "P346" ) = D( "P346" ); //Проценты от 0 до 1 %
    H( "P352" ) = D( "P352" );
   // H( "P343" ) = 0.0f;
    H( "P411" ) = D( "P411" );
    H( "P511" ) = D( "P511" );
    H( "P911" ) = D( "P911" );
    H( "P122-1" ) = D( "P122-1" );
    //Вторая партия
    H("P22-1") = 10.0f;//D("P22-1");
    H("P16K") = 0.25f;//Проценты

    Unicus::console( "1 | P14 ", LD( "P14" ) );
    Unicus::console( "2 | P16 ", LD( "P16" ) );
    Unicus::console( "3 | P97 ", LD( "P97" ) );
    Unicus::console( "4 | P161 ", LD( "P161" ) );
    Unicus::console( "5 | P331 ", LD( "P331" ) );
    Unicus::console( "6 | P341 ", LD( "P341" ) );
    Unicus::console( "7 | P332 ", LD( "P332" ) );
    Unicus::console( "8 | P346 ", LD( "P346" ) );
    Unicus::console( "9 | P352 ", LD( "P352" ) );
    Unicus::console( "10| P411 ", LD( "P411" ) );
    Unicus::console( "11| P511 ", LD( "P511" ) );
    Unicus::console( "12| P911 ", LD( "P911" ) );
    Unicus::console( "13| P122-1 ", LD( "P122-1" ) );
}

void C2DJacket::UpdatePoints()
{
    QLineF line1,line2;
    QPointF p;

    P["P0"] = QPointF( 0.0f, 0.0f );
//ПЕРВАЯ СТРАНИЦА-№79 *******************************************
    P["11"] = P["P0"];
    P["91"] = P["11"] - QPointF( 0.0f, LD("LT40") + ( LD("LT7") - LD("LT12") ) );
    P["21"] = P["11"] - QPointF( 0.0f, 0.3f * LD("LT40"));
    P["31"] = P["11"] - QPointF( 0.0f, LD("LT39") );
    P["41"] = P["11"] - QPointF( 0.0f, LD("LT40") );
    P["51"] = P["41"] - QPointF( 0.0f, 0.65f * ( LD("LT7") - LD("LT12") ) );
    P["33"] = P["31"] + QPointF( LD("LT47"), 0.0f );
    P["35"] = P["33"] + QPointF( LD("LT57"), 0.0f );
    P["37"] = P["35"] + QPointF( ( LD("LT45")+LD("LT15")-12.0f-LD("LT14") ), 0.0f );
    P["47"] = P["37"] - QPointF( 0.0f, LD("LT40") - LD("LT39") );
    P["57"] = P["47"] - QPointF( 0.0f, 0.65f * ( LD("LT7") - LD("LT12") ) );
    P["97"] = P["47"] - QPointF( 0.0f, LD("LT7") - LD("LT12") + LD("P97") );
    P["13"] = P["33"] + QPointF( 0.0f, 0.49f * LD("LT38") );
    P["15"] = P["35"] + QPointF( 0.0f, 0.43f * LD("LT38") );
    P["331"] = P["33"] - QPointF( 0.0f, LD("P331") );
    P["351"] = P["35"] - QPointF( 0.0f, LD("P331") );
    line1.setPoints(P["33"],P["35"]);
    P["341"] = P["331"] + QPointF( 0.62f * line1.length() + LD("P341"), 0.0f );
    P["341-1"] = P["351"] - QPointF( 0.38f * line1.length() + LD("P341"), 0.0f );
    P["332"] = P["331"] + QPointF( 0.0f, 0.62f * line1.length() + LD("P332") );
    P["342"] = Unicus::CircCirc(P["332"], 0.62f * line1.length() + LD("P332"),
                                P["341"],  0.62f * line1.length() + LD("P332"), true);
    P["342m"] = Unicus::CircCirc(P["332"], 0.62f * line1.length() + LD("P332"),
                                P["341"],  0.62f * line1.length() + LD("P332"), false);
    if( P["342"].x()<P["342m"].x() )
        P["342"] = P["342m"];

//ВТОРАЯ СТРАНИЦА-№81 *******************************************
    P["352"] = P["351"] + QPointF( 0.0f, 0.38f * line1.length() + LD("P352") );
    P["343"] = Unicus::CircCirc(P["352"], 0.38f * line1.length(),
                                P["341-1"], 0.38f * line1.length(), true);
    P["343m"] = Unicus::CircCirc(P["352"], 0.38f * line1.length(),
                                P["341-1"], 0.38f * line1.length(), false);
    if( P["343"].x()>P["343m"].x() )
        P["343"] = P["343m"];
    P["411"] = P["41"] + QPointF( LD("P411"), 0.0f );
    P["511"] = P["51"] + QPointF( LD("P511"), 0.0f );
    P["911"] = P["91"] + QPointF( LD("P911"), 0.0f );
    P["12"] = P["11"] + QPointF( 0.36f * LD("LT13"), 0.0f );
    P["112"] = P["11"] + QPointF( 0.25f * QLineF(P["11"],P["12"]).length(), 0.0f );
    P["121"] = P["12"] + QPointF( 0.0f, 0.07f * LD("LT13") );
    P["14"] = P["13"] + QPointF( LD("P14"), 0.0f );
    P["122"] = QLineF(P["121"],P["14"]).pointAt(0.5f);
    P["32"] = P["31"] + QPointF( 0.34f * LD("LT47"), 0.0f );
    P["22"] = QLineF(P["122"],P["32"]).pointAt(0.5f);
    P["122-2"] = Unicus::rPoint( P["122"], P["22"], LD("P122-1") );
    QLineF(P["121"],P["14"]).intersect(QLineF(P["22"],P["122-2"]),&p);
    P["122-1"] = p;

    P["14-1"]= Unicus::CircCirc(P["122"], QLineF(P["122-1"],P["14"]).length(),
                                P["33"], QLineF(P["33"],P["13"]).length(), true);
    P["14-1m"]= Unicus::CircCirc(P["122"], QLineF(P["122-1"],P["14"]).length(),
                                P["33"], QLineF(P["33"],P["13"]).length(), false);
    if( P["14-1"].x()<P["14-1m"].x() )
        P["14-1"] = P["14-1m"];


    P["141"] = Unicus::CircCirc(P["121"], QLineF(P["121"],P["14"]).length(),
                                P["22"], QLineF(P["22"],P["14-1"]).length(), true);
    P["141m"] = Unicus::CircCirc(P["121"], QLineF(P["121"],P["14"]).length(),
                                P["22"], QLineF(P["22"],P["14-1"]).length(), false);

    if( P["141"].x()<P["141m"].x() )
        P["141"] = P["141m"];

    line1.setPoints(P["121"],P["141"]);
    QLineF(P["22"],P["122"]).intersect(line1,&p);
    P["123"] = p;
    QLineF(P["22"],P["122-1"]).intersect(line1,&p);
    P["123-1"] = p;
//ТРЕТЬЯ СТРАНИЦА-№81 *******************************************
    P["46"] = P["47"] - QPointF( LD("LT46"), 0.0f );
    P["36"] = P["46"] + QPointF( 0.0f, LD("LT36")-LD("LT35") );
    P["371"] = QPointF( P["47"].x(), P["36"].y() );
    P["372"] = P["36"] + QPointF( LD("LT35")-LD("LT34"), 0.0f );
    double beta = 2*180/M_PI*asin( (0.5f*( LD("LT15")-12.0f-LD("LT14") ) ) /2.0f/QLineF(P["36"],P["372"]).length());///
    rotatebeta = beta;
    P["372-1"] = Unicus::rPoint(P["372"],P["36"],beta);
    P["371-1"] = Unicus::rPoint(P["371"],P["36"],beta);
    line1.setPoints(P["371-1"],P["36"]);
    P["361"] = line1.pointAt(0.36f*LD("LT13")/line1.length());

    beta = LD("LT44") - ( LD("LT40") + 0.07f * LD("LT13") ) - ( LD("LT36") - LD("LT35") ) + LD("P16");
    line1.setPoints( P["361"], P["36"] );
    line2.setPoints( P["361"], P["36"] );
    line2.setAngle( line2.angle() + 90.0f );
    line2.setLength( sqrt( pow( beta,2 ) - pow( line1.length(),2 ) ) );
    P["16"] = line2.p2();

    P["14-2"] = Unicus::CircCirc(P["16"], QLineF(P["121"],P["14"]).length(),
                                P["35"], QLineF(P["35"],P["15"]).length(), false);
    P["14-2m"] = Unicus::CircCirc(P["16"], QLineF(P["121"],P["14"]).length(),
                                  P["35"], QLineF(P["35"],P["15"]).length(), true);

    if( P["14-2"].x()>P["14-2m"].x() )
        P["14-2"] = P["14-2m"];

    line1.setPoints( P["16"], P["361"] );
    line1.setLength( 0.41f * LD("LT13") + LD("P161") );
    P["161"] = line1.p2();

    line1.setPoints( P["161"], P["16"] );
    line1.setAngle( line1.angle() + 90.0f );
    line2.setPoints( P["371-1"], P["361"] );
    line2.setAngle( line2.angle() + 90.0f );
    line1.intersect( line2, &p );
    P["17"] = p;

/////////Чертвертая страница №83

    P["470"] = P["411"] + QPointF( 0.5f * LD("LT18"), 0.0f );
    P["570"] = P["511"] + QPointF( 0.5f * LD("LT19"), 0.0f );
    line1.setPoints(P["331"],P["351"]);
    P["346"] = line1.pointAt( LD("P346") );
    P["441"] = QPointF( P["346"].x(), P["41"].y() );
    P["541"] = QPointF( P["346"].x(), P["51"].y() );
    P["941"] = QPointF( P["346"].x(), P["91"].y() );
    P["442"] = P["441"] + QPointF( 0.0f, LD("LT25") - LD("LT26") - 0.8f );

////Рассчет точек для сплайнов
    line1.setPoints(P["97"],P["97"]-QPointF(1.0f,0.0f));
    line1.setLength( QLineF(P["97"],P["941"]).length()/2);
    P["97l"] = line1.p2();
    line1.setPoints(P["16"],P["161"]);
    line1.setLength( line1.length()/2 );
    P["16d"] = line1.p2();
    line1.setPoints(P["17"],P["161"]);
    line1.setLength( line1.length()/2 );
    P["17l"] = line1.p2();
    ////proima
    line1.setPoints(P["352"],P["351"]);
    line1.setLength( line1.length()/2 );
    P["352d"] = line1.p2();
    line1.setPoints(P["341"],P["351"]);
    line1.setLength( line1.length()/2 );
    P["341r"] = line1.p2();
    line1.setPoints(P["332"],P["331"]);
    line1.setLength( line1.length()/2 );
    P["332d"] = line1.p2();
    line1.setPoints(P["331"],P["341"]);
    line1.setLength( line1.length()/2 );
    P["341l"] = line1.p2();

    line2.setPoints( P["14-1"], P["332"] );
    line1.setPoints( P["14-1"], P["123"] );
    line1.setAngle( line1.angle() - 90.0f );
    line1.setLength( line2.length()/3 );
    P["14-1d"] = line1.p2();
    line1.setPoints(P["332"],P["332"]+QPointF(0,1));
    line1.setLength( line2.length()/4 );
    P["332u"] = line1.p2();

    line2.setPoints( P["14-2"], P["352"] );
    line1.setPoints( P["14-2"], P["16"] );
    line1.setAngle( line1.angle() + 90.0f );
    line1.setLength( line2.length()/3 );
    P["14-2d"] = line1.p2();
    line1.setPoints(P["352"],P["352"]+QPointF(0,1));
    line1.setLength( line2.length()/4 );
    P["352u"] = line1.p2();

    line2.setPoints( P["112"], P["121"] );
    line1.setPoints( P["112"], P["12"] );
    line1.setLength( line2.length() * 0.7f );
    P["112r"] = line1.p2();

//P346
    QPainterPath bottomspline;
    bottomspline.moveTo( P["341"] );
    if( P["346"].x() >= P["341"].x() )
        bottomspline.cubicTo( P["341r"],P["352d"],P["352"] );
    else
        bottomspline.cubicTo( P["341l"],P["332d"],P["332"] );

    P["346"] = Unicus::splinepointonx( bottomspline, P["346"].x(), 0.5f );
    line1.setPoints( P["22"], Unicus::rPoint( P["123"], P["22"], LD("P122-1")/2 ) );
    line1.setLength( LD("P22-1") );
    P["22-1"] = line1.p2();

    P["16K"] = QLineF(P["16"],P["14-2"]).pointAt( LD("P16K") );

    //ROTATED PART
    P["371-1rotated"] = P["371"];
    P["17rotated"] = Unicus::rPoint( P["17"], P["36"], -rotatebeta );
    P["161rotated"] = Unicus::rPoint( P["161"], P["36"], -rotatebeta );
    P["361rotated"] = Unicus::rPoint( P["361"], P["36"], -rotatebeta );
    P["16rotated"] = Unicus::rPoint( P["16"], P["36"], -rotatebeta );
    P["16drotated"] = Unicus::rPoint( P["16d"], P["36"], -rotatebeta );
    P["17lrotated"] = Unicus::rPoint( P["17l"], P["36"], -rotatebeta );
    P["16Krotated"] = Unicus::rPoint( P["16K"], P["36"], -rotatebeta );
   //////End of rotated part
    double Dt = QLineF( P["31"],P["37"] ).length() - ( QLineF(P["41"],P["411"]).length()+QLineF(P["411"],P["470"]).length() );
    double Db = QLineF( P["31"],P["37"] ).length() - ( QLineF(P["51"],P["511"]).length()+QLineF(P["511"],P["570"]).length() );

    P["442"] = P["441"] + QPointF( 0.0f, LD("LT25")-LD("LT26")-8.0f );
    P["430"] = QPointF(P["332"].x(),P["442"].y());
    P["53"] = QPointF( P["332"].x(),P["541"].y() );
    P["412"] = P["411"] + QPointF( 0.08f*Dt, 0.0f );
    line1.setPoints(P["430"],P["412"]);
    line1.setLength( 0.25f * Dt );
    P["431"] = line1.p2();
    line2.setPoints(P["430"],P["442"]);
    line2.setLength( 0.17*Dt );
    P["431-1"] =  line2.p2();
    line1.setPoints( P["442"],P["430"] );
    line1.setLength( 0.07f * Dt );
    P["443"] = line1.p2();


    P["461"] = P["46"] - QPointF( 0.18f * Dt,0 );
    P["461-1"] = P["46"] + QPointF( 0.18f * Dt,0 );
    line1.setPoints( P["442"],P["461"] );
    line1.setLength(0.07f * Dt);
    P["443-1"] = line1.p2();

    P["531-1"] = P["53"] - QPointF( 0.25f * Db + 6, 0 );
    P["531"] = P["53"] +  QPointF( 0.25f * Db + 6, 0 );

    P["542"] = P["541"] +  QPointF( 0.125f * Db + 13, 0 );
    P["542-1"] = P["541"] -  QPointF( 0.125f * Db + 13, 0 );

    P["55"] = QPointF(P["36"].x(),P["541"].y());
    P["561"] = P["55"] -  QPointF( 0.125f * Db + 7, 0 );
    P["561-1"] = P["55"] +  QPointF( 0.125f * Db + 7, 0 );

    line2.setPoints( P["91"],P["941"] );
    line1.setPoints(P["412"],P["511"]);
    line1.intersect(line2,&p);
    P["912"] = p;
    line1.setPoints(P["431"],P["531"]);
    line1.intersect(line2,&p);
    P["931"] = p;
    line1.setPoints(P["431-1"],P["531-1"]);
    line1.intersect(line2,&p);
    P["931-1"] = p;
    line1.setPoints(P["542-1"],P["542-1"]-QPointF(0,1));
    line1.intersect(line2,&p);
    P["942-1"] = p;

    QPainterPath myspline;
    myspline.moveTo(P["97"]);
    myspline.cubicTo(P["97l"],P["97l"],P["941"]);
    P["942"] = Unicus::splinepointonx( myspline, P["542"].x(), 0.5f );
    P["961"] = Unicus::splinepointonx( myspline, P["561"].x(), 0.5f );
    P["961-1"] = Unicus::splinepointonx( myspline, P["561-1"].x(), 0.5f );

    myspline=QPainterPath();
    myspline.moveTo(P["341"]);
    if(P["431-1"].x()>=P["430"].x())
        P["431d"] = P["431-1"];
    else
        P["431d"] = P["341"];

    if( P["431d"].x() > P["341"].x() )
        myspline.cubicTo( P["341r"],P["352d"],P["352"] );
    else
        myspline.cubicTo( P["341l"],P["332d"],P["332"] );

    P["330"] = Unicus::splinepointonx( myspline, P["431d"].x(), 0.5f );

    P["000"] = QPointF(0,0.1f);
    P["001"] = QPointF(10,1);
    P["002"] = QPointF(20,2);
    QStringList splinename;
    splinename << "s21" << "s412" << "s911";
    QVariant list[] = { true, P["21"],P["412"],0.3f,0.2f,P["412"],0.2f,
                        P["912"],P["512"],0.5f,NULL };
    DrawSpline( splinename, list );
    /////////////////****************************
    splinename.clear();
    splinename << "s330" << "s431" << "s531";
    QVariant list1[] = { true, P["330"],P["431"],0.3f,0.2f,P["431"],0.2f,
                        P["531"],P["431"],0.3f,NULL };
    DrawSpline( splinename, list1 );
    /////////////////****************************
    splinename.clear();
    splinename << "s330-1" << "s431-1" << "s531-1";
    QVariant list2[] = { true, P["330"],P["431-1"],0.3f,0.2f,P["431-1"],0.2f,
                        P["531-1"],P["431-1"],0.3f,NULL };
    DrawSpline( splinename, list2 );
    /////////////////****************************
    splinename.clear();
    splinename << "s346" << "s443" << "s542";
    QVariant list3[] = { true, P["346"],P["443"],0.3f,0.2f,P["443"],0.2f,
                        P["542"],P["443"],0.3f,NULL };
    DrawSpline( splinename, list3 );
    /////////////////****************************
    splinename.clear();
    splinename << "s346-1" << "s443-1" << "s542-1";
    QVariant list4[] = { true, P["346"],P["443-1"],0.3f,0.2f,P["443-1"],0.2f,
                        P["542-1"],P["443-1"],0.3f,NULL };
    DrawSpline( splinename, list4 );
    /////////////////****************************
    line1.setPoints(P["36"],P["16Krotated"]);
    line1.setAngle(line1.angle()+180);
    splinename.clear();
    splinename << "s36-1" << "s461-1" << "s561-1";
    QVariant list5[] = { true, P["36"],line1.p2(),0.3f,0.2f,P["461-1"],0.2f,
                        P["561-1"],P["461-1"],0.3f,NULL };
    DrawSpline( splinename, list5 );
    /////////////////****************************
    line1.setPoints(P["36"],P["461"]);
    line1.setLength(line1.length()*0.25f);
    splinename.clear();
    splinename << "s36" << "s461" << "s561";
    QVariant list6[] = { true, line1.p2(),P["461"],0.3f,0.2f,P["461"],0.2f,
                        P["561"],P["461"],0.3f,NULL };
    DrawSpline( splinename, list6 );
    /////////////////****************************
    P["461u"]= line1.p2();
    line2.setPoints(P["36"],P["16K"]);
    line2.setLength( line2.length()*0.25f );
    P["16Kd"]= line2.p2();
}

void C2DJacket::DrawOnWidget()
{
    this->line( Sync( attr( SYNC_NAME, QString( "11-31" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "11","31" ) ),
                      LM->thick_solid() ), true );
    this->line( Sync( attr( SYNC_NAME, QString( "11-21" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "11","21" ) ),
                      LM->bold_solid() ), true );
    this->line( Sync( attr( SYNC_NAME, QString( "31-41" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "31","41" ) ),
                      LM->thick_solid() ), true );
    this->line( Sync( attr( SYNC_NAME, QString( "41-51" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "41","51" ) ),
                      LM->thick_solid() ), true );
    this->line( Sync( attr( SYNC_NAME, QString( "51-91" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "51","91" ) ),
                      LM->thick_solid() ), true );
    this->line( Sync( attr( SYNC_NAME, QString( "31-37" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "31","37" ) ),
                      LM->thick_solid() ), true );
    this->line( Sync( attr( SYNC_NAME, QString( "37-47" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "37","47" ) ),
                      LM->thick_solid() ), true );
    this->line( Sync( attr( SYNC_NAME, QString( "47-57" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "47","57" ) ),
                      LM->thick_solid() ), true );
    this->line( Sync( attr( SYNC_NAME, QString( "57-97" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "57","97" ) ),
                      LM->thick_solid() ), true );
    this->line( Sync( attr( SYNC_NAME, QString( "41-411" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "41","411" ) ),
                      LM->thick_solid() ), true );
    this->line( Sync( attr( SYNC_NAME, QString( "51-511" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "51","511" ) ),
                      LM->thick_solid() ), true );
    this->line( Sync( attr( SYNC_NAME, QString( "91-911" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "91","911" ) ),
                      LM->thick_solid() ), true );
    //this->line( Sync( attr( SYNC_NAME, QString( "911-511" ) ),
    //                  attr( SYNC_TYPE, C2DSync::Line ),
    //                  attr( SYNC_LIST, MakeList( "911","511" ) ),
    //                  LM->thick_solid() ), true );
    this->line( Sync( attr( SYNC_NAME, QString( "511-411" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "511","411" ) ),
                      LM->thick_solid() ), true );
    //this->line( Sync( attr( SYNC_NAME, QString( "412-21" ) ),
    //                  attr( SYNC_TYPE, C2DSync::Line ),
    //                  attr( SYNC_LIST, MakeList( "412","21" ) ),
    //                  LM->bold_solid() ), true );
    //this->line( Sync( attr( SYNC_NAME, QString( "412-912" ) ),
    //                  attr( SYNC_TYPE, C2DSync::Line ),
    //                  attr( SYNC_LIST, MakeList( "412","912" ) ),
    //                  LM->bold_solid() ), true );
    this->line( Sync( attr( SYNC_NAME, QString( "912-941" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "912","941" ) ),
                      LM->bold_solid() ), true );
    //
    this->line( Sync( attr( SYNC_NAME, QString( "411-47" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "411","47" ) ),
                      LM->thick_solid() ), true );
    this->line( Sync( attr( SYNC_NAME, QString( "511-57" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "511","57" ) ),
                      LM->thick_solid() ), true );
    this->line( Sync( attr( SYNC_NAME, QString( "31-33" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "31","33" ) ),
                      LM->thick_solid() ), true );
    this->line( Sync( attr( SYNC_NAME, QString( "33-35" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "33","35" ) ),
                      LM->thick_solid() ), true );
    //
    this->line( Sync( attr( SYNC_NAME, QString( "35-351" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "35","351" ) ),
                      LM->thick_solid() ), true );
    this->line( Sync( attr( SYNC_NAME, QString( "33-331" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "33","331" ) ),
                      LM->thick_solid() ), true );
    this->line( Sync( attr( SYNC_NAME, QString( "331-341" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "331","341" ) ),
                      LM->thick_solid() ), true );
    this->line( Sync( attr( SYNC_NAME, QString( "341-1-351" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "341-1","351" ) ),
                      LM->thick_solid() ), true );
    //
    this->line( Sync( attr( SYNC_NAME, QString( "11-112" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "11","112" ) ),
                      LM->bold_solid() ), true );
    this->line( Sync( attr( SYNC_NAME, QString( "112-12" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "112","12" ) ),
                      LM->thick_solid() ), true );
    this->line( Sync( attr( SYNC_NAME, QString( "12-121" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "12","121" ) ),
                      LM->thick_solid() ), true );
    this->line( Sync( attr( SYNC_NAME, QString( "121-122-1" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "121","122-1" ) ),
                      LM->thick_solid() ), true );
    //
    this->line( Sync( attr( SYNC_NAME, QString( "122-1-22" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "122-1","22" ) ),
                      LM->thick_solid() ), true );
    this->line( Sync( attr( SYNC_NAME, QString( "22-122" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "22","122" ) ),
                      LM->thick_solid() ), true );
    this->line( Sync( attr( SYNC_NAME, QString( "122-123" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "122","123" ) ),
                      LM->thick_solid() ), true );
    this->line( Sync( attr( SYNC_NAME, QString( "122-1-123-1" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "122-1","123-1" ) ),
                      LM->thick_solid() ), true );
    this->line( Sync( attr( SYNC_NAME, QString( "123-1-121" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "123-1","121" ) ),
                      LM->bold_solid() ), true );

    this->line( Sync( attr( SYNC_NAME, QString( "123-1-22-1" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "123-1","22-1" ) ),
                      LM->bold_solid() ), true );
    this->line( Sync( attr( SYNC_NAME, QString( "123-22-1" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "123","22-1" ) ),
                      LM->bold_solid() ), true );
    //
    this->line( Sync( attr( SYNC_NAME, QString( "121-141" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "121","141" ) ),
                      LM->thick_solid() ), true );
    this->line( Sync( attr( SYNC_NAME, QString( "123-14-1" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "123","14-1" ) ),
                      LM->bold_solid() ), true );
    this->line( Sync( attr( SYNC_NAME, QString( "121-14" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "121","14" ) ),
                      LM->thick_solid() ), true );
    this->line( Sync( attr( SYNC_NAME, QString( "22-32" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "22","32" ) ),
                      LM->thick_solid() ), true );
    //
    this->line( Sync( attr( SYNC_NAME, QString( "13-332" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "13","332" ) ),
                      LM->thick_solid() ), true );
    this->line( Sync( attr( SYNC_NAME, QString( "332-342" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "332","342" ) ),
                      LM->thick_solid() ), true );
    this->line( Sync( attr( SYNC_NAME, QString( "352-15" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "352","15" ) ),
                      LM->thick_solid() ), true );
    this->line( Sync( attr( SYNC_NAME, QString( "352-343" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "352","343" ) ),
                      LM->thick_solid() ), true );
    this->line( Sync( attr( SYNC_NAME, QString( "46-35" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "46","36" ) ),
                      LM->thick_solid() ), true );
    this->line( Sync( attr( SYNC_NAME, QString( "371-47" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "371","47" ) ),
                      LM->thick_solid() ), true );
    this->line( Sync( attr( SYNC_NAME, QString( "372-36" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "372","36" ) ),
                      LM->thick_solid() ), true );
    this->line( Sync( attr( SYNC_NAME, QString( "372-1-36" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "372-1","36" ) ),
                      LM->thick_solid() ), true );
    this->line( Sync( attr( SYNC_NAME, QString( "371-1-361" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "371-1","361" ) ),
                      LM->thick_solid() ), true );
    this->line( Sync( attr( SYNC_NAME, QString( "17-371-1" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "17","371-1" ) ),
                      LM->thick_solid() ), true );

    this->line( Sync( attr( SYNC_NAME, QString( "16-361" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "16","361" ) ),
                      LM->thick_solid() ), true );
    this->line( Sync( attr( SYNC_NAME, QString( "16-14-2" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "16","14-2" ) ),
                      LM->thick_solid() ), true );
    this->line( Sync( attr( SYNC_NAME, QString( "16K-36" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "16K","36" ) ),
                      LM->bold_solid() ), true );
    this->line( Sync( attr( SYNC_NAME, QString( "161-17" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "161","17" ) ),
                      LM->thick_solid() ), true );
    this->point( Sync( attr( SYNC_NAME, QString( "470" ) ),
                      attr( SYNC_TYPE, C2DSync::Point ),
                      attr( SYNC_LIST, MakeList( "470" ) ),
                      LM->thick_solid() ), true );
    this->point( Sync( attr( SYNC_NAME, QString( "570" ) ),
                      attr( SYNC_TYPE, C2DSync::Point ),
                      attr( SYNC_LIST, MakeList( "570" ) ),
                      LM->thick_solid() ), true );
    this->line( Sync( attr( SYNC_NAME, QString( "346-441" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "346","441" ) ),
                      LM->thick_solid() ), true );
    this->line( Sync( attr( SYNC_NAME, QString( "541-441" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "541","441" ) ),
                      LM->thick_solid() ), true );
    this->line( Sync( attr( SYNC_NAME, QString( "541-941" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "541","941" ) ),
                      LM->thick_solid() ), true );
    this->line( Sync( attr( SYNC_NAME, QString( "911-941" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "911","941" ) ),
                      LM->thick_solid() ), true );
    this->line( Sync( attr( SYNC_NAME, QString( "97-372" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "97","372" ) ),
                      LM->bold_solid() ), true );
    this->line( Sync( attr( SYNC_NAME, QString( "16K-14-2" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "16K","14-2" ) ),
                      LM->bold_solid() ), true );
   \



//------ROTATEDPART
    this->spline( Sync( attr( SYNC_NAME,  QString( "s16rotated-17rotated" ) ),
                        attr( SYNC_TYPE, C2DSync::Spline ),
                        attr( SYNC_LIST, MakeList( "16rotated", "16drotated", "17lrotated", "17rotated" ) ),
                        LM->bold_solid() ), true );
    this->line( Sync( attr( SYNC_NAME, QString( "16rotated-16Krotated" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "16rotated","16Krotated" ) ),
                      LM->bold_solid() ), true );
    this->line( Sync( attr( SYNC_NAME, QString( "17rotated-371-1rotated" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "17rotated","371-1rotated" ) ),
                      LM->bold_solid() ), true );
    this->line( Sync( attr( SYNC_NAME, QString( "16rotated-161rotated" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "16rotated","161rotated" ) ),
                      LM->thick_solid() ), true );
    this->line( Sync( attr( SYNC_NAME, QString( "17rotated-161rotated" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "17rotated","161rotated" ) ),
                      LM->thick_solid() ), true );
    this->line( Sync( attr( SYNC_NAME, QString( "36-371-1rotated" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "36","371-1rotated" ) ),
                      LM->bold_solid() ), true );
    this->line( Sync( attr( SYNC_NAME, QString( "36-16Krotated" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "36","16Krotated" ) ),
                      LM->bold_solid() ), true );

//------SPLINES
    this->spline( Sync( attr( SYNC_NAME,  QString( "s97-941" ) ),
                        attr( SYNC_TYPE, C2DSync::Spline ),
                        attr( SYNC_LIST, MakeList( "97", "97l", "97l", "941" ) ),
                        LM->bold_solid() ), true );
    this->spline( Sync( attr( SYNC_NAME,  QString( "s16-17" ) ),
                        attr( SYNC_TYPE, C2DSync::Spline ),
                        attr( SYNC_LIST, MakeList( "16", "16d", "17l", "17" ) ),
                        LM->thick_solid() ), true );
    this->spline( Sync( attr( SYNC_NAME,  QString( "s332-341" ) ),
                        attr( SYNC_TYPE, C2DSync::Spline ),
                        attr( SYNC_LIST, MakeList( "332", "332d", "341l", "341" ) ),
                        LM->bold_solid() ), true );
    this->spline( Sync( attr( SYNC_NAME,  QString( "s352-341" ) ),
                        attr( SYNC_TYPE, C2DSync::Spline ),
                        attr( SYNC_LIST, MakeList( "352", "352d", "341r", "341" ) ),
                        LM->bold_solid() ), true );
    this->spline( Sync( attr( SYNC_NAME,  QString( "s14-1-332" ) ),
                        attr( SYNC_TYPE, C2DSync::Spline ),
                        attr( SYNC_LIST, MakeList( "14-1", "14-1d", "332u", "332" ) ),
                        LM->bold_solid() ), true );
    this->spline( Sync( attr( SYNC_NAME,  QString( "s14-2-352" ) ),
                        attr( SYNC_TYPE, C2DSync::Spline ),
                        attr( SYNC_LIST, MakeList( "14-2", "14-2d", "352u", "352" ) ),
                        LM->bold_solid() ), true );
    this->spline( Sync( attr( SYNC_NAME,  QString( "s112-121" ) ),
                        attr( SYNC_TYPE, C2DSync::Spline ),
                        attr( SYNC_LIST, MakeList( "112", "112r", "121", "121" ) ),
                        LM->bold_solid() ), true );
    //Inside lines
   // this->line( Sync( attr( SYNC_NAME, QString( "346-343" ) ),
   //                   attr( SYNC_TYPE, C2DSync::Line ),
   //                   attr( SYNC_LIST, MakeList( "346","443" ) ),
   //                   LM->bold_solid() ), true );
   // this->line( Sync( attr( SYNC_NAME, QString( "346-443-1" ) ),
   //                   attr( SYNC_TYPE, C2DSync::Line ),
   //                   attr( SYNC_LIST, MakeList( "346","343-1" ) ),
   //                   LM->bold_solid() ), true );
   // this->line( Sync( attr( SYNC_NAME, QString( "542-343" ) ),
   //                   attr( SYNC_TYPE, C2DSync::Line ),
   //                   attr( SYNC_LIST, MakeList( "542","443" ) ),
   //                   LM->bold_solid() ), true );
   // this->line( Sync( attr( SYNC_NAME, QString( "542-1-343-1" ) ),
   //                   attr( SYNC_TYPE, C2DSync::Line ),
   //                   attr( SYNC_LIST, MakeList( "542-1","443-1" ) ),
   //                   LM->bold_solid() ), true );
    this->line( Sync( attr( SYNC_NAME, QString( "542-942" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "542","942" ) ),
                      LM->bold_solid() ), true );
    this->line( Sync( attr( SYNC_NAME, QString( "542-1-942-1" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "542-1","942-1" ) ),
                      LM->bold_solid() ), true );
   // this->line( Sync( attr( SYNC_NAME, QString( "346-443-1" ) ),
   //                   attr( SYNC_TYPE, C2DSync::Line ),
   //                   attr( SYNC_LIST, MakeList( "346","443-1" ) ),
   //                   LM->bold_solid() ), true );
   // this->line( Sync( attr( SYNC_NAME, QString( "330-431-1" ) ),
   //                   attr( SYNC_TYPE, C2DSync::Line ),
   //                   attr( SYNC_LIST, MakeList( "330","431-1" ) ),
   //                   LM->bold_solid() ), true );
   // this->line( Sync( attr( SYNC_NAME, QString( "431-330" ) ),
   //                   attr( SYNC_TYPE, C2DSync::Line ),
   //                   attr( SYNC_LIST, MakeList( "431","330" ) ),
   //                   LM->bold_solid() ), true );
    this->line( Sync( attr( SYNC_NAME, QString( "531-931" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "531","931" ) ),
                      LM->bold_solid() ), true );
    this->line( Sync( attr( SYNC_NAME, QString( "531-1-931-1" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "531-1","931-1" ) ),
                      LM->bold_solid() ), true );
   // this->line( Sync( attr( SYNC_NAME, QString( "36-461-1" ) ),
   //                   attr( SYNC_TYPE, C2DSync::Line ),
   //                   attr( SYNC_LIST, MakeList( "36","461-1" ) ),
   //                   LM->bold_solid() ), true );
   // this->line( Sync( attr( SYNC_NAME, QString( "561-1-461-1" ) ),
   //                   attr( SYNC_TYPE, C2DSync::Line ),
   //                   attr( SYNC_LIST, MakeList( "561-1","461-1" ) ),
   //                   LM->bold_solid() ), true );
    this->line( Sync( attr( SYNC_NAME, QString( "561-1-961-1" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "561-1","961-1" ) ),
                      LM->bold_solid() ), true );
    this->line( Sync( attr( SYNC_NAME, QString( "561-961" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "561","961" ) ),
                      LM->bold_solid() ), true );
   // this->line( Sync( attr( SYNC_NAME, QString( "461-561" ) ),
   //                   attr( SYNC_TYPE, C2DSync::Line ),
   //                   attr( SYNC_LIST, MakeList( "461","561" ) ),
   //                   LM->bold_solid() ), true );
    this->spline( Sync( attr( SYNC_NAME,  QString( "s16Kd-461u" ) ),
                        attr( SYNC_TYPE, C2DSync::Spline ),
                        attr( SYNC_LIST, MakeList( "16Kd", "36", "36", "461u" ) ),
                        LM->bold_solid() ), true );

    this->point( Sync( attr( SYNC_NAME, QString( "53" ) ),
                      attr( SYNC_TYPE, C2DSync::Point ),
                      attr( SYNC_LIST, MakeList( "53" ) ),
                      LM->thick_solid() ), true );
    this->point( Sync( attr( SYNC_NAME, QString( "531" ) ),
                      attr( SYNC_TYPE, C2DSync::Point ),
                      attr( SYNC_LIST, MakeList( "531" ) ),
                      LM->thick_solid() ), true );
    this->point( Sync( attr( SYNC_NAME, QString( "531-1" ) ),
                      attr( SYNC_TYPE, C2DSync::Point ),
                      attr( SYNC_LIST, MakeList( "531-1" ) ),
                      LM->thick_solid() ), true );
}

void C2DJacket::DrawSpline( QStringList splinename, QVariant list[] )
{
//    QVariant list[] = { true,P["21"],P["412"],0.5f,0.5f,P["412"],0.5f,
//                        P["911"],P["511"],0.5f,NULL };
    QStringList splinepointsnames;
    splinepointsnames << "sd-" + splinename.at(0) + "-to-" + splinename.at(1) + "-start"
                      << "sd-" + splinename.at(0) + "-to-" + splinename.at(1) + "-end"
                      << "sd-" + splinename.at(1) + "-to-" + splinename.at(0) + "-end"
                      << "sd-" + splinename.at(1) + "-to-" + splinename.at(0) + "-start"
                      << "sd-" + splinename.at(1) + "-to-" + splinename.at(2) + "-start"
                      << "sd-" + splinename.at(1) + "-to-" + splinename.at(2) + "-end"
                      << "sd-" + splinename.at(2) + "-to-" + splinename.at(1) + "-end"
                      << "sd-" + splinename.at(2) + "-to-" + splinename.at(1) + "-start";


    QLineF line1, line2, line3;
   // QStringList name = list[0].toStringList();
    line1.setPoints( list[1].toPointF(),list[2].toPointF() );
    line1.setLength( QLineF( list[1].toPointF(), list[5].toPointF()).length() * list[3].toDouble());
    line2.setPoints( list[5].toPointF(),list[5].toPointF()+QPointF(1.0f,0.0f));
    line2.setAngle( ( QLineF(list[7].toPointF(),list[5].toPointF()).angle() +
                    QLineF(list[5].toPointF(),list[1].toPointF()).angle() ) / 2 );
    line2.setLength( QLineF( list[5].toPointF(),list[1].toPointF() ).length() * list[4].toDouble());

    P[splinepointsnames.at(0)] = line1.p1();
    P[splinepointsnames.at(1)] = line1.p2();
    P[splinepointsnames.at(2)] = line2.p2();
    P[splinepointsnames.at(3)] = line2.p1();

    this->spline( Sync( attr( SYNC_NAME, splinename.at(0)+'-'+splinename.at(1) ),
                        attr( SYNC_TYPE, C2DSync::Spline ),
                        attr( SYNC_LIST, MakeList( splinepointsnames.at(0),
                                                   splinepointsnames.at(1),
                                                   splinepointsnames.at(2),
                                                   splinepointsnames.at(3) ) ),
                        LM->bold_solid() ), list[0].toBool() );
    line2.setAngle(line2.angle()+180.0f);
    line2.setLength( QLineF( list[7].toPointF(), list[5].toPointF()).length() * list[6].toDouble());
    line3.setPoints( list[7].toPointF(), list[8].toPointF() );
    line3.setLength( QLineF( list[7].toPointF(),list[5].toPointF() ).length() * list[9].toDouble());
    P[splinepointsnames.at(4)] = line2.p1();
    P[splinepointsnames.at(5)] = line2.p2();
    P[splinepointsnames.at(6)] = line3.p2();
    P[splinepointsnames.at(7)] = line3.p1();
    this->spline( Sync( attr( SYNC_NAME, splinename.at(1)+'-'+splinename.at(2) ),
                        attr( SYNC_TYPE, C2DSync::Spline ),
                        attr( SYNC_LIST, MakeList( splinepointsnames.at(4),
                                                   splinepointsnames.at(5),
                                                   splinepointsnames.at(6),
                                                   splinepointsnames.at(7) ) ),
                        LM->bold_solid() ), list[0].toBool() );

  //  for( int i = 1;i<8;i++ )
  //      this->point( Sync( attr( SYNC_NAME, QString( splinepointsnames.at(i) ) ),
  //                        attr( SYNC_TYPE, C2DSync::Point ),
  //                        attr( SYNC_LIST, MakeList( splinepointsnames.at(i) ) ),
  //                        LM->thick_solid() ), true );


}
