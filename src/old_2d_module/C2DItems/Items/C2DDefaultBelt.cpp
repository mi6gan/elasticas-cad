#include "C2DDefaultBelt.h"

C2DDefaultBelt::C2DDefaultBelt( const QString & prefix )
    : C2DItem()
{
    this->setPrefix( prefix );

    this->requiredVariables();
}

void C2DDefaultBelt::Update()
{
    this->setVariables();
    this->UpdatePoints();
    this->DrawOnWidget();
}

void C2DDefaultBelt::requiredVariables()
{

    this->addVariable( C2DVariable::set( "Belt:Type", this->prefix() + "BeltNum",
                       "Not described", C2DVariable::Unitless, C2DVariable::General ) );

    this->addVariable( C2DVariable::set( "Belt:Width", this->prefix() + "BeltWidth",
                       "Not described", C2DVariable::Metrics, C2DVariable::General, 50.0f, 10.0f ) );

    this->addVariable( C2DVariable::set( "Belt:Clasp", this->prefix() + "Clasp",
                       "Not described", C2DVariable::Unitless, C2DVariable::General ) );

    this->addVariable( C2DVariable::set( "Belt:Clasp:Position", this->prefix() + "ClaspPositionNum",
                       "Not described", C2DVariable::Unitless, C2DVariable::General ) );

    this->addVariable( C2DVariable::set( "Belt:ZipperUntilEnd", this->prefix() + "ZipperAtBeltEnd",
                       "Not described", C2DVariable::Unitless, C2DVariable::General ) );

    this->addVariable( C2DVariable::set( "Belt:Ledge:Width", this->prefix() + "BeltLedgeWidth",
                       "Not described", C2DVariable::Metrics, C2DVariable::General, 160.0f, 10.0f ) );

    this->addVariable( C2DVariable::set( "Belt:Zipper:Length", this->prefix() + "BeltZipperLength",
                       "Not described", C2DVariable::Metrics, C2DVariable::General, 160.0f, 10.0f ) );

    this->addVariable( C2DVariable::set( "Belt:Clasp:Position", this->prefix() + "ClaspPosition",
                       "Not described", C2DVariable::Unitless, C2DVariable::General ) );

    //  ************************************************************************************ //

    this->addVariable( C2DVariable::set( "T18", "T18", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 10.0f ) );

    this->addVariable( C2DVariable::set( "T19", "T19", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 10.0f ) );

    this->addVariable( C2DVariable::set( "P18", this->prefix() + "P18", "Not described",
                       C2DVariable::Metrics, C2DVariable::General, 0.0f, 10.0f ) );

    this->addVariable( C2DVariable::set( "P19", this->prefix() + "P19", "Not described",
                       C2DVariable::Metrics, C2DVariable::General, 0.0f, 10.0f ) );

}

void C2DDefaultBelt::setVariables()
{

    H( "Belt" ) = I( "Belt:Type" );

    H( "Belt:Length" ) = D( "T18" ) + 2.0f * D( "P18" );

    //ok
    H( "Belt:Length1" ) = 0.0f;
    H( "Belt:Length2" ) = 0.0f;

    H( "Belt:Length1" ) = ( ( P["P54"] - P["P51"] ).manhattanLength() -
                          D( "SideDart1Spread" ) / 2.0f - D( "BackDart1Spread" ) ) * 2.0f;
    H( "Belt:Length2" ) = ( ( P["P57"] - P["P54"] ).manhattanLength() -
                          D( "SideDart1Spread" ) / 2.0f - D( "FrontDart1Spread" ) ) * 2.0f;

}

