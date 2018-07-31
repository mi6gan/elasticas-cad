#include "C2DBlouseDialog.h"

C2DBlouseDialog::C2DBlouseDialog( const QString            & name,
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
        for ( int i = 1; i <= 10; i++ )
        {
            blousespin[ i ] = new QDoubleSpinBox( this );
            blousespin[ i ]->setMinimum( -100 );
            blousespin[ i ]->setMaximum( 100 );
        }
        QLabel * label = new QLabel( this );
        label->setPixmap( QPixmap( "images/blouse/blouse.jpg" ) );
        l->addWidget( label, 0, 0, 12 ,1);

        l->addWidget( new QLabel( this->trUtf8( "Блузка: " ) ), 0, 1, Qt::AlignTop );

        l->addWidget( new QLabel( this->trUtf8( "K1 (см):" ) ), 1, 1, Qt::AlignTop );
        //blousespin[0]->setMinimum( 0 );
        //blousespin[0]->setMaximum( 1 );
        blousespin[1]->setSingleStep( 0.1f );
        l->addWidget( blousespin[1] , 1, 2, Qt::AlignTop );

        l->addWidget( new QLabel( this->trUtf8( "K2 (см):"  ) ), 2, 1, Qt::AlignTop );
        //blousespin[1]->setMinimum( 1 );
        //blousespin[1]->setMaximum( 4 );
        blousespin[2]->setSingleStep( 0.1f );
        l->addWidget( blousespin[2] , 2, 2, Qt::AlignTop );

        l->addWidget( new QLabel( this->trUtf8( "K3 (см):" ) ), 3, 1, Qt::AlignTop );
        //blousespin[2]->setMinimum( 8 );
        //blousespin[2]->setMaximum( 80 );
        blousespin[3]->setSingleStep(0.1);
        l->addWidget( blousespin[3] , 3, 2, Qt::AlignTop );

        l->addWidget( new QLabel( this->trUtf8( "K4 (см):" ) ), 4, 1, Qt::AlignTop );
        //blousespin[3]->setMinimum( 6 );
        //blousespin[3]->setMaximum( 80 );
        blousespin[4]->setSingleStep(0.5);
        l->addWidget( blousespin[4] , 4, 2, Qt::AlignTop );

        l->addWidget( new QLabel( this->trUtf8( "K5 (см):" ) ), 5, 1, Qt::AlignTop );
        //blousespin[3]->setMinimum( 6 );
        //blousespin[3]->setMaximum( 80 );
        blousespin[5]->setSingleStep(0.5);
        l->addWidget( blousespin[5] , 5, 2, Qt::AlignTop );

        l->addWidget( new QLabel( this->trUtf8( "K6 (см):" ) ), 6, 1, Qt::AlignTop );
        //blousespin[3]->setMinimum( 6 );
        //blousespin[3]->setMaximum( 80 );
        blousespin[6]->setSingleStep(0.5);
        l->addWidget( blousespin[6] , 6, 2, Qt::AlignTop );

        l->addWidget( new QLabel( this->trUtf8( "K7 (см):" ) ), 7, 1, Qt::AlignTop );
        //blousespin[3]->setMinimum( 6 );
        //blousespin[3]->setMaximum( 80 );
        blousespin[7]->setSingleStep(0.5);
        l->addWidget( blousespin[7] , 7, 2, Qt::AlignTop );

        l->addWidget( new QLabel( this->trUtf8( "K8 (см):" ) ), 8, 1, Qt::AlignTop );
        //blousespin[3]->setMinimum( 6 );
        //blousespin[3]->setMaximum( 80 );
        blousespin[8]->setSingleStep(0.5);
        l->addWidget( blousespin[8] , 8, 2, Qt::AlignTop );

        l->addWidget( new QLabel( this->trUtf8( "K9 (см):" ) ), 9, 1, Qt::AlignTop );
        //blousespin[3]->setMinimum( 6 );
        //blousespin[3]->setMaximum( 80 );
        blousespin[9]->setSingleStep(0.5);
        l->addWidget( blousespin[9] , 9, 2, Qt::AlignTop );

        l->addWidget( new QLabel( this->trUtf8( "K10 (см):" ) ), 10, 1, Qt::AlignTop );
        //blousespin[3]->setMinimum( 6 );
        //blousespin[3]->setMaximum( 80 );
        blousespin[10]->setSingleStep(0.5);
        l->addWidget( blousespin[10] , 10, 2, Qt::AlignTop );


        l->addWidget( this->top_dialog_button_box, 11, 1, 1, 2 );
        l->addWidget( this->bottom_dialog_button_box, 12, 1, 1, 2);

        this->setFixedSize( this->sizeHint() );

        this->Reset();
        this->Apply();

    }

    this->setLayout( l );
}

