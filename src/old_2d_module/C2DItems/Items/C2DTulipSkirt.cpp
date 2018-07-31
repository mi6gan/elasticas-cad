#include "C2DTulipSkirt.h"

C2DTulipSkirt::C2DTulipSkirt() : C2DItem()
{
    this->setPrefix( "TulipSkirt" );

    this->requiredVariables();

    this->addChildItem( new C2DDefaultBelt( this->prefix( false ) ) );
}

void C2DTulipSkirt::Update()
{
    this->setVariables();
    this->UpdatePoints();
    this->DrawOnWidget();

    C2DItem::Update();
}

void C2DTulipSkirt::requiredVariables()
{
    this->addVariable( C2DVariable::set( "PTx", this->prefix() + "PTx",
                       "Not described", C2DVariable::Unitless, C2DVariable::General ) );
    this->addVariable( C2DVariable::set( "PTy", this->prefix() + "PTy", "Not describedd",
                       C2DVariable::Unitless, C2DVariable::General ) );

    this->addVariable( C2DVariable::set( "T7", "T7", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "T9", "T9", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "T12", "T12", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "T18", "T18", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "T19", "T19", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "T25", "T25", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "T26", "T26", "Not described", C2DVariable::Metrics,
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

    this->addVariable( C2DVariable::set( "K25", "K25", "Not described", C2DVariable::Metrics,
                       C2DVariable::Additional, 0.0f ) );
    this->addVariable( C2DVariable::set( "K26", "K26", "Not described", C2DVariable::Metrics,
                       C2DVariable::Additional, -50.0f ) );

    this->addVariable( C2DVariable::set( "Height", this->prefix() + "Length", "Not described",
                       C2DVariable::Metrics, C2DVariable::General, 60.0f, 10.0f ) );

    this->addVariable( C2DVariable::set( "Kr", this->prefix() + "Kr", "Not described",
                       C2DVariable::Metrics, C2DVariable::General, 1.25f ) );
    this->addVariable( C2DVariable::set( "SideSeam", this->prefix() + "VB", "Not described",
                       C2DVariable::Logical, C2DVariable::Optional, true ) );
    this->addVariable( C2DVariable::set( "SideSeamShift", this->prefix() + "A2", "Not described",
                       C2DVariable::Metrics, C2DVariable::Optional, 1.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "FrontSeam", this->prefix() + "VP", "Not described",
                       C2DVariable::Logical, C2DVariable::Optional, true ) );
    this->addVariable( C2DVariable::set( "BackSeam", this->prefix() + "VZ", "Not described",
                       C2DVariable::Logical, C2DVariable::Optional, true ) );

}

void C2DTulipSkirt::setVariables()
{
    H( "LibVersion" ) = 0.9f;

    H( "Material" ) = 0.0f;

    // Could be rounded up to 2 digits
    H( "Kmin" ) = ( D( "T18" ) + D( "P18" ) ) / ( D( "T19" ) + D( "P19" ) );

    qDebug() << "Kmin: " << LD( "Kmin" );

    H( "HeightRight" ) = D( "Height" ) + ( D( "T26" ) - D( "T7" ) - D( "K26" ) );
    H( "HeightCenter" ) = D( "Height" ) + ( D( "T25" ) - D( "T7" ) - D( "K25" ) );
    H( "HeightBottom" ) = D( "Height" ) - D( "T86" );

    H( "Width" ) = D( "T19" ) / 2.0f + D( "P19" );

    H( "HiplineWidth" ) = ( 0.5 * ( D( "T19" ) - D( "T18" ) ) + ( D( "P19" ) - D( "P18" ) ) );

    //Kr == 0.86
    H( "SideDart1Height" ) = QVariant( D( "T7" ) - D( "T86" ) );

    //Kr > 0.86
    H( "TopDeltaK" ) = QVariant( 6.0f );
    H( "TopDelta"  ) = D( "T25" ) - D( "T7" ) - LD( "TopDeltaK" ); // = T25 - T7 - 10.5f;

    qDebug() << "TopDelta: " << LD( "TopDelta" );

    /* Darts from StraightSkirt */

    H( "Sb" ) = 0.32f * LD( "HiplineWidth" );
    H( "Ss" ) = 0.50f * LD( "HiplineWidth" );
    H( "Sf" ) = 0.18f * LD( "HiplineWidth" );

    H( "Hb" ) = 0.8f * LD( "HeightLeft" ) - 10.0f;
    H( "Hs" ) = LD( "HeightCenter" ) - LD( "HeightBottom" );
    H( "Hf" ) = 0.5f * LD( "HeightLeft" ) - 10.0f;

    H( "Wb" ) = 0.4f * LD( "Width" ) / 2.0f;
    H( "Ws" ) = LD( "Width" ) - LD( "SideSeamShift" );
    H( "Wf" ) = LD( "Width" ) - ( LD( "T46" ) / 2.0f + 3.0f );

}

void C2DTulipSkirt::UpdatePoints()
{
    P["B:P0"] = QPointF( 0.0f , 0.0f );

    P["B:Belt"] = P["P0"] + QPointF( D( "Height" ), 0.0f );

    this->children().at( 0 )->setPos( P["B:Belt"] );

    P["View:Center"] = P["B:P0"] + QPointF( LD( "Width" ) / 2.0f - D( "SideSeamShift" ),
                                            D( "Height" ) / 2.0f );

    //Main circuit
    P["B:P91"]  = P["B:P0"];
    P["B:P94"]  = P["B:P0"] + QPointF( ( LD( "Width" ) / 2.0f ) - D( "SideSeamShift" ), 0.0f );
    P["B:P97"]  = P["B:P0"] + QPointF( LD( "Width" ), 0.0f );
    P["B:P51"]  = P["B:P0"] + QPointF( 0.0f, D( "Height" ) - ( D( "T7" ) - D( "T86" ) ) );
    P["B:P54"]  = P["B:P0"] + QPointF( ( LD( "Width" ) / 2.0f ) - D( "SideSeamShift" ),
                                         D( "Height" ) - ( D( "T7" ) - D( "T86" ) ) );
    P["B:P57"]  = P["B:P0"] + QPointF( LD("Width"), D("Height") - ( D("T7") - D("T86") ) );
    P["B:P41"]  = P["B:P0"] + QPointF( 0.0f, D("Height") );
    P["B:P42"]  = P["B:P0"] + QPointF( 0.1f * LD("Width"), D("Height") );
    P["B:P47a"] = P["B:P0"] + QPointF( LD("Width"), D("Height") );
    P["B:P46a"] = P["B:P0"] + QPointF( 0.9f * LD("Width"), D("Height") );
    P["B:P47"]  = P["B:P0"] + QPointF( LD("Width"), LD("HeightRight") );

    P["V:P420"] = P["B:P0"] + QPointF( ( LD( "Width" ) / 2.0f ) - D( "SideSeamShift" ),
                                       D( "Height" ) + LD( "TopDelta" ) );

    /* Darts */

        QLineF dartline;

        dartline = QLineF( P[ "B:P44" ], P[ "B:P41" ] );

        P[ "B:BD:P0" ] = P[ "P0" ] + QPointF( D( "Wb"), P[ "B:P41" ].y() +
                                              dartline.dy() * D( "Wb" ) / dartline.dx() );
        P[ "B:BD:PL" ] = P[ "B:BD:P0" ] + QPointF( - D( "Sb" ) / 2.0f, 0.0f );
        P[ "B:BD:PR" ] = P[ "B:BD:P0" ] + QPointF(   D( "Sb" ) / 2.0f, 0.0f );
        P[ "B:BD:PB" ] = P[ "B:BD:P0" ] + QPointF( 0.0f, - D( "Hb" ) );

        P[ "B:SD:P0" ] = P[ "B:P44" ];
        P[ "B:SD:PL" ] = P[ "B:SD:P0" ] + QPointF( - D( "Ss" ) / 2.0f, 0.0f );
        P[ "B:SD:PR" ] = P[ "B:SD:P0" ] + QPointF(   D( "Ss" ) / 2.0f, 0.0f );
        P[ "B:SD:PB" ] = P[ "B:SD:P0" ] + QPointF( 0.0f, - D( "Hs" ) );

        P[ "C:SD:P0" ] = P[ "B:P44" ];
        P[ "C:SD:PL" ] = P[ "C:SD:P0" ] + QPointF( - D( "Ssl" ) / 2.0f, 0.0f );
        P[ "C:SD:PR" ] = P[ "C:SD:P0" ] + QPointF(   D( "Ssr" ) / 2.0f, 0.0f );
        P[ "C:SD:PB" ] = P[ "C:SD:P0" ] + QPointF( 0.0f, - D( "Hcs" )  );

        dartline = QLineF( P[ "B:P44" ], P[ "B:P47" ] );

        P[ "B:FD:P0" ] = P[ "P0" ] + QPointF( D( "Wf"), P[ "B:P44" ].y() +
                                              ( dartline.dy() / dartline.dx() ) *
                                              ( D( "Wf" ) - D( "Width" ) / 2.0f ) );
        P[ "B:FD:PL" ] = P[ "B:FD:P0" ] + QPointF( - D( "Sf" ) / 2.0f, 0.0f );
        P[ "B:FD:PR" ] = P[ "B:FD:P0" ] + QPointF(   D( "Sf" ) / 2.0f, 0.0f );
        P[ "B:FD:PB" ] = P[ "B:FD:P0" ] + QPointF( 0.0f, - D( "Hf" ) );

    /*/ Darts /*/

    /*/ Base points /*/



    if ( D( "Kr" ) == 0.86f )
    {
        H( "Kr=0.86" ) = QVariant( true  );
        H( "Kr>0.86" ) = QVariant( false );
        H( "Kr=1.00" ) = QVariant( false );
        H( "Kr>1.00" ) = QVariant( false );

        H( "SideDart1Spread" ) = QVariant( 0.5f * LD( "HiplineWidth" ) );

        P["SideDart1TopPosition"]     = P["B:P94"]                + QPointF( 0.0f, LD( "HeightCenter" ) );
        P["SideDart1Position"]        = P["SideDart1TopPosition"] + QPointF( 0.0f, -LD( "SideDart1Height" ) );
        P["SideDart1SplineBottom"]    = P["SideDart1Position"]    + QPointF( 0.0f, 10.0f );
        P["SideDart1Right"]           = P["SideDart1TopPosition"] + QPointF( D( "SideDart1Spread" ) / 2.0f, 0.0f );
        P["SideDart1SplineRight"]     = Unicus::rLine( QLineF( P["SideDart1Right"], P["SideDart1Position"] ),
                                                       P["SideDart1Right"], -10.0f ).pointAt( 0.1f );
        P["SideDart1Left"]            = P["SideDart1TopPosition"] + QPointF( -D("SideDart1Spread") / 2.0f, 0.0f );
        P["SideDart1SplineLeft"]      = Unicus::rLine( QLineF( P["SideDart1Left"], P["SideDart1Position"] ), P["SideDart1Left"], 10.0f )
                                        .pointAt( 0.1f );
        P["SideDart1ConnectionLeft"]  = Unicus::rPoint( P["SideDart1SplineLeft"], P["SideDart1Left"], -90.0f );
        P["SideDart1ConnectionRight"] = Unicus::rPoint( P["SideDart1SplineRight"], P["SideDart1Right"], 90.0f );
    }

    if ( ( D( "Kr" ) > 0.86f ) && ( D( "Kr" ) < 1.00f ) )
    {
        H( "Kr=0.86" ) = QVariant( false );
        H( "Kr>0.86" ) = QVariant( true  );
        H( "Kr=1.00" ) = QVariant( false );
        H( "Kr>1.00" ) = QVariant( false );

        H( "SideDart1Spread" ) = QVariant( LD( "Width" ) * ( 1.0f - D( "Kr" ) ) );

        P["SideDart1TopPosition"]     = P["B:P94"]                + QPointF( 0.0f, LD( "HeightCenter" ) );
        P["SideDart1Position"]        = P["SideDart1TopPosition"] + QPointF( 0.0f, -LD( "SideDart1Height" ) );
        P["SideDart1SplineBottom"]    = P["SideDart1Position"]    + QPointF( 0.0f, 10.0f );
        P["SideDart1Right"]           = P["B:P47a"] + this->rightTop( D( "SideDart1Spread" ) / 2.0f );
        P["SideDart1SplineRight"]     = Unicus::rLine( QLineF( P["SideDart1Right"], P["SideDart1Position"] ),
                                                       P["SideDart1Right"], -10.0f ).pointAt( 0.1f );
        P["SideDart1Left"]            = P["B:P41"] + this->leftTop( D( "SideDart1Spread" ) / 2.0f );
        P["SideDart1SplineLeft"]      = Unicus::rLine( QLineF( P["SideDart1Left"], P["SideDart1Position"] ), P["SideDart1Left"], 10.0f )
                                        .pointAt( 0.1f );
        P["SideDart1ConnectionLeft"]  = Unicus::rPoint(P["SideDart1SplineLeft"],P["SideDart1Left"], -90);
        P["SideDart1ConnectionRight"] = Unicus::rPoint(P["SideDart1SplineRight"],P["SideDart1Right"], 90);

    }

    if ( D( "Kr" ) == 1.00f )
    {
        H( "Kr=0.86" ) = QVariant( false );
        H( "Kr>0.86" ) = QVariant( false );
        H( "Kr=1.00" ) = QVariant( true  );
        H( "Kr>1.00" ) = QVariant( false );
    }

    if ( ( D( "Kr" ) > 1.00f ) && ( D( "Kr" ) <= 2.25f ) )
    {
        H( "Kr=0.86" ) = QVariant( false );
        H( "Kr>0.86" ) = QVariant( false );
        H( "Kr=1.00" ) = QVariant( false );
        H( "Kr>1.00" ) = QVariant( true  );

        double left_half_width  = ( LD("Width") / 2.0f ) - D("SideSeamShift");
        double right_half_width = ( LD("Width") / 2.0f ) + D("SideSeamShift");

        double left_delta = ( D( "Kr" ) - 1.0f ) * left_half_width / 3.0f;
        double left_angle = left_delta * 180.0f / ( D( "Height" ) * M_PI );

        double right_delta = ( D( "Kr" ) - 1.0f ) * right_half_width / 3.0f;
        double right_angle = right_delta * 180.0f / ( D( "Height" ) * M_PI );

        P["L:S0L"] = P["B:P91"];
        P["L:S0R"] = P["L:S0L"] + QPointF( left_half_width / 4.0f, 0.0f );
        P["L:P0L"] = P["B:P41"];
        P["L:P0R"] = P["L:P0L"] + QPointF( left_half_width / 4.0f,
                                           this->leftTop( left_half_width * 1.0f / 4.0f ).y() );

        P["L:S1L"] = P["L:S0R"];
        P["L:S1R"] = Unicus::rPoint( P["L:S1L"] + QPointF( left_half_width / 4.0f, 0.0f ),
                                                           P["L:S1L"], -left_angle );

        P["L:P1L"] = Unicus::rPoint( P["L:S1L"] + QPointF( 0.0f,
                                    D( "Height" ) + this->leftTop( left_half_width * 1.0f / 4.0f ).y() ),
                                    P["L:S1L"], -left_angle );
        P["L:P1R"] = Unicus::rPoint( P["L:S1R"] + QPointF( 0.0f,
                                    D( "Height" ) + this->leftTop( left_half_width * 2.0f / 4.0f ).y() ),
                                    P["L:S1R"], -left_angle );

        P["L:S2L"] = P["L:S1R"];
        P["L:S2R"] = Unicus::rPoint( P["L:S2L"] + QPointF( left_half_width / 4.0f, 0.0f ),
                                                           P["L:S2L"], -left_angle * 2.0f );

        P["L:P2L"] = Unicus::rPoint( P["L:S2L"] + QPointF( 0.0f,
                                    D( "Height" ) + this->leftTop( left_half_width * 2.0f / 4.0f ).y() ),
                                    P["L:S2L"], -left_angle * 2.0f );
        P["L:P2R"] = Unicus::rPoint( P["L:S2R"] + QPointF( 0.0f,
                                    D( "Height" ) + this->leftTop( left_half_width * 3.0f / 4.0f ).y() ),
                                    P["L:S2R"], -left_angle * 2.0f );

        P["L:S3L"] = P["L:S2R"];
        P["L:S3R"] = Unicus::rPoint( P["L:S3L"] + QPointF( left_half_width / 4.0f, 0.0f ),
                                                           P["L:S3L"], -left_angle * 3.0f );

        P["L:P3L"] = Unicus::rPoint( P["L:S3L"] + QPointF( 0.0f,
                                    D( "Height" ) + this->leftTop( left_half_width * 3.0f / 4.0f ).y() ),
                                    P["L:S3L"], -left_angle * 3.0f );
        P["L:P3R"] = Unicus::rPoint( P["L:S3R"] + QPointF( 0.0f,
                                    D( "Height" ) + this->leftTop( left_half_width * 4.0f / 4.0f ).y() ),
                                    P["L:S3R"], -left_angle * 3.0f );


        P["R:S0R"] = P["B:P97"];
        P["R:S0L"] = P["R:S0R"] + QPointF( -right_half_width / 4.0f, 0.0f );
        P["R:P0R"] = P["B:P47a"];
        P["R:P0L"] = P["R:P0R"] + QPointF( -right_half_width / 4.0f,
                                           this->rightTop( right_half_width * 1.0f / 4.0f ).y() );

        P["R:S1R"] = P["R:S0L"];
        P["R:S1L"] = Unicus::rPoint( P["R:S1R"] + QPointF( -right_half_width / 4.0f, 0.0f ),
                                                           P["R:S1R"], right_angle );

        P["R:P1R"] = Unicus::rPoint( P["R:S1R"] + QPointF( 0.0f,
                                    D( "Height" ) + this->rightTop( right_half_width * 1.0f / 4.0f ).y() ),
                                    P["R:S1R"], right_angle );
        P["R:P1L"] = Unicus::rPoint( P["R:S1L"] + QPointF( 0.0f,
                                    D( "Height" ) + this->rightTop( right_half_width * 2.0f / 4.0f ).y() ),
                                    P["R:S1L"], right_angle );

        P["R:S2R"] = P["R:S1L"];
        P["R:S2L"] = Unicus::rPoint( P["R:S2R"] + QPointF( -right_half_width / 4.0f, 0.0f ),
                                                           P["R:S2R"], right_angle * 2.0f );

        P["R:P2R"] = Unicus::rPoint( P["R:S2R"] + QPointF( 0.0f,
                                    D( "Height" ) + this->rightTop( right_half_width * 2.0f / 4.0f ).y() ),
                                    P["R:S2R"], right_angle * 2.0f );
        P["R:P2L"] = Unicus::rPoint( P["R:S2L"] + QPointF( 0.0f,
                                    D( "Height" ) + this->rightTop( right_half_width * 3.0f / 4.0f ).y() ),
                                    P["R:S2L"], right_angle * 2.0f );

        P["R:S3R"] = P["R:S2L"];
        P["R:S3L"] = Unicus::rPoint( P["R:S3R"] + QPointF( -right_half_width / 4.0f, 0.0f ),
                                                           P["R:S3R"], right_angle * 3.0f );

        P["R:P3R"] = Unicus::rPoint( P["R:S3R"] + QPointF( 0.0f,
                                    D( "Height" ) + this->rightTop( right_half_width * 3.0f / 4.0f ).y() ),
                                    P["R:S3R"], right_angle * 3.0f );
        P["R:P3L"] = Unicus::rPoint( P["R:S3L"] + QPointF( 0.0f,
                                    D( "Height" ) + this->rightTop( right_half_width * 4.0f / 4.0f ).y() ),
                                    P["R:S3L"], right_angle * 3.0f );


        P["R:SS"] = QLineF( P["R:P3L"], P["R:S3L"] )
                    .pointAt( ( QLineF( P["R:P3L"], P["R:S3L"] ).length() -
                                ( D("T7") - D("T86") ) - LD( "TopDelta" ) )
                              / QLineF( P["R:P3L"], P["R:S3L"] ).length() );
        P["L:SS"] = QLineF( P["L:P3R"], P["L:S3R"] )
                    .pointAt( ( QLineF( P["L:P3R"], P["L:S3R"] ).length() -
                                ( D("T7") - D("T86") ) - LD( "TopDelta" ) )
                              / QLineF( P["L:P3R"], P["L:S3R"] ).length() );


        // Arcs
        P[ "L:C1" ] = QPointF( 0.0f, 0.0f );
        P[ "L:C2" ] = QPointF( 0.0f, 0.0f );
        P[ "L:C3" ] = QPointF( 0.0f, 0.0f );
        P[ "R:C1" ] = QPointF( 0.0f, 0.0f );
        P[ "R:C2" ] = QPointF( 0.0f, 0.0f );
        P[ "R:C3" ] = QPointF( 0.0f, 0.0f );

        QLineF( P[ "L:S0L" ], P[ "L:P0L" ] )
                .intersect( QLineF( P[ "L:S3R" ], P[ "L:P3R" ] ), &P[ "L:C1" ] );

        qDebug() << "L:C1 : " << P[ "L:C1" ];

        H( "LeftTopArcRadius" ) = QLineF( P[ "L:P3R" ], P[ "L:C1" ] ).length();

        qDebug() << "LeftTopArcRadius : " << LD( "LeftTopArcRadius" );

        P[ "L:C1" ] = Unicus::CircCirc( P[ "L:P0L" ], LD( "LeftTopArcRadius" ),
                                        P[ "L:P3R" ], LD( "LeftTopArcRadius" ), true );

        qDebug() << "L:C1 : " << P[ "L:C1" ];

        QLineF( P[ "R:S0R" ], P[ "R:P0R" ] )
                .intersect( QLineF( P[ "R:S3L" ], P[ "R:P3L" ] ), &P[ "R:C1" ] );



        H( "LeftSignAngle"  ) = QVariant( Unicus::angleOx( QLineF( P["L:S3R"], P["L:P3R"] ) ) );
        H( "RightSignAngle" ) = QVariant( Unicus::angleOx( QLineF( P["R:S3L"], P["R:P3L"] ) ) );

        qDebug() << "LeftSignAngle: "
                << QLineF( P["L:S5"], P["L:P5"] )
                << Unicus::angleOx( QLineF( P["L:S5"], P["L:P5"] ) )
                << D( "LeftSignAngle" );


        qDebug() << "RightSignAngle: "
                << QLineF( P["R:S5"], P["R:P5"] )
                << Unicus::angleOx( QLineF( P["R:S5"], P["R:P5"] ) )
                << D( "RightSignAngle" );
    }

    if ( D( "Kr" ) > 2.25f )
    {
        H( "Kr=0.86" ) = QVariant( false );
        H( "Kr>0.86" ) = QVariant( false );
        H( "Kr=1.00" ) = QVariant( false );
        H( "Kr>1.00" ) = QVariant( false );
    }

}

void C2DTulipSkirt::DrawOnWidget()
{
    qDebug() << "Kr=0.86: " << LB( "Kr=0.86" );
    qDebug() << "Kr>0.86: " << LB( "Kr>0.86" );
    qDebug() << "Kr=1.00: " << LB( "Kr=1.00" );
    qDebug() << "Kr>1.00: " << LB( "Kr>1.00" );

    qDebug() << "Type: " << C2DSync::Line;

//    point( Sync( attr( SYNC_NAME, "L:C1" ),
//                 attr( SYNC_TYPE, C2DSync::Point ),
//                 attr( SYNC_LIST, MakeList( "L:C1" ) ),
//                 LM->bold_solid() ),
//           LB( "Kr>1.00" ) );

//    circle( Sync( attr( SYNC_NAME, "Circle::1" ),
//                  attr( SYNC_TYPE, C2DSync::Circle ),
//                  attr( SYNC_LIST, MakeList( "L:P0L" ) ),
//                  LM->bold_solid(),
//                  attr( SYNC_RADIUS, LD( "LeftTopArcRadius" ) )),
//            LB( "Kr>1.00" ) );

//    circle( Sync( attr( SYNC_NAME, "Circle::2" ),
//                  attr( SYNC_TYPE, C2DSync::Circle ),
//                  attr( SYNC_LIST, MakeList( "L:P3R" ) ),
//                  LM->bold_solid(),
//                  attr( SYNC_RADIUS, LD( "LeftTopArcRadius" ) )),
//            LB( "Kr>1.00" ) );


//    //Base shape: lines
    line( Sync( attr( SYNC_NAME, "SS:B-001" ),
                attr( SYNC_TYPE, C2DSync::Line ),
                attr( SYNC_LIST, MakeList( "B:P51", "B:P54" ) ),
                LM->thick_dashed() ), true );
    line( Sync( attr( SYNC_NAME, "SS:B-002" ),
                attr( SYNC_TYPE, C2DSync::Line ),
                attr( SYNC_LIST, MakeList( "B:P41", "B:P47a" ) ),
                LM->thick_dashed() ), true );
    line( Sync( attr( SYNC_NAME, "SS:B-003" ),
                attr( SYNC_TYPE, C2DSync::Line ),
                attr( SYNC_LIST, MakeList( "B:P54", "B:P57" ) ),
                LM->thick_dashed() ), true );
    line( Sync( attr( SYNC_NAME, "SS:B-004" ),
                attr( SYNC_TYPE, C2DSync::Line ),
                attr( SYNC_LIST, MakeList( "B:P91", "B:P94" ) ),
                LM->bold_solid() ), true );
    line( Sync( attr( SYNC_NAME, "SS:B-005" ),
                attr( SYNC_TYPE, C2DSync::Line ),
                attr( SYNC_LIST, MakeList( "B:P94", "B:P97" ) ),
                LM->bold_solid() ), true );
    line( Sync( attr( SYNC_NAME, "SS:B:B-001" ),
                attr( SYNC_TYPE, C2DSync::Line ),
                attr( SYNC_LIST, MakeList( "B:P41", "B:P51" ) ),
                LM->bold_solid() ), true );
    line( Sync( attr( SYNC_NAME, "SS:B:B-002" ),
                attr( SYNC_TYPE, C2DSync::Line ),
                attr( SYNC_LIST, MakeList( "B:P51", "B:P91" ) ),
                LM->bold_solid() ), true );
    line( Sync( attr( SYNC_NAME, "SS:B:B-003" ),
                attr( SYNC_TYPE, C2DSync::Line ),
                attr( SYNC_LIST, MakeList( "B:P47a", "B:P57" ) ),
                LM->bold_solid() ), true );
    line( Sync( attr( SYNC_NAME, "SS:B:B-004" ),
                attr( SYNC_TYPE, C2DSync::Line ),
                attr( SYNC_LIST, MakeList( "B:P57", "B:P97" ) ),
                LM->bold_solid() ), true );

    DartItem * bd = this->dart( Sync( attr( SYNC_NAME, "D:BDB-BDL-BDR" ),
                                      attr( SYNC_TYPE, C2DSync::Dart ),
                                      attr( SYNC_LIST, MakeList( "B:BD:PB", "B:BD:PL", "B:BD:PR" ) ),
                                      LM->thick_solid() ), true );

    if ( bd )
    {
        bd->setKK( 0.0f );
        P[ "B:BD:CL" ] = bd->connectLeft();
        P[ "B:BD:CR" ] = bd->connectRight();
    }

    DartItem * sd = this->dart( Sync( attr( SYNC_NAME, "D:SDB-SDL-SDR" ),
                                      attr( SYNC_TYPE, C2DSync::Dart ),
                                      attr( SYNC_LIST, MakeList( "B:SD:PB", "B:SD:PL", "B:SD:PR" ) ),
                                      LM->thick_solid() ), true );

    if ( sd )
    {
        sd->setKK( 10.0f );
        P[ "B:SD:CL" ] = sd->connectLeft();
        P[ "B:SD:CR" ] = sd->connectRight();
    }

    DartItem * fd = this->dart( Sync( attr( SYNC_NAME, "D:FDB-FDL-FDR" ),
                                      attr( SYNC_TYPE, C2DSync::Dart ),
                                      attr( SYNC_LIST, MakeList( "B:FD:PB", "B:FD:PL", "B:FD:PR" ) ),
                                      LM->thick_solid() ), true );

    if ( fd )
    {
        fd->setKK( 2.5f );
        P[ "B:FD:CL" ] = fd->connectLeft();
        P[ "B:FD:CR" ] = fd->connectRight();
    }


//    this->spline( Sync( attr( SYNC_NAME, "S:P41-BDL" ),
//                        attr( SYNC_TYPE, C2DSync::Spline ),
//                        attr( SYNC_LIST, MakeList( "B:P41", "B:P410", "B:BD:CL", "B:BD:PL" ) ),
//                        LM->thick_dashed() ), true );

//    this->spline( Sync( attr( SYNC_NAME, "S:BDR-SDL" ),
//                        attr( SYNC_TYPE, C2DSync::Spline ),
//                        attr( SYNC_LIST, MakeList( "B:BD:PR", "B:BD:CR", "B:SD:CL", "B:SD:PL" ) ),
//                        LM->thick_dashed() ), true );

//    this->spline( Sync( attr( SYNC_NAME, "S:SDR-FDL" ),
//                        attr( SYNC_TYPE, C2DSync::Spline ),
//                        attr( SYNC_LIST, MakeList( "B:SD:PR", "B:SD:CR", "B:FD:CL", "B:FD:PL" ) ),
//                        LM->thick_dashed() ), true );

//    this->spline( Sync( attr( SYNC_NAME, "S:FDR-P47" ),
//                        attr( SYNC_TYPE, C2DSync::Spline ),
//                        attr( SYNC_LIST, MakeList( "B:FD:PR", "B:FD:CR", "B:P470", "B:P47" ) ),
//                        LM->thick_dashed() ), true );

    line( Sync( attr( SYNC_NAME, "SS:B:B-005" ),
                attr( SYNC_TYPE, C2DSync::Line ),
                attr( SYNC_LIST, MakeList( "B:P54", "B:P94" ) ),
                LM->bold_solid() ), ( LB( "Kr=0.86" ) || LB( "Kr>0.86" ) || LB( "Kr=1.00" ) ) );

    spline( Sync( attr( SYNC_NAME, "SSSS:B:B-000" ),
                  attr( SYNC_TYPE, C2DSync::Spline ),
                  attr( SYNC_LIST, MakeList( "B:P41", "B:P42", "SideDart1ConnectionLeft", "SideDart1Left" ) ),
            LM->bold_solid() ), ( LB( "Kr=0.86" ) || LB( "Kr>0.86" ) ) );

    spline( Sync( attr( SYNC_NAME, "SSSS:B:B-001" ),
                  attr( SYNC_TYPE, C2DSync::Spline ),
                  attr( SYNC_LIST, MakeList( "SideDart1Right", "SideDart1ConnectionRight", "B:P46a", "B:P47a" ) ),
                  LM->bold_solid() ), ( LB( "Kr=0.86" ) || LB( "Kr>0.86" ) ) );

    line( Sync( attr( SYNC_NAME, "VV:B:B-008" ),
                attr( SYNC_TYPE, C2DSync::Line ),
                attr( SYNC_LIST, MakeList( "V:P420", "B:P54" ) ),
                LM->bold_solid() ), LB( "Kr=1.00" ) );

    line( Sync( attr( SYNC_NAME, "VV:B:B-002" ),
                attr( SYNC_TYPE, C2DSync::Line ),
                attr( SYNC_LIST, MakeList( "B:P41", "V:P420" ) ),
                LM->bold_solid() ), LB( "Kr=1.00" ) );

    line( Sync( attr( SYNC_NAME, "VV:B:B-003" ),
                attr( SYNC_TYPE, C2DSync::Line ),
                attr( SYNC_LIST, MakeList( "V:P420", "B:P47a" ) ),
                LM->bold_solid() ), LB( "Kr=1.00" ) );

    // K > 1.0f
    for ( int it = 0; it < 4; it++ )
    {
        // Left
        line( Sync( attr( SYNC_NAME, QString( "L-PLS%1L-PLS%1R" ).arg( it ) ),
                    attr( SYNC_TYPE, C2DSync::Line ),
                    attr( SYNC_LIST, MakeList( QString( "L:S%1L" ).arg( it ),
                                               QString( "L:S%1R" ).arg( it ) ) ),
                    LM->thick_solid() ), LB( "Kr>1.00" ) );

        line( Sync( attr( SYNC_NAME, QString( "L-PLP%1L-PLP%1R" ).arg( it ) ),
                    attr( SYNC_TYPE, C2DSync::Line ),
                    attr( SYNC_LIST, MakeList( QString( "L:P%1L" ).arg( it ),
                                               QString( "L:P%1R" ).arg( it ) ) ),
                    LM->thick_solid() ), LB( "Kr>1.00" ) );

        line( Sync( attr( SYNC_NAME, QString( "L-PLS%1L-PLP%1L" ).arg( it ) ),
                    attr( SYNC_TYPE, C2DSync::Line ),
                    attr( SYNC_LIST, MakeList( QString( "L:S%1L" ).arg( it ),
                                               QString( "L:P%2L" ).arg( it ) ) ),
                    LM->thick_solid() ), LB( "Kr>1.00" ) );

        line( Sync( attr( SYNC_NAME, QString( "L-PLS%1R-PLP%1R" ).arg( it ) ),
                    attr( SYNC_TYPE, C2DSync::Line ),
                    attr( SYNC_LIST, MakeList( QString( "L:S%1R" ).arg( it ),
                                               QString( "L:P%1R" ).arg( it ) ) ),
                    LM->thick_solid() ), LB( "Kr>1.00" ) );

        // Right


        line( Sync( attr( SYNC_NAME, QString( "L-PRS%1L-PRS%1R" ).arg( it ) ),
                    attr( SYNC_TYPE, C2DSync::Line ),
                    attr( SYNC_LIST, MakeList( QString( "R:S%1L" ).arg( it ),
                                               QString( "R:S%1R" ).arg( it ) ) ),
                    LM->thick_solid() ), LB( "Kr>1.00" ) );

        line( Sync( attr( SYNC_NAME, QString( "L-PRP%1L-PRP%1R" ).arg( it ) ),
                    attr( SYNC_TYPE, C2DSync::Line ),
                    attr( SYNC_LIST, MakeList( QString( "R:P%1L" ).arg( it ),
                                               QString( "R:P%1R" ).arg( it ) ) ),
                    LM->thick_solid() ), LB( "Kr>1.00" ) );

        line( Sync( attr( SYNC_NAME, QString( "L-PRS%1L-PRP%1L" ).arg( it ) ),
                    attr( SYNC_TYPE, C2DSync::Line ),
                    attr( SYNC_LIST, MakeList( QString( "R:S%1L" ).arg( it ),
                                               QString( "R:P%2L" ).arg( it ) ) ),
                    LM->thick_solid() ), LB( "Kr>1.00" ) );

        line( Sync( attr( SYNC_NAME, QString( "L-PRS%1R-PRP%1R" ).arg( it ) ),
                    attr( SYNC_TYPE, C2DSync::Line ),
                    attr( SYNC_LIST, MakeList( QString( "R:S%1R" ).arg( it ),
                                               QString( "R:P%1R" ).arg( it ) ) ),
                    LM->thick_solid() ), LB( "Kr>1.00" ) );
    }

//    arc( Sync( attr( SYNC_NAME, "A:TL" ),
//                  attr( SYNC_TYPE, C2DSync::Arc ),
//                  attr( SYNC_LIST, MakeList( "L:C1", "L:P0L", "L:P3R" ) ),
//                  LM->bold_solid() ),
//            LB( "Kr>1.00" ) );

    sign( Sync( attr( SYNC_NAME, "Sign1" ),
                attr( SYNC_TYPE, C2DSync::Sign ),
                attr( SYNC_LIST, MakeList( "B:P54" ) ),
                LM->bold_solid(),
                attr( SYNC_SIGN_DUAL, true ),
                attr( SYNC_SIGN_ANGLE, 0.0f ) ),
          ( LB( "Kr=0.86" ) || LB( "Kr>0.86" ) || LB( "Kr=1.00" ) ) );

    /*
    sign( Sync( attr( SYNC_NAME, "Sign2" ),
                attr( SYNC_TYPE, C2DSync::Sign ),
                attr( SYNC_LIST, MakeList( "L:SS" ) ),
                LM->bold_solid(),
                attr( SYNC_SIGN_DUAL, false ),
                attr( SYNC_SIGN_ANGLE, LD( "LeftSignAngle" ) + 90.0f ) ),
          LB( "Kr>1.00" ) );

    sign( Sync( attr( SYNC_NAME, "Sign3" ),
                attr( SYNC_TYPE, C2DSync::Sign ),
                attr( SYNC_LIST, MakeList( "R:SS" ) ),
                LM->bold_solid(),
                attr( SYNC_SIGN_DUAL, false ),
                attr( SYNC_SIGN_ANGLE, LD( "RightSignAngle" ) - 90.0f ) ),
          LB( "Kr>1.00" ) );
*/

}

QPointF C2DTulipSkirt::leftTop( double half_spread )
{
    return QPointF( half_spread,
                    LD( "TopDelta" ) * half_spread / ( LD("Width") / 2.0f - D( "SideSeamShift" ) ) );
}

QPointF C2DTulipSkirt::rightTop( double half_spread )
{
    return QPointF( LD( "Width" ) - half_spread,
                    LD( "TopDelta" ) * half_spread / ( LD( "Width" ) / 2.0f + D( "SideSeamShift" ) ) );
}
