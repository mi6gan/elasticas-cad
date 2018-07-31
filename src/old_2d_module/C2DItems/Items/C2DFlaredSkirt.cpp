#include "C2DFlaredSkirt.h"

C2DFlaredSkirt::C2DFlaredSkirt() : C2DItem()
{
    this->setPrefix( "FlaredSkirt" );

    this->requiredVariables();

    this->addDialog(
            new C2DFlaredSkirtKMProperties( QObject::trUtf8( "Параметры Конструктивного Моделирования" ),
                                            this->prefix( false ), QObject::trUtf8( "Параметры МК/МФ/Форма МК" ),
                                            QPair< QString, double> ( QObject::trUtf8( "см" ), 10.0f ),
                                            NULL ) );

}

void C2DFlaredSkirt::Update()
{
//    this->setVariables();
//    this->UpdatePoints();
//    this->DrawOnWidget();
}

void C2DFlaredSkirt::requiredVariables()
{
    this->addVariable( C2DVariable::set( "PTx", this->prefix() + "PTx",
                       "Not described", C2DVariable::Metrics, C2DVariable::General ) );
    this->addVariable( C2DVariable::set( "PTy", this->prefix() + "PTy",
                       "Not described", C2DVariable::Metrics, C2DVariable::General ) );

    this->addVariable( C2DVariable::set( "Kr", this->prefix() + "Kr",
                       "Not described", C2DVariable::Metrics, C2DVariable::General, 0.4f ) );
    this->addVariable( C2DVariable::set( "Height", this->prefix() + "A1",
                       "Not described", C2DVariable::Metrics, C2DVariable::General, 40.0f, 10.0f ) );

    this->addVariable( C2DVariable::set( "T7", "T7", "Not described",
                       C2DVariable::Metrics, C2DVariable::General, 1000.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "T9", "T9", "Not described",
                       C2DVariable::Metrics, C2DVariable::General, 1000.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "T12", "T12", "Not described",
                       C2DVariable::Metrics, C2DVariable::General, 1000.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "T18", "T18", "Not described",
                       C2DVariable::Metrics, C2DVariable::General, 1000.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "T19", "T19", "Not described",
                       C2DVariable::Metrics, C2DVariable::General, 1000.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "T25", "T25", "Not described",
                       C2DVariable::Metrics, C2DVariable::General, 1000.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "T26", "T26", "Not described",
                       C2DVariable::Metrics, C2DVariable::General, 1000.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "T46", "T46", "Not described",
                       C2DVariable::Metrics, C2DVariable::General, 1000.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "T86", "T86", "Not described",
                       C2DVariable::Metrics, C2DVariable::General, 1000.0f, 10.0f ) );

    this->addVariable( C2DVariable::set( "P18", this->prefix() + "P18", "Not described",
                       C2DVariable::Metrics, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "P19", this->prefix() + "P19", "Not described",
                       C2DVariable::Metrics, C2DVariable::General, 0.0f, 10.0f ) );

    this->addVariable( C2DVariable::set( "K25", this->prefix() + "K1", "Not described",
                       C2DVariable::Metrics, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "K26", this->prefix() + "K2", "Not described",
                       C2DVariable::Metrics, C2DVariable::General, -30.0f, 10.0f ) );

    //P19r = const, в диалоге её нет и не будет.
    this->addVariable( C2DVariable::set( "P19r", "P19r", "Not described",
                       C2DVariable::Metrics, C2DVariable::General, 30.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "Snr", "Snr", "Not described",
                       C2DVariable::Metrics, C2DVariable::General, 700.0f, 10.0f ) );

    //Seams
    this->addVariable( C2DVariable::set( "SideSeam", this->prefix() + "VB", "Not described",
                       C2DVariable::Logical, C2DVariable::Optional, true ) );
    this->addVariable( C2DVariable::set( "FrontSeam", this->prefix() + "VP", "Not described",
                       C2DVariable::Logical, C2DVariable::Optional, true ) );
    this->addVariable( C2DVariable::set( "BackSeam", this->prefix() + "VZ", "Not described",
                       C2DVariable::Logical, C2DVariable::Optional, true ) );

    this->addVariable( C2DVariable::set( "SideSeamShift", this->prefix() + "A2",
                       "Not described", C2DVariable::Metrics, C2DVariable::Optional, 0.0f, 10.0f ) );
}

