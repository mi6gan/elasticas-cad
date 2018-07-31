#include "C2DPants.h"

C2DPantsDialog * bla;
C2DPants::C2DPants() : C2DItem()
{
    this->setPrefix( QString( "Pants" ) );
    this->requiredVariables();
    //this->addDialog( new C2DPantsDialog( QObject::trUtf8( "Брюки" ), this->prefix(), QObject::trUtf8( "Параметры БК" ),
    //                 QPair< QString, double> ( QObject::trUtf8( "см" ), 10.0f ), NULL ) );
    this->addElDialog(new Elasticas::DockDialog("Button1","Pants:"),"Tab1");
   // C2DItem::plugin->AddAction(QObject::trUtf8("Параметры БК"),new QAction("Action1" ,new QWidget));
    //C2DItem::plugin->AddMenu(QObject::trUtf8("Параметры БК"),new QLabel("some"));

}

void C2DPants::Update()
{
    this->setVariables();
    this->UpdatePoints();
    this->DrawOnWidget();

}

void C2DPants::requiredVariables()
{

    this->addVariable( C2DVariable::set( "PTx", this->prefix() + "PTx",
                       "Not described", C2DVariable::Unitless, C2DVariable::General, 0.0f, 0.01f ) );
    this->addVariable( C2DVariable::set( "PTy", this->prefix() + "PTy", "Not describedd",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 0.01f  ) );
    this->addVariable( C2DVariable::set( "T7", "T7", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "T9", "T9", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "T18", "T18", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "T19", "T19", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "T26", "T26", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 10.0f ) );

    this->addVariable( C2DVariable::set( "T27", "T27", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "T46", "T46", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "T86", "T86", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 10.0f ) );
    //P18 - прибавка к полуобхвату талии
    //P19 - прибавка к полуобхвату бедер
    this->addVariable( C2DVariable::set( "P18", this->prefix() + "P18", "Not described",
                       C2DVariable::Metrics, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "P19", this->prefix() + "P19", "Not described",
                       C2DVariable::Metrics, C2DVariable::General, 0.0f, 10.0f ) );

    this->addVariable( C2DVariable::set( "K26", "K26", "Not described", C2DVariable::Metrics,
                       C2DVariable::Additional, -50.0f ) );

    /////////////////////////Диалоги
    this->addVariable( C2DVariable::set( "Length", this->prefix() + "Length", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "Clasp", this->prefix() + "Clasp",
                       "Not described", C2DVariable::Logical, C2DVariable::Optional, false ) );
    this->addVariable( C2DVariable::set( "ClaspType", this->prefix() + "ClaspType",
                       "Not described", C2DVariable::Unitless, C2DVariable::Optional, 1 ) );
    this->addVariable( C2DVariable::set( "ClaspPosition",
                       this->prefix() + "ClaspPosition", "Not described",
                       C2DVariable::Unitless, C2DVariable::Optional, 1 ) );
    this->addVariable( C2DVariable::set( "BeltZipperLength",
                       this->prefix() + "BeltZipperLength", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "Belt",
                       this->prefix() + "Belt", "Not described", C2DVariable::Unitless,
                       C2DVariable::Optional, 0.0f, 1.0f ) );
    this->addVariable( C2DVariable::set( "BeltWidth",
                       this->prefix() + "BeltWidth", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "ZipperAtBeltEnd",
                       this->prefix() + "ZipperAtBeltEnd", "Not described", C2DVariable::Logical,
                       C2DVariable::General ) );
    this->addVariable( C2DVariable::set( "BeltLedgeWidth",
                       this->prefix() + "BeltLedgeWidth", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 0.0f, 10.0f ) );

    /*
    H( "T7" ) = 984.0f );
    H( "T9" ) = 435.0f );
    H( "T18" ) = 323.0f );
    H( "T19" ) = 460.0f );
    H( "T26" ) = 992.0f );
    H( "T27" ) = 735.0f );//735
    H( "T46" ) = 93.0f );
    H( "T86" ) = 800.0f );
    */
//    H( "P18" ) = 1.0f );
//    H( "P19" ) = 1.0f );
    /*
    H( "K26" ) = 1.0f );
    */

    this->addVariable( C2DVariable::set( "combo", "Pants:combo", "Not described",
                       C2DVariable::Metrics, C2DVariable::General, 0.0f, 1.0f ) ) ;
    this->addVariable( C2DVariable::set( "K1", "Pants:L1", "Not described",
                       C2DVariable::Metrics, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "Len1", "Pants:L2", "Not described",
                       C2DVariable::Metrics, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "SHk", "Pants:SHk", "Not described",
                       C2DVariable::Metrics, C2DVariable::General, 0.0f, 10.0f ) ) ;
    this->addVariable( C2DVariable::set( "SHn", "Pants:SHn", "Not described",
                       C2DVariable::Metrics, C2DVariable::General, 0.0f, 10.0f ) ) ;
    this->addVariable( C2DVariable::set( "Sk", "Pants:K1", "Not described",
                       C2DVariable::Metrics, C2DVariable::General, 0.0f, 10.0f ) );


}

