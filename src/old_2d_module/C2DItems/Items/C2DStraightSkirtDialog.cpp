#include "C2DStraightSkirtDialog.h"

C2DStraightSkirtDialog::C2DStraightSkirtDialog( const QString            & name,
                                                const QString            & prefix,
                                                const QString            & tab,
                                                QPair< QString, double >   units,
                                                QWidget                  * parent )
    : C2DItemDialog( name, prefix, tab, units, parent )
{
    this->requiredVariables();

    QGridLayout * l = new QGridLayout( this );

    if ( l )
    {
        QGroupBox * group;
        QVBoxLayout * vbox;
        QDoubleSpinBox * dspin;

        QLabel * label[ 3 ] = { new QLabel( QObject::trUtf8( "Боковые"  ), this ),
                                new QLabel( QObject::trUtf8( "Передние" ), this ),
                                new QLabel( QObject::trUtf8( "Задние"   ), this ) };

        QList< QDoubleSpinBox * > list;

        for ( int i = 0; i <= 2; i++ )
        {
            spins[ i ] = new QSpinBox( this );
            spins[ i ]->setMinimum( 1 );
            spins[ i ]->setValue( 1 );

            int b;
            if ( i != 0 )
            {
                spins[ i ]->setMaximum( 3 );
                b = 1;
            }
            else
            {
                spins[ i ]->setMaximum( 1 );
                b = 0;
            }

            spins[ i ]->setStyleSheet( "* { padding-right: 10px; }" );

            l->addWidget( label[ i ], 2 * i + b, 3 );
            l->addWidget( spins[ i ], 2 * i + b, 4 );

            if ( i == 0 )
                for ( int j = 0; j <= 2; j++ )
                    l->addWidget(
                            new QLabel( QObject::trUtf8( "Вытачка №%1" ).arg( j + 1 ), this ), 1, 2 + j );

            QObject::connect( spins[ i ], SIGNAL( valueChanged( int ) ), this, SLOT( valueChanged() ) );

            for ( int j = 0; j <= 3; j++ )
            {
                group = new QGroupBox( this );

                group->setStyleSheet( "* { margin: 0px; padding: 0px; }" );

                vbox = new QVBoxLayout;

                if ( j != 0 )
                {
                    for ( int k = 0; k <= 2; k++ )
                    {

                        dspin = new QDoubleSpinBox( this );
                        dspin->setStyleSheet( "* { margin: 0px; padding: 0px; }" );
                        dspin->setValue( 0.0f );
                        dspin->setMinimum( 0.0f );
                        dspin->setSingleStep( 0.1f );
                        vbox->addWidget( dspin );

                        list.append( dspin );
                    }
                }
                else
                {
                    vbox->addWidget( new QLabel( QObject::trUtf8( "Длина, H, см" ),    this ) );
                    vbox->addWidget( new QLabel( QObject::trUtf8( "Раствор, R, см" ),  this ) );
                    vbox->addWidget( new QLabel( QObject::trUtf8( "Смещение, S, см" ), this ) );
                }
                group->setLayout( vbox );

                l->addWidget( group, 2 * i + 2, j + 1 );

                qDebug() << i * 3 + j;
                if ( j != 0 )
                    this->sets.insert( i * 3 + ( j - 1 ),
                        QPair< QGroupBox *, QList< QDoubleSpinBox * > >( group, list ) );
                list.clear();
            }
            l->addWidget( this->top_dialog_button_box, 7, 1, 1, 4 );
            l->addWidget( this->bottom_dialog_button_box, 8, 1, 1, 4 );
        }
        this->valueChanged();

        this->setFixedSize( this->sizeHint() );

        this->Reset();
        this->Apply();
    }

    this->setLayout( l );
}

C2DStraightSkirtDialog::~C2DStraightSkirtDialog()  {  }

void C2DStraightSkirtDialog::valueChanged()
{
    for ( int i = 0; i <= 2; i++ )
        for ( int j = 0; j <= 2; j++ )
            if ( j < this->spins[ i ]->value() )
            {
                if ( this->sets.value( i * 3 + j ).first )
                    this->sets.value( i * 3 + j ).first->setEnabled( true );
                else
                    qDebug() << "Missed" << i * 3 + j;
            }
            else
            {
                if ( this->sets.value( i * 3 + j ).first )
                    this->sets.value( i * 3 + j ).first->setEnabled( false );
                else
                    qDebug() << "Missed" << i * 3 + j;
            }
}

