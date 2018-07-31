#include "C2DDressDialog.h"

C2DDressDialog::C2DDressDialog( const QString            & name,
                                const QString            & prefix,
                                const QString            & tab,
                                QPair< QString, double >   units,
                                QWidget                  * parent )
    : C2DItemDialog( name, prefix, tab, units, parent )
{

    this->requiredVariables();

    QGridLayout * l = new QGridLayout( this );

    QTextCodec::setCodecForTr( QTextCodec::codecForName( "UTF-8" ) );

    if ( l )
    {
        tabwidget[0] = new QWidget;
        tablayout[0] = new QGridLayout;
        tabwidget[0]->setLayout(tablayout[0]);

        tabs = new QTabWidget;

        for ( int i = 0; i <= 9; i++ )
            dressspin[ i ] = new QDoubleSpinBox( this );

        for ( int i = 0; i <= 4; i++ )
            middleline[ i ] = new QDoubleSpinBox( this );

        for ( int i = 0; i <= 3; i++ )
            dressspin2[ i ] = new QDoubleSpinBox( this );

    ////////////////////////////////////////////////////Первая вкладка
        tablayout[0]->addWidget( new QLabel( this->trUtf8( "47-471. K (0...2 см):" ) ), 0, 0 );
        dressspin[0]->setMinimum( 0 );
        dressspin[0]->setMaximum( 2 );
        dressspin[0]->setSingleStep( 0.1f );
        tablayout[0]->addWidget( dressspin[0] , 0, 1 );

        tablayout[0]->addWidget( new QLabel( this->trUtf8( "Раствор вытачки 14-14'. K3 (1...4 см):" ) ), 1, 0 );
        dressspin[3]->setMinimum( 1 );
        dressspin[3]->setMaximum( 4 );
        dressspin[3]->setSingleStep( 0.1f );
        tablayout[0]->addWidget( dressspin[3] , 1, 1 );

        tablayout[0]->addWidget( new QLabel( this->trUtf8( "Ширина горловины /11-12/ - K4 (0...1 см):" ) ), 2, 0 );
        dressspin[4]->setMinimum( 0 );
        dressspin[4]->setMaximum( 1 );
        dressspin[4]->setSingleStep( 0.1f );
        tablayout[0]->addWidget( dressspin[4] , 2, 1 );

        tablayout[0]->addWidget( new QLabel( this->trUtf8( "/33-331/. K7 (см):" ) ), 3, 0 );
       // dressspin[7]->setMinimum( 0 );
       // dressspin[7]->setMaximum( 10 ) ;
        dressspin[7]->setSingleStep( 0.1f );
        tablayout[0]->addWidget( dressspin[7] , 3, 1 );

        tablayout[0]->addWidget( new QLabel( this->trUtf8( "/33-35/ * K8:" ) ), 4, 0 );
        dressspin[8]->setMinimum( 0.25 );
        dressspin[8]->setMaximum( 0.5 ) ;
        dressspin[8]->setSingleStep( 0.01f );
        tablayout[0]->addWidget( dressspin[8] , 4, 1 );

        tablayout[0]->addWidget( new QLabel( this->trUtf8( "Расширение спинки на линии низа. K9 (-5...10 см):" ) ), 5, 0 );
        dressspin[9]->setMinimum( -5 );
        dressspin[9]->setMaximum( 10 ) ;
        dressspin[9]->setSingleStep( 0.1f );
        tablayout[0]->addWidget( dressspin[9] , 5, 1 );



        tablayout[0]->addWidget( new QLabel( this->trUtf8( "Расстояние от горизонтали низа до нижней балансовой горизонтали переда (см):" ) ), 7, 0 );
      //  dressspin2[1]->setMinimum( -5 );
      //  dressspin2[1]->setMaximum( 10 ) ;
        dressspin2[1]->setSingleStep( 0.1f );
        tablayout[0]->addWidget( dressspin2[1] , 7, 1 );

        tablayout[0]->addWidget( new QLabel( this->trUtf8( "Прибавка к высоте горловины (см):" ) ), 8, 0 );
      //  dressspin2[2]->setMinimum( -5 );
      //  dressspin2[2]->setMaximum( 10 ) ;
        dressspin2[2]->setSingleStep( 0.1f );
        tablayout[0]->addWidget( dressspin2[2] , 8, 1 );

        tabs->addTab( tabwidget[0], trUtf8("Рассчетные коэффициенты") );
    /////////////////////////////////////////////////вкладка 2

        tabwidget[1] = new QWidget;
        tablayout[1] = new QGridLayout;
        tabwidget[1]->setLayout(tablayout[1]);

        tablayout[1]->addWidget( new QLabel( this->trUtf8( "Параметры плечевой вытачки полочки, см" ) ), 0, 0, 1, 4 );
        QLabel * label = new QLabel( this );
        label->setPixmap( QPixmap( "images/dress/dressp.jpg" ) );
        tablayout[1]->addWidget( label, 1, 0, 10 , 2, Qt::AlignTop);

        //tablayout[1]->addWidget( new QLabel( this->trUtf8( "Раствор вытачки. /26-26'/ + K6 (0...10 см):" ) ), 0, 1 );
        tablayout[1]->addWidget( new QLabel( this->trUtf8( "K2 (0...10 см):" ) ), 1, 2 );
        dressspin[6]->setMinimum( -10 );
        dressspin[6]->setMaximum( 10 ) ;
        dressspin[6]->setSingleStep( 0.1f );
        tablayout[1]->addWidget( dressspin[6] , 1, 3 );

        tablayout[1]->addWidget( new QLabel( this->trUtf8( "K2 (0...2 см):" ) ), 2, 2 );
        dressspin[5]->setMinimum( 0 );
        dressspin[5]->setMaximum( 2 );
        dressspin[5]->setSingleStep( 0.1f );
        tablayout[1]->addWidget( dressspin[5] , 2, 3 );

        tablayout[1]->addWidget( new QLabel( this->trUtf8( "K3 (см):" ) ), 3, 2 );
      //  dressspin2[3]->setMinimum( -5 );
      //  dressspin2[3]->setMaximum( 10 ) ;
        dressspin2[3]->setSingleStep( 0.1f );
        tablayout[1]->addWidget( dressspin2[3] , 3, 3 );

        tablayout[1]->addWidget( new QLabel( this->trUtf8( "K4 (см):" ) ), 4, 2 );
      //  dressspin2[0]->setMinimum( -5 );
      //  dressspin2[0]->setMaximum( 10 ) ;
        dressspin2[0]->setSingleStep( 0.1f );
        tablayout[1]->addWidget( dressspin2[0] , 4, 3 );

        tabs->addTab( tabwidget[1], trUtf8("Полочка") );

    //////////ВКЛАДКА 3 Спинка
        tabwidget[2] = new QWidget;
        tablayout[2] = new QGridLayout;
        tabwidget[2]->setLayout(tablayout[2]);

        tablayout[2]->addWidget( new QLabel( this->trUtf8( "Параметры плечевой вытачки спинки, см" ) ), 0, 0, 1, 4 );
        QLabel * label2 = new QLabel( this );
        label2->setPixmap( QPixmap( "images/dress/dresss.jpg" ) );
        tablayout[2]->addWidget( label2, 1, 0, 10 , 2, Qt::AlignTop);


        //tablayout[1]->addWidget( new QLabel( this->trUtf8( "Раствор вытачки. /26-26'/ + K6 (0...10 см):" ) ), 0, 1 );
        tablayout[2]->addWidget( new QLabel( this->trUtf8( "K (-2...2 см):" ) ), 1, 2 );
        dressspin[1]->setMinimum( -2 );
        dressspin[1]->setMaximum( 2 );
        dressspin[1]->setSingleStep( 0.1f );
        tablayout[2]->addWidget( dressspin[1] , 1, 3 );

        tablayout[2]->addWidget( new QLabel( this->trUtf8( "L (5...10 см):" ) ), 2, 2 );
        dressspin[2]->setMinimum( 5 );
        dressspin[2]->setMaximum( 10 );
        dressspin[2]->setSingleStep( 0.1f );
        tablayout[2]->addWidget( dressspin[2] , 2, 3 );

        tabs->addTab( tabwidget[2], trUtf8("Спинка") );

    //////////ВКЛАДКА 4 Средняя линия спинки
        tabwidget[3] = new QWidget;
        tablayout[3] = new QGridLayout;
        tabwidget[3]->setLayout(tablayout[3]);

        tablayout[3]->addWidget( new QLabel( this->trUtf8( "Параметры средней линии спинки, см" ) ), 0, 0, 1, 4 );
        QLabel * label3 = new QLabel( this );
        label3->setPixmap( QPixmap( "images/dress/dresssred.jpg" ) );
        tablayout[3]->addWidget( label3, 1, 0, 10 , 2, Qt::AlignTop);


        //tablayout[1]->addWidget( new QLabel( this->trUtf8( "Раствор вытачки. /26-26'/ + K6 (0...10 см):" ) ), 0, 1 );
        tablayout[3]->addWidget( new QLabel( this->trUtf8( "K1 (см):" ) ), 1, 2 );
        middleline[0]->setSingleStep( 0.1f );
        tablayout[3]->addWidget( middleline[0] , 1, 3 );

        tablayout[3]->addWidget( new QLabel( this->trUtf8( "K2 (см):" ) ), 2, 2 );
        middleline[1]->setSingleStep( 0.1f );
        tablayout[3]->addWidget( middleline[1] , 2, 3 );

        tablayout[3]->addWidget( new QLabel( this->trUtf8( "K3 (см):" ) ), 3, 2 );
        middleline[2]->setSingleStep( 0.1f );
        tablayout[3]->addWidget( middleline[2] , 3, 3 );

        tablayout[3]->addWidget( new QLabel( this->trUtf8( "K4 (см):" ) ), 4, 2 );
        middleline[3]->setSingleStep( 0.1f );
        tablayout[3]->addWidget( middleline[3] , 4, 3 );

        tablayout[3]->addWidget( new QLabel( this->trUtf8( "K5 (см):" ) ), 5, 2 );
        middleline[4]->setSingleStep( 0.1f );
        tablayout[3]->addWidget( middleline[4] , 5, 3 );

        tabs->addTab( tabwidget[3], trUtf8("Параметры средней линии спинки") );
    //////////////////////////////////////////////////////////////////////
        l->addWidget( tabs, 1, 0, 1, 2 );
        l->addWidget( this->top_dialog_button_box, 2, 0, 1, 2 );
        l->addWidget( this->bottom_dialog_button_box, 3, 0, 1, 2);

        this->setFixedSize( this->sizeHint() );

        this->Reset();
        this->Apply();
    }
    this->setLayout( l );

}

