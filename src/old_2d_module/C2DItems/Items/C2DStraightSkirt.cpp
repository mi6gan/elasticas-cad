#include "C2DStraightSkirt.h"

C2DStraightSkirt::C2DStraightSkirt( C2DLayerManager * LayerManager, QGraphicsScene * scene )
                                    : C2DItem( LayerManager, scene )
{
    this->setPrefix( "StraightSkirt" );
    this->Constructed = false;
    this->requiredVariables();

    this->dialog = new StraightSkirtDarts( QObject::trUtf8( "Вытачки" ), this->prefix(),
                                           QPair< QString, double> ( QObject::trUtf8( "см" ), 10.0f ), scene, NULL );

    //    LM = LayerManager;
    //    this->f->setPixmap( QPixmap(":/images/fabrics.png" ) );
    //    this->setFabricsShape();

}

void C2DStraightSkirt::Update()
{
    this->setVariables();
    this->UpdatePoints();
    this->DrawOnWidget();
    this->BeltUpdate();
    C2DItem::Update();
}

void C2DStraightSkirt::BeltUpdate()
{
    const Elasticas::CommonData & var = Elasticas::Core::Instance()->CommonVariables();
    /******************   BELT    *************************/
    //Belt
    if (var["StraightSkirt:BeltNum"].toInt()!=0)
        S.insert("b:Belt", QVariant(true));
    else S.insert("b:Belt", QVariant(false));//Ok

    S.insert( "Belt:Length", V("T18") + 2 * V("P18") );
    S.insert( "Belt:Width", var["StraightSkirt:BeltWidth"].toDouble() * 10 );
    //ok
    S.insert( "Belt:Length1", 0 );
    S.insert( "Belt:Length2", 0 );

    S.insert( "Belt:Length1", ( ( P["P54"] - P["P51"] ).manhattanLength() - V("SideDart1Spread") / 2 - V("BackDart1Spread") ) * 2 );
    S.insert( "Belt:Length2", ( ( P["P57"] - P["P54"] ).manhattanLength() - V("SideDart1Spread") / 2 - V("FrontDart1Spread") ) * 2 );

//    Unicus::console( "Belt length1: ", V("Belt:Length1") );
//    Unicus::console( "Belt length1: ", V("Belt:Length2") );

    //?
    //Belt:Ledge                        (!!!)
    S.insert("b:Belt:Clasp", var["StraightSkirt:Clasp"] );
    S.insert("b:Belt:ZipperUntilEnd", var["StraightSkirt:ZipperAtBeltEnd"] );
    S.insert( "Belt:Ledge:Width", var["StraightSkirt:BeltLedgeWidth"].toDouble()*10 );      //(!!!)
    S.insert( "Belt:Zipper:Length", var["StraightSkirt:BeltZipperLength"].toDouble()*10 );

    if ( var["StraightSkirt:ClaspPositionNum"].toInt()!=0 &&
         var["StraightSkirt:ClaspPositionNum"].toInt()!=1 )
    {   S.insert("b:Belt:Midline", QVariant(true));
        S.insert("b:Belt:Doubleline", QVariant(false));    }
    else
    {   S.insert("b:Belt:Midline", QVariant(false));
        S.insert("b:Belt:Doubleline", QVariant(true));     }


    /******************   BELT : END    *************************/

    /******************   BELT : PARAMS     *************************/

    P["Belt:Anchor"] = P["Belt:BL"] = P["P0"] + QPointF(0, V("Height") + 160);
    P["Belt:TL"] = P["Belt:Anchor"] + QPointF(0, V("Belt:Width") );
    P["Belt:BR"] = P["Belt:Anchor"] + QPointF( V("Belt:Length"), 0 );
    P["Belt:TR"] = P["Belt:Anchor"] + QPointF( V("Belt:Length"), V("Belt:Width") );


    switch (var["StraightSkirt:ClaspPositionNum"].toInt())
    {
    case (0):
        P["Belt:BD1"] = P["Belt:Anchor"] + QPointF( V("Belt:Length1") / 2, 0 );
        P["Belt:TD1"] = P["Belt:BD1"] + QPointF( 0, V("Belt:Width") );
        P["Belt:BD2"] = P["Belt:Anchor"] + QPointF( V("Belt:Length1") + V("Belt:Length2") / 2, 0 );
        P["Belt:TD2"] = P["Belt:BD2"] + QPointF( 0, V("Belt:Width") );

        P["Belt:Sign1Pos"] = P["Belt:Anchor"] + QPointF( V("Belt:Length1"), 0 );
        break;
    case (1):
        P["Belt:BD1"] = P["Belt:Anchor"] + QPointF( V("Belt:Length2")/2, 0 );
        P["Belt:TD1"] = P["Belt:BD1"] + QPointF( 0, V("Belt:Width") );
        P["Belt:BD2"] = P["Belt:Anchor"] + QPointF( V("Belt:Length2") + V("Belt:Length1") / 2, 0 );
        P["Belt:TD2"] = P["Belt:BD2"] + QPointF( 0, V("Belt:Width") );

        P["Belt:Sign1Pos"] = P["Belt:Anchor"] + QPointF( V("Belt:Length2"), 0 );
        break;
    case (2):
        P["Belt:BM"] = P["Belt:Anchor"] + QPointF( V("Belt:Length2") / 2 + V("Belt:Length1") / 2, 0 );
        P["Belt:TM"] = P["Belt:BM"] + QPointF( 0, V("Belt:Width") );

        P["Belt:Sign1Pos"] = P["Belt:Anchor"] + QPointF( V("Belt:Length2") / 2, 0 );
        P["Belt:Sign2Pos"] = P["Belt:Anchor"] + QPointF( V("Belt:Length2") / 2 + V("Belt:Length1"), 0 );
        break;
    case (3):
        P["Belt:BM"] = P["Belt:Anchor"] + QPointF( V("Belt:Length1") / 2 + V("Belt:Length2") / 2, 0 );
        P["Belt:TM"] = P["Belt:BM"] + QPointF( 0, V("Belt:Width") );

        P["Belt:Sign1Pos"] = P["Belt:Anchor"] + QPointF( V("Belt:Length1") / 2, 0 );
        P["Belt:Sign2Pos"] = P["Belt:Anchor"] + QPointF( V("Belt:Length1") / 2 + V("Belt:Length2"), 0 );
        break;
    }

    P["Belt:PC1-L"] = P["Belt:TL"] + QPointF( -V("Belt:Ledge:Width"), 0 );
    P["Belt:PC2-L"] = P["Belt:TL"] + QPointF( -V("Belt:Ledge:Width"), -V("Belt:Width") );
    P["Belt:PC3-L"] = P["Belt:TL"] + QPointF( 0, -V("Belt:Width") );


    if (S["b:Belt:ZipperUntilEnd"].toBool())
        P["Belt:ClaspSignShift"] = QPointF( 0, -V("Belt:Zipper:Length") );
    else
        P["Belt:ClaspSignShift"] = QPointF( 0, V("Belt:Width") - V("Belt:Zipper:Length") );

    S.insert( "b:Belt:DualClasp", QVariant( false ) );
    S.insert( "b:Belt:FrontClasp", QVariant( false ) );
    S.insert( "b:Belt:BackClasp", QVariant( false ) );
    S.insert( "b:Belt:CenterClasp", QVariant( false ) );

//    qDebug() << "Var: " << QVariant( var.value( "StraightSkirt:ClaspPosition" ) ).toString().length();
//    qDebug() << "Left: " << QVariant( "В левом боковом шве" ).toString().length();
//    qDebug() << "Right: " << QVariant("В правом боковом шве").toString().length();
//    qDebug() << "Front: " << QVariant("В шве спереди").toString().length();
//    qDebug() << "Back: " << QVariant("В шве сзади").toString().length();

    if  ( var.value( "StraightSkirt:ClaspPosition" ).toString().length() == 19.0f ||
          var.value( "StraightSkirt:ClaspPosition" ).toString().length() == 20.0f )
    {
        DartItem * sd1 = this->dart( MakeSync( "SideDart-001", Sync::Dart,
                                     MakeList( "P54", "SideDart1Left", "SideDart1Right" ),
                                     LM->thick_solid() ), S["SideDart"].toBool() );

//        Unicus::console( "DualClasp", "true" );
//        Unicus::console( "Manhattan Length", P["Belt:ClaspSignShift"].manhattanLength() );
//        Unicus::console( "Spline Length", sd1->leftSplineShape().length() );
//        Unicus::console( "Paraneter P", P["Belt:ClaspSignShift"].manhattanLength() / sd1->leftSplineShape().length() );
        double p = fabs( P["Belt:ClaspSignShift"].manhattanLength() ) / sd1->leftSplineShape().length();

        if ( p <= 1.0f )
        {
            P["Belt:ClaspLeft"] = sd1->leftSplineShape().pointAtPercent( p );
            P["Belt:ClaspRight"] = sd1->rightSplineShape().pointAtPercent( p );
            S.insert( "Belt:ClaspAngleLeft", ( -1 ) * ( sd1->leftSplineShape().angleAtPercent( p ) - 90.0f ) );
            S.insert( "Belt:ClaspAngleRight", ( -1 ) * ( sd1->rightSplineShape().angleAtPercent( p ) + 90.0f ) );
            S.insert( "b:Belt:DualClasp", QVariant( true ) );
//            Unicus::console( "Rush angle", sd1->rightSplineShape().angleAtPercent( 0.999f ) );
//            Unicus::console( "Rush angle of left spline", V("Belt:ClaspAngleLeft") );
//            Unicus::console( "Rush angle of right spline", V("Belt:ClaspAngleRight") );
        }
        else
        {
            P["Belt:Clasp"] = P["P54"] +
                              QPointF( 0, - P["Belt:ClaspSignShift"].manhattanLength()
                                          + sd1->leftSplineShape().length() );
            S.insert( "Belt:ClaspAngle", 0.0f );
            S.insert( "b:Belt:CenterClasp", QVariant( true ) );
        }
    }

    if ( var.value( "StraightSkirt:ClaspPosition" ).toString().length() == 13.0f )
    {
//        Unicus::console( "FrontClasp", "true" );
        P["Belt:Clasp"] = P["P47"] + P["Belt:ClaspSignShift"];
        S.insert( "Belt:ClaspAngle", 180.0f );
        S.insert( "b:Belt:FrontClasp", QVariant( true ) );
    }

    if ( var.value( "StraightSkirt:ClaspPosition" ).toString().length() == 11.0f )
    {
//        Unicus::console( "BackClasp", "true" );
        P["Belt:Clasp"] = P["P41"] + P["Belt:ClaspSignShift"];
        S.insert( "Belt:ClaspAngle", 0.0f );
        S.insert( "b:Belt:BackClasp", QVariant( true ) );
    }

    /******************   BELT : PARAMS : END     *************************/

    /******************   BELT : SHAPE     *************************/
    //Belt

    line(MakeSync("L-B1-001", Sync::Line, MakeList("Belt:BL", "Belt:TL"), LM->bold_solid()), S["b:Belt"].toBool());
    line(MakeSync("L-B1-002", Sync::Line, MakeList("Belt:BR", "Belt:TR"), LM->bold_solid()), S["b:Belt"].toBool());
    line(MakeSync("L-B1-003", Sync::Line, MakeList("Belt:BL", "Belt:BR"), LM->bold_solid()), S["b:Belt"].toBool());
    line(MakeSync("L-B1-004", Sync::Line, MakeList("Belt:TL", "Belt:TR"), LM->bold_solid()), S["b:Belt"].toBool());

    line(MakeSync("L-B1-005", Sync::Line, MakeList("Belt:TM", "Belt:BM"), LM->thick_dashed()), ( S["b:Belt"].toBool() && S["b:Belt:Midline"].toBool() ) );
    line(MakeSync("L-B1-005-1", Sync::Line, MakeList("Belt:TD1", "Belt:BD1"), LM->thick_dashed()), ( S["b:Belt"].toBool() && S["b:Belt:Doubleline"].toBool() ) );
    line(MakeSync("L-B1-005-2", Sync::Line, MakeList("Belt:TD2", "Belt:BD2"), LM->thick_dashed()), ( S["b:Belt"].toBool() && S["b:Belt:Doubleline"].toBool() ) );

    line(MakeSync("L-B1-006",   Sync::Line, MakeList("Belt:PC1-L", "Belt:PC2-L"), LM->bold_solid()), ( S["b:Belt"].toBool() && S["b:Belt:ZipperUntilEnd"].toBool() ) );
    line(MakeSync("L-B1-006-1", Sync::Line, MakeList("Belt:PC1-L", "Belt:TL"), LM->bold_solid()), ( S["b:Belt"].toBool() && S["b:Belt:ZipperUntilEnd"].toBool() ) );
    line(MakeSync("L-B1-006-2", Sync::Line, MakeList("Belt:PC2-L", "Belt:PC3-L"), LM->bold_solid()), ( S["b:Belt"].toBool() && S["b:Belt:ZipperUntilEnd"].toBool() ) );

    sign("L-B1-S1", "Belt:Sign1Pos", false, 90, S["b:Belt"].toBool());
    sign("L-B1-S2", "Belt:Sign2Pos", false, 90, S["b:Belt"].toBool() && !S["b:Belt:Doubleline"].toBool() );
  //  sign("L-B1-S3", "Belt:Sign3Pos", false, 0, S["b:Belt"].toBool());


    this->sign( "Belt:ClaspSign:Front", "Belt:Clasp", false, V("Belt:ClaspAngle"), S.value( "b:Belt:FrontClasp" ).toBool() );
    this->sign( "Belt:ClaspSign:Back", "Belt:Clasp", false, V("Belt:ClaspAngle"), S.value( "b:Belt:BackClasp" ).toBool() );
    this->sign( "Belt:ClaspSign:DualLeft", "Belt:ClaspLeft", false, V("Belt:ClaspAngleLeft"), S.value( "b:Belt:DualClasp" ).toBool() );
    this->sign( "Belt:ClaspSign:Dual", "Belt:ClaspRight", false, V("Belt:ClaspAngleRight"), S.value( "b:Belt:DualClasp" ).toBool() );
    this->sign( "Belt:ClaspSign:Center", "Belt:Clasp", true, V("Belt:ClaspAngle"), S.value( "b:Belt:CenterClasp" ).toBool() );

    /******************   BELT : SHAPE : END     *************************/
}

