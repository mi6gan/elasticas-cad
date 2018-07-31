#include "C2DJacketDialog.h"

C2DJacketDialog::C2DJacketDialog( const QString            & name,
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
        for ( int i = 1; i <= 13; i++ )
        {
            jacketspin[ i ] = new QDoubleSpinBox( this );
            jacketspin[ i ]->setMinimum( -100 );
            jacketspin[ i ]->setMaximum( 100 );
        }
        QLabel * label = new QLabel( this );
        label->setPixmap( QPixmap( "images/jacket/jacket.jpg" ) );
        l->addWidget( label, 0, 0, 15 ,1);

        l->addWidget( new QLabel( this->trUtf8( "Пиджак: " ) ), 0, 1, Qt::AlignTop );

        l->addWidget( new QLabel( this->trUtf8( "K1 (см):" ) ), 1, 1, Qt::AlignTop );
        //jacketspin[0]->setMinimum( 0 );
        //jacketspin[0]->setMaximum( 1 );
        jacketspin[1]->setSingleStep( 0.1f );
        l->addWidget( jacketspin[1] , 1, 2, Qt::AlignTop );

        l->addWidget( new QLabel( this->trUtf8( "K2 (см):"  ) ), 2, 1, Qt::AlignTop );
        //jacketspin[1]->setMinimum( 1 );
        //jacketspin[1]->setMaximum( 4 );
        jacketspin[2]->setSingleStep( 0.1f );
        l->addWidget( jacketspin[2] , 2, 2, Qt::AlignTop );

        l->addWidget( new QLabel( this->trUtf8( "K3 (см):" ) ), 3, 1, Qt::AlignTop );
        //jacketspin[2]->setMinimum( 8 );
        //jacketspin[2]->setMaximum( 80 );
        jacketspin[3]->setSingleStep(0.1);
        l->addWidget( jacketspin[3] , 3, 2, Qt::AlignTop );

        l->addWidget( new QLabel( this->trUtf8( "K4 (см):" ) ), 4, 1, Qt::AlignTop );
        //jacketspin[3]->setMinimum( 6 );
        //jacketspin[3]->setMaximum( 80 );
        jacketspin[4]->setSingleStep(0.5);
        l->addWidget( jacketspin[4] , 4, 2, Qt::AlignTop );

        l->addWidget( new QLabel( this->trUtf8( "K5 (см):" ) ), 5, 1, Qt::AlignTop );
        //jacketspin[3]->setMinimum( 6 );
        //jacketspin[3]->setMaximum( 80 );
        jacketspin[5]->setSingleStep(0.5);
        l->addWidget( jacketspin[5] , 5, 2, Qt::AlignTop );

        l->addWidget( new QLabel( this->trUtf8( "K6 (см):" ) ), 6, 1, Qt::AlignTop );
        //jacketspin[3]->setMinimum( 6 );
        //jacketspin[3]->setMaximum( 80 );
        jacketspin[6]->setSingleStep(0.5);
        l->addWidget( jacketspin[6] , 6, 2, Qt::AlignTop );

        l->addWidget( new QLabel( this->trUtf8( "K7 (см):" ) ), 7, 1, Qt::AlignTop );
        //jacketspin[3]->setMinimum( 6 );
        //jacketspin[3]->setMaximum( 80 );
        jacketspin[7]->setSingleStep(0.5);
        l->addWidget( jacketspin[7] , 7, 2, Qt::AlignTop );

        l->addWidget( new QLabel( this->trUtf8( "K8 (%):" ) ), 8, 1, Qt::AlignTop );
        jacketspin[8]->setMinimum( 0 );
        jacketspin[8]->setMaximum( 100 );
        jacketspin[8]->setSingleStep(1);
        l->addWidget( jacketspin[8] , 8, 2, Qt::AlignTop );

        l->addWidget( new QLabel( this->trUtf8( "K9 (см):" ) ), 9, 1, Qt::AlignTop );
        //jacketspin[3]->setMinimum( 6 );
        //jacketspin[3]->setMaximum( 80 );
        jacketspin[9]->setSingleStep(0.5);
        l->addWidget( jacketspin[9] , 9, 2, Qt::AlignTop );

        l->addWidget( new QLabel( this->trUtf8( "K10 (см):" ) ), 10, 1, Qt::AlignTop );
        //jacketspin[3]->setMinimum( 6 );
        //jacketspin[3]->setMaximum( 80 );
        jacketspin[10]->setSingleStep(0.5);
        l->addWidget( jacketspin[10] , 10, 2, Qt::AlignTop );

        l->addWidget( new QLabel( this->trUtf8( "K11 (см):" ) ), 11, 1, Qt::AlignTop );
        //jacketspin[3]->setMinimum( 6 );
        //jacketspin[3]->setMaximum( 80 );
        jacketspin[11]->setSingleStep(0.5);
        l->addWidget( jacketspin[11] , 11, 2, Qt::AlignTop );

        l->addWidget( new QLabel( this->trUtf8( "K12 (см):" ) ), 12, 1, Qt::AlignTop );
        //jacketspin[3]->setMinimum( 6 );
        //jacketspin[3]->setMaximum( 80 );
        jacketspin[12]->setSingleStep(0.5);
        l->addWidget( jacketspin[12] , 12, 2, Qt::AlignTop );

        l->addWidget( new QLabel( this->trUtf8( "K13 (град.):" ) ), 13, 1, Qt::AlignTop );
        //jacketspin[3]->setMinimum( 6 );
        //jacketspin[3]->setMaximum( 80 );
        jacketspin[13]->setSingleStep(0.5);
        l->addWidget( jacketspin[13] , 13, 2, Qt::AlignTop );


        l->addWidget( this->top_dialog_button_box, 14, 1, 1, 2 );
        l->addWidget( this->bottom_dialog_button_box, 15, 1, 1, 2);

        this->setFixedSize( this->sizeHint() );

        this->Reset();
        this->Apply();

    }

    this->setLayout( l );
}