void C2DStraightSkirtDialog::Apply()
{
    qDebug() << "StraightSkirtDarts::Apply();";

    QList< double > list;

    QString first_name, count_name, second_name, full_name;

    for ( int i = 0; i <= 2; i++ )
    {
        switch( i )
        {
        case ( 0 ):
            first_name = QString( "%1:SideDarts" ).arg( this->prefix() );
            break;
        case ( 1 ):
            first_name = QString( "%1:FrontDarts" ).arg( this->prefix() );
            break;
        case ( 2 ):
            first_name = QString( "%1:BackDarts" ).arg( this->prefix() );
            break;
        }

        count_name = QString( "%1%2" ).arg( first_name ).arg( QString( "Count" ) );

        qDebug() << "Count: " << count_name << " = " << this->spins[ i ]->value();

        this->values[ count_name ] = QVariant( this->spins[ i ]->value() );

        for ( int j = 0; j <= 2; j++ )
        {
            second_name = QString( "%1%2" ).arg( first_name ).arg( j );

            if ( this->sets.value( i * 3 + j ).first )
            {
                for ( int k = 0; k <= 2; k++ )
                {
                    double value = this->sets.value( i * 3 + j ).second.at( k )->value();

                    list.append( value );

                    switch ( k )
                    {
                    case ( 0 ):
                        full_name = QString( "%1%2" ).arg( second_name ).arg( "Height" );
                        break;
                    case ( 1 ):
                        full_name = QString( "%1%2" ).arg( second_name ).arg( "Spread" );
                        break;
                    case ( 2 ):
                        full_name = QString( "%1%2" ).arg( second_name ).arg( "Width" );
                        break;
                    }
                    qDebug() << "Value: " << full_name << " = "
                                          << this->sets.value( i * 3 + j ).second.at( k )->value();
                    this->values[ full_name ] =
                            QVariant( this->sets.value( i * 3 + j ).second.at( k )->value() );

                    full_name.clear();
                }
                this->user.append( list );

                list.clear();
            }
            else
                qDebug() << "Missed" << i * 3 + j;

            second_name.clear();
        }
        first_name.clear();
    }

    this->transmitData( this->values );
}

void C2DStraightSkirtDialog::Reject()
{
    qDebug() << "StraightSkirtDarts::Reject();";

    for ( int i = 0; i <= 2; i++ )
        for ( int j = 0; j <= 2; j++ )
            if ( this->sets.value( i * 3 + j ).first->isEnabled() )
            {
                for ( int k = 0; k <= 2; k++ )
                    if ( this->user.at( i * 3 + j ).count() >= k )
                        this->sets.value( i * 3 + j )
                              .second.at( k )->setValue( this->user.at( i * 3 + j ).at( k ) );
                    else
                        this->sets.value( i * 3 + j )
                              .second.at( k )->setValue( 0.0f );
            }
            else
                qDebug() << "Missed" << i * 3 + j;
}

void C2DStraightSkirtDialog::Reset()
{
    qDebug() << "StraightSkirtDarts::Reset();";

    QList< QList< double > > list = this->defaults();

    qDebug() << list;

    for ( int i = 0; i <= 2; i++ )
        for ( int j = 0; j <= 2; j++ )
            if ( this->sets.value( i * 3 + j ).first->isEnabled() )
                for ( int k = 0; k <= 2; k++ )
                    this->sets.value( i * 3 + j )
                    .second.at( k )->setValue( list.at( i * 3 + j ).at( k ) );
            else
                qDebug() << "GroupBox " << i * 3 + j << " disabled.";
}

