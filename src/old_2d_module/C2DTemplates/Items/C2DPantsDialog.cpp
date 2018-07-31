#include "C2DPantsDialog.h"

C2DPantsDialog::C2DPantsDialog( const QString            & name,
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
        for ( int i = 0; i <= 4; i++ )
        {
            pantsspin[ i ] = new QDoubleSpinBox( this );
        }
        QLabel * label = new QLabel( this );
        label->setPixmap( QPixmap( "images/pants/pants.jpg" ) );
        l->addWidget( label, 0, 0, 19 ,1);

        l->addWidget( new QLabel( this->trUtf8( "Брюки: " ) ), 0, 1 );
        l->addWidget( pantscombo = new QComboBox( this ), 0, 2 );
        QList< QString > list;
        list << this->trUtf8( "Ш1, Ш2 вместе" )
             << this->trUtf8( "Ш1, Ш2 раздельно" );

        pantscombo->addItems( list );


        l->addWidget( new QLabel( this->trUtf8( "L1 (0...1 см):" ) ), 1, 1 );
        pantsspin[0]->setMinimum( 0 );
        pantsspin[0]->setMaximum( 1 );
        pantsspin[0]->setSingleStep( 0.1f );

        l->addWidget( pantsspin[0] , 1, 2 );

        l->addWidget( new QLabel( this->trUtf8( "L2 (1...4 см):" ) ), 2, 1 );
        pantsspin[1]->setMinimum( 1 );
        pantsspin[1]->setMaximum( 4 );
        pantsspin[1]->setSingleStep( 0.1f );


        l->addWidget( pantsspin[1] , 2, 2 );

        l->addWidget( new QLabel( this->trUtf8( "Шк (8...80 см):" ) ), 3, 1 );
        pantsspin[2]->setMinimum( 8 );
        pantsspin[2]->setMaximum( 80 );
        pantsspin[2]->setSingleStep(0.5);

        l->addWidget( pantsspin[2] , 3, 2 );

        l->addWidget( new QLabel( this->trUtf8( "Шн (6...80 см):" ) ), 4, 1 );
        pantsspin[3]->setMinimum( 6 );
        pantsspin[3]->setMaximum( 80 );
        pantsspin[3]->setSingleStep(0.5);

        l->addWidget( pantsspin[3] , 4, 2 );


        l->addWidget( new QLabel( this->trUtf8( "/68'-78'/ = /68-78/ - K" ) ), 5, 1, 1, 2, Qt::AlignTop );
        l->addWidget( new QLabel( this->trUtf8( "K ( 0...1 cм):" ) ), 6, 1, 1, 1, Qt::AlignTop );
        pantsspin[4]->setMinimum( 0 );
        pantsspin[4]->setMaximum( 1 );
        pantsspin[4]->setSingleStep(0.1);

        l->addWidget( pantsspin[4] , 6, 2, 1, 1, Qt::AlignTop  );

        l->addWidget( this->top_dialog_button_box, 17, 1, 1, 2 );
        l->addWidget( this->bottom_dialog_button_box, 18, 1, 1, 2);

        this->setFixedSize( this->sizeHint() );

        this->Reset();
        this->Apply();

    }

    this->setLayout( l );

}

void C2DPantsDialog::Apply()
{
    qDebug() << "Apply.";
    this->pantsdialog_list.clear();
    this->pantsdialog_list << this->pantscombo->currentIndex()
                           << this->pantsspin[0]->value()
                           << this->pantsspin[1]->value()
                           << this->pantsspin[2]->value()
                           << this->pantsspin[3]->value()
                           << this->pantsspin[4]->value();

    this->values.insert( QString( "%1%2" ).arg( this->prefix() ).arg( "combo" ), QVariant( this->pantsdialog_list.at( 0 ) ) );
    this->values.insert( QString( "%1%2" ).arg( this->prefix() ).arg( "L1" ), QVariant( this->pantsdialog_list.at( 1 ) ) );
    this->values.insert( QString( "%1%2" ).arg( this->prefix() ).arg( "L2" ), QVariant( this->pantsdialog_list.at( 2 ) ) );
    this->values.insert( QString( "%1%2" ).arg( this->prefix() ).arg( "SHk" ), QVariant( this->pantsdialog_list.at( 3 ) ) );
    this->values.insert( QString( "%1%2" ).arg( this->prefix() ).arg( "SHn" ), QVariant( this->pantsdialog_list.at( 4 ) ) );
    this->values.insert( QString( "%1%2" ).arg( this->prefix() ).arg( "K1" ), QVariant( this->pantsdialog_list.at( 5 ) ) );

    this->transmitData( this->values );
}

void C2DPantsDialog::Reject()
{
    if ( this->pantsdialog_list.isEmpty() )
        this->Reset();
    else
    {
        this->pantscombo->setCurrentIndex( this->pantsdialog_list.at( 0 ).toInt() );
        this->pantsspin[0]->setValue( this->pantsdialog_list.at( 1 ).toFloat() );
        this->pantsspin[1]->setValue( this->pantsdialog_list.at( 2 ).toFloat() );
        this->pantsspin[2]->setValue( this->pantsdialog_list.at( 3 ).toFloat() );
        this->pantsspin[3]->setValue( this->pantsdialog_list.at( 4 ).toFloat() );
        this->pantsspin[4]->setValue( this->pantsdialog_list.at( 5 ).toFloat() );
    }
}

void C2DPantsDialog::Reset()
{
    pantscombo->setCurrentIndex( 0 );
    pantsspin[0]->setValue( 1 );
    pantsspin[1]->setValue( 1 );
    pantsspin[2]->setValue( 20 );
    pantsspin[3]->setValue( 15 );
    pantsspin[4]->setValue( 1 );
    this->pantsdialog_list.clear();

}

QList< QList< double > > C2DPantsDialog::defaults()
{
    this->Reset();
}
void C2DPantsDialog::requiredVariables()
{



}