void C2DFlaredSkirt::setVariables()
{
    //  D("LibVersion"]=0.1;

    //  Material:
    //     1 - for monotonic material;
    //     2 - for material with character texture

    H( "Material:Monochromic" ) = QVariant( true );
    H( "Material:Texturized" ) = QVariant( false );

    H( "Base" ) =   QVariant( false );
    H( "Flared" ) = QVariant( true  );

    //Temp Kr
    H( "Kr" ) = QVariant( 1.12f );

    H( "Width" ) =            D( "T19" ) / 2.0f + D( "P19" );
    H( "WidthBottom" ) =      D( "Width" ) * D( "Kr" );
    H( "AdditionalLength" ) = D( "WidthBottom" ) - D( "Width" );

    H( "T" ) =  D( "T18" ) + D( "P18" );
    H( "B" ) =  D( "T19" ) + D( "P19" );
    H( "Sv" ) = D( "B" ) - D( "T" );
    H( "HiplineWidth" ) = 0.5 * ( D( "B" ) - D( "T" ) );

    H( "HeightLeft" ) =   ( D( "T7" ) - D( "T86" ) );
    H( "HeightCenter" ) = D( "Height" ) + ( D( "T25" ) - D( "T7" ) + D( "K25" ) );
    H( "HeightRight" ) =  D( "Height" ) + ( D( "T26" ) - D( "T7" ) + D( "K26" ) );
    H( "HeightBottom" ) = D( "Height" ) - D( "HeightLeft" );

    H( "TopDelta" ) = D( "HeightCenter" ) - D( "Height" );

    /* Darts from StraightSkirt */

    H( "Sb" ) = 0.32f * D( "HiplineWidth" );
    H( "Ss" ) = 0.50f * D( "HiplineWidth" );
    H( "Sf" ) = 0.18f * D( "HiplineWidth" );

    H( "Hb" ) = 0.8f * D( "HeightLeft" ) - 10.0f;
    H( "Hs" ) = D( "HeightCenter" ) - D( "HeightBottom" );
    H( "Hf" ) = 0.5f * D( "HeightLeft" ) - 10.0f;

    H( "Wb" ) = 0.4f * D( "Width" ) / 2.0f;
    H( "Ws" ) = D( "Width" ) - D( "SideSeamShift" );
    H( "Wf" ) = D( "Width" ) - ( D( "T46" ) / 2.0f + 3.0f );

    /*/ Darts from StraightSkirt /*/

    /* Critical modifiers */

    H( "Kmin" ) = 1.0f;
    H( "Ka" ) =   2.0f * D( "Sf" ) / D( "Width" ) + 1.0f;
    H( "Kb" ) =   2.0f * D( "Sb" ) / D( "Width" ) + 1.0f;
    H( "Kc" ) =   ( 2.0f * D( "Sb" ) + D( "Ss" ) ) / D( "Width" ) + 1.0f;

    H( "Rt" ) = D( "HeightBottom" ) / ( D( "Kr" ) - 1.0f ) - D( "HeightLeft" );
    H( "Al" ) = ( D( "Kr" ) * D( "Width" ) ) /
                    ( D( "Rt" ) + D( "HeightLeft" ) + D( "HeightBottom" ) );

    H( "Kmax" ) = ( 1.0f + pow( ( 1.0f - ( M_PI * D( "HeightBottom" ) / ( 2.0f * D( "Width" ) ) ) ),
                            0.5f ) ) / 2.0f;

    qDebug() << "Ka: "   << D( "Ka" );
    qDebug() << "Kb: "   << D( "Kb" );
    qDebug() << "Kc: "   << D( "Kc" );
    qDebug() << "Kmax: " << D( "Kmax" );
    qDebug() << "Rt: "   << D( "Rt" );
    qDebug() << "Al: "   << D( "Al" ) * 180.0f / M_PI;

    /*/ Critical modifiers /*/

    /* Angles */

    H( "Ab" ) = D( "HeightLeft"  ) - 5.0f;
    H( "Af" ) = D( "HeightRight" ) - D( "HeightBottom" ) - 5.0f;

    qDebug() << "Ab: " << D( "Ab" );
    qDebug() << "Af: " << D( "Af" );

    H( "Hwb" ) = D( "Width" ) / 2.0f - D( "SideSeamShift" );
    H( "Hwf" ) = D( "Width" ) / 2.0f + D( "SideSeamShift" );

    if ( D( "Kr" ) == D( "Kmin" ) )
    {
        H( "Bt" ) = 0.0f;
        H( "Bb" ) = 0.0f;
        H( "Ft" ) = 0.0f;
        H( "Fb" ) = 0.0f;

        H( "BackDart" ) =  QVariant( true );
        H( "SideDart" ) =  QVariant( true );
        H( "FrontDart" ) = QVariant( true );
    }

    if ( ( D( "Kr" ) >= D( "Kmin" ) ) &&
         ( D( "Kr" ) <  D( "Ka" ) ) )
    {
        H( "Bt" ) = asin( D( "AdditionalLength" ) / ( 2.0f * D( "Ab" ) ) );
        H( "Bb" ) = 0.0f;
        H( "Ft" ) = asin( D( "AdditionalLength" ) / ( 2.0f * D( "Af" ) ) );
        H( "Fb" ) = 0.0f;

        H( "BackDart" ) =  QVariant( true );
        H( "SideDart" ) =  QVariant( true );
        H( "FrontDart" ) = QVariant( true );
    }

    if ( ( D( "Kr" ) >= D( "Ka" ) ) &&
         ( D( "Kr" ) <  D( "Kb" ) ) )
    {
        H( "Bt" ) = asin( D( "Sf" ) / D( "Ab" ) );
        H( "Bb" ) = 0.0f;
        H( "Ft" ) = asin( D( "Sb" ) / D( "Af" ) );
        H( "Fb" ) = asin( ( D( "AdditionalLength" ) / 2.0f - D( "Sf" ) ) /
                              ( D( "HeightRight" ) + D( "HeightBottom" ) ) );

        H( "BackDart" ) =  QVariant( true  );
        H( "SideDart" ) =  QVariant( true  );
        H( "FrontDart" ) = QVariant( false );
    }

    if ( ( D( "Kr" ) >= D( "Kb" ) ) &&
         ( D( "Kr" ) <  D( "Kc" ) ) )
    {
        H( "Bt" ) = asin( D( "Sb" ) / D( "Ab" ) );
        H( "Bb" ) = asin( ( D( "AdditionalLength" ) / 2.0f - D( "Sb" ) ) /
                              ( D( "HeightRight" ) + D( "HeightBottom" ) ) );
        H( "Ft" ) = asin( D( "Sf" ) / D( "Af" ) );
        H( "Fb" ) = asin( ( D( "AdditionalLength" ) / 2.0f - D( "Sf" ) ) /
                              ( D( "HeightRight" ) + D( "HeightBottom" ) ) );

        H( "BackDart" ) =  QVariant( false );
        H( "SideDart" ) =  QVariant( true  );
        H( "FrontDart" ) = QVariant( false );
    }

    if ( D( "Kr" ) >= D( "Kc" ) )
    {
        H( "Bt" ) = asin( D( "Sb" ) / D( "Ab" ) );
        H( "Bb" ) = asin( ( D( "AdditionalLength" ) / 2.0f - D( "Sb" ) ) /
                              ( D( "HeightRight" ) + D( "HeightBottom" ) ) );
        H( "Ft" ) = asin( D( "Sf" ) / D( "Af" ) );
        H( "Fb" ) = asin( ( D( "AdditionalLength" ) / 2.0f - D( "Sf" ) ) /
                              ( D( "HeightRight" ) + D( "HeightBottom" ) ) );

        H( "BackDart" ) =  QVariant( false );
        H( "SideDart" ) =  QVariant( false );
        H( "FrontDart" ) = QVariant( false );
    }

    H( "Bt" ) = D( "Bt" ) * 180.0f / M_PI;
    H( "Bb" ) = D( "Bb" ) * 180.0f / M_PI;
    H( "Ft" ) = D( "Ft" ) * 180.0f / M_PI;
    H( "Fb" ) = D( "Fb" ) * 180.0f / M_PI;

    /*/ Angles /*/

    H( "Ssl" ) = D( "Ss" ) - ( D( "AdditionalLength" ) / 2.0f - D( "Sb" ) );
    H( "Ssr" ) = D( "Ss" ) - ( D( "AdditionalLength" ) / 2.0f - D( "Sf" ) );

        if ( ( D( "AdditionalLength" ) < 100.0f ) && B( "SideDart" ) )
        {
            H( "Hcs" ) = D( "Hs" ) * ( 100.0f - D( "AdditionalLength" ) ) / 100.0f;
        }
        else
        {
            H( "Hcs" ) = QVariant( 0.0f );
            H( "SideDart" ) = false;
        }



        qDebug() << "Backdart: "  << B( "BackDart" );
        qDebug() << "Sidedart: "  << B( "SideDart" );
        qDebug() << "Frontdart: " << B( "FrontDart" );
        qDebug() << "AdditionalLength: " << D( "AdditionalLength" );
}