QList< QList< double > > C2DStraightSkirtDialog::defaults()
{
//    const Elasticas::CommonData & var = Elasticas::Core::Instance()->CommonVariables();

    int s = this->spins[ 0 ]->value();
    int f = this->spins[ 1 ]->value();
    int b = this->spins[ 2 ]->value();

    //Короткая инструкция
    //Для работы функции нужны переменные Т7, Т18, Т19, T46, T86, Р18, Р19.
    //Фунукция считает Spread (Раствор), Width (Растояние от линии симметрии) и Height (Длину)
    // для
    //Side1,
    //Front1,Front2,Front3
    //Back1,Back2,Back3
    //После расчета она записывает их в
    //Elasticas::CommonData var
    //с префиксом "Default"

    /*** HEADER ***/
    /*** INPUT  ***/

    //Measures
    double T7  = D( "T7"  );
    double T9  = D( "T9"  );
    double T18 = D( "T18" );
    double T19 = D( "T19" );
    double P18 = D( "P18" );
    double P19 = D( "P19" );
    double T46 = D( "T46" );
    double T86 = D( "T86" );

    qDebug() << "T7: " << T7;
    qDebug() << "T9: " << T9;
    qDebug() << "T18: " << T18;
    qDebug() << "T19: " << T19;
    qDebug() << "P18: " << P18;
    qDebug() << "P19: " << P19;
    qDebug() << "T46: " << T46;
    qDebug() << "T86: " << T86;

    double Width = T19 / 2.0f + P19;
    double WidthAtHipline = 0.5f * ( T19 - T18 ) + ( P19 - P18 ) ;

    double AB_f = T46 / 2.0f + 3.0f;
    double AB_b = 0.4f * Width / 2.0f;

    double a = T7 - T86;
    //a=T7-Vyt;

    /***   OUTPUT   ***/

    double SideDart0Width( 0.0f ),  SideDart0Height( 0.0f ),  SideDart0Spread( 0.0f );
    double SideDart1Width( 0.0f ),  SideDart1Height( 0.0f ),  SideDart1Spread( 0.0f );
    double SideDart2Width( 0.0f ),  SideDart2Height( 0.0f ),  SideDart2Spread( 0.0f );

    double FrontDart0Width( 0.0f ), FrontDart0Height( 0.0f ), FrontDart0Spread( 0.0f );
    double FrontDart1Width( 0.0f ), FrontDart1Height( 0.0f ), FrontDart1Spread( 0.0f );
    double FrontDart2Width( 0.0f ), FrontDart2Height( 0.0f ), FrontDart2Spread( 0.0f );

    double BackDart0Width( 0.0f ),  BackDart0Height( 0.0f ),  BackDart0Spread( 0.0f );
    double BackDart1Width( 0.0f ),  BackDart1Height( 0.0f ),  BackDart1Spread( 0.0f );
    double BackDart2Width( 0.0f ),  BackDart2Height( 0.0f ),  BackDart2Spread( 0.0f );

    /***   Header - end   ***/

    /***   Math - start   ***/

    //  side0( spread, height, width),  side1( spread, height, width),  side2( spread, height, width)
    // front0( spread, height, width), front1( spread, height, width), front2( spread, height, width)
    //  back0( spread, height, width),  back1( spread, height, width),  back2( spread, height, width)

    double spread_side[ 4 ][ 4 ] =
    {
        { 1.00f, 0.60f, 0.46f, 0.40f },
        { 0.60f, 0.50f, 0.40f, 0.40f },
        { 0.46f, 0.48f, 0.38f, 0.38f },
        { 0.40f, 0.48f, 0.38f, 0.38f }
    };

    double spread_front[ 4 ][ 4 ][ 3 ] =
    {
        { { 0.00f, 0.00f, 0.00f }, { 0.00f, 0.00f, 0.00f }, { 0.00f, 0.00f, 0.00f }, { 0.00f, 0.00f, 0.00f } },
        { { 0.40f, 0.00f, 0.00f }, { 0.18f, 0.00f, 0.00f }, { 0.18f, 0.00f, 0.00f }, { 0.18f, 0.00f, 0.00f } },
        { { 0.27f, 0.27f, 0.00f }, { 0.10f, 0.10f, 0.00f }, { 0.10f, 0.10f, 0.00f }, { 0.10f, 0.10f, 0.00f } },
        { { 0.20f, 0.20f, 0.20f }, { 0.0633f, 0.0633f, 0.0633 }, { 0.0633f, 0.0633f, 0.0633f }, { 0.0633f, 0.0633f, 0.0633f } }
    };

    double spread_back[ 4 ][ 4 ][ 3 ] =
    {
        { { 0.00f, 0.00f, 0.00f }, { 0.00f, 0.00f, 0.00f }, { 0.00f, 0.00f, 0.00f }, { 0.00f, 0.00f, 0.00f } },
        { { 0.40f, 0.00f, 0.00f }, { 0.32f, 0.00f, 0.00f }, { 0.32f, 0.00f, 0.00f }, { 0.32f, 0.00f, 0.00f } },
        { { 0.27f, 0.27f, 0.00f }, { 0.21f, 0.21f, 0.00f }, { 0.21f, 0.21f, 0.00f }, { 0.21f, 0.21f, 0.00f } },
        { { 0.20f, 0.20f, 0.20f }, { 0.14f, 0.14f, 0.14f }, { 0.14f, 0.14f, 0.14f }, { 0.14f, 0.14f, 0.14f } }
    };

    double height_side[ 4 ][ 3 ] =
    {
        { 0.0f, 0.0f, 0.0f },
        {    a, 0.0f, 0.0f },
        {    a, 0.0f, 0.0f },
        {    a, 0.0f, 0.0f }
    };

    double height_front[ 4 ][ 3 ] =
    {
        { 0.0f, 0.0f, 0.0f },
        { a * 0.50f - 10.00f, 0.0f, 0.0f },
        { a * 0.50f - 10.00f, a * 0.50f - 20.00f, 0.0f },
        { a * 0.50f - 20.00f, a * 0.50f - 20.00f, a * 0.50f - 20.00f }
    };

    double height_back[ 4 ][ 3 ] =
    {
        { 0.0f, 0.0f, 0.0f },
        { a * 0.80f - 10.00f, 0.0f, 0.0f },
        { a * 0.80f - 10.00f, a * 0.80f - 20.00f, 0.0f },
        { a * 0.80f - 20.00f, a * 0.80f - 20.00f, a * 0.80f - 20.00f }
    };

    double width_side[ 4 ][ 3 ] =
    {
        { 0.0f, 0.0f, 0.0f },
        { Width / 2.0f, 0.0f, 0.0f },
        { Width / 2.0f, 0.0f, 0.0f },
        { Width / 2.0f, 0.0f, 0.0f }
    };

    double width_back[ 4 ][ 3 ] =
    {
        { 0.0f, 0.0f, 0.0f },
        { AB_b, 0.0f, 0.0f },
        { AB_b, AB_b + ( Width / 2.0f - spread_side[ f ][ b ] * WidthAtHipline / 2.0f - AB_b ) * 0.5f, 0.0f },
        { AB_b,
          AB_b + ( Width / 2.0f - spread_side[ f ][ b ] * WidthAtHipline / 2.0f - AB_b ) * 0.333f,
          AB_b + ( Width / 2.0f - spread_side[ f ][ b ] * WidthAtHipline / 2.0f - AB_b ) * 0.666f }
    };

    double width_front[ 4 ][ 3 ] =
    {
        { 0.0f, 0.0f, 0.0f },
        { Width - AB_f, 0.0f, 0.0f },
        { Width - AB_f, Width / 2.00f + spread_side[ f ][ b ] * WidthAtHipline / 2.00f +
          ( Width - AB_f - Width / 2.00f - spread_side[ f ][ b ] * WidthAtHipline / 2.00f ) * 0.5f, 0.0f },
        { Width - AB_f,
          Width / 2.00f + spread_side[ f ][ b ] * WidthAtHipline / 2.00f +
          ( Width - AB_f - Width / 2.00f - spread_side[ f ][ b ] * WidthAtHipline / 2.00f ) * 0.333f,
          Width / 2.00f + spread_side[ f ][ b ] * WidthAtHipline / 2.00f +
          ( Width - AB_f - Width / 2.00f - spread_side[ f ][ b ] * WidthAtHipline / 2.00f ) * 0.666f }
    };

    SideDart0Spread = spread_side[ f ][ b ] * WidthAtHipline;
    SideDart0Height = height_side[ s ][ 0 ];
    SideDart0Width  =  width_side[ s ][ 0 ];

    FrontDart0Spread = spread_front[ f ][ b ][ 0 ] * WidthAtHipline;
    FrontDart0Height = height_front[ f ][ 0 ];
    FrontDart0Width  =  width_front[ f ][ 0 ];

    FrontDart1Spread = spread_front[ f ][ b ][ 1 ] * WidthAtHipline;
    FrontDart1Height = height_front[ f ][ 1 ];
    FrontDart1Width  =  width_front[ f ][ 1 ];

    FrontDart2Spread = spread_front[ f ][ b ][ 2 ] * WidthAtHipline;
    FrontDart2Height = height_front[ f ][ 2 ];
    FrontDart2Width  =  width_front[ f ][ 2 ];

    BackDart0Spread = spread_back[ b ][ f ][ 0 ] * WidthAtHipline;
    BackDart0Height = height_back[ b ][ 0 ];
    BackDart0Width  =  width_back[ b ][ 0 ];

    BackDart1Spread = spread_back[ b ][ f ][ 1 ] * WidthAtHipline;
    BackDart1Height = height_back[ b ][ 1 ];
    BackDart1Width  =  width_back[ b ][ 1 ];

    BackDart2Spread = spread_back[ b ][ f ][ 2 ] * WidthAtHipline;
    BackDart2Height = height_back[ b ][ 2 ];
    BackDart2Width  =  width_back[ b ][ 2 ];

    /***   MATH:END   ***/

    QList< double > small;
    QList< QList< double > > big;

    // i = 0 - First side dart
    small.append( SideDart0Height / this->modifier() );
    small.append( SideDart0Spread / this->modifier() );
    small.append( SideDart0Width  / this->modifier() );
    big.append( small );
    small.clear();

    // i = 1 - Second side dart
    small.append( SideDart1Height / this->modifier() );
    small.append( SideDart1Spread / this->modifier() );
    small.append( SideDart1Width  / this->modifier() );
    big.append( small );
    small.clear();

    // i = 2 - First side dart
    small.append( SideDart2Height / this->modifier() );
    small.append( SideDart2Spread / this->modifier() );
    small.append( SideDart2Width  / this->modifier() );
    big.append( small );
    small.clear();

    // i = 3 - First front dart
    small.append( FrontDart0Height / this->modifier() );
    small.append( FrontDart0Spread / this->modifier() );
    small.append( FrontDart0Width  / this->modifier() );
    big.append( small );
    small.clear();

    // i = 4 - Second front dart
    small.append( FrontDart1Height / this->modifier() );
    small.append( FrontDart1Spread / this->modifier() );
    small.append( FrontDart1Width  / this->modifier() );
    big.append( small );
    small.clear();

    // i = 5 - Third front dart
    small.append( FrontDart2Height / this->modifier() );
    small.append( FrontDart2Spread / this->modifier() );
    small.append( FrontDart2Width  / this->modifier() );
    big.append( small );
    small.clear();

    // i = 6 - First back dart
    small.append( BackDart0Height / this->modifier() );
    small.append( BackDart0Spread / this->modifier() );
    small.append( BackDart0Width  / this->modifier() );
    big.append( small );
    small.clear();

    // i = 7 - Second back dart
    small.append( BackDart1Height / this->modifier() );
    small.append( BackDart1Spread / this->modifier() );
    small.append( BackDart1Width  / this->modifier() );
    big.append( small );
    small.clear();

    // i = 8 - Third Back dart
    small.append( BackDart2Height / this->modifier() );
    small.append( BackDart2Spread / this->modifier() );
    small.append( BackDart2Width  / this->modifier() );
    big.append( small );
    small.clear();

    return big;
}

void C2DStraightSkirtDialog::requiredVariables()
{
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
    this->addVariable( C2DVariable::set( "T46", "T46", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "T86", "T86", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 10.0f ) );

    //P18 - прибавка к полуобхвату талии
    //P19 - прибавка к полуобхвату бедер
    this->addVariable( C2DVariable::set( "P18", this->prefix() + ":P18", "Not described",
                       C2DVariable::Metrics, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "P19", this->prefix() + ":P19", "Not described",
                       C2DVariable::Metrics, C2DVariable::General, 0.0f, 10.0f ) );


}