void C2DPants::setVariables()
{
    // Диалоги
    H( "First" ) = QVariant( true );
    H( "Second" ) = QVariant( true );

    H( "Tx" ) = 1.0f + D( "PTx" );
    H( "Ty" ) = 1.0f + D( "PTy" );
    H( "Sk" ) = D("Sk") * LD( "Ty" );
    H( "SHn" ) = D("SHn") * LD( "Tx" );
    H( "SHk" ) = D("SHk") * LD( "Tx" );
   // H( "Len1" ) = D("Len1") * LD( "Tx" ) );
    H( "K1" ) = D("K1") * LD( "Tx" );

    //this->H( "SHn" ) = 150.0f );
    //this->H( "SHk" ) = 200.0f );

    //this->H( "K1" ) = 10.0f );

    //this->H( "Len1" ) = 10.0f );

    //this->H( "Sk" ) = 10.0f );

    //////////////////////////////////////////////////////////////////////////////////

    H( "Height" ) = D("Length") * LD("Ty");
    H( "Width" ) = D("T19") / 2.0f + D("P19");
    H( "Width" ) = LD("Width") + LD("Width")*D("PTx");
    H( "SideSeamShift" ) = LD("Width") * 0.03f;

    H( "WidthAtHipline" ) =
               ( 0.5f * ( D("T19") - D("T18") ) + ( D("P19") - D("P18") ) ) * LD("Tx");

    H( "AB_f" ) = (D("T46") / 2.0f) + 3.0f;
    H( "AB_f" ) = LD("AB_f")* LD("Tx");

    H( "AB_b" ) = 0.4f * LD("Width") / 2.0f;
    /* Temp */

    H( "H1" ) = D("T7") - D("T86");
    H( "H2" ) = D("T26") - D("T7") - D("K26") + LD("H1");
    H( "H1" ) = LD("H1") * LD("Ty");
    H( "H2" ) = LD("H2") * LD("Ty");

    H( "L1" ) = ( LD("Width") / 2.0f ) + LD("SideSeamShift");
    H( "L2" ) = ( LD("Width") / 2.0f ) - LD("SideSeamShift");

    //Back darts
    H( "BD:S1" ) = 0.21f * LD("WidthAtHipline");
    H( "BD:H1" ) = LD("H1") * 0.8f - 10.0f;
    H( "BD:W1" ) = LD("AB_b");

    H( "BD:S2" ) = 0.21f * LD("WidthAtHipline");
    H( "BD:H2" ) = LD("H1") * 0.8f - 20.0f;
    H( "BD:W2" ) =
        LD("AB_b") + ( LD("Width") / 2.0f - 0.4f * LD("WidthAtHipline") / 2.0f - LD("AB_b") ) * 0.5f;

    //Side dart
    H( "SD:S" ) = 0.4f * LD("WidthAtHipline");
    H( "SD:H" ) = LD("H1");
    H( "SD:W" ) = LD("L1");

    //Front dart
    H( "FD:S" ) = 0.18f * LD("WidthAtHipline");
    H( "FD:H" ) = LD("H1") * 0.5f - 10.0f;
    H( "FD:W" ) = LD("Width") - LD("AB_f");

    H( "BottomPart" ) = true;


}