void C2DFlaredSkirt::UpdatePoints()
{
    /* Base points */

    P[ "P0" ] = QPointF( 0.0f, 0.0f );

    P[ "View:Center" ] = P[ "P0" ] + QPointF( D( "Width" ) / 2.0f - D( "SideSeamShift" ),
                                              D( "Height" ) / 2.0f );

    //Main circuit
    P[ "B:P91" ] = P[ "P0" ];
    P[ "B:P94" ] = P[ "P0" ] + QPointF( D( "Width" ) / 2.0f - D( "SideSeamShift" ), 0.0f );
    P[ "B:P97" ] = P[ "P0" ] + QPointF( D( "Width" ), 0.0f );
    P[ "B:P51" ] = P[ "P0" ] + QPointF( 0.0f, D( "HeightBottom" ) );
    P[ "B:P54" ] = P[ "P0" ] + QPointF( D( "Width" ) / 2.0f - D( "SideSeamShift" ), D( "HeightBottom" ) );
    P[ "B:P57" ] = P[ "P0" ] + QPointF( D( "Width" ), D( "HeightBottom" ) );
    P[ "B:P41" ] = P[ "P0" ] + QPointF( 0.0f, D( "Height" ) );
    P[ "B:P410"] = P[ "P0" ] + QPointF( 0.05f * D( "Width" ), D( "Height" ) );
    P[ "B:P44" ] = P[ "P0" ] + QPointF( D( "Width" ) / 2.0f - D( "SideSeamShift" ), D( "HeightCenter" ) );
    P[ "B:P47a"] = P[ "P0" ] + QPointF( D( "Width" ), D( "Height" ) );
    P[ "B:P470"] = P[ "P0" ] + QPointF( 0.95f * D( "Width" ), D( "HeightRight" ) );
    P[ "B:P47" ] = P[ "P0" ] + QPointF( D( "Width" ), D( "HeightRight" ) );

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

    /* Current shape */

        qDebug() << "Bt" << D( "Bt" );
        qDebug() << "Bb" << D( "Bb" );
        qDebug() << "Ft" << D( "Ft" );
        qDebug() << "Fb" << D( "Fb" );

        /* Point matrix */

        // Back
        P[ "L:PS0" ] = P[ "B:P51" ] + QPointF( 0.0f, 0.0f );
        P[ "L:PT0" ] = P[ "B:P41" ];
        P[ "L:PB0" ] = P[ "B:P91" ];

        P[ "L:PS1" ] = P[ "B:P51" ] + QPointF( D( "Hwb" ) * 2.0f / 5.0f, 0.0f );
        P[ "L:PT1" ] = P[ "B:P41" ] + QPointF( D( "Hwb" ) * 2.0f / 5.0f, 0.0f )
                       + QPointF( 0.0f, this->leftTop( D( "Hwb" ) * 2.0f / 5.0f ).y() );
        P[ "L:PB1" ] = P[ "B:P91" ] + QPointF( D( "Hwb" ) * 2.0f / 5.0f, 0.0f );

        P[ "L:PS2" ] = P[ "B:P51" ] + QPointF( D( "Hwb" ) * 4.0f / 5.0f, 0.0f );
        P[ "L:PT2" ] = P[ "B:P41" ] + QPointF( D( "Hwb" ) * 4.0f / 5.0f, 0.0f )
                       + QPointF( 0.0f, this->leftTop( D( "Hwb" ) * 4.0f / 5.0f ).y() );
        P[ "L:PB2" ] = P[ "B:P91" ] + QPointF( D( "Hwb" ) * 4.0f / 5.0f, 0.0f );

        P[ "L:PS3" ] = P[ "B:P51" ] + QPointF( D( "Hwb" ) * 5.0f / 5.0f, 0.0f );
        P[ "L:PT3" ] = P[ "B:P41" ] + QPointF( D( "Hwb" ) * 5.0f / 5.0f, 0.0f )
                       + QPointF( 0.0f, this->leftTop( D( "Hwb" ) * 5.0f / 5.0f ).y() );
        P[ "L:PB3" ] = P[ "B:P91" ] + QPointF( D( "Hwb" ) * 5.0f / 5.0f, 0.0f );

        P[ "S:BL:SPoint" ] = P[ "L:PB0" ];
        P[ "S:BL:SGuide" ] = P[ "L:PB0" ] + QPointF(   D( "Hwb" ) * 1.0f / 5.0f, 0.0f );
        P[ "S:BL:EGuide" ] = P[ "L:PB3" ] + QPointF( - D( "Hwb" ) * 1.0f / 5.0f, 0.0f );
        P[ "S:BL:EPoint" ] = P[ "L:PB3" ];

        P[ "S:TL:SPoint" ] = P[ "L:PT0" ];
        P[ "S:TL:SGuide" ] = P[ "L:PT0" ] + QPointF(   D( "Hwf" ) * 2.0f / 5.0f, 0.0f );
        P[ "S:TL:EGuide" ] = P[ "L:PT3" ] + QPointF( - D( "Hwf" ) * 2.0f / 5.0f, 0.0f );
        P[ "S:TL:EPoint" ] = P[ "L:PT3" ];

        // Front
        P[ "R:PS0" ] = P[ "B:P57" ] + QPointF( 0.0f, 0.0f );
        P[ "R:PT0" ] = P[ "B:P47" ];
        P[ "R:PB0" ] = P[ "B:P97" ];

        P[ "R:PS1" ] = P[ "B:P57" ] + QPointF( - D( "Hwf" ) * 2.0f / 5.0f, 0.0f );
        P[ "R:PT1" ] = P[ "B:P47" ] + QPointF( - D( "Hwf" ) * 2.0f / 5.0f, 0.0f )
                       + QPointF( 0.0f, this->rightTop( D( "Hwf" ) * 2.0f / 5.0f ).y() );
        P[ "R:PB1" ] = P[ "B:P97" ] + QPointF( - D( "Hwf" ) * 2.0f / 5.0f, 0.0f );

        P[ "R:PS2" ] = P[ "B:P57" ] + QPointF( - D( "Hwf" ) * 4.0f / 5.0f, 0.0f );
        P[ "R:PT2" ] = P[ "B:P47" ] + QPointF( - D( "Hwf" ) * 4.0f / 5.0f, 0.0f )
                       + QPointF( 0.0f, this->rightTop( D( "Hwf" ) * 4.0f / 5.0f ).y() );
        P[ "R:PB2" ] = P[ "B:P97" ] + QPointF( - D( "Hwf" ) * 4.0f / 5.0f, 0.0f );

        P[ "R:PS3" ] = P[ "B:P57" ] + QPointF( - D( "Hwf" ) * 5.0f / 5.0f, 0.0f );
        P[ "R:PT3" ] = P[ "B:P47" ] + QPointF( - D( "Hwf" ) * 5.0f / 5.0f, 0.0f )
                       + QPointF( 0.0f, this->rightTop( D( "Hwf" ) * 5.0f / 5.0f ).y() );
        P[ "R:PB3" ] = P[ "B:P97" ] + QPointF( - D( "Hwf" ) * 5.0f / 5.0f, 0.0f );

        P[ "S:BR:SPoint" ] = P[ "R:PB0" ];
        P[ "S:BR:SGuide" ] = P[ "R:PB0" ] + QPointF( - D( "Hwf" ) * 2.0f / 5.0f, 0.0f );
        P[ "S:BR:EGuide" ] = P[ "R:PB3" ] + QPointF(   D( "Hwf" ) * 2.0f / 5.0f, 0.0f );
        P[ "S:BR:EPoint" ] = P[ "R:PB3" ];

        P[ "S:TR:SPoint" ] = P[ "R:PT0" ];
        P[ "S:TR:SGuide" ] = P[ "R:PT0" ] + QPointF( - D( "Hwf" ) * 2.0f / 5.0f, 0.0f );
        P[ "S:TR:EGuide" ] = P[ "R:PT3" ] + QPointF(   D( "Hwf" ) * 2.0f / 5.0f, 0.0f );
        P[ "S:TR:EPoint" ] = P[ "R:PT3" ];

        /*/ Point matrix : back /*/

        /* First rotation : back */

        P[ "L:PS1" ] = P[ "L:PS1" ];
        P[ "L:PT1" ] = Unicus::rPoint( P[ "L:PT1" ], P[ "L:PS1" ], D( "Bt" ) * 1.0f / 3.0f );
        P[ "L:PB1" ] = Unicus::rPoint( P[ "L:PB1" ], P[ "L:PS1" ], D( "Bt" ) * 1.0f / 3.0f );

        P[ "L:PS2" ] = Unicus::rPoint( P[ "L:PS2" ], P[ "L:PS1" ], D( "Bt" ) * 1.0f / 3.0f );
        P[ "L:PT2" ] = Unicus::rPoint( P[ "L:PT2" ], P[ "L:PS1" ], D( "Bt" ) * 1.0f / 3.0f );
        P[ "L:PB2" ] = Unicus::rPoint( P[ "L:PB2" ], P[ "L:PS1" ], D( "Bt" ) * 1.0f / 3.0f );
        P[ "L:PS3" ] = Unicus::rPoint( P[ "L:PS3" ], P[ "L:PS1" ], D( "Bt" ) * 1.0f / 3.0f );
        P[ "L:PT3" ] = Unicus::rPoint( P[ "L:PT3" ], P[ "L:PS1" ], D( "Bt" ) * 1.0f / 3.0f );
        P[ "L:PB3" ] = Unicus::rPoint( P[ "L:PB3" ], P[ "L:PS1" ], D( "Bt" ) * 1.0f / 3.0f );

        P[ "S:TL:EGuide" ] = Unicus::rPoint( P[ "S:TL:EGuide" ], P[ "L:PS1" ], D( "Bt" ) * 1.0f / 3.0f );
        P[ "S:BL:EGuide" ] = Unicus::rPoint( P[ "S:BL:EGuide" ], P[ "L:PS1" ], D( "Bt" ) * 1.0f / 3.0f );

        P[ "C:SD:PBL" ] = Unicus::rPoint( P[ "C:SD:PB" ], P[ "L:PS1" ], D( "Bt" ) * 1.0f / 3.0f );
        P[ "C:SD:PLL" ] = Unicus::rPoint( P[ "C:SD:PL" ], P[ "L:PS1" ], D( "Bt" ) * 1.0f / 3.0f );
        P[ "C:SD:PRL" ] = Unicus::rPoint( P[ "C:SD:PR" ], P[ "L:PS1" ], D( "Bt" ) * 1.0f / 3.0f );

        P[ "L:PT2" ] = Unicus::rPoint( P[ "L:PT2" ], P[ "L:PS2" ], D( "Bt" ) * 1.0f / 3.0f );
        P[ "L:PB2" ] = Unicus::rPoint( P[ "L:PB2" ], P[ "L:PS2" ], D( "Bt" ) * 1.0f / 3.0f );

        P[ "L:PS3" ] = Unicus::rPoint( P[ "L:PS3" ], P[ "L:PS2" ], D( "Bt" ) * 1.0f / 3.0f );
        P[ "L:PT3" ] = Unicus::rPoint( P[ "L:PT3" ], P[ "L:PS2" ], D( "Bt" ) * 1.0f / 3.0f );
        P[ "L:PB3" ] = Unicus::rPoint( P[ "L:PB3" ], P[ "L:PS2" ], D( "Bt" ) * 1.0f / 3.0f );

        P[ "S:TL:EGuide" ] = Unicus::rPoint( P[ "S:TL:EGuide" ], P[ "L:PS2" ], D( "Bt" ) * 1.0f / 3.0f );
        P[ "S:BL:EGuide" ] = Unicus::rPoint( P[ "S:BL:EGuide" ], P[ "L:PS2" ], D( "Bt" ) * 1.0f / 3.0f );

        P[ "C:SD:PBL" ] = Unicus::rPoint( P[ "C:SD:PBL" ], P[ "L:PS2" ], D( "Bt" ) * 1.0f / 3.0f );
        P[ "C:SD:PLL" ] = Unicus::rPoint( P[ "C:SD:PLL" ], P[ "L:PS2" ], D( "Bt" ) * 1.0f / 3.0f );
        P[ "C:SD:PRL" ] = Unicus::rPoint( P[ "C:SD:PRL" ], P[ "L:PS2" ], D( "Bt" ) * 1.0f / 3.0f );

        P[ "L:PT3" ] = Unicus::rPoint( P[ "L:PT3" ], P[ "L:PS3" ], D( "Bt" ) * 1.0f / 3.0f );
        P[ "L:PB3" ] = Unicus::rPoint( P[ "L:PB3" ], P[ "L:PS3" ], D( "Bt" ) * 1.0f / 3.0f );


        P[ "S:TL:SPoint" ] = P[ "L:PT0" ];
        P[ "S:TL:SGuide" ] = P[ "L:PT0" ] + QPointF( D( "Hwb" ) * 2.0f / 5.0f, 0.0f );
        P[ "S:TL:EGuide" ] = Unicus::rPoint( P[ "S:TL:EGuide" ], P[ "L:PS3" ], D( "Bt" ) * 1.0f / 3.0f );
        P[ "S:TL:EPoint" ] = P[ "L:PT3" ];

        P[ "S:BL:SPoint" ] = P[ "L:PB0" ];
        P[ "S:BL:SGuide" ] = P[ "L:PB0" ] + QPointF( D( "Hwb" ) * 2.0f / 5.0f, 0.0f );
        P[ "S:BL:EGuide" ] = Unicus::rPoint( P[ "S:BL:EGuide" ], P[ "L:PS3" ], D( "Bt" ) * 1.0f / 3.0f );
        P[ "S:BL:EPoint" ] = P[ "L:PB3" ];

        P[ "C:SD:PBL" ] = Unicus::rPoint( P[ "C:SD:PBL" ], P[ "L:PS3" ], D( "Bt" ) * 1.0f / 3.0f );
        P[ "C:SD:PLL" ] = Unicus::rPoint( P[ "C:SD:PLL" ], P[ "L:PS3" ], D( "Bt" ) * 1.0f / 3.0f );
        P[ "C:SD:PRL" ] = Unicus::rPoint( P[ "C:SD:PRL" ], P[ "L:PS3" ], D( "Bt" ) * 1.0f / 3.0f );

        /*/ First rotation : back /*/

        /* Second rotation : back */

        P[ "L:PS1" ] = Unicus::rPoint( P[ "L:PS1" ], P[ "L:PT1" ], D( "Bb" ) * 1.0f / 3.0f );
        P[ "L:PB1" ] = Unicus::rPoint( P[ "L:PB1" ], P[ "L:PT1" ], D( "Bb" ) * 1.0f / 3.0f );

        P[ "L:PS2" ] = Unicus::rPoint( P[ "L:PS2" ], P[ "L:PT2" ], D( "Bb" ) * 1.0f / 3.0f );
        P[ "L:PB2" ] = Unicus::rPoint( P[ "L:PB2" ], P[ "L:PT2" ], D( "Bb" ) * 1.0f / 3.0f );

        P[ "L:PS3" ] = Unicus::rPoint( P[ "L:PS3" ], P[ "L:PT3" ], D( "Bb" ) * 1.0f / 3.0f );
        P[ "L:PB3" ] = Unicus::rPoint( P[ "L:PB3" ], P[ "L:PT3" ], D( "Bb" ) * 1.0f / 3.0f );

        P[ "S:BL:SPoint" ] = P[ "L:PB0" ];
        P[ "S:BL:SGuide" ] = P[ "L:PB0" ] + QPointF( D( "Hwb" ) * 2.0f / 5.0f, 0.0f );
        P[ "S:BL:EGuide" ] = Unicus::rPoint( P[ "S:BL:EGuide" ],
                                             P[ "L:PS3" ], D( "Bb" ) * 1.0f / 3.0f );
        P[ "S:BL:EPoint"] = P[ "L:PB3" ];

        /*/ Second rotation : back /*/

        /* First rotation : front */

        P[ "R:PS1" ] = P[ "R:PS1" ];
        P[ "R:PT1" ] = Unicus::rPoint( P[ "R:PT1" ], P[ "R:PS1" ], - D( "Ft" ) * 1.0f / 3.0f );
        P[ "R:PB1" ] = Unicus::rPoint( P[ "R:PB1" ], P[ "R:PS1" ], - D( "Ft" ) * 1.0f / 3.0f );

        P[ "C:SD:PBR" ] = Unicus::rPoint( P[ "C:SD:PB" ], P[ "R:PS1" ], - D( "Ft" ) * 1.0f / 3.0f );
        P[ "C:SD:PLR" ] = Unicus::rPoint( P[ "C:SD:PL" ], P[ "R:PS1" ], - D( "Ft" ) * 1.0f / 3.0f );
        P[ "C:SD:PRR" ] = Unicus::rPoint( P[ "C:SD:PR" ], P[ "R:PS1" ], - D( "Ft" ) * 1.0f / 3.0f );

        P[ "R:PS2" ] = Unicus::rPoint( P[ "R:PS2" ], P[ "R:PS1" ], - D( "Ft" ) * 1.0f / 3.0f );
        P[ "R:PT2" ] = Unicus::rPoint( P[ "R:PT2" ], P[ "R:PS1" ], - D( "Ft" ) * 1.0f / 3.0f );
        P[ "R:PB2" ] = Unicus::rPoint( P[ "R:PB2" ], P[ "R:PS1" ], - D( "Ft" ) * 1.0f / 3.0f );
        P[ "R:PS3" ] = Unicus::rPoint( P[ "R:PS3" ], P[ "R:PS1" ], - D( "Ft" ) * 1.0f / 3.0f );
        P[ "R:PT3" ] = Unicus::rPoint( P[ "R:PT3" ], P[ "R:PS1" ], - D( "Ft" ) * 1.0f / 3.0f );
        P[ "R:PB3" ] = Unicus::rPoint( P[ "R:PB3" ], P[ "R:PS1" ], - D( "Ft" ) * 1.0f / 3.0f );

        P[ "S:TR:EGuide" ] = Unicus::rPoint( P[ "S:TR:EGuide" ], P[ "R:PS1" ], - D( "Ft" ) * 1.0f / 3.0f );
        P[ "S:BR:EGuide" ] = Unicus::rPoint( P[ "S:BR:EGuide" ], P[ "R:PS1" ], - D( "Ft" ) * 1.0f / 3.0f );

        P[ "R:PT2" ] = Unicus::rPoint( P[ "R:PT2" ], P[ "R:PS2" ], - D( "Ft" ) * 1.0f / 3.0f );
        P[ "R:PB2" ] = Unicus::rPoint( P[ "R:PB2" ], P[ "R:PS2" ], - D( "Ft" ) * 1.0f / 3.0f );


        P[ "C:SD:PBR" ] = Unicus::rPoint( P[ "C:SD:PBR" ], P[ "R:PS2" ], - D( "Ft" ) * 1.0f / 3.0f );
        P[ "C:SD:PLR" ] = Unicus::rPoint( P[ "C:SD:PLR" ], P[ "R:PS2" ], - D( "Ft" ) * 1.0f / 3.0f );
        P[ "C:SD:PRR" ] = Unicus::rPoint( P[ "C:SD:PRR" ], P[ "R:PS2" ], - D( "Ft" ) * 1.0f / 3.0f );

        P[ "R:PS3" ] = Unicus::rPoint( P[ "R:PS3" ], P[ "R:PS2" ], - D( "Ft" ) * 1.0f / 3.0f );
        P[ "R:PT3" ] = Unicus::rPoint( P[ "R:PT3" ], P[ "R:PS2" ], - D( "Ft" ) * 1.0f / 3.0f );
        P[ "R:PB3" ] = Unicus::rPoint( P[ "R:PB3" ], P[ "R:PS2" ], - D( "Ft" ) * 1.0f / 3.0f );

        P[ "S:TR:EGuide" ] = Unicus::rPoint( P[ "S:TR:EGuide" ], P[ "R:PS2" ], - D( "Ft" ) * 1.0f / 3.0f );
        P[ "S:BR:EGuide" ] = Unicus::rPoint( P[ "S:BR:EGuide" ], P[ "R:PS2" ], - D( "Ft" ) * 1.0f / 3.0f );

        P[ "R:PT3" ] = Unicus::rPoint( P[ "R:PT3" ], P[ "R:PS3" ], - D( "Ft" ) * 1.0f / 3.0f );
        P[ "R:PB3" ] = Unicus::rPoint( P[ "R:PB3" ], P[ "R:PS3" ], - D( "Ft" ) * 1.0f / 3.0f );

        P[ "C:SD:PBR" ] = Unicus::rPoint( P[ "C:SD:PBR" ], P[ "R:PS3" ], - D( "Ft" ) * 1.0f / 3.0f );
        P[ "C:SD:PLR" ] = Unicus::rPoint( P[ "C:SD:PLR" ], P[ "R:PS3" ], - D( "Ft" ) * 1.0f / 3.0f );
        P[ "C:SD:PRR" ] = Unicus::rPoint( P[ "C:SD:PRR" ], P[ "R:PS3" ], - D( "Ft" ) * 1.0f / 3.0f );


        P[ "S:TR:SPoint" ] = P[ "R:PT0" ];
        P[ "S:TR:SGuide" ] = P[ "R:PT0" ] + QPointF( - D( "Hwb" ) * 2.0f / 5.0f, 0.0f );
        P[ "S:TR:EGuide" ] = Unicus::rPoint( P[ "S:TR:EGuide" ], P[ "R:PS3" ], - D( "Ft" ) * 1.0f / 3.0f );
        P[ "S:TR:EPoint" ] = P[ "R:PT3" ];

        P[ "S:BR:SPoint" ] = P[ "R:PB0" ];
        P[ "S:BR:SGuide" ] = P[ "R:PB0" ] + QPointF( - D( "Hwb" ) * 2.0f / 5.0f, 0.0f );
        P[ "S:BR:EGuide" ] = Unicus::rPoint( P[ "S:BR:EGuide" ], P[ "R:PS3" ], - D( "Ft" ) * 1.0f / 3.0f );
        P[ "S:BR:EPoint" ] = P[ "R:PB3" ];

        /*/ First rotation : front /*/

        /* Second rotation : front */

        P[ "R:PS1" ] = Unicus::rPoint( P[ "R:PS1" ], P[ "R:PT1" ], - D( "Fb" ) * 1.0f / 3.0f );
        P[ "R:PB1" ] = Unicus::rPoint( P[ "R:PB1" ], P[ "R:PT1" ], - D( "Fb" ) * 1.0f / 3.0f );

        P[ "R:PS2" ] = Unicus::rPoint( P[ "R:PS2" ], P[ "R:PT2" ], - D( "Fb" ) * 1.0f / 3.0f );
        P[ "R:PB2" ] = Unicus::rPoint( P[ "R:PB2" ], P[ "R:PT2" ], - D( "Fb" ) * 1.0f / 3.0f );

        P[ "R:PS3" ] = Unicus::rPoint( P[ "R:PS3" ], P[ "R:PT3" ], - D( "Fb" ) * 1.0f / 3.0f );
        P[ "R:PB3" ] = Unicus::rPoint( P[ "R:PB3" ], P[ "R:PT3" ], - D( "Fb" ) * 1.0f / 3.0f );

        P[ "S:BR:SPoint" ] = P[ "R:PB0" ];
        P[ "S:BR:SGuide" ] = P[ "R:PB0" ] + QPointF( - D( "Hwb" ) * 2.0f / 5.0f, 0.0f );
        P[ "S:BR:EGuide" ] = Unicus::rPoint( P[ "S:BR:EGuide" ],
                                             P[ "R:PS3" ], - D( "Fb" ) * 1.0f / 3.0f );
        P[ "S:BR:EPoint"] = P[ "R:PB3" ];

        /*/ Second rotation : front /*/

    // Tolerance : 5 mm.

    /*/ Current shape /*/
}