void C2DDressDialog::Apply()
{
    qDebug() << "Apply.";
    this->dressdialog_list.clear();
    this->dressdialog_list << this->dressspin[0]->value()
                           << this->dressspin[1]->value()
                           << this->dressspin[2]->value()
                           << this->dressspin[3]->value()
                           << this->dressspin[4]->value()
                           << this->dressspin[5]->value()
                           << this->dressspin[6]->value()
                           << this->dressspin[7]->value()
                           << this->dressspin[8]->value()
                           << this->dressspin[9]->value()
                           << this->middleline[0]->value()
                           << this->middleline[1]->value()
                           << this->middleline[2]->value()
                           << this->middleline[3]->value()
                           << this->middleline[4]->value()
                           << this->dressspin2[0]->value()
                           << this->dressspin2[1]->value()
                           << this->dressspin2[2]->value()
                           << this->dressspin2[3]->value();


    this->values.insert( QString( "%1%2" ).arg( this->prefix() ).arg( "K0" ), QVariant( this->dressdialog_list.at( 0 ) ) );
    this->values.insert( QString( "%1%2" ).arg( this->prefix() ).arg( "K1" ), QVariant( this->dressdialog_list.at( 1 ) ) );
    this->values.insert( QString( "%1%2" ).arg( this->prefix() ).arg( "K2" ), QVariant( this->dressdialog_list.at( 2 ) ) );
    this->values.insert( QString( "%1%2" ).arg( this->prefix() ).arg( "K3" ), QVariant( this->dressdialog_list.at( 3 ) ) );
    this->values.insert( QString( "%1%2" ).arg( this->prefix() ).arg( "K4" ), QVariant( this->dressdialog_list.at( 4 ) ) );
    this->values.insert( QString( "%1%2" ).arg( this->prefix() ).arg( "K5" ), QVariant( this->dressdialog_list.at( 5 ) ) );
    this->values.insert( QString( "%1%2" ).arg( this->prefix() ).arg( "K6" ), QVariant( this->dressdialog_list.at( 6 ) ) );
    this->values.insert( QString( "%1%2" ).arg( this->prefix() ).arg( "Pspr" ), QVariant( this->dressdialog_list.at( 7 ) ) );
    this->values.insert( QString( "%1%2" ).arg( this->prefix() ).arg( "K7" ), QVariant( this->dressdialog_list.at( 8 ) ) );
    this->values.insert( QString( "%1%2" ).arg( this->prefix() ).arg( "K8" ), QVariant( this->dressdialog_list.at( 9 ) ) );

    this->values.insert( QString( "%1%2" ).arg( this->prefix() ).arg( "K11" ), QVariant( this->dressdialog_list.at( 10 ) ) );
    this->values.insert( QString( "%1%2" ).arg( this->prefix() ).arg( "K31" ), QVariant( this->dressdialog_list.at( 11 ) ) );
    this->values.insert( QString( "%1%2" ).arg( this->prefix() ).arg( "K41" ), QVariant( this->dressdialog_list.at( 12 ) ) );
    this->values.insert( QString( "%1%2" ).arg( this->prefix() ).arg( "K51" ), QVariant( this->dressdialog_list.at( 13 ) ) );
    this->values.insert( QString( "%1%2" ).arg( this->prefix() ).arg( "K91" ), QVariant( this->dressdialog_list.at( 14 ) ) );

    this->values.insert( QString( "%1%2" ).arg( this->prefix() ).arg( "K01" ), QVariant( this->dressdialog_list.at( 15 ) ) );
    this->values.insert( QString( "%1%2" ).arg( this->prefix() ).arg( "K02" ), QVariant( this->dressdialog_list.at( 16 ) ) );
    this->values.insert( QString( "%1%2" ).arg( this->prefix() ).arg( "K03" ), QVariant( this->dressdialog_list.at( 17 ) ) );
    this->values.insert( QString( "%1%2" ).arg( this->prefix() ).arg( "K36" ), QVariant( this->dressdialog_list.at( 18 ) ) );

    this->transmitData( this->values );
}