void C2DDefaultBelt::UpdatePoints()
{
    P[ "P0" ] = QPointF( 0.0f, 0.0f );

    P["Belt:Anchor"] = P["Belt:BL"] = P["P0"];
    P["Belt:TL"] = P["Belt:Anchor"] + QPointF( 0.0f, D( "Belt:Width" ) );
    P["Belt:BR"] = P["Belt:Anchor"] + QPointF( LD( "Belt:Length" ), 0.0f );
    P["Belt:TR"] = P["Belt:Anchor"] + QPointF( LD( "Belt:Length" ), D( "Belt:Width" ) );

    switch ( I( "Belt:Clasp:Position" ) )
    {
    case ( 0 ) :
        P["Belt:BD1"] = P["Belt:Anchor"] + QPointF( LD("Belt:Length1") / 2.0f, 0.0f );
        P["Belt:TD1"] = P["Belt:BD1"] + QPointF( 0.0f, D("Belt:Width") );
        P["Belt:BD2"] = P["Belt:Anchor"] + QPointF( LD("Belt:Length1") + LD("Belt:Length2") / 2.0f, 0.0f );
        P["Belt:TD2"] = P["Belt:BD2"] + QPointF( 0.0f, D("Belt:Width") );

        P["Belt:Sign1Pos"] = P["Belt:Anchor"] + QPointF( LD("Belt:Length1"), 0.0f );
        break;
    case ( 1 ) :
        P["Belt:BD1"] = P["Belt:Anchor"] + QPointF( LD("Belt:Length2") / 2.0f, 0.0f );
        P["Belt:TD1"] = P["Belt:BD1"] + QPointF( 0.0f, D("Belt:Width") );
        P["Belt:BD2"] = P["Belt:Anchor"] + QPointF( LD("Belt:Length2") + LD("Belt:Length1") / 2.0f, 0.0f );
        P["Belt:TD2"] = P["Belt:BD2"] + QPointF( 0.0f, D("Belt:Width") );

        P["Belt:Sign1Pos"] = P["Belt:Anchor"] + QPointF( LD("Belt:Length2"), 0.0f );
        break;
    case ( 2 ) :
        P["Belt:BM"] = P["Belt:Anchor"] + QPointF( LD("Belt:Length2") / 2.0f + LD("Belt:Length1") / 2.0f, 0.0f );
        P["Belt:TM"] = P["Belt:BM"] + QPointF( 0.0f, D("Belt:Width") );

        P["Belt:Sign1Pos"] = P["Belt:Anchor"] + QPointF( LD("Belt:Length2") / 2.0f, 0.0f );
        P["Belt:Sign2Pos"] = P["Belt:Anchor"] + QPointF( LD("Belt:Length2") / 2.0f + LD("Belt:Length1"), 0.0f );
        break;
    case ( 3 ) :
        P["Belt:BM"] = P["Belt:Anchor"] + QPointF( LD("Belt:Length1") / 2.0f + LD("Belt:Length2") / 2.0f, 0.0f );
        P["Belt:TM"] = P["Belt:BM"] + QPointF( 0.0f, D("Belt:Width") );

        P["Belt:Sign1Pos"] = P["Belt:Anchor"] + QPointF( LD("Belt:Length1") / 2.0f, 0.0f );
        P["Belt:Sign2Pos"] = P["Belt:Anchor"] + QPointF( LD("Belt:Length1") / 2.0f + LD("Belt:Length2"), 0.0f );
        break;
    }

    P["Belt:PC1-L"] = P["Belt:TL"] + QPointF( -D("Belt:Ledge:Width"), 0.0f );
    P["Belt:PC2-L"] = P["Belt:TL"] + QPointF( -D("Belt:Ledge:Width"), -D("Belt:Width") );
    P["Belt:PC3-L"] = P["Belt:TL"] + QPointF( 0.0f, -D("Belt:Width") );

}