void C2DPants::UpdatePoints()
{
    double delta = (D("T26")*LD("Ty"))-LD("Height");
    P["P0"] = QPointF( -200.0f, 900.0f );

    P["Template1:P0"] = P["P0"] + QPointF( 400.0f , 0.0f );

    /************************************************************
    ****** Рассчет точек шаблона номер 1 ************************
    ************************************************************/
    P["54"] = P["Template1:P0"];
    P["57"] = P["54"] + QPointF( LD("L2") , 0.0f ) ;
    P["47"] = P["57"] + QPointF( 0.0f , LD("H2") ) ;

    P["D3ur"] = P["54"] + QPointF( LD("SD:S")/2 , LD("SD:H") ) ;
    P["44"] = P["D3ur"];
    P["44ls"] = QPointF( P["54"].x()+(P["54"].x()-P["44"].x()) ,P["44"].y() );

  /*  P["D4b"] = P["54"] + QPointF( LD("FD:W")-LD("L1") , LD("H1") -LD("FD:H") ) ;
    P["D4ul"] = P["D4b"] + QPointF( -(LD("FD:S")/2) , LD("FD:H") ) ;
    P["D4ur"] = P["D4b"] + QPointF( LD("FD:S")/2 , LD("FD:H") ) ;
*/

    double templength = (0.35f * ( 0.2f * (D("T19")*LD("Tx")) - 20.0f )) ;
    P["58"] = P["57"] + QPointF( templength , 0.0f );
    P["56"] = P["54"] + QPointF( ( LD("L2") + templength ) / 2  , 0.0f );

    P["66"] = P["56"] - QPointF( 0.0f , (D("T26") - D("T27"))*LD("Ty")-(P["47"].y()-P["56"].y()) );
    P["96"] = P["56"] - QPointF( 0.0f , LD("Height")-(P["47"].y()-P["56"].y()) );

    if( delta < D("T9")*LD("Ty") )
    {
        P["76"] = P["96"] - QPointF( 0.0f , delta - D("T9")*LD("Ty"));
        H( "BottomPart" ) = true;
        P["94"] = P["96"] - QPointF( ( LD("SHn") - 20.0f ) * 0.5f , 0.0f );
        P["98"] = P["94"] + QPointF( ( LD("SHn") - 20.0f ) , 0.0f );
    }else
    {
        P["76"] = P["96"];
        H("BottomPart") = false;

    }

    P["74"] = P["76"] - QPointF( ( LD("SHk") - 25.0f ) * 0.5f , 0.0f );
    P["78"] = P["74"] + QPointF( ( LD("SHk") - 25.0f ) , 0.0f );

    QLineF line1( P["66"], QPointF( P["66"].x() + 1.0f, P["66"].y() ) ), line2(P["58"],P["78"]);
    QPointF intersectionPoint;
    QPointF* p;
    p=&intersectionPoint;
    line1.intersect(line2, p);
    P["68"] = intersectionPoint;

    P["471"] = P["47"] - QPointF( LD("K1") , 0.0f );

    line1.setPoints(P["471"],P["57"]);
    line2.setPoints(P["66"],P["68"]);
    line1.intersect(line2, p);
    P["P12"] = intersectionPoint;
    QLineF line3(P["66"],P["56"]);
    if( line3.length() >= 60.0f )
    {
        line1.setPoints(P["57"],P["68"]);
        line1.setLength(line1.length()/2);
        line2.setPoints(P["P12"] ,line1.p2());
        line2.setLength(line2.length()/2);
        P["P13"] = line2.p2();
        P["571"] = P["57"];
    }else
    {
        line3.setLength(70.0f);
        line2.setPoints(line3.p2(),QPointF( line3.p2().x()+1,line3.p2().y() ));
        line1.intersect(line2,p);
        P["571"] = intersectionPoint;
        line1.setPoints(P["571"],P["68"]);
        line1.setLength(line1.length()/2);
        line2.setPoints(P["P12"] ,line1.p2());
        line2.setLength(line2.length()/2);
        P["P13"] = line2.p2();
    }

    line1.setPoints( P["56"], P["56"] + QPointF( 0.0f , 1.0f) );
    line2.setPoints( P["47"], P["44"] );
    line1.intersect( line2 , p );
    P["46"] = intersectionPoint;
    P["D4b"] = QPointF( P["46"].x() , P["46"].y() - LD("FD:H") );
    P["D4ul"] = P["D4b"] + QPointF( -(LD("FD:S")/2) , LD("FD:H") ) ;
    P["D4ur"] = P["D4b"] + QPointF( LD("FD:S")/2 , LD("FD:H") ) ;

    ///74-54
    line1.setPoints( P["54"], P["57"] );
    line1.setAngle( line1.angle() + 90.0f );
    if( P["94"]==P["74"] )
        line2.setPoints( P["74"], P["74"] + QPointF( 0.0f, 1.0f ) );
    else
        line2.setPoints( P["94"], P["74"] );
    //line2.setAngle( line2.angle() + 180.0f );
    templength = QLineF( P["54"], P["74"] ).length();
    line1.setLength( templength / 4 );
    line2.setLength( line2.length() + templength / 6 );
    P["54b"] = line1.p2();
    P["74u"] = line2.p2();

    if( P["98"]==P["78"] )
        line1.setPoints( P["78"], P["78"] + QPointF( 0.0f, 1.0f ) );
    else
        line1.setPoints( P["98"], P["78"]);
    //line1.setAngle( line1.angle() + 180.0f );
    templength = QLineF( P["78"], P["68"] ).length();
    line1.setLength( line1.length() + templength / 2 );
    P["78u"] = line1.p2();

    ///////////////P13
    line1.setPoints( P["P13"], P["571"] );
    line2.setPoints( P["68"], P["P13"] );
    line1.setAngle( (line1.angle()+line2.angle())/2 );

    line2.setPoints( P["571"], P["471"] );
    line2.setAngle( line2.angle() + 180.0f );
    templength = QLineF( P["P13"], P["571"] ).length();
    line1.setLength( templength / 4 );
    line2.setLength( templength / 4 );
    P["P13u"] = line1.p2();
    P["571b"] = line2.p2();

    line1.setAngle( line1.angle() + 180.0f );
    templength = QLineF( P["P13"], P["68"] ).length();
    line1.setLength( templength / 2 );
    P["P13b"] = line1.p2();
    P["68u"] = P["68"] + QPointF( -templength / 4, 0.0f );

    /***********************************************************/
    templength = (0.65f * ( 0.2f * (D("T19")*LD("Tx")) - 20.0f ) ) ;
    P["Template2:P0"] = P["56"] - QPointF( ( LD("L1") + templength ) / 2  , 0.0f );
    /************************************************************
    ****** Рассчет точек шаблона номер 2 перевернутого***********
    ************************************************************/
    P["54'"] = P["Template2:P0"] - QPointF( D("combo")* -400.0f , 0.0f );
    P["51"] = P["54'"] + QPointF( LD("L1") , 0.0f ) ;
    P["41"] = P["51"] + QPointF( 0.0f , LD("H1") ) ;

    P["D1b"] = P["41"] + QPointF( -LD("BD:W1") , -LD("BD:H1") ) ;
    P["D1ul"] = P["D1b"] + QPointF( -(LD("BD:S1")/2) , LD("BD:H1") ) ;
    P["D1ur"] = P["D1b"] + QPointF( LD("BD:S1")/2 , LD("BD:H1") ) ;

    P["D2b"] = P["41"] + QPointF( -LD("BD:W2") , -LD("BD:H2") ) ;
    P["D2ul"] = P["D2b"] + QPointF( -(LD("BD:S2")/2) , LD("BD:H2") ) ;
    P["D2ur"] = P["D2b"] + QPointF( LD("BD:S2")/2 , LD("BD:H2") ) ;

    P["D3b"] = P["54'"]; // P["41"] + QPointF( -LD("SD:W") , -LD("SD:H") ) ;
    P["44'"] = P["D3b"] + QPointF( +(LD("SD:S")/2) , LD("SD:H") ) ;
    P["44'ls"] = QPointF( P["54'"].x()+(P["54'"].x()-P["44'"].x()) ,P["44'"].y() );

    P["58'"] = P["51"] + QPointF( templength , 0.0f );
    P["52"] = P["54'"] + QPointF( ( LD("L1") + templength ) / 2  , 0.0f );

    //line1.setPoints();
    double beta;
    beta = 2*180/M_PI*asin(D("Len1")/2.0f/LD("L1"));
    Unicus::console("BETA", beta);
    qDebug() << "beta: " << beta;
    P["51old"] = P["51"];
    P["51"] = Unicus::rPoint(P["51"],P["54'"],beta);
    P["41"] = Unicus::rPoint(P["41"],P["54'"],beta);
    P["44'"] = Unicus::rPoint(P["44'"],P["54'"],beta);

    P["D1b"] = Unicus::rPoint(P["D1b"],P["54'"],beta);
    P["D1ul"] = Unicus::rPoint(P["D1ul"],P["54'"],beta);
    Unicus::console("D1ur", QString("%1 | %2").arg( P["D1ur"].x() ).arg( P["D1ur"].y() ).toStdString().c_str() );
    P["D1ur"] = Unicus::rPoint(P["D1ur"],P["54'"],beta);
    Unicus::console("D1ur", QString("%1 | %2").arg( P["D1ur"].x() ).arg( P["D1ur"].y() ).toStdString().c_str() );

    P["D2b"] = Unicus::rPoint(P["D2b"],P["54'"],beta);
    P["D2ul"] = Unicus::rPoint(P["D2ul"],P["54'"],beta);
    P["D2ur"] = Unicus::rPoint(P["D2ur"],P["54'"],beta);

    if ( LB("BottomPart")== true )
    {
        P["92"] = P["52"] + ( P["96"] - P["56"] );
        P["98'"] = P["52"] + ( P["98"] - P["56"] ) + QPointF( 20.f , 0.0f );
        P["94'"] = P["52"] + ( P["94"] - P["56"] ) - QPointF( 20.f , 0.0f );

    }
    P["72"] = P["52"] + ( P["76"] - P["56"] );

    P["78'"] = P["52"] + ( P["78"] - P["56"] ) + QPointF( 25.f , 0.0f );
    P["74'"] = P["52"] + ( P["74"] - P["56"] ) - QPointF( 25.f , 0.0f );

    P["P68"]= QPointF( P["68"].x() , P["68"].y()-LD("Sk"));
    line1.setPoints( P["P68"] , P["P68"] - QPointF( 1, 0 ));
    line2.setPoints( P["78'"], P["58'"] );
    line2.intersect( line1, p );
    P["68'"] = intersectionPoint;

    ////Нижние сплайны
    line1.setPoints( P["54'"], P["51"] );
    line1.setAngle( line1.angle() + 90.0f );

    if( P["94'"]==P["74'"] )
        line2.setPoints( P["74'"], P["74'"] + QPointF( 0.0f, 1.0f ) );
    else
        line2.setPoints( P["94'"], P["74'"]);
    //line2.setAngle( line2.angle() + 180.0f );
    templength = QLineF( P["54'"], P["74'"] ).length();
    line1.setLength( templength / 4 );

    line2.setLength( line2.length() + templength / 6 );
    P["54'b"] = line1.p2();
    P["74'u"] = line2.p2();

    ////нижние
    ////    правые
    if( P["98'"]==P["78'"] )
        line1.setPoints( P["78'"], P["78'"] + QPointF( 0.0f, 1.0f ) );
    else
        line1.setPoints( P["98'"],P["78'"] );
    //line1.setAngle( line1.angle() + 180.0f );
    templength = QLineF( P["78'"], P["68'"] ).length();
    line1.setLength( line1.length() + templength / 2 );
    P["78'u"] = line1.p2();

    ///////////////P13'
    P["P13'"] = P["52"] + ( P["P13"] - P["56"] );
    P["P13'"] = P["P13'"] - QPointF( 7.0f, 7.0f );

    line1.setPoints( P["P13'"], P["51old"] );
    line2.setPoints( P["68'"], P["P13'"] );
    line1.setAngle( (line1.angle()+line2.angle())/2 );

    line2.setPoints( P["51old"], P["41"] );
    line2.setAngle( line2.angle() + 180.0f );
    templength = QLineF( P["P13'"], P["51old"] ).length();
    line1.setLength( templength / 4 );
    line2.setLength( templength / 4 );
    P["P13'u"] = line1.p2();
    P["51oldb"] = line2.p2();

    line1.setAngle( line1.angle() + 180.0f );
    templength = QLineF( P["P13'"], P["68'"] ).length();
    line1.setLength( templength / 2 );
    P["P13'b"] = line1.p2();
    P["68'u"] = P["68'"] + QPointF( -templength / 4, 0.0f );

    line1.setPoints( P["44'"],P["41"] );
    line2.setPoints( P["52"], P["52"] + QPointF( 0.0f, 1.0f) );
    line1.intersect(line2 , p);
    P["P1"] = intersectionPoint;


    /////////////////////////////
    P["View:Center"] = P["44"];
}