void C2DStraightSkirt::requiredVariables()
{
    this->variables.insert( "PTx", Variable::set( "PTx", this->prefix() + "PTx",
                                                  "Not described", Variable::Unitless, Variable::General ) );
    this->variables.insert( "PTy", Variable::set( "PTy", this->prefix() + "PTy", "Not describedd",
                                                  Variable::Unitless, Variable::General ) );

    this->variables.insert( "T7", Variable::set( "T7", "T7", "Not described", Variable::Metrics,
                                                 Variable::General, 1000.0f, 10.0f ) );
    this->variables.insert( "T9", Variable::set( "T9", "T9", "Not described", Variable::Metrics,
                                                 Variable::General, 1000.0f, 10.0f ) );
    this->variables.insert( "T12", Variable::set( "T12", "T12", "Not described", Variable::Metrics,
                                                  Variable::General, 1000.0f, 10.0f ) );
    this->variables.insert( "T18", Variable::set( "T18", "T18", "Not described", Variable::Metrics,
                                                  Variable::General, 1000.0f, 10.0f ) );
    this->variables.insert( "T19", Variable::set( "T19", "T19", "Not described", Variable::Metrics,
                                                  Variable::General, 1000.0f, 10.0f ) );
    this->variables.insert( "T25", Variable::set( "T25", "T25", "Not described", Variable::Metrics,
                                                  Variable::General, 1000.0f, 10.0f ) );
    this->variables.insert( "T26", Variable::set( "T26", "T26", "Not described", Variable::Metrics,
                                                  Variable::General, 1000.0f, 10.0f ) );
    this->variables.insert( "T46", Variable::set( "T46", "T46", "Not described", Variable::Metrics,
                                                  Variable::General, 1000.0f, 10.0f ) );
    this->variables.insert( "T86", Variable::set( "T86", "T86", "Not described", Variable::Metrics,
                                                  Variable::General, 1000.0f, 10.0f ) );

    //P18 - прибавка к полуобхвату талии
    //P19 - прибавка к полуобхвату бедер
    this->variables.insert( "P18", Variable::set( "P18", this->prefix() + "P18", "Not described",
                                                  Variable::Metrics, Variable::General, 0.0f, 10.0f ) );
    this->variables.insert( "P19", Variable::set( "P19", this->prefix() + "P19", "Not described",
                                                  Variable::Metrics, Variable::General, 0.0f, 10.0f ) );

    this->variables.insert( "K25", Variable::set( "K25", "K25", "Not described", Variable::Metrics,
                                                  Variable::Additional, 0.0f ) );
    this->variables.insert( "K26", Variable::set( "K26", "K26", "Not described", Variable::Metrics,
                                                  Variable::Additional, -50.0f ) );

    this->variables.insert( "Height", Variable::set( "Height", this->prefix() + "A1", "Not described",
                                                     Variable::Metrics, Variable::General, 60.0f, 10.0f ) );

    this->variables.insert( "SideDart", Variable::set( "SideDart", this->prefix() + "SideDartsCount",
                                                       "Not described", Variable::Unitless, Variable::Optional, 1 ) );
    this->variables.insert( "FrontDart", Variable::set( "FrontDart", this->prefix() + "FrontDartsCount",
                                                        "Not described", Variable::Unitless, Variable::Optional, 1 ) );
    this->variables.insert( "BackDart", Variable::set( "BackDart", this->prefix() + "BackDartsCount",
                                                       "Not described", Variable::Unitless, Variable::Optional, 1 ) );

    this->variables.insert( "SideSeam",
                            Variable::set( "SideSeam", this->prefix() + "VB", "Not described",
                                           Variable::Logical, Variable::Optional, true ) );
    this->variables.insert( "SideSeamShift",
                            Variable::set( "SideSeamShift", this->prefix() + "A2", "Not described",
                                           Variable::Metrics, Variable::Optional, 1.0f, 10.0f ) );
    this->variables.insert( "FrontSeam",
                            Variable::set( "FrontSeam", this->prefix() + "VP", "Not described",
                                           Variable::Logical, Variable::Optional, true ) );
    this->variables.insert( "BackSeam",
                            Variable::set( "BackSeam", this->prefix() + "VZ", "Not described",
                                           Variable::Logical, Variable::Optional, true ) );


    this->variables.insert( "SideVentWidth",
                            Variable::set( "SideVentWidth",  this->prefix() + "SideVentWidth",
                                           "Not described", Variable::Metrics, Variable::Optional, 30.0f, 10.0f ) );
    this->variables.insert( "SideVentHeight",
                            Variable::set( "SideVentHeight", this->prefix() + "SideVentHeight",
                           "Not described", Variable::Metrics, Variable::Optional, 60.0f, 10.0f ) );
    this->variables.insert( "FrontVentWidth",
                            Variable::set( "FrontVentWidth", this->prefix() + "FrontVentWidth",
                            "Not described", Variable::Metrics, Variable::Optional, 30.0f, 10.0f ) );
    this->variables.insert( "FrontVentHeight",
                            Variable::set( "FrontVentHeight", this->prefix() + "FrontVentHeight",
                            "Not described", Variable::Metrics, Variable::Optional, 60.0f, 10.0f ) );
    this->variables.insert( "BackVentWidth",
                            Variable::set( "BackVentWidth", this->prefix() + "BackVentWidth",
                           "Not described", Variable::Metrics, Variable::Optional, 30.0f, 10.0f ) );
    this->variables.insert( "BackVentHeight",
                            Variable::set( "BackVentHeight", this->prefix() + "BackVentHeight",
                            "Not described", Variable::Metrics, Variable::Optional, 60.0f, 10.0f ) );

    this->variables.insert( "Narrow",
                            Variable::set( "Narrow", this->prefix() + "Narrow", "Not described",
                                           Variable::Logical, Variable::Optional, false ) );
    this->variables.insert( "NarrowValue",
                            Variable::set( "NarrowValue", this->prefix() + "A3", "Not described",
                                           Variable::Metrics, Variable::Optional, 20.0f, 10.0f ) );
    this->variables.insert( "NarrowTopPoint",
                            Variable::set( "NarrowTopPoint", this->prefix() + "A4", "Not described",
                                            Variable::Metrics, Variable::Optional, 100.0f, 10.0f ) );

    QList<QString> a;
    a << "Side"  << "Front" << "Back";
    for ( int i = 0; i <= 2; ++i )
    foreach ( QString str, a )
    {
        this->variables.insert( QString( "%2Dart%1Spread" ).arg( i + 1 ).arg( str ),
                                Variable::set( QString( "%2Dart%1Spread" ).arg( i + 1 ).arg( str ),
                                               this->prefix() + QString( "%2Darts%1Spread" ).arg( i ).arg( str ),
                                               "Not described", Variable::Metrics, Variable::Optional, 10.0f, 10.0f ) );
        this->variables.insert( QString( "%2Dart%1Width" ).arg( i + 1 ).arg( str ),
                                Variable::set( QString( "%2Dart%1Width" ).arg( i + 1 ).arg( str ),
                                               this->prefix() + QString("%2Darts%1Width").arg( i ).arg( str ),
                                               "Not described", Variable::Metrics, Variable::Optional, i * 10.0f, 10.0f ) );
        this->variables.insert( QString( "%2Dart%1Height" ).arg( i + 1 ).arg( str ),
                                Variable::set( QString( "%2Dart%1Height" ).arg( i + 1 ).arg( str ),
                                               this->prefix() + QString( "%2Darts%1Height" ).arg( i ).arg( str ),
                                               "Not described", Variable::Metrics, Variable::Optional, 10.0f, 10.0f ) );

        this->variables.insert( QString( "%1VentTypeNum" ).arg( str ),
                                Variable::set( QString( "%1VentTypeNum" ).arg( str ),
                                               this->prefix() + QString( "%1VentTypeNum" ).arg( str ),
                                               "Not described", Variable::Metrics, Variable::Optional, 1.0f ) );
    }

}