void C2DDressDialog::Reject()
{
    if ( this->dressdialog_list.isEmpty() )
        this->Reset();
    else
    {
        this->dressspin[0]->setValue( this->dressdialog_list.at( 0 ).toFloat() );
        this->dressspin[1]->setValue( this->dressdialog_list.at( 1 ).toFloat() );
        this->dressspin[2]->setValue( this->dressdialog_list.at( 2 ).toFloat() );
        this->dressspin[3]->setValue( this->dressdialog_list.at( 3 ).toFloat() );
        this->dressspin[4]->setValue( this->dressdialog_list.at( 4 ).toFloat() );
        this->dressspin[5]->setValue( this->dressdialog_list.at( 5 ).toFloat() );
        this->dressspin[6]->setValue( this->dressdialog_list.at( 6 ).toFloat() );
        this->dressspin[7]->setValue( this->dressdialog_list.at( 7 ).toFloat() );
        this->dressspin[8]->setValue( this->dressdialog_list.at( 8 ).toFloat() );
        this->dressspin[9]->setValue( this->dressdialog_list.at( 9 ).toFloat() );

        this->middleline[0]->setValue( this->dressdialog_list.at( 10 ).toFloat() );
        this->middleline[1]->setValue( this->dressdialog_list.at( 11 ).toFloat() );
        this->middleline[2]->setValue( this->dressdialog_list.at( 12 ).toFloat() );
        this->middleline[3]->setValue( this->dressdialog_list.at( 13 ).toFloat() );
        this->middleline[4]->setValue( this->dressdialog_list.at( 14 ).toFloat() );

        this->dressspin2[0]->setValue( this->dressdialog_list.at( 15 ).toFloat() );
        this->dressspin2[1]->setValue( this->dressdialog_list.at( 16 ).toFloat() );
        this->dressspin2[2]->setValue( this->dressdialog_list.at( 17 ).toFloat() );
        this->dressspin2[3]->setValue( this->dressdialog_list.at( 18 ).toFloat() );
    }
}

void C2DDressDialog::Reset()
{
    dressspin[0]->setValue( 2.0f );
    dressspin[1]->setValue( 0.0f );
    dressspin[2]->setValue( 7.0f );
    dressspin[3]->setValue( 2.5f );
    dressspin[4]->setValue( 0.0f );
    dressspin[5]->setValue( 1.0f );
    dressspin[6]->setValue( 0.5f );
    dressspin[7]->setValue( 3.5f );
    dressspin[8]->setValue( 0.35f );
    dressspin[9]->setValue( 3.0f );

    middleline[0]->setValue( 0.0f );
    middleline[1]->setValue( 0.0f );
    middleline[2]->setValue( 2.0f );
    middleline[3]->setValue( 2.0f );
    middleline[4]->setValue( 3.0f );

    dressspin2[0]->setValue( 0.5f );
    dressspin2[1]->setValue( 1.0f );
    dressspin2[2]->setValue( 0.5f );
    dressspin2[3]->setValue( 1.5f );

    this->dressdialog_list.clear();

}

QList< QList< double > > C2DDressDialog::defaults()
{
    this->Reset();
}

void C2DDressDialog::requiredVariables()
{



}