void C2DPants::DrawOnWidget()
{
    QLineF line1;
    double templength, FrontLength=0, BackLength=0;
    SplineItem * TempSpline;

    /************************************************************
    ****** Отрисовка шаблона номер 2 ****************************
    ************************************************************/
    this->line ( Sync( attr( SYNC_NAME, QString( "54'-51" ) ),
                       attr( SYNC_TYPE, C2DSync::Line ),
                       attr( SYNC_LIST, MakeList( "54'", "51" ) ),
                       LM->thick_solid() ), LB( "Second") );

    this->line ( Sync( attr( SYNC_NAME, QString( "41-51old" ) ),
                       attr( SYNC_TYPE, C2DSync::Line ),
                       attr( SYNC_LIST, MakeList( "41", "51old" ) ),
                       LM->bold_solid() ), LB( "Second") );

    if ( !LB( "BottomPart" ) )
        P["92"] = P["72"];

    this->line ( Sync( attr( SYNC_NAME, QString( "92-P1" ) ),
                       attr( SYNC_TYPE, C2DSync::Line ),
                       attr( SYNC_LIST, MakeList( "92", "P1" ) ),
                       LM->thick_solid() ), LB( "Second") );

    this->line ( Sync( attr( SYNC_NAME, QString( "98'-78'" ) ),
                       attr( SYNC_TYPE, C2DSync::Line ),
                       attr( SYNC_LIST, MakeList( "98'", "78'" ) ),
                       LM->bold_solid() ), LB( "Second") );

    this->line ( Sync( attr( SYNC_NAME, QString( "74'-78'" ) ),
                       attr( SYNC_TYPE, C2DSync::Line ),
                       attr( SYNC_LIST, MakeList( "74'", "78'" ) ),
                       LM->thick_solid() ), LB( "Second") );

    this->line ( Sync( attr( SYNC_NAME, QString( "74'-94'" ) ),
                       attr( SYNC_TYPE, C2DSync::Line ),
                       attr( SYNC_LIST, MakeList( "74'", "94'" ) ),
                       LM->bold_solid() ), LB( "Second") );



    this->spline( Sync( attr( SYNC_NAME, QString( "S-54'-74'" ) ),
                        attr( SYNC_TYPE, C2DSync::Spline ),
                        attr( SYNC_LIST, MakeList( "54'", "54'b", "74'u", "74'" ) ),
                        LM->bold_solid() ), LB( "Second") );

    this->line( Sync( attr( SYNC_NAME, QString( "94'-98'" ) ),
                       attr( SYNC_TYPE, C2DSync::Line ),
                       attr( SYNC_LIST, MakeList( "94'", "98'" ) ),
                       LM->bold_solid() ), LB( "Second") );

    this->spline( Sync( attr( SYNC_NAME, QString( "S-78'-68'" ) ),
                        attr( SYNC_TYPE, C2DSync::Spline ),
                        attr( SYNC_LIST, MakeList( "78'", "78'u", "68'", "68'" ) ),
                        LM->bold_solid() ), LB( "Second") );

    DartItem * D1 = this->dart( Sync( attr( SYNC_NAME, QString( "D1" ) ),
                                      attr( SYNC_TYPE, C2DSync::Dart ),
                                      attr( SYNC_LIST, MakeList( "D1b", "D1ul", "D1ur" ) ),
                                      LM->bold_solid() ), LB( "Second") );

    P["D1T1"] = P["D1b"] + D1->leftSplineShape().pointAtPercent(0);
    P["D1T2"] = P["D1b"] + D1->leftSplineShape().pointAtPercent(1);
    P["D1T3"] = P["D1b"] + D1->rightSplineShape().pointAtPercent(1);
    this->point( Sync( attr( SYNC_NAME, QString( "D1T1" ) ),
                       attr( SYNC_TYPE, C2DSync::Point ),
                       attr( SYNC_LIST, MakeList( "D1T1" ) ),
                       LM->bold_solid() ), LB( "Second") );
    this->point( Sync( attr( SYNC_NAME, QString( "D1T2" ) ),
                       attr( SYNC_TYPE, C2DSync::Point ),
                       attr( SYNC_LIST, MakeList( "D1T2" ) ),
                       LM->bold_solid() ), LB( "Second") );
    this->point( Sync( attr( SYNC_NAME, QString( "D1T3" ) ),
                       attr( SYNC_TYPE, C2DSync::Point ),
                       attr( SYNC_LIST, MakeList( "D1T3" ) ),
                       LM->bold_solid() ), LB( "Second") );

    DartItem * D2 = this->dart( Sync( attr( SYNC_NAME, QString( "D2" ) ),
                                      attr( SYNC_TYPE, C2DSync::Dart ),
                                      attr( SYNC_LIST, MakeList( "D2b", "D2ul", "D2ur" ) ),
                                      LM->bold_solid() ), LB( "Second") );

    if ( D1 )
        D1->setKK( 0.0f );

    if ( D2 ) D2->setKK( 0.0f );


    DartItem * D31 = this->dart( Sync( attr( SYNC_NAME, QString( "D31" ) ),
                                       attr( SYNC_TYPE, C2DSync::Dart ),
                                       attr( SYNC_LIST, MakeList( "54'", "44'ls" , "44'" ) ),
                                       LM->bold_solid() ), LB( "Second") );

    if ( D31 )
    {
        D31->setKK( 5.0f );
        D31->setLeftVisible( false );
        line1.setPoints( P["44'"], D31->connectRight() );
        line1.setLength( QLineF(P["44'"],P["D2ul"]).length()/3 );
        P["44'conr"] = line1.p2();
    }
    if ( D2 )
    {
        line1.setPoints( P["D2ul"], D2->connectLeft() );
        line1.setLength( QLineF(P["44'"],P["D2ul"]).length()/3 );
        P["D2conl"] = line1.p2();


        TempSpline = this->spline( Sync( attr( SYNC_NAME, QString( "S-44'-D2" ) ),
                                         attr( SYNC_TYPE, C2DSync::Spline ),
                                         attr( SYNC_LIST, MakeList( "44'", "44'conr", "D2conl", "D2ul" ) ),
                                         LM->bold_solid() ), LB( "Second") );

        if(TempSpline)
            BackLength = TempSpline->shape().length();

        line1.setPoints( P["D2ur"], D2->connectRight() );
        line1.setLength( QLineF(P["D2ur"],P["D1ul"]).length()/3 );
        P["D2conr"] = line1.p2();
     }
     if (D1)
     {
         line1.setPoints( P["D1ul"], D1->connectLeft() );
         line1.setLength( QLineF(P["D2ur"],P["D1ul"]).length()/3 );
         P["D1conl"] = line1.p2();

         TempSpline = this->spline( Sync( attr( SYNC_NAME, QString( "S-D2-D1" ) ),
                                          attr( SYNC_TYPE, C2DSync::Spline ),
                                          attr( SYNC_LIST, MakeList( "D2ur", "D2conr", "D1conl", "D1ul" ) ),
                                          LM->bold_solid() ), LB( "Second") );

         BackLength = BackLength + TempSpline->shape().length();

         line1.setPoints( P["D1ur"], D1->connectRight() );
         line1.setLength( QLineF(P["D1ur"],P["41"]).length()/3 );
         P["D1conr"] = line1.p2();

         line1.setPoints(P["41"],P["51"]);
         line1.setLength( QLineF(P["D1ur"],P["41"]).length()/3 );
         line1=Unicus::rLine(line1,line1.p1(),-90.0f );
         P["41conl"]=line1.p2();
         TempSpline = this->spline( Sync( attr( SYNC_NAME, QString( "S-D1-41" ) ),
                                          attr( SYNC_TYPE, C2DSync::Spline ),
                                          attr( SYNC_LIST, MakeList( "D1ur", "D1conr", "41conl", "41" ) ),
                                          LM->bold_solid() ), LB( "Second") );

         BackLength = BackLength + TempSpline->shape().length();
     }



///////////////////////// Отрисовка верхних сплайников




    this->spline( Sync( attr( SYNC_NAME, QString( "S-51old-P13'" ) ),
                        attr( SYNC_TYPE, C2DSync::Spline ),
                        attr( SYNC_LIST, MakeList( "51old", "51oldb", "P13'u", "P13'" ) ),
                        LM->bold_solid() ), LB( "Second") );


    this->spline( Sync( attr( SYNC_NAME, QString( "S-P13'-68'" ) ),
                        attr( SYNC_TYPE, C2DSync::Spline ),
                        attr( SYNC_LIST, MakeList( "P13'", "P13'b", "68'u", "68'" ) ),
                        LM->bold_solid() ), LB( "Second") );
    /************************************************************
    ****** Отрисовка шаблона номер 1 ****************************
    ************************************************************/
   // this->line ( Sync( "47-57", C2DSync::Line, MakeList( "47", "57" ), LM->thick_solid() ), LB( "First") );
    this->line ( Sync( attr( SYNC_NAME, QString( "57-54" ) ),
                       attr( SYNC_TYPE, C2DSync::Line ),
                       attr( SYNC_LIST, MakeList( "57", "54" ) ),
                       LM->thick_solid() ), LB( "First") );



    DartItem * D4 = this->dart( Sync( attr( SYNC_NAME, QString( "D4" ) ),
                                      attr( SYNC_TYPE, C2DSync::Dart ),
                                      attr( SYNC_LIST, MakeList( "D4b", "D4ul", "D4ur" ) ),
                                      LM->bold_solid() ), LB( "First") );


    DartItem * D3 = this->dart( Sync( attr( SYNC_NAME, QString( "D3" ) ),
                                      attr( SYNC_TYPE, C2DSync::Dart ),
                                      attr( SYNC_LIST, MakeList( "54", "44ls", "44" ) ),
                                      LM->bold_solid() ), LB( "First") );


    if ( D3 )
    {
        D3->setKK( 5.0f );
        D3->setLeftVisible( false );
        line1.setPoints( P["44"], D3->connectRight() );
        line1.setLength( QLineF(P["44"],P["D4ul"]).length()/3 );
        P["44conr"] = line1.p2();
    }

    if ( D4 )
    {
        D4->setKK( 0.0f );
        line1.setPoints( P["D4ul"], D4->connectLeft() );
        line1.setLength( QLineF(P["44"],P["D4ul"]).length()/3 );
        P["D4conl"] = line1.p2();


        TempSpline = this->spline( Sync( attr( SYNC_NAME, QString( "S-44-D4ul" ) ),
                                         attr( SYNC_TYPE, C2DSync::Spline ),
                                         attr( SYNC_LIST, MakeList( "44", "44conr", "D4conl", "D4ul" ) ),
                                         LM->bold_solid() ), LB( "First") );

        FrontLength = TempSpline->shape().length();

        line1.setPoints( P["D4ur"], D4->connectRight() );
        templength = QLineF(P["D4ur"],P["471"]).length();
        line1.setLength( templength /3 );
        P["D4conr"] = line1.p2();


        line1.setPoints(P["471"],P["571"]);
        line1.setLength( templength/2 );
        line1=Unicus::rLine(line1,line1.p1(),-90.0f );
        P["471conl"]=line1.p2();
        TempSpline = this->spline( Sync( attr( SYNC_NAME, QString( "S-D4ur-471" ) ),
                                         attr( SYNC_TYPE, C2DSync::Spline ),
                                         attr( SYNC_LIST, MakeList( "D4ur", "D4conr", "471conl", "471" ) ),
                                         LM->bold_solid() ), LB( "First") );

        FrontLength = FrontLength + TempSpline->shape().length();
    }
   // this->line ( Sync( "D4ur-471", C2DSync::Line, MakeList( "D4ur", "47" ), LM->thick_solid() ), LB( "First") );


  //  this->line ( Sync( "57-58", C2DSync::Line, MakeList( "57", "58" ), LM->thick_solid() ), LB( "First") );
 //   this->line ( Sync( "56-D4b", C2DSync::Line, MakeList( "56", "D4b" ), LM->thick_solid() ), LB( "First") );

    if ( !LB("BottomPart") )
        P["96"] = P["76"];
    this->line( Sync( attr( SYNC_NAME, QString( "D4b-96" ) ),
                           attr( SYNC_TYPE, C2DSync::Line ),
                           attr( SYNC_LIST, MakeList( "D4b", "96" ) ),
                           LM->thick_solid() ), LB( "First") );


    this->spline( Sync( attr( SYNC_NAME, QString( "S-54-74" ) ),
                        attr( SYNC_TYPE, C2DSync::Spline ),
                        attr( SYNC_LIST, MakeList( "54", "54b", "74u", "74" ) ),
                        LM->bold_solid() ), LB( "First") );

    this->line( Sync( attr( SYNC_NAME, QString( "74-94" ) ),
                       attr( SYNC_TYPE, C2DSync::Line ),
                       attr( SYNC_LIST, MakeList( "74", "94" ) ),
                       LM->bold_solid() ), LB( "BottomPart" ) );


    this->spline( Sync( attr( SYNC_NAME, QString( "S-78-68" ) ),
                        attr( SYNC_TYPE, C2DSync::Spline ),
                        attr( SYNC_LIST, MakeList( "78", "78u", "68", "68" ) ),
                        LM->bold_solid() ), LB( "First") );

    this->line( Sync( attr( SYNC_NAME, QString( "78-98" ) ),
                       attr( SYNC_TYPE, C2DSync::Line ),
                       attr( SYNC_LIST, MakeList( "78", "98" ) ),
                       LM->bold_solid() ), LB( "BottomPart" ) );


    this->line( Sync( attr( SYNC_NAME, QString( "74-78" ) ),
                       attr( SYNC_TYPE, C2DSync::Line ),
                       attr( SYNC_LIST, MakeList( "74", "78" ) ),
                       LM->thick_solid() ), LB( "First") );

    this->line( Sync( attr( SYNC_NAME, QString( "94-98" ) ),
                       attr( SYNC_TYPE, C2DSync::Line ),
                       attr( SYNC_LIST, MakeList( "94", "98" ) ),
                       LM->bold_solid() ), LB( "BottomPart" ) );

    this->line( Sync( attr( SYNC_NAME, QString( "471-57" ) ),
                       attr( SYNC_TYPE, C2DSync::Line ),
                       attr( SYNC_LIST, MakeList( "471", "57" ) ),
                       LM->bold_solid() ), LB( "First") );

    this->spline( Sync( attr( SYNC_NAME, QString( "S-571-P13" ) ),
                        attr( SYNC_TYPE, C2DSync::Spline ),
                        attr( SYNC_LIST, MakeList( "571", "571b", "P13u", "P13" ) ),
                        LM->bold_solid() ), LB( "First") );

    this->spline( Sync( attr( SYNC_NAME, QString( "S-P13-68" ) ),
                        attr( SYNC_TYPE, C2DSync::Spline ),
                        attr( SYNC_LIST, MakeList( "P13", "P13b", "68u", "68" ) ),
                        LM->bold_solid() ), LB( "First") );

    /***********************************************************/
    /************BELT******************************************/
    bool belt;
    if( D("Belt") == 0 )
    {
        belt = false;
    }else{
        belt = true;
        //////////////////Считаем точки
        //double templength;

        P["Belt:BL"] = QPointF( P["54"].x(),P["41"].y() ) + QPointF( 0.0f , 30.0f );
        P["Belt:TL"] = P["Belt:BL"] + QPointF( 0.0f , 0 + D("BeltWidth") );
        templength = (FrontLength+BackLength)*2;
        P["Belt:TR"] = P["Belt:TL"] + QPointF( templength, 0.0f );
        P["Belt:BR"] = P["Belt:BL"] + QPointF( templength, 0.0f );

        //P["Belt:BD1"] = P["Belt:BL"] + QPointF( 0.0f + D("BeltWidth") , 0.0f );
        //P["Belt:TD1"]
        if(!B("ZipperAtBeltEnd")){
            P["Belt:BLW"]=P["Belt:BL"] - QPoint( D("BeltLedgeWidth"), 0.0f );
            P["Belt:TLW"]=P["Belt:BLW"] + QPointF( 0.0f , 0 + D("BeltWidth") );
        }else{
            P["Belt:BLW"]=P["Belt:BL"];
            P["Belt:TLW"]=P["Belt:BLW"];
        }

    }



    /***********************************************************/
    /************CLASP******************************************/
    //Молния
    QPainterPath myspline;
    bool pos1=false,pos2=false,pos3=false;
    if ( D("Clasp") )
    {
        if( D("ClaspType") == 0 )
        {
            if( (D("ClaspPosition") == 0) || ( D("ClaspPosition") == 1 )) //если в левом или правом
            {
                pos1=true;
                pos2=false;
                pos3=false;
                if(belt){
                    P["PBelt:sign0"] = P["Belt:BR"] - QPointF( FrontLength , 0.0f );
                    P["PBelt:sign1"] = P["PBelt:sign0"] - QPointF( FrontLength , 0.0f );
                    P["PBelt:sign2"] = P["PBelt:sign1"] - QPointF( BackLength , 0.0f );
                    P["PBelt:sign3"] = P["PBelt:sign2"] - QPointF( BackLength , 0.0f );
                }

            }else if( D("ClaspPosition") == 2 ) //если в шве спереди
            {
                pos1=false;
                pos2=true;
                pos3=false;
                if(belt){
                    P["PBelt:sign0"] = P["Belt:BR"] - QPointF( FrontLength , 0.0f );
                    P["PBelt:sign1"] = P["PBelt:sign0"] - QPointF( BackLength , 0.0f );
                    P["PBelt:sign2"] = P["PBelt:sign1"] - QPointF( BackLength , 0.0f );
                    P["PBelt:sign3"] = P["PBelt:sign2"] - QPointF( FrontLength , 0.0f );
                }
            }else if( D("ClaspPosition") == 3 ) //если в шве сзади
            {
                pos1=false;
                pos2=false;
                pos3=true;
                if(belt){
                    P["PBelt:sign0"] = P["Belt:BR"] - QPointF( BackLength , 0.0f );
                    P["PBelt:sign1"] = P["PBelt:sign0"] - QPointF( FrontLength , 0.0f );
                    P["PBelt:sign2"] = P["PBelt:sign1"] - QPointF( FrontLength , 0.0f );
                    P["PBelt:sign3"] = P["PBelt:sign2"] - QPointF( BackLength , 0.0f );
                }
            }

        }

    }
    if( B("ZipperAtBeltEnd"))
        if( D("BeltZipperLength") > D("BeltWidth") )
            H("BeltZipperLength") = D("BeltZipperLength") -  D("BeltWidth");
        else
            H("BeltZipperLength" ) = 0.01f;
    myspline = D31->rightSplineShape();
    templength = 1.0f - LD("BeltZipperLength") / myspline.length();
    P["PClasp:sign1"] = P["54'"] + myspline.pointAtPercent(templength);
    this->sign(  Sync( attr( SYNC_NAME, QString("Clasp:sign1") ),
                       attr( SYNC_TYPE, C2DSync::Sign ),
                       attr( SYNC_LIST, MakeList("PClasp:sign1") ),
                       LM->thick_solid(),
                       attr( SYNC_SIGN_DUAL, false ),
                       attr( SYNC_SIGN_ANGLE, -myspline.angleAtPercent(templength)-90.0f ) ), pos1 );


    myspline = D3->rightSplineShape();
    templength = 1.0f - LD("BeltZipperLength") / myspline.length();

    P["PClasp:sign1'"] = P["54"] + myspline.pointAtPercent( templength );


    this->sign(  Sync( attr( SYNC_NAME, QString( "Clasp:sign1'" ) ),
                       attr( SYNC_TYPE, C2DSync::Sign ),
                       attr( SYNC_LIST, MakeList( "PClasp:sign1'" ) ),
                       LM->thick_solid(),
                       attr( SYNC_SIGN_DUAL, false ),
                       attr( SYNC_SIGN_ANGLE, -myspline.angleAtPercent(templength)-90.0f ) ), pos1 );

    line1 = QLineF(P["471"],P["571"]);
    line1.setLength(LD("BeltZipperLength"));
    P["PClasp:sign2"] = line1.p2();
    this->sign(  Sync( attr( SYNC_NAME, QString( "Clasp:sign2" ) ),
                       attr( SYNC_TYPE, C2DSync::Sign ),
                       attr( SYNC_LIST, MakeList( "PClasp:sign2" ) ),
                       LM->thick_solid(),
                       attr( SYNC_SIGN_DUAL, false ),
                       attr( SYNC_SIGN_ANGLE, -line1.angle()-90.0f ) ), pos2 );

    line1 = QLineF(P["41"],P["51"]);
    line1.setLength(LD("BeltZipperLength"));
    P["PClasp:sign3"] = line1.p2();
    this->sign(  Sync( attr( SYNC_NAME, QString( "Clasp:sign3" ) ),
                       attr( SYNC_TYPE, C2DSync::Sign ),
                       attr( SYNC_LIST, MakeList( "PClasp:sign3" ) ),
                       LM->thick_solid(),
                       attr( SYNC_SIGN_DUAL, false ),
                       attr( SYNC_SIGN_ANGLE, -line1.angle()-90.0f ) ), pos3 );

    //////////////////Рисуем пояс
    this->line ( Sync( attr( SYNC_NAME, QString( "Belt:BL-Belt:TL" ) ),
                       attr( SYNC_TYPE, C2DSync::Line ),
                       attr( SYNC_LIST, MakeList( "Belt:BL", "Belt:TL" ) ),
                       LM->thick_dashed() ), belt );

    this->line ( Sync( attr( SYNC_NAME, QString( "Belt:BL-Belt:BR" ) ),
                       attr( SYNC_TYPE, C2DSync::Line ),
                       attr( SYNC_LIST, MakeList( "Belt:BL", "Belt:BR" ) ),
                       LM->bold_solid() ), belt );

    this->line ( Sync( attr( SYNC_NAME, QString( "Belt:BL-Belt:BLW" ) ),
                       attr( SYNC_TYPE, C2DSync::Line ),
                       attr( SYNC_LIST, MakeList( "Belt:BL", "Belt:BLW" ) ),
                       LM->bold_solid() ), belt );


    this->line ( Sync( attr( SYNC_NAME, QString( "Belt:TLW-Belt:BLW" ) ),
                       attr( SYNC_TYPE, C2DSync::Line ),
                       attr( SYNC_LIST, MakeList( "Belt:TLW", "Belt:BLW" ) ),
                       LM->bold_solid() ), belt );


    this->line ( Sync( attr( SYNC_NAME, QString( "Belt:TL-Belt:TLW" ) ),
                       attr( SYNC_TYPE, C2DSync::Line ),
                       attr( SYNC_LIST, MakeList( "Belt:TL", "Belt:TLW" ) ),
                       LM->bold_solid() ), belt );

    this->line ( Sync( attr( SYNC_NAME, QString( "Belt:TR-Belt:BR" ) ),
                       attr( SYNC_TYPE, C2DSync::Line ),
                       attr( SYNC_LIST, MakeList( "Belt:TR", "Belt:BR" ) ),
                       LM->bold_solid() ), belt );

    this->line ( Sync( attr( SYNC_NAME, QString( "Belt:TL-Belt:TR" ) ),
                       attr( SYNC_TYPE, C2DSync::Line ),
                       attr( SYNC_LIST, MakeList( "Belt:TL", "Belt:TR" ) ),
                       LM->bold_solid() ), belt );

    ///Засечки на поясе
    this->sign(  Sync( attr( SYNC_NAME, QString( "Belt:sign0" ) ),
                       attr( SYNC_TYPE, C2DSync::Sign ),
                       attr( SYNC_LIST, MakeList( "PBelt:sign0" ) ),
                       LM->thick_solid(),
                       attr( SYNC_SIGN_DUAL, false ),
                       attr( SYNC_SIGN_ANGLE, 90.0f ) ), (belt&&D("Clasp")) );

    this->sign(  Sync( attr( SYNC_NAME, QString( "Belt:sign1" ) ),
                       attr( SYNC_TYPE, C2DSync::Sign ),
                       attr( SYNC_LIST, MakeList( "PBelt:sign1" ) ),
                       LM->thick_solid(),
                       attr( SYNC_SIGN_DUAL, false ),
                       attr( SYNC_SIGN_ANGLE, 90.0f ) ), (belt&&D("Clasp")) );


    this->sign(  Sync( attr( SYNC_NAME, QString( "Belt:sign2" ) ),
                       attr( SYNC_TYPE, C2DSync::Sign ),
                       attr( SYNC_LIST, MakeList( "PBelt:sign2" ) ),
                       LM->thick_solid(),
                       attr( SYNC_SIGN_DUAL, false ),
                       attr( SYNC_SIGN_ANGLE, 90.0f ) ), (belt&&D("Clasp")) );

    this->sign(  Sync( attr( SYNC_NAME, QString( "Belt:sign3" ) ),
                       attr( SYNC_TYPE, C2DSync::Sign ),
                       attr( SYNC_LIST, MakeList( "PBelt:sign3" ) ),
                       LM->thick_solid(),
                       attr( SYNC_SIGN_DUAL, false ),
                       attr( SYNC_SIGN_ANGLE, 90.0f ) ), (belt&&D("Clasp")) );

    //Засечки**************************************/
    /**********************************************/
    myspline = D31->rightSplineShape();
    line1.setPoints( P["54'"], P["54'b"] );
    double beta = ((line1.angle()-90) + (-myspline.angleAtPercent(1)+90.0f))/2;
    //P["54'"]= myspline.pointAtPercent(1);
    this->sign(  Sync( attr( SYNC_NAME, QString( "Back1" ) ),
                       attr( SYNC_TYPE, C2DSync::Sign ),
                       attr( SYNC_LIST, MakeList( "54'" ) ),
                       LM->thick_solid(),
                       attr( SYNC_SIGN_DUAL, false ),
                       attr( SYNC_SIGN_ANGLE, beta ) ), LB( "Second" ) );


    myspline = D3->rightSplineShape();
    line1.setPoints( P["54"], P["54b"] );
    beta = ((line1.angle()-90) + (-myspline.angleAtPercent(1)+90.0f))/2;

    this->sign( Sync( attr( SYNC_NAME, QString( "Front1" ) ),
                      attr( SYNC_TYPE, C2DSync::Sign ),
                      attr( SYNC_LIST, MakeList( "54" ) ),
                      LM->thick_solid(),
                      attr( SYNC_SIGN_DUAL, false ),
                      attr( SYNC_SIGN_ANGLE, beta ) ), LB( "First") );

    this->sign( Sync( attr( SYNC_NAME, QString( "Back2" ) ),
                       attr( SYNC_TYPE, C2DSync::Sign ),
                       attr( SYNC_LIST, MakeList( "74'" ) ),
                       LM->thick_solid(),
                       attr( SYNC_SIGN_DUAL, false ),
                       attr( SYNC_SIGN_ANGLE, QLineF(P["74'"],P["78'"]).angle() ) ), LB( "Second") );

    this->sign( Sync( attr( SYNC_NAME, QString( "Front2" ) ),
                       attr( SYNC_TYPE, C2DSync::Sign ),
                       attr( SYNC_LIST, MakeList( "74" ) ),
                       LM->thick_solid(),
                       attr( SYNC_SIGN_DUAL, false ),
                       attr( SYNC_SIGN_ANGLE, QLineF(P["74"],P["76"]).angle() ) ), LB( "First") );

    this->sign( Sync( attr( SYNC_NAME, QString( "Back3" ) ),
                       attr( SYNC_TYPE, C2DSync::Sign ),
                       attr( SYNC_LIST, MakeList( "78'" ) ),
                       LM->thick_solid(),
                       attr( SYNC_SIGN_DUAL, false ),
                       attr( SYNC_SIGN_ANGLE, QLineF(P["78'"],P["74'"]).angle() ) ), LB( "Second" ) );


    this->sign( Sync( attr( SYNC_NAME, QString( "Front3" ) ),
                       attr( SYNC_TYPE, C2DSync::Sign ),
                       attr( SYNC_LIST, MakeList( "78" ) ),
                       LM->thick_solid(),
                       attr( SYNC_SIGN_DUAL, false ),
                       attr( SYNC_SIGN_ANGLE, QLineF(P["78"],P["76"]).angle() ) ), LB( "First" ) );



}