void C2DJacketDialog::Apply()
{
    qDebug() << "Apply.";
    this->jacketdialog_list.clear();
    this->jacketdialog_list << this->jacketspin[1]->value()
                            << this->jacketspin[2]->value()
                            << this->jacketspin[3]->value()
                            << this->jacketspin[4]->value()
                            << this->jacketspin[5]->value()
                            << this->jacketspin[6]->value()
                            << this->jacketspin[7]->value()
                            << this->jacketspin[8]->value()
                            << this->jacketspin[9]->value()
                            << this->jacketspin[10]->value()
                            << this->jacketspin[11]->value()
                            << this->jacketspin[12]->value()
                            << this->jacketspin[13]->value();


    this->values.insert( QString( "%1%2" ).arg( this->prefix() ).arg( "P14" ), QVariant( this->jacketdialog_list.at( 0 ) ) );
    this->values.insert( QString( "%1%2" ).arg( this->prefix() ).arg( "P16" ), QVariant( this->jacketdialog_list.at( 1 ) ) );
    this->values.insert( QString( "%1%2" ).arg( this->prefix() ).arg( "P97" ), QVariant( this->jacketdialog_list.at( 2 ) ) );
    this->values.insert( QString( "%1%2" ).arg( this->prefix() ).arg( "P161" ), QVariant( this->jacketdialog_list.at( 3 ) ) );
    this->values.insert( QString( "%1%2" ).arg( this->prefix() ).arg( "P331" ), QVariant( this->jacketdialog_list.at( 4 ) ) );
    this->values.insert( QString( "%1%2" ).arg( this->prefix() ).arg( "P341" ), QVariant( this->jacketdialog_list.at( 5 ) ) );
    this->values.insert( QString( "%1%2" ).arg( this->prefix() ).arg( "P332" ), QVariant( this->jacketdialog_list.at( 6 ) ) );
    this->values.insert( QString( "%1%2" ).arg( this->prefix() ).arg( "P346" ), QVariant( this->jacketdialog_list.at( 7 ) ) );
    this->values.insert( QString( "%1%2" ).arg( this->prefix() ).arg( "P352" ), QVariant( this->jacketdialog_list.at( 8 ) ) );
    this->values.insert( QString( "%1%2" ).arg( this->prefix() ).arg( "P411" ), QVariant( this->jacketdialog_list.at( 9 ) ) );
    this->values.insert( QString( "%1%2" ).arg( this->prefix() ).arg( "P511" ), QVariant( this->jacketdialog_list.at( 10 ) ) );
    this->values.insert( QString( "%1%2" ).arg( this->prefix() ).arg( "P911" ), QVariant( this->jacketdialog_list.at( 11 ) ) );
    this->values.insert( QString( "%1%2" ).arg( this->prefix() ).arg( "P122-1" ), QVariant( this->jacketdialog_list.at( 12 ) ) );


    this->transmitData( this->values );
}

void C2DJacketDialog::Reject()
{
    if ( this->jacketdialog_list.isEmpty() )
        this->Reset();
    else
    {
        this->jacketspin[1]->setValue( this->jacketdialog_list.at( 0 ).toFloat() );
        this->jacketspin[2]->setValue( this->jacketdialog_list.at( 1 ).toFloat() );
        this->jacketspin[3]->setValue( this->jacketdialog_list.at( 2 ).toFloat() );
        this->jacketspin[4]->setValue( this->jacketdialog_list.at( 3 ).toFloat() );
        this->jacketspin[5]->setValue( this->jacketdialog_list.at( 4 ).toFloat() );
        this->jacketspin[6]->setValue( this->jacketdialog_list.at( 5 ).toFloat() );
        this->jacketspin[7]->setValue( this->jacketdialog_list.at( 6 ).toFloat() );
        this->jacketspin[8]->setValue( this->jacketdialog_list.at( 7 ).toFloat() );
        this->jacketspin[9]->setValue( this->jacketdialog_list.at( 8 ).toFloat() );
        this->jacketspin[10]->setValue( this->jacketdialog_list.at( 9 ).toFloat() );
        this->jacketspin[11]->setValue( this->jacketdialog_list.at( 10 ).toFloat() );
        this->jacketspin[12]->setValue( this->jacketdialog_list.at( 11 ).toFloat() );
        this->jacketspin[13]->setValue( this->jacketdialog_list.at( 12 ).toFloat() );
    }
}

void C2DJacketDialog::Reset()
{
    jacketspin[1]->setValue( 0.8f );//"P14"
    jacketspin[2]->setValue( -4.0f );//"P16"
    jacketspin[3]->setValue( 2.0f );//P97
    jacketspin[4]->setValue( 0.0f );//P161
    jacketspin[5]->setValue( 2.0f );//P331
    jacketspin[6]->setValue( 0.0f );//P341
    jacketspin[7]->setValue( 1.0f );//P332
    jacketspin[8]->setValue( 80.0f );//P346
    jacketspin[9]->setValue( 0.0f );//P352
    jacketspin[10]->setValue( 0.75f );//P411
    jacketspin[11]->setValue( 0.75f );//P511
    jacketspin[12]->setValue( 0.75f );//P911
    jacketspin[13]->setValue( 10.5f );//P122-1

    this->jacketdialog_list.clear();

}

QList< QList< double > > C2DJacketDialog::defaults()
{
    this->Reset();
}
void C2DJacketDialog::requiredVariables()
{


}