void C2DStraightSkirt::setVariables()
{
    C2DItem::setVariables();

    S.insert( "LibVersion", 0.9f );

    S.insert("Material", 0);

    S.insert( "HeightRight", V("Height") + ( V("T26") - V("T7") - V("K26") ) );
    S.insert( "DartTopCenter", V("Height") + ( V("T25") - V("T7") - V("K25") ) );

    S.insert( "Width", V("T19") / 2 + V("P19") );


    S.insert( "WidthAtHipline", ( 0.5 * ( V("T19") - V("T18") ) + ( V("P19") - V("P18") ) ) * V("TX") );
    S.insert( "TopHeightLeft", V("Height") - V("T86") );

    for ( int i = 1 ; i <= 3 ; ++i )
    {

        if ( i <= I( "FrontDart" ) )
            S.insert( QString( "FrontDart%1" ).arg( i ), QVariant( true ) );
        else
            S.insert( QString( "FrontDart%1" ).arg( i ), QVariant( false ) );

        if ( i <= I( "BackDart") )
            S.insert( QString( "BackDart%1" ).arg( i ), QVariant( true ) );
        else
            S.insert( QString( "BackDart%1" ).arg( i ), QVariant( false ) );

    }

    QList<QString> templist = MakeList( "Front" , "Back" , "Side" );
    foreach ( QString str, templist )
        switch ( S.value( QString( "StraightSkirt:%1VentTypeNum" ).arg( str ) ).toInt() )
        {
        case (0):
        S.insert(QString("b:%1Seam:Vent").arg(str), QVariant(false));
        S.insert(QString("b:%1Seam:Sign").arg(str), QVariant(false));
        break;
        case (1):
        if (V(QString("%1Seam").arg(str)))
            S.insert(QString("b:%1Seam:Vent").arg(str), QVariant(true));
        else
            S.insert(QString("b:%1Seam:Vent").arg(str), QVariant(false));

        S.insert(QString("b:%1Seam:Sign").arg(str), QVariant(false));
        break;
        case (2):
        S.insert(QString("b:%1Seam:Vent").arg(str), QVariant(false));

        if (V(QString("%1Seam").arg(str)))
            S.insert(QString("b:%1Seam:Sign").arg(str), QVariant(true));
        else
            S.insert(QString("b:%1Seam:Sign").arg(str), QVariant(false));
        break;
    }

    if ( V("NarrowValue") < 0 )
        {
            S.insert("Narrow:Negative",
                 QVariant( true && B("Narrow") ) );
            S.insert("Narrow", QVariant( false ) );
        }
        else
        {
            S.insert("Narrow",
                     QVariant( true && B("Narrow") ) );
            S.insert("Narrow:Negative", QVariant( false ) );
        }
}