void C2DDefaultBelt::DrawOnWidget()
{
#ifdef C2D_DEBUG
    qDebug() << "Belt: " << LB( "Belt" );
#endif
    line( Sync( attr( SYNC_NAME, "L-B1-001" ),
                attr( SYNC_TYPE, C2DSync::Line ),
                attr( SYNC_LIST, MakeList( "Belt:BL", "Belt:TL" ) ),
                LM->bold_solid() ),
          LB( "Belt" ) );

    line( Sync( attr( SYNC_NAME, "L-B1-002" ),
                attr( SYNC_TYPE, C2DSync::Line ),
                attr( SYNC_LIST, MakeList( "Belt:BR", "Belt:TR" ) ),
                LM->bold_solid() ),
          LB( "Belt" ) );

    line( Sync( attr( SYNC_NAME, "L-B1-003" ),
                attr( SYNC_TYPE, C2DSync::Line ),
                attr( SYNC_LIST, MakeList( "Belt:BL", "Belt:BR" ) ),
                LM->bold_solid()),
          LB( "Belt" ) );

    line( Sync( attr( SYNC_NAME, "L-B1-004" ),
                attr( SYNC_TYPE, C2DSync::Line ),
                attr( SYNC_LIST, MakeList( "Belt:TL", "Belt:TR" ) ),
                LM->bold_solid() ),
          LB( "Belt" ) );

    line( Sync( attr( SYNC_NAME, "L-B1-006" ),
                attr( SYNC_TYPE, C2DSync::Line ),
                attr( SYNC_LIST, MakeList( "Belt:PC1-L", "Belt:PC2-L" ) ),
                LM->bold_solid() ),
          ( LB( "Belt" ) && B( "Belt:ZipperUntilEnd" ) ) );

    line( Sync( attr( SYNC_NAME, "L-B1-006-1" ),
                attr( SYNC_TYPE, C2DSync::Line ),
                attr( SYNC_LIST, MakeList( "Belt:PC1-L", "Belt:TL" ) ),
                LM->bold_solid() ),
          ( LB( "Belt" ) && B( "Belt:ZipperUntilEnd" ) ) );

    line( Sync( attr( SYNC_NAME, "L-B1-006-2" ),
                attr( SYNC_TYPE, C2DSync::Line ),
                attr( SYNC_LIST, MakeList( "Belt:PC2-L", "Belt:PC3-L" ) ),
                LM->bold_solid() ),
          ( LB( "Belt" ) && B( "Belt:ZipperUntilEnd" ) ) );

    sign( Sync( attr( SYNC_NAME, "L-B1-S1" ),
                attr( SYNC_TYPE, C2DSync::Sign ),
                attr( SYNC_LIST, MakeList( "Belt:Sign1Pos" ) ),
                LM->thick_solid(),
                attr( SYNC_SIGN_DUAL, false ),
                attr( SYNC_SIGN_ANGLE, 90.0f ) ),
          LB( "Belt" ) );

    //----------------------------------------------------------------------------------------

    this->sign( Sync( attr( SYNC_NAME, "Belt:ClaspSign:Front" ),
                      attr( SYNC_TYPE, C2DSync::Sign ),
                      attr( SYNC_LIST, MakeList( "Belt:Clasp" ) ),
                      LM->thick_solid(),
                      attr( SYNC_SIGN_DUAL, false ),
                      attr( SYNC_SIGN_ANGLE, D( "Belt:ClaspAngle" ) ) ),
                B( "Belt:FrontClasp" ) );

    this->sign( Sync( attr( SYNC_NAME, "Belt:ClaspSign:Back" ),
                      attr( SYNC_TYPE, C2DSync::Sign ),
                      attr( SYNC_LIST, MakeList( "Belt:Clasp" ) ),
                      LM->thick_solid(),
                      attr( SYNC_SIGN_DUAL, false ),
                      attr( SYNC_SIGN_ANGLE, D( "Belt:ClaspAngle" ) ) ),
                B( "Belt:BackClasp" ) );

    this->sign( Sync( attr( SYNC_NAME, "Belt:ClaspSign:DualLeft" ),
                      attr( SYNC_TYPE, C2DSync::Sign ),
                      attr( SYNC_LIST, MakeList( "Belt:ClaspLeft" ) ),
                      LM->thick_solid(),
                      attr( SYNC_SIGN_DUAL, false ),
                      attr( SYNC_SIGN_ANGLE, D( "Belt:ClaspAngleLeft" ) ) ),
                 B( "Belt:DualClasp" ) );

    this->sign( Sync( attr( SYNC_NAME, "Belt:ClaspSign:Dual" ),
                      attr( SYNC_TYPE, C2DSync::Sign ),
                      attr( SYNC_LIST, MakeList( "Belt:ClaspRight" ) ),
                      LM->thick_solid(),
                      attr( SYNC_SIGN_DUAL, false ),
                      attr( SYNC_SIGN_ANGLE, D( "Belt:ClaspAngleRight" ) ) ),
                B( "Belt:DualClasp" ) );

    this->sign( Sync( attr( SYNC_NAME, "Belt:ClaspSign:Center" ),
                      attr( SYNC_TYPE, C2DSync::Sign ),
                      attr( SYNC_LIST, MakeList( "Belt:Clasp" ) ),
                      LM->thick_solid(),
                      attr( SYNC_SIGN_DUAL, false ),
                      attr( SYNC_SIGN_ANGLE, D( "Belt:ClaspAngle" ) ) ),
                B( "Belt:CenterClasp" ) );

}