void C2DBlouseDialog::Apply()
{
    qDebug() << "Apply.";
    this->blousedialog_list.clear();
    this->blousedialog_list << this->blousespin[1]->value()
                            << this->blousespin[2]->value()
                            << this->blousespin[3]->value()
                            << this->blousespin[4]->value()
                            << this->blousespin[5]->value()
                            << this->blousespin[6]->value()
                            << this->blousespin[7]->value()
                            << this->blousespin[8]->value()
                            << this->blousespin[9]->value()
                            << this->blousespin[10]->value();


    this->values.insert( QString( "%1%2" ).arg( this->prefix() ).arg( "P5" ), QVariant( this->blousedialog_list.at( 0 ) ) );
    this->values.insert( QString( "%1%2" ).arg( this->prefix() ).arg( "P15" ), QVariant( this->blousedialog_list.at( 1 ) ) );
    this->values.insert( QString( "%1%2" ).arg( this->prefix() ).arg( "P17" ), QVariant( this->blousedialog_list.at( 2 ) ) );
    this->values.insert( QString( "%1%2" ).arg( this->prefix() ).arg( "P18" ), QVariant( this->blousedialog_list.at( 3 ) ) );
    this->values.insert( QString( "%1%2" ).arg( this->prefix() ).arg( "P19" ), QVariant( this->blousedialog_list.at( 4 ) ) );
    this->values.insert( QString( "%1%2" ).arg( this->prefix() ).arg( "P20" ), QVariant( this->blousedialog_list.at( 5 ) ) );
    this->values.insert( QString( "%1%2" ).arg( this->prefix() ).arg( "P21" ), QVariant( this->blousedialog_list.at( 6 ) ) );
    this->values.insert( QString( "%1%2" ).arg( this->prefix() ).arg( "P22" ), QVariant( this->blousedialog_list.at( 7 ) ) );
    this->values.insert( QString( "%1%2" ).arg( this->prefix() ).arg( "P23" ), QVariant( this->blousedialog_list.at( 8 ) ) );
    this->values.insert( QString( "%1%2" ).arg( this->prefix() ).arg( "P13'" ), QVariant( this->blousedialog_list.at( 9 ) ) );

    this->transmitData( this->values );
}

void C2DBlouseDialog::Reject()
{
    if ( this->blousedialog_list.isEmpty() )
        this->Reset();
    else
    {
        this->blousespin[1]->setValue( this->blousedialog_list.at( 0 ).toFloat() );
        this->blousespin[2]->setValue( this->blousedialog_list.at( 1 ).toFloat() );
        this->blousespin[3]->setValue( this->blousedialog_list.at( 2 ).toFloat() );
        this->blousespin[4]->setValue( this->blousedialog_list.at( 3 ).toFloat() );
        this->blousespin[5]->setValue( this->blousedialog_list.at( 4 ).toFloat() );
        this->blousespin[6]->setValue( this->blousedialog_list.at( 5 ).toFloat() );
        this->blousespin[7]->setValue( this->blousedialog_list.at( 6 ).toFloat() );
        this->blousespin[8]->setValue( this->blousedialog_list.at( 7 ).toFloat() );
        this->blousespin[9]->setValue( this->blousedialog_list.at( 8 ).toFloat() );
        this->blousespin[10]->setValue( this->blousedialog_list.at( 9 ).toFloat() );
    }
}

void C2DBlouseDialog::Reset()
{
    blousespin[1]->setValue( 2.0f );//"P5"
    blousespin[2]->setValue( 2.0f );//"P15"
    blousespin[3]->setValue( 1.5f );//P17
    blousespin[4]->setValue( 0.0f );//P18
    blousespin[5]->setValue( 0.0f );//P19
    blousespin[6]->setValue( -2.0f );//P20
    blousespin[7]->setValue( 0.5f );//P21
    blousespin[8]->setValue( 1.5f );//P22
    blousespin[9]->setValue( 0.5f );//P23
    blousespin[10]->setValue( 0.5f );//P13'
    this->blousedialog_list.clear();
}

QList< QList< double > > C2DBlouseDialog::defaults()
{
    this->Reset();
}
void C2DBlouseDialog::requiredVariables()
{


}