void C2DStraightSkirt::UpdatePoints()
{
    QPointF TempPoint;
    QLineF TempLine;

    P["P0"] = QPointF( 0 , 0 );

    P["View:Center"] = P["P0"] + QPointF( V("Width") / 2.0f - V("SideSeamShift"), V("Height") / 2.0f );

    //Main circuit
    P["P97"] = P["P0"] + QPointF( V("Width"), 0 );
    P["P51"] = P["P0"] + QPointF(0, V("Height") - ( V("T7") - V("T86") ) );
    P["P54"] = P["P0"] + QPointF( ( V("Width") / 2 ) - V("SideSeamShift"), V("Height") - ( V("T7") - V("T86") ) );
    P["P57"] = P["P0"] + QPointF( V("Width"), V("Height") - ( V("T7") - V("T86") ) );
    P["P47a"] = P["P0"] + QPointF( V("Width"), V("Height") );
    P["P41"] = P["P0"] + QPointF(0, V("Height") );
    P["P-C-001"] = P["P41"] + QPointF( 10.0f, 0 );
    P["P420"] = P["P41"] + QPointF( 0.1f * V("WidthAtHipline"), 0 );
    P["P47"] = P["P0"] + QPointF( V("Width"), V("HeightRight") );
    P["P-C-002"] = P["P47"] + QPointF( -10.0f, 0 );
    P["P460"] = P["P47"] + QPointF( -0.1 * V("WidthAtHipline"), 0 );

    P["P94"] = P["P0"] + QPointF( ( V("Width") / 2 ) - V("SideSeamShift"), 0 );

    P["PT1"] = P["P0"] + QPointF( 20.0f, V("Height") / 3.0f );
    P["PT2"] = P["P0"] + QPointF( V("Width") - 10.0f, V("Height") / 3.0f );

    // Narrow
    P["P941"]=P["P0"]+QPointF(V("NarrowValue"),0);
    P["P941a"]=P["P97"]+QPointF(-V("NarrowValue"),0);
    P["SG3"]=P["P941"]+QPointF(QLineF(P["P0"],P["P941"]).length()*3,0);
    P["SG4"]=P["P941a"]+QPointF(-QLineF(P["P97"],P["P941a"]).length()*3,0);
    P["P54a"]=P["P54"]+QPointF(0,-V("NarrowTopPoint"));

    P["SG0"]=P["P54a"]+QPointF( 0,-1.0f );

    if ( S.value( "Narrow" ).toBool() )
    {
    TempLine.setPoints(P["P54a"],P["P94"]+QPointF(-V("NarrowValue"),0));
    TempLine.intersect(QLineF(P["P941"],P["P941"]+QPointF(0,-1)),&TempPoint);
    TempLine.setP1(TempPoint);
    TempLine.setLength(QLineF(TempPoint,P["P941"]).length());
    P["P9411"]=TempLine.p2();
    TempLine=TempLine.normalVector();
    P["SG5"]=P["P9411"]+QPointF(-abs(TempLine.dx())*0.02,abs(TempLine.dy())*0.02);

    TempLine=QLineF(TempPoint,P["P54a"]);
    TempLine.setLength(TempLine.length()-30);
    P["P9411a"]=TempLine.p2();
    TempLine.setLength(TempLine.length()+10);
    P["SG1"]=TempLine.p2();

    TempLine.setPoints(P["P54a"],P["P94"]+QPointF(V("NarrowValue"),0));
    TempLine.intersect(QLineF(P["P941a"],P["P941a"]+QPointF(0,-1)),&TempPoint);
    TempLine.setP1(TempPoint);
    TempLine.setLength(QLineF(TempPoint,P["P941a"]).length());
    P["P9412"]=TempLine.p2();
    TempLine=TempLine.normalVector();
    P["SG6"]=P["P9412"]+QPointF(abs(TempLine.dx())*0.02,abs(TempLine.dy())*0.02);

    TempLine=QLineF(TempPoint,P["P54a"]);
    TempLine.setLength(TempLine.length()-30);
    P["P9412a"]=TempLine.p2();
    TempLine.setLength(TempLine.length()+10);
    P["SG2"]=TempLine.p2();

    P["P54a"]=P["P54"]+QPointF(0,-V("NarrowTopPoint")*0.9);

    TempLine.setPoints(P["P9411a"],P["P9411"]);
    TempLine.translate(-TempLine.normalVector().unitVector().dx()*40,
                       TempLine.normalVector().unitVector().dy()*40);
    QLineF TempLine2(P["P54a"],P["P54"]);
    TempLine2.translate(-TempLine2.normalVector().unitVector().dx()*40,
                        TempLine2.normalVector().unitVector().dy()*40);
    TempLine.intersect(TempLine2,&TempPoint);
    P["NarrowStartLeft"]=TempPoint;
    QLineF(P["P9412a"],P["P9412"]).normalVector().intersect(
            QLineF(P["P54a"],P["P54"]).normalVector(),&TempPoint);
    P["NarrowStartRight"]=TempPoint;
    }

    if ( S.value( "Narrow:Negative" ).toBool() )
    {
        double length = Unicus::dPointPoint( P["P54a"], P["P94"] );
        double angle = abs( V("NarrowValue") ) / length * 180.0f / M_PI;

        P["P941"] = P["P94"] + QPointF( V("NarrowValue"), 0.0f );
        P["P941a"] = P["P94"] + QPointF( -V("NarrowValue"), 0.0f );
        P["SG3"] = P["P941"] + QPointF( -QLineF( P["P94"], P["P941"] ).length() * 0.3f, 0.0f );
        P["SG4"] = P["P941a"] + QPointF( QLineF( P["P94"], P["P941a"] ).length() * 0.3f, 0.0f );

        P["P9411"] = Unicus::PointOnRay( P["P54a"], ( angle ) - 90.0f, length );
        P["P9412"] = Unicus::PointOnRay( P["P54a"], ( -angle ) - 90.0f, length );

//        Unicus::console( "Narrow:Negative:Angle", angle );

        TempLine = QLineF( P["P9411"], P["P54a"] );
        TempLine.setLength( TempLine.length() - 30.0f );
        P["P9411a"] = TempLine.p2();
        TempLine.setLength( TempLine.length() + 10.0f );
        P["SG1"]=TempLine.p2();

        TempLine = QLineF( P["P9412"], P["P54a"] );
        TempLine.setLength( TempLine.length() - 30.0f );
        P["P9412a"] = TempLine.p2();
        TempLine.setLength( TempLine.length() + 10.0f );
        P["SG2"]=TempLine.p2();

        TempLine = Unicus::uNormal( QLineF( P["P9411"], P["P9411a"] ), true );
        P["SG6"] = P["P9411"] + TempLine.pointAt( 0.1f );
        TempLine = Unicus::uNormal( QLineF( P["P9412"], P["P9412a"] ), false );
        P["SG5"] = P["P9412"] + TempLine.pointAt( 0.1f );

        P["P54a"]=P["P54"]+QPointF(0,-V("NarrowTopPoint")*0.9);

        TempLine.setPoints(P["P9411a"],P["P9411"]);
        TempLine.translate(-TempLine.normalVector().unitVector().dx()*40,
                           TempLine.normalVector().unitVector().dy()*40);
        QLineF TempLine2(P["P54a"],P["P54"]);
        TempLine2.translate(-TempLine2.normalVector().unitVector().dx()*40,
                            TempLine2.normalVector().unitVector().dy()*40);
        TempLine.intersect(TempLine2,&TempPoint);
        P["NarrowStartLeft"]=TempPoint;
        QLineF(P["P9412a"],P["P9412"]).normalVector().intersect(
                QLineF(P["P54a"],P["P54"]).normalVector(),&TempPoint);
        P["NarrowStartRight"]=TempPoint;
    }

    //Vent is at the Back seam
    P["V:L:TT"] = P["P51"];
    P["V:L:RT"] = P["P0"] + QPointF( 0,V("BackVentHeight") );
    P["V:L:LT"] = P["P0"] + QPointF( -V("BackVentWidth"), V("BackVentHeight") );
    P["V:L:LB"] = P["P0"] + QPointF( -V("BackVentWidth"),0 );
    P["V:L:RB"] = P["P0"];
    //Vent is at the Front seam
    P["V:R:TT"] = P["P57"];
    P["V:R:LT"] = P["P97"] + QPointF( 0,V("FrontVentHeight") );
    P["V:R:RT"] = P["P97"] + QPointF( V("FrontVentWidth"), V("FrontVentHeight") );
    P["V:R:RB"] = P["P97"] + QPointF( V("FrontVentWidth"),0 );
    P["V:R:LB"] = P["P97"];
    //Vent is at the Side seam
    if ( S["Narrow"].toBool() || S["Narrow:Negative"].toBool() )
    {
        P["V:S:L:TT"] = P["P9411a"];
        P["V:S:L:LB"] = P["P9411"];
        QLineF temp = QLineF( P["P9411"], P["P9411a"] ).unitVector();
        temp.setLength( V("SideVentHeight") );
        P["V:S:L:LT"] = temp.p2();
        temp = temp.unitVector();
        temp = Unicus::uNormal( temp , false ).translated( P["P9411"] );
        temp.setLength( V("SideVentWidth") );
        P["V:S:L:RB"] = temp.p2();
        P["V:S:L:RT"] = P["V:S:L:RB"] + QPointF( P["V:S:L:LT"].x() - P["V:S:L:LB"].x(),
                                                 P["V:S:L:LT"].y() - P["V:S:L:LB"].y() );

        P["V:S:R:TT"] = P["P9412a"];
        P["V:S:R:RB"] = P["P9412"];
        temp = QLineF( P["P9412"], P["P9412a"] ).unitVector();
        temp.setLength(V("SideVentHeight"));
        P["V:S:R:RT"] = temp.p2();
        temp = temp.unitVector();
        temp=Unicus::uNormal( temp , true ).translated( P["P9412"] );
        temp.setLength( V("SideVentWidth") );
        P["V:S:R:LB"] = temp.p2();
        P["V:S:R:LT"] = P["V:S:R:LB"] + QPointF( P["V:S:R:RT"].x() - P["V:S:R:RB"].x(),
                                                 P["V:S:R:RT"].y() - P["V:S:R:RB"].y() );
    }
    else
    {
        P["V:S:L:TT"] = P["P54"];
        P["V:S:L:LT"] = P["P94"]+QPointF(0,V("SideVentHeight"));
        P["V:S:L:RT"] = P["P94"]+QPointF(V("SideVentWidth"), V("SideVentHeight"));
        P["V:S:L:RB"] = P["P94"]+QPointF(V("SideVentWidth"),0);
        P["V:S:L:LB"] = P["P94"];

        P["V:S:R:TT"] = P["P54"];
        P["V:S:R:RT"] = P["P94"]+QPointF(0,V("SideVentHeight"));
        P["V:S:R:LT"] = P["P94"]+QPointF(-V("SideVentWidth"), V("SideVentHeight"));
        P["V:S:R:LB"] = P["P94"]+QPointF(-V("SideVentWidth"),0);
        P["V:S:R:RB"] = P["P94"];
    }


    //
    //Clasp
    //

    //New Darts
    P["SideDart1TopPosition"]=P["P94"]+QPointF(0,V("DartTopCenter"));
    P["SideDart1Position"]=P["SideDart1TopPosition"]+QPointF(0,-V("SideDart1Height"));
    P["SideDart1SplineBottom"]=P["SideDart1Position"]+QPointF(0,10);
    P["SideDart1Right"]=P["SideDart1TopPosition"]+QPointF(V("SideDart1Spread")/2,0);
    P["SideDart1SplineRight"]=Unicus::rLine(QLineF(P["SideDart1Right"],P["SideDart1Position"]),P["SideDart1Right"],-10).pointAt(0.1);
    P["SideDart1Left"]=P["SideDart1TopPosition"]+QPointF(-V("SideDart1Spread")/2,0);
    P["SideDart1SplineLeft"]=Unicus::rLine(QLineF(P["SideDart1Left"],P["SideDart1Position"]),P["SideDart1Left"],10).pointAt(0.1);
    P["SideDart1ConnectionLeft"]=Unicus::rPoint(P["SideDart1SplineLeft"],P["SideDart1Left"], -90);
    P["SideDart1ConnectionRight"]=Unicus::rPoint(P["SideDart1SplineRight"],P["SideDart1Right"], 90);

    P["BackDart1TopPosition"]=P["P41"]+BackDartTopPosition(V("BackDart1Width"), P["P94"]+QPointF(0,V("DartTopCenter")), P["P41"]);
    P["BackDart1Position"]=P["BackDart1TopPosition"]+QPointF(0,-V("BackDart1Height"));
    P["BackDart1SplineBottom"]=P["BackDart1Position"]+QPointF(0,10);
    P["BackDart1Right"]=P["BackDart1TopPosition"]+QPointF(V("BackDart1Spread")/2,0);
    P["BackDart1SplineRight"]=Unicus::rLine(QLineF(P["BackDart1Right"],P["BackDart1Position"]),P["BackDart1Right"],-10).pointAt(0.1);
    P["BackDart1Left"]=P["BackDart1TopPosition"]+QPointF(-V("BackDart1Spread")/2,0);
    P["BackDart1SplineLeft"]=Unicus::rLine(QLineF(P["BackDart1Left"],P["BackDart1Position"]),P["BackDart1Left"],10).pointAt(0.1);
    P["BackDart1ConnectionLeft"]=Unicus::rPoint(P["BackDart1SplineLeft"],P["BackDart1Left"], -90);
    P["BackDart1ConnectionRight"]=Unicus::rPoint(P["BackDart1SplineRight"],P["BackDart1Right"], 90);

    P["BackDart2TopPosition"]=P["P41"]+BackDartTopPosition(V("BackDart2Width"), P["P94"]+QPointF(0,V("DartTopCenter")), P["P41"]);
    P["BackDart2Position"]=P["BackDart2TopPosition"]+QPointF(0,-V("BackDart2Height"));
    P["BackDart2SplineBottom"]=P["BackDart2Position"]+QPointF(0,10);
    P["BackDart2Right"]=P["BackDart2TopPosition"]+QPointF(V("BackDart2Spread")/2,0);
    P["BackDart2SplineRight"]=Unicus::rLine(QLineF(P["BackDart2Right"],P["BackDart2Position"]),P["BackDart2Right"],-10).pointAt(0.1);
    P["BackDart2Left"]=P["BackDart2TopPosition"]+QPointF(-V("BackDart2Spread")/2,0);
    P["BackDart2SplineLeft"]=Unicus::rLine(QLineF(P["BackDart2Left"],P["BackDart2Position"]),P["BackDart2Left"],10).pointAt(0.1);
    P["BackDart2ConnectionLeft"]=Unicus::rPoint(P["BackDart2SplineLeft"],P["BackDart2Left"], -90);
    P["BackDart2ConnectionRight"]=Unicus::rPoint(P["BackDart2SplineRight"],P["BackDart2Right"], 90);

    P["BackDart3TopPosition"]=P["P41"]+BackDartTopPosition(V("BackDart3Width"), P["P94"]+QPointF(0,V("DartTopCenter")), P["P41"]);
    P["BackDart3Position"]=P["BackDart3TopPosition"]+QPointF(0,-V("BackDart3Height"));
    P["BackDart3SplineBottom"]=P["BackDart3Position"]+QPointF(0,10);
    P["BackDart3Right"]=P["BackDart3TopPosition"]+QPointF(V("BackDart3Spread")/2,0);
    P["BackDart3SplineRight"]=Unicus::rLine(QLineF(P["BackDart3Right"],P["BackDart3Position"]),P["BackDart3Right"],-10).pointAt(0.1);
    P["BackDart3Left"]=P["BackDart3TopPosition"]+QPointF(-V("BackDart3Spread")/2,0);
    P["BackDart3SplineLeft"]=Unicus::rLine(QLineF(P["BackDart3Left"],P["BackDart3Position"]),P["BackDart3Left"],10).pointAt(0.1);
    P["BackDart3ConnectionLeft"]=Unicus::rPoint(P["BackDart3SplineLeft"],P["BackDart3Left"], -90);
    P["BackDart3ConnectionRight"]=Unicus::rPoint(P["BackDart3SplineRight"],P["BackDart3Right"], 90);

    P["FrontDart1TopPosition"]=P["P47"]+FrontDartTopPosition(V("FrontDart1Width"), P["P94"]+QPointF(0,V("DartTopCenter")), P["P47"]);
    P["FrontDart1Position"]=P["FrontDart1TopPosition"]+QPointF(0,-V("FrontDart1Height"));
    P["FrontDart1SplineBottom"]=P["FrontDart1Position"]+QPointF(0,10);
    P["FrontDart1Right"]=P["FrontDart1TopPosition"]+QPointF(V("FrontDart1Spread")/2,0);
    P["FrontDart1SplineRight"]=Unicus::rLine(QLineF(P["FrontDart1Right"],P["FrontDart1Position"]),P["FrontDart1Right"],-10).pointAt(0.1);
    P["FrontDart1Left"]=P["FrontDart1TopPosition"]+QPointF(-V("FrontDart1Spread")/2,0);
    P["FrontDart1SplineLeft"]=Unicus::rLine(QLineF(P["FrontDart1Left"],P["FrontDart1Position"]),P["FrontDart1Left"],10).pointAt(0.1);
    P["FrontDart1ConnectionLeft"]=Unicus::rPoint(P["FrontDart1SplineLeft"],P["FrontDart1Left"], -90);
    P["FrontDart1ConnectionRight"]=Unicus::rPoint(P["FrontDart1SplineRight"],P["FrontDart1Right"], 90);

    P["FrontDart2TopPosition"]=P["P47"]+FrontDartTopPosition(V("FrontDart2Width"), P["P94"]+QPointF(0,V("DartTopCenter")), P["P47"]);
    P["FrontDart2Position"]=P["FrontDart2TopPosition"]+QPointF(0,-V("FrontDart2Height"));
    P["FrontDart2SplineBottom"]=P["FrontDart2Position"]+QPointF(0,10);
    P["FrontDart2Right"]=P["FrontDart2TopPosition"]+QPointF(V("FrontDart2Spread")/2,0);
    P["FrontDart2SplineRight"]=Unicus::rLine(QLineF(P["FrontDart2Right"],P["FrontDart2Position"]),P["FrontDart2Right"],-10).pointAt(0.1);
    P["FrontDart2Left"]=P["FrontDart2TopPosition"]+QPointF(-V("FrontDart2Spread")/2,0);
    P["FrontDart2SplineLeft"]=Unicus::rLine(QLineF(P["FrontDart2Left"],P["FrontDart2Position"]),P["FrontDart2Left"],10).pointAt(0.1);
    P["FrontDart2ConnectionLeft"]=Unicus::rPoint(P["FrontDart2SplineLeft"],P["FrontDart2Left"], -90);
    P["FrontDart2ConnectionRight"]=Unicus::rPoint(P["FrontDart2SplineRight"],P["FrontDart2Right"], 90);

    P["FrontDart3TopPosition"]=P["P47"]+FrontDartTopPosition(V("FrontDart3Width"), P["P94"]+QPointF(0,V("DartTopCenter")), P["P47"]);
    P["FrontDart3Position"]=P["FrontDart3TopPosition"]+QPointF(0,-V("FrontDart3Height"));
    P["FrontDart3SplineBottom"]=P["FrontDart3Position"]+QPointF(0,10);
    P["FrontDart3Right"]=P["FrontDart3TopPosition"]+QPointF(V("FrontDart3Spread")/2,0);
    P["FrontDart3SplineRight"]=Unicus::rLine(QLineF(P["FrontDart3Right"],P["FrontDart3Position"]),P["FrontDart3Right"],-10).pointAt(0.1);
    P["FrontDart3Left"]=P["FrontDart3TopPosition"]+QPointF(-V("FrontDart3Spread")/2,0);
    P["FrontDart3SplineLeft"]=Unicus::rLine(QLineF(P["FrontDart3Left"],P["FrontDart3Position"]),P["FrontDart3Left"],10).pointAt(0.1);
    P["FrontDart3ConnectionLeft"]=Unicus::rPoint(P["FrontDart3SplineLeft"],P["FrontDart3Left"], -90);
    P["FrontDart3ConnectionRight"]=Unicus::rPoint(P["FrontDart3SplineRight"],P["FrontDart3Right"], 90);

}