void C2DFlaredSkirt::DrawOnWidget()
{
    /* Base shape */

    C2DLayer * layer = ( D( "Kr" ) == D( "Kmin" ) ) ? this->LM->bold_solid() : this->dashed( true );

    this->line( Sync( attr( SYNC_NAME, "L:P91-P94" ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "B:P91", "B:P94" ) ),
                      layer ), B( "Base" ) );
    this->line( Sync( attr( SYNC_NAME, "L:P94-P97" ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "B:P94", "B:P97" ) ),
                      layer ), B( "Base" ) );

    this->line( Sync( attr( SYNC_NAME, "L:P91-P51" ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "B:P91", "B:P51" ) ),
                      layer ), B( "Base" ) );
    this->line( Sync( attr( SYNC_NAME, "L:P94-P54" ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "B:P94", "B:P54" ) ),
                      layer ), B( "Base" ) );
    this->line( Sync( attr( SYNC_NAME, "L:P97-P57" ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "B:P97", "B:P57" ) ),
                      layer ), B( "Base" ) );

    this->line( Sync( attr( SYNC_NAME, "L:P51-P54" ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "B:P51", "B:P54" ) ),
                      layer ), B( "Base" ) );
    this->line( Sync( attr( SYNC_NAME, "L:P54-P57" ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "B:P54", "B:P57" ) ),
                      layer ), B( "Base" ) );

    this->line( Sync( attr( SYNC_NAME, "L:P51-P41" ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "B:P51", "B:P41" ) ),
                      layer ), B( "Base" ) );
    this->line( Sync( attr( SYNC_NAME, "L:P54-P44" ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "B:P54", "B:P44" ) ),
                      layer ), B( "Base" ) );
    this->line( Sync( attr( SYNC_NAME, "L:P57-P47" ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "B:P57", "B:P47" ) ),
                      layer ), B( "Base" ) );

    /* Darts */

    this->line( Sync( attr( SYNC_NAME, "L:P41-P44" ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "B:P41", "B:P44" ) ),
                      layer ), B( "Base" ) );
    this->line( Sync( attr( SYNC_NAME, "L:P44-P47" ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "B:P44", "B:P47" ) ),
                      layer ), B( "Base" ) );

    DartItem * bd = this->dart( Sync( attr( SYNC_NAME, "D:BDB-BDL-BDR" ),
                                      attr( SYNC_TYPE, C2DSync::Dart ),
                                      attr( SYNC_LIST, MakeList( "B:BD:PB", "B:BD:PL", "B:BD:PR" ) ),
                                      layer ), B( "Base" ) );

    if ( bd )
    {
        bd->setKK( 0.0f );
        P[ "B:BD:CL" ] = bd->connectLeft();
        P[ "B:BD:CR" ] = bd->connectRight();
    }

    DartItem * sd = this->dart( Sync( attr( SYNC_NAME, "D:SDB-SDL-SDR" ),
                                      attr( SYNC_TYPE, C2DSync::Dart ),
                                      attr( SYNC_LIST, MakeList( "B:SD:PB", "B:SD:PL", "B:SD:PR" ) ),
                                      layer ), B( "Base" ) );

    if ( sd )
    {
        sd->setKK( 10.0f );
        P[ "B:SD:CL" ] = sd->connectLeft();
        P[ "B:SD:CR" ] = sd->connectRight();
    }

    DartItem * fd = this->dart( Sync( attr( SYNC_NAME, "D:FDB-FDL-FDR" ),
                                      attr( SYNC_TYPE, C2DSync::Dart ),
                                      attr( SYNC_LIST, MakeList( "B:FD:PB", "B:FD:PL", "B:FD:PR" ) ),
                                      layer ), B( "Base" ) );

    if ( fd )
    {
        fd->setKK( 2.5f );
        P[ "B:FD:CL" ] = fd->connectLeft();
        P[ "B:FD:CR" ] = fd->connectRight();
    }

    /*/ Darts /*/

    /* Splines */

    this->spline( Sync( attr( SYNC_NAME, "S:P41-BDL" ),
                        attr( SYNC_TYPE, C2DSync::Spline ),
                        attr( SYNC_LIST, MakeList( "B:P41", "B:P410", "B:BD:CL", "B:BD:PL" ) ),
                        layer ), B( "Base" ) );

    this->spline( Sync( attr( SYNC_NAME, "S:BDR-SDL" ),
                        attr( SYNC_TYPE, C2DSync::Spline ),
                        attr( SYNC_LIST, MakeList( "B:BD:PR", "B:BD:CR", "B:SD:CL", "B:SD:PL" ) ),
                        layer ), B( "Base" ) );

    this->spline( Sync( attr( SYNC_NAME, "S:SDR-FDL" ),
                        attr( SYNC_TYPE, C2DSync::Spline ),
                        attr( SYNC_LIST, MakeList( "B:SD:PR", "B:SD:CR", "B:FD:CL", "B:FD:PL" ) ),
                        layer ), B( "Base" ) );

    this->spline( Sync( attr( SYNC_NAME, "S:FDR-P47" ),
                        attr( SYNC_TYPE, C2DSync::Spline ),
                        attr( SYNC_LIST, MakeList( "B:FD:PR", "B:FD:CR", "B:P470", "B:P47" ) ),
                        layer ), B( "Base" ) );

    /*/ Splines /*/

    /*/ Base shape /*/

    /* Current shape */

    this->line( Sync( attr( SYNC_NAME, "L:LPT0-LPB0" ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "L:PT0", "L:PB0" ) ),
                      this->LM->bold_solid() ), B( "Flared" ) );

    this->line( Sync( attr( SYNC_NAME, "L:RPT0-RPB0" ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "R:PT0", "R:PB0" ) ),
                      this->LM->bold_solid() ), B( "Flared" ) );

    for ( int i = 0; i <= 3; i++ )
    {
        this->point( Sync( attr( SYNC_NAME, QString( "%1%2" ).arg( "P:PS" ).arg( i ) ),
                           attr( SYNC_TYPE, C2DSync::Point ),
                           attr( SYNC_LIST, MakeList( QString( "%1%2" ).arg( "L:PS" ).arg( i ) ) ),
                           layer ), B( "Flared" ) );

        this->point( Sync( attr( SYNC_NAME, QString( "%1%2" ).arg( "P:PT" ).arg( i ) ),
                           attr( SYNC_TYPE, C2DSync::Point ),
                           attr( SYNC_LIST, MakeList( QString( "%1%2" ).arg( "L:PT" ).arg( i ) ) ),
                           layer ), B( "Flared" ) );

        this->point( Sync( attr( SYNC_NAME, QString( "%1%2" ).arg( "P:PB" ).arg( i ) ),
                           attr( SYNC_TYPE, C2DSync::Point ),
                           attr( SYNC_LIST, MakeList( QString( "%1%2" ).arg( "L:PB" ).arg( i ) ) ),
                           layer ), B( "Flared" ) );

        this->point( Sync( attr( SYNC_NAME, QString( "%1%2" ).arg( "P:PS" ).arg( i ) ),
                           attr( SYNC_TYPE, C2DSync::Point ),
                           attr( SYNC_LIST, MakeList( QString( "%1%2" ).arg( "R:PS" ).arg( i ) ) ),
                           layer ), B( "Flared" ) );

        this->point( Sync( attr( SYNC_NAME, QString( "%1%2" ).arg( "P:PT" ).arg( i ) ),
                           attr( SYNC_TYPE, C2DSync::Point ),
                           attr( SYNC_LIST, MakeList( QString( "%1%2" ).arg( "R:PT" ).arg( i ) ) ),
                           layer ), B( "Flared" ) );

        this->point( Sync( attr( SYNC_NAME, QString( "%1%2" ).arg( "P:PB" ).arg( i ) ),
                           attr( SYNC_TYPE, C2DSync::Point ),
                           attr( SYNC_LIST, MakeList( QString( "%1%2" ).arg( "R:PB" ).arg( i ) ) ),
                           layer ), B( "Flared" ) );

    }

    this->line( Sync( attr( SYNC_NAME, "L:LPS3-LPB3" ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "L:PS3", "L:PB3" ) ),
                      this->LM->bold_solid() ), B( "Flared" ) );

    this->line( Sync( attr( SYNC_NAME, "L:RPS3-RPB3" ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "R:PS3", "R:PB3" ) ),
                      this->LM->bold_solid() ), B( "Flared" ) );

    this->line( Sync( attr( SYNC_NAME, "L:LPT3-LPS3" ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "L:PT3", "L:PS3" ) ),
                      this->LM->bold_solid() ), ( !B( "SideDart" ) && B( "Flared" ) ) );

    this->line( Sync( attr( SYNC_NAME, "L:RPT3-RPS3" ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "R:PT3", "R:PS3" ) ),
                      this->LM->bold_solid() ), ( !B( "SideDart" ) && B( "Flared" ) ) );


    /* Darts */

    DartItem * bdc = this->dart( Sync( attr( SYNC_NAME, "D:BDBR-BDLR-BDRR" ),
                                       attr( SYNC_TYPE, C2DSync::Dart ),
                                       attr( SYNC_LIST, MakeList( "B:BD:PBR", "B:BD:PLR", "B:BD:PRR" ) ),
                                       this->LM->bold_solid() ), ( B( "BackDart" ) && B( "Flared" ) ) );

    if ( bdc )
    {
        bdc->setKK( 0.0f );
        P[ "B:BD:CLR" ] = bdc->connectLeft();
        P[ "B:BD:CRR" ] = bdc->connectRight();
    }

    DartItem * sdl = this->dart( Sync( attr( SYNC_NAME, "D:CSDLL-CSDRL-CSDLL" ),
                                       attr( SYNC_TYPE, C2DSync::Dart ),
                                       attr( SYNC_LIST, MakeList( "C:SD:PBL", "C:SD:PLL", "C:SD:PRL" ) ),
                                       this->LM->bold_solid() ), ( B( "SideDart" ) && B( "Flared" ) ) );

    if ( sdl )
    {
        sdl->setKK( ( 100.0f - D( "AdditionalLength" ) ) / 10.0f );
        P[ "S:TL:EGuide" ] = sdl->connectLeft();
        sdl->setRightVisible( false );
    }

    this->line( Sync( attr( SYNC_NAME, "L:CSDPB-LPS3" ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "C:SD:PBL", "L:PS3" ) ),
                      this->LM->bold_solid() ), ( B( "SideDart" ) && B( "Flared" ) ) );

    DartItem * sdr = this->dart( Sync( attr( SYNC_NAME, "D:CSDLR-CSDRR-CSDLR" ),
                                       attr( SYNC_TYPE, C2DSync::Dart ),
                                       attr( SYNC_LIST, MakeList( "C:SD:PBR", "C:SD:PLR", "C:SD:PRR" ) ),
                                       this->LM->bold_solid() ), ( B( "SideDart" ) && B( "Flared" ) ) );

    if ( sdr )
    {
        sdr->setKK( ( 100.0f - D( "AdditionalLength" ) ) / 10.0f );
        P[ "S:TR:EGuide" ] = sdr->connectRight();
        sdr->setLeftVisible( false );
    }

    this->line( Sync( attr( SYNC_NAME, "L:CSDPB-RPS3" ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "C:SD:PBR", "R:PS3" ) ),
                      this->LM->bold_solid() ), ( B( "SideDart" ) && B( "Flared" ) ) );


    DartItem * fdc = this->dart( Sync( attr( SYNC_NAME, "D:FDBR-FDLR-FDRR" ),
                                       attr( SYNC_TYPE, C2DSync::Dart ),
                                       attr( SYNC_LIST, MakeList( "B:FD:PBR", "B:FD:PLR", "B:FD:PRR" ) ),
                                       this->LM->bold_solid() ), ( B( "FrontDart" ) && B( "Flared" ) ) );

    if ( fdc )
    {
        fdc->setKK( 2.5f );
        P[ "B:FD:CLR" ] = fdc->connectLeft();
        P[ "B:FD:CRR" ] = fdc->connectRight();
    }

    /*/ Darts /*/

    this->spline( Sync( attr( SYNC_NAME, "S:TLS-TLE" ),
                        attr( SYNC_TYPE, C2DSync::Spline ),
                        attr( SYNC_LIST, MakeList( "S:TL:SPoint", "S:TL:SGuide", "S:TL:EGuide", "C:SD:PLL" ) ),
                        this->LM->bold_solid() ), B( "Flared" ) );

    this->spline( Sync( attr( SYNC_NAME, "S:BLS-BLE" ),
                        attr( SYNC_TYPE, C2DSync::Spline ),
                        attr( SYNC_LIST, MakeList( "S:BL:SPoint", "S:BL:SGuide", "S:BL:EGuide", "S:BL:EPoint" ) ),
                        this->LM->bold_solid() ), B( "Flared" ) );

    this->spline( Sync( attr( SYNC_NAME, "S:TRS-TRE" ),
                        attr( SYNC_TYPE, C2DSync::Spline ),
                        attr( SYNC_LIST, MakeList( "S:TR:SPoint", "S:TR:SGuide", "S:TR:EGuide", "C:SD:PRR" ) ),
                        this->LM->bold_solid() ), B( "Flared" ) );

    this->spline( Sync( attr( SYNC_NAME, "S:BRS-BSE" ),
                        attr( SYNC_TYPE, C2DSync::Spline ),
                        attr( SYNC_LIST, MakeList( "S:BR:SPoint", "S:BR:SGuide", "S:BR:EGuide", "S:BR:EPoint" ) ),
                        this->LM->bold_solid() ), B( "Flared" ) );

    /*/ Current shape /*/
}

QPointF C2DFlaredSkirt::leftTop( double half_spread )
{
    double x = half_spread / ( D( "Width" ) / 2.0f - D( "SideSeamShift" ) );

    return QPointF( 0.0f, D( "TopDelta" ) * x );
}

QPointF C2DFlaredSkirt::rightTop( double half_spread )
{
    double x = half_spread / ( D( "Width" ) / 2.0f + D( "SideSeamShift" ) );

    return QPointF( 0.0f, D( "TopDelta" ) * x );
}

//QPointF C2DFlaredSkirt::CircInter(double R1, double R2, double h)
//{
//    //Returns deltas for intersection point of two equal circles
//    //situated one strong above other
//    QPointF Point(0,0);
//    double k=((R1*R1-R2*R2-h*h)/(2*h*R2));
//    Point.setY(h+k*R2);
//    Point.setX(R2*sqrt(1-k*k));
//    return Point;
//}