void  C2DStraightSkirt::DrawOnWidget()
{

    Border * b;
    C2DLayer * Layer;

    //Base shape: lines
    line(MakeSync("SS:B-001" , Sync::Line, MakeList("P51", "P54"), LM->thick_dashed() ), true);
    line(MakeSync("SS:B-002" , Sync::Line, MakeList("P41", "P47a"), LM->thick_dashed() ), true);
    line(MakeSync("SS:B-003" , Sync::Line, MakeList("P54", "P57"), LM->thick_dashed() ), true);

    if ( S["BackSeam"].toBool() )
        Layer = LM->bold_solid();
    else
        Layer = LM->thick_dashed();

    b = MakeBorder( "V:L:1", false, S["b:BackSeam:Vent"].toBool(), "NoVent-L" );
    line(MakeSync("SS:B:B-001" , Sync::Line, MakeList("P41", "P51"), Layer, 0, b ), true);

    //Vent is at the Back seam
    line(MakeSync("V:L:1" , Sync::Line, MakeList("V:L:TT", "V:L:RT"),
                  Layer, 0, MakeBorder( "V:L:2" ) ), S["b:BackSeam:Vent"].toBool() );
    line(MakeSync("V:L:2" , Sync::Line, MakeList("V:L:RT", "V:L:LT"),
                  LM->bold_solid(), 0, MakeBorder( "V:L:3" ) ), S["b:BackSeam:Vent"].toBool() );
    line(MakeSync("V:L:3" , Sync::Line, MakeList("V:L:LT", "V:L:LB"),
                  LM->bold_solid(), 0, MakeBorder( "V:L:4" ) ), S["b:BackSeam:Vent"].toBool() );
    line(MakeSync("V:L:4" , Sync::Line, MakeList("V:L:LB", "V:L:RB"),
                  LM->bold_solid(), 0, MakeBorder( NULL ) ), S["b:BackSeam:Vent"].toBool() );
    line(MakeSync("L-V1-005" , Sync::Line, MakeList("V:L:RB", "V:L:RT"), LM->thick_dashed()), S["b:BackSeam:Vent"].toBool() );
    line(MakeSync("NoVent-L", Sync::Line, MakeList("V:L:TT", "V:L:RB"),
                  Layer, 0, MakeBorder( NULL ) ), !S["b:BackSeam:Vent"].toBool() );


    if ( S["FrontSeam"].toBool() )
        Layer = LM->bold_solid();
    else
        Layer = LM->thick_dashed();
    line(MakeSync("SS:B:F-001" , Sync::Line, MakeList("P57", "P47"), Layer ), true);

    //Vent is at the Front seam
    line(MakeSync("V:R:1" , Sync::Line, MakeList("V:R:TT", "V:R:LT"), Layer ), S["b:FrontSeam:Vent"].toBool() );
    line(MakeSync("V:R:2" , Sync::Line, MakeList("V:R:LT", "V:R:RT"), LM->bold_solid()), S["b:FrontSeam:Vent"].toBool() );
    line(MakeSync("V:R:3" , Sync::Line, MakeList("V:R:RT", "V:R:RB"), LM->bold_solid()), S["b:FrontSeam:Vent"].toBool() );
    line(MakeSync("V:R:4" , Sync::Line, MakeList("V:R:RB", "V:R:LB"), LM->bold_solid()), S["b:FrontSeam:Vent"].toBool() );
    line(MakeSync("V:R:5" , Sync::Line, MakeList("V:R:LB", "V:R:LT"), LM->thick_dashed()), S["b:FrontSeam:Vent"].toBool() );
    line(MakeSync("NoVent-R", Sync::Line, MakeList("V:R:TT", "V:R:LB"), Layer ), !S["b:FrontSeam:Vent"].toBool() );

    //Vent is at the side seam
    //Left
    line(MakeSync("V:S:L:1" , Sync::Line, MakeList("V:S:L:TT", "V:S:L:LT"), LM->bold_solid()), S["b:SideSeam:Vent"].toBool() );
    line(MakeSync("V:S:L:2" , Sync::Line, MakeList("V:S:L:LT", "V:S:L:RT"), LM->bold_solid()), S["b:SideSeam:Vent"].toBool() );
    line(MakeSync("V:S:L:3" , Sync::Line, MakeList("V:S:L:RT", "V:S:L:RB"), LM->bold_solid()), S["b:SideSeam:Vent"].toBool() );
    line(MakeSync("V:S:L:4" , Sync::Line, MakeList("V:S:L:RB", "V:S:L:LB"), LM->bold_solid()), S["b:SideSeam:Vent"].toBool() );
    line(MakeSync("V:S:L:5" , Sync::Line, MakeList("V:S:L:LB", "V:S:L:LT"), LM->thick_dashed()), S["b:SideSeam:Vent"].toBool() );

    //Right
    line(MakeSync("V:S:R:1" , Sync::Line, MakeList("V:S:R:TT", "V:S:R:RT"), LM->bold_solid()), S["b:SideSeam:Vent"].toBool() );
    line(MakeSync("V:S:R:2" , Sync::Line, MakeList("V:S:R:RT", "V:S:R:LT"), LM->bold_solid()), S["b:SideSeam:Vent"].toBool() );
    line(MakeSync("V:S:R:3" , Sync::Line, MakeList("V:S:R:LT", "V:S:R:LB"), LM->bold_solid()), S["b:SideSeam:Vent"].toBool() );
    line(MakeSync("V:S:R:4" , Sync::Line, MakeList("V:S:R:LB", "V:S:R:RB"), LM->bold_solid()), S["b:SideSeam:Vent"].toBool() );
    line(MakeSync("V:S:R:5" , Sync::Line, MakeList("V:S:R:RB", "V:S:R:RT"), LM->thick_dashed()), S["b:SideSeam:Vent"].toBool() );

    //Narrow
    line(MakeSync("NoVent-S-L", Sync::Line, MakeList("V:S:L:TT", "V:S:L:LB"), LM->bold_solid()),
         ( !S["b:SideSeam:Vent"].toBool() && ( S["Narrow"].toBool() || S["Narrow:Negative"].toBool() ) ) );
    line(MakeSync("NoVent-S-R", Sync::Line, MakeList("V:S:R:TT", "V:S:R:RB"), LM->bold_solid()),
         ( !S["b:SideSeam:Vent"].toBool() && ( S["Narrow"].toBool() || S["Narrow:Negative"].toBool() ) ) );

    spline(MakeSync("S-N1-001", Sync::Spline, MakeList("P9411a", "SG1", "SG0", "P54a"), LM->bold_solid()),
           ( S["Narrow"].toBool() || S["Narrow:Negative"].toBool() ) );
    spline(MakeSync("S-N1-002", Sync::Spline, MakeList("P9412a", "SG2", "SG0", "P54a"), LM->bold_solid()),
           ( S["Narrow"].toBool() || S["Narrow:Negative"].toBool() ) );
    spline(MakeSync("S-N1-003", Sync::Spline, MakeList("P941", "SG3", "SG5", "P9411"), LM->bold_solid()),
           ( S["Narrow"].toBool() || S["Narrow:Negative"].toBool() ) );
    spline(MakeSync("S-N1-004", Sync::Spline, MakeList("P941a", "SG4", "SG6", "P9412"), LM->bold_solid()),
           ( S["Narrow"].toBool() || S["Narrow:Negative"].toBool() ) );

    line(MakeSync("L-N1-002", Sync::Line, MakeList("P941a","P97"), LM->bold_solid()),
         ( S["Narrow"].toBool() || S["Narrow:Negative"].toBool() ) );
    line(MakeSync("L-N1-003", Sync::Line, MakeList("P0","P941"), LM->bold_solid()),
         ( S["Narrow"].toBool() || S["Narrow:Negative"].toBool() ) );
    line(MakeSync("L-N1-004", Sync::Line, MakeList("P94","P54a"), LM->thick_dashed()),
         ( S["Narrow"].toBool() || S["Narrow:Negative"].toBool() ) );
    line(MakeSync("L-N1-005", Sync::Line, MakeList("P941","P941a"), LM->thick_dashed()),
         ( S["Narrow"].toBool() || S["Narrow:Negative"].toBool() ) );
    line(MakeSync("L-N1-006", Sync::Line, MakeList("P54a","P54"), LM->thick_dashed()),
         ( S["Narrow"].toBool() || S["Narrow:Negative"].toBool() ) );


    if ( S["SideSeam"].toBool() )
    {
        Layer = LM->bold_solid();
//        Unicus::console( "Error", "Wrong layer!" );
    }
    else
    {
        Layer = LM->thick_dashed();
//        Unicus::console( "Error", "Right layer!" );
    }


    line(MakeSync("L-N0-001", Sync::Line, MakeList("P94","P54"), Layer ),
         !( S["Narrow"].toBool() || S["Narrow:Negative"].toBool() ) );
    line(MakeSync("L-N0-002", Sync::Line, MakeList("P0","P97"), LM->bold_solid() ),
         !( S["Narrow"].toBool() || S["Narrow:Negative"].toBool() ) );

    text(scene()->trUtf8("Сгиб"), QString("PT1"), 90.0f,  !S["BackSeam"].toBool());
    text(scene()->trUtf8("Сгиб"), QString("PT2"), 90.0f,  !S["FrontSeam"].toBool());

    //Darts: no darts
    spline( MakeSync( "NoDarts",
                      Sync::Spline,
                      MakeList("P41", "P420", "P460", "P47"),
                      LM->bold_solid() ),
                      !(S["FrontDart1"].toBool() ||
                        S["BackDart1"].toBool() ||
                        S["SideDart"].toBool() ) );


    //Darts: side
    S.insert(QString("SideDart"), QVariant(I("SideDart")).toBool());
    DartItem * sd1 = this->dart( MakeSync( "SideDart-001", Sync::Dart,
                                 MakeList( "P54", "SideDart1Left", "SideDart1Right" ),
                                 LM->bold_solid() ), S["SideDart"].toBool() );
    if ( sd1 ) sd1->setKK( 10.0f );
    if ( sd1 ) P["Dialog:ViewCenter"] = P["P54"] + QPointF( 0, sd1->getHeight() / 2.0f );

    //Darts: front
    DartItem * fd1 = this->dart( MakeSync( "FrontDart-001", Sync::Dart,
                                 MakeList( "FrontDart1Position", "FrontDart1Left", "FrontDart1Right" ),
                                 LM->bold_solid() ), S["FrontDart1"].toBool() );
    DartItem * fd2 = this->dart( MakeSync( "FrontDart-002", Sync::Dart,
                                 MakeList( "FrontDart2Position", "FrontDart2Left", "FrontDart2Right" ),
                                 LM->bold_solid() ), S["FrontDart2"].toBool() );
    DartItem * fd3 = this->dart( MakeSync( "FrontDart-003", Sync::Dart,
                                 MakeList( "FrontDart3Position", "FrontDart3Left", "FrontDart3Right" ),
                                 LM->bold_solid() ), S["FrontDart3"].toBool() );
    if ( fd1 ) fd1->setKK( 2.5f );
    if ( fd2 ) fd2->setKK( 2.5f );
    if ( fd3 ) fd3->setKK( 2.5f );


    //Darts: back
    DartItem * bd1 = this->dart( MakeSync( "BackDart-001", Sync::Dart,
                                 MakeList( "BackDart1Position", "BackDart1Left", "BackDart1Right" ),
                                 LM->bold_solid() ), S["BackDart1"].toBool() );
    DartItem * bd2 = this->dart( MakeSync( "BackDart-002", Sync::Dart,
                                 MakeList( "BackDart2Position", "BackDart2Left", "BackDart2Right" ),
                                 LM->bold_solid() ), S["BackDart2"].toBool() );
    DartItem * bd3 = this->dart( MakeSync( "BackDart-003", Sync::Dart,
                                 MakeList( "BackDart3Position", "BackDart3Left", "BackDart3Right" ),
                                 LM->bold_solid() ), S["BackDart3"].toBool() );
    if ( bd1 ) bd1->setKK( 0.0f );
    if ( bd2 ) bd2->setKK( 0.0f );
    if ( bd3 ) bd3->setKK( 0.0f );


    //Darts: connections
    spline( MakeSync("BackDart1ConnectionLeft", Sync::Spline,
                     MakeList("P41", "P-C-001", "BackDart1ConnectionLeft", "BackDart1Left"),
                     LM->bold_solid() ),
            S["BackDart1"].toBool());
    spline( MakeSync("BackDart2ConnectionLeft", Sync::Spline,
                     MakeList("BackDart1Right", "BackDart1ConnectionRight",
                              "BackDart2ConnectionLeft", "BackDart2Left"),
                     LM->bold_solid() ),
            S["BackDart2"].toBool());
    spline( MakeSync("BackDart3ConnectionLeft", Sync::Spline,
                     MakeList("BackDart2Right", "BackDart2ConnectionRight",
                              "BackDart3ConnectionLeft", "BackDart3Left"),
                     LM->bold_solid() ),
            S["BackDart3"].toBool());
    spline( MakeSync("FrontDart1ConnectionRight", Sync::Spline,
                     MakeList("P47", "P-C-002", "FrontDart1ConnectionRight", "FrontDart1Right"),
                     LM->bold_solid() ),
            S["FrontDart1"].toBool());
    spline( MakeSync("FrontDart2ConnectionRight", Sync::Spline,
                     MakeList("FrontDart1Left", "FrontDart1ConnectionLeft",
                              "FrontDart2ConnectionRight", "FrontDart2Right"),
                     LM->bold_solid() ),
            S["FrontDart2"].toBool());
    spline( MakeSync("FrontDart3ConnectionRight", Sync::Spline,
                     MakeList("FrontDart2Left", "FrontDart2ConnectionLeft",
                              "FrontDart3ConnectionRight", "FrontDart3Right"),
                     LM->bold_solid()),
            S["FrontDart3"].toBool());

    //SideDart1:true
    spline( MakeSync("BackDart1ConnectionRight", Sync::Spline,
                     MakeList("BackDart1Right", "BackDart1ConnectionRight",
                              "SideDart1ConnectionLeft", "SideDart1Left"),
                     LM->bold_solid() ),
            (S["BackDart1"].toBool() && !S["BackDart2"].toBool() && S["SideDart"].toBool()));
    spline( MakeSync("BackDart2ConnectionRight", Sync::Spline,
                     MakeList("BackDart2Right", "BackDart2ConnectionRight",
                              "SideDart1ConnectionLeft", "SideDart1Left"),
                     LM->bold_solid() ),
            (S["BackDart2"].toBool() && !S["BackDart3"].toBool() && S["SideDart"].toBool()));
    spline( MakeSync("BackDart3ConnectionRight", Sync::Spline,
                     MakeList("BackDart3Right", "BackDart3ConnectionRight",
                              "SideDart1ConnectionLeft", "SideDart1Left"),
                     LM->bold_solid() ),
            (S["BackDart3"].toBool()  && S["SideDart"].toBool()));

    spline( MakeSync("FrontDart1ConnectionLeft", Sync::Spline,
                     MakeList("FrontDart1Left", "FrontDart1ConnectionLeft",
                              "SideDart1ConnectionRight", "SideDart1Right"),
                     LM->bold_solid() ),
            (S["FrontDart1"].toBool() && !S["FrontDart2"].toBool() && S["SideDart"].toBool()));
    spline( MakeSync("FrontDart2ConnectionLeft", Sync::Spline,
                     MakeList("FrontDart2Left", "FrontDart2ConnectionLeft",
                              "SideDart1ConnectionRight", "SideDart1Right"),
                     LM->bold_solid() ),
            (S["FrontDart2"].toBool() && !S["FrontDart3"].toBool() && S["SideDart"].toBool()));
    spline( MakeSync("FrontDart3ConnectionLeft", Sync::Spline,
                     MakeList("FrontDart3Left", "FrontDart3ConnectionLeft",
                              "SideDart1ConnectionRight", "SideDart1Right"),
                     LM->bold_solid() ),
            (S["FrontDart3"].toBool()  && S["SideDart"].toBool()));

    LM->SetCurrentID(0);
    sign("SideSeam", "P54", true, 0, S["SideDart"].toBool());


    S.insert("FrontCut", QVariant(false));
    S.insert("BackCut", QVariant(false));
    sign("FrontCut", "P-FC-1", false, 0, S["FrontCut"].toBool());
    sign("BackCut", "P-BC-1", false, 0, S["BackCut"].toBool());

    this->scene()->update();
}

QPointF C2DStraightSkirt::FrontDartTopPosition(double width, QPointF SideDartTop, QPointF RightPoint)
{
    double dx = RightPoint.x()-SideDartTop.x();
    double dy = SideDartTop.y()-RightPoint.y();
    double k = width - V("Width")/2;
    return QPointF(-(V("Width")-width), dy*(1-k/dx));
}

QPointF C2DStraightSkirt::BackDartTopPosition(double width, QPointF SideDartTop, QPointF LeftPoint)
{
    double dx = SideDartTop.x()-LeftPoint.x();
    double dy = SideDartTop.y()-LeftPoint.y();
    return QPointF(width, dy*width/dx);
}
