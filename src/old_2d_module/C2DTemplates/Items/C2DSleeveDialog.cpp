#include "C2DSleeveDialog.h"

C2DSleeveDialog::C2DSleeveDialog( const QString            & name,
                                  const QString            & prefix,
                                  const QString            & tab,
                                  QPair< QString, double >   units,
                                  QWidget                  * parent )
    : C2DItemDialog( name, prefix, tab, units, parent )
{
    this->requiredVariables();

    QGridLayout * layout = new QGridLayout( this );

    QTextCodec::setCodecForTr( QTextCodec::codecForName( "UTF-8" ) );

    if ( layout )
    {
        QLabel * label = new QLabel( this );
        label->setPixmap( QPixmap( "images/sleeve/sleeve.jpg" ) );
        layout->addWidget( label, 0, 0, 12,1 );
        layout->addWidget( new QLabel( this->trUtf8( "Коэффициент: " ), this ), 1, 1 );
        QLineEdit * l = 0;
        layout->addWidget( l = new QLineEdit( this->trUtf8( "" ), this ), 1, 2 );
        l->setValidator( new QDoubleValidator( l ) );
        this->returns.append( l );
        QComboBox * c = 0;
        layout->addWidget( c = new QComboBox( this ), 0, 1 );
        QList< QString > list;
        list << this->trUtf8( "Одношовный" )
             << this->trUtf8( "Двухшовный" )
             << this->trUtf8( "3" )  ;

        c->addItems( list );
        this->combobox_returns.append( c );
        connect( c,
                 SIGNAL( activated(int) ),
                 this,
                 SLOT( typeselect(int) ) );
        /*************Комбо бокс**********************************************/

        QGroupBox * Ppos = new QGroupBox( this->trUtf8( "Посадка: " ), this );
        Ppos->setFlat( true );
        Ppos->setStyleSheet( QString( "QComboBox::title { font-weight: normal; }") );

        QGridLayout * Pposl = new QGridLayout( Ppos );

        Pposl->addWidget( l = new QLineEdit( this->trUtf8( "" ), this ), 0, 1 );
        l->setValidator( new QDoubleValidator( l ) );
        this->returns.append( l );
        Pposl->addWidget( l = new QLineEdit( this->trUtf8( "" ), this ), 1, 1 );
        l->setValidator( new QDoubleValidator( l ) );
        this->returns.append( l );

        QRadioButton * b = 0;
        Pposl->addWidget( b = new QRadioButton( this->trUtf8( "H: " ), this ), 0, 0 );
        this->connect( b, SIGNAL( toggled( bool ) ), this, SLOT( pposchange() ) );
        this->radio_returns.append( b );

        Pposl->addWidget( b = new QRadioButton( this->trUtf8( "Ппос: " ), this ), 1, 0 );
        this->radio_returns.append( b );

        layout->addWidget( Ppos, 2, 1, 1, 2 );
        /**********************COMBO END****************************************/
        layout->addWidget( new QLabel( this->trUtf8( "Положение шва %: " ), this ), 3, 1 );

        layout->addWidget( shovpos = new QDoubleSpinBox( this ), 3, 2 );
        shovpos->setMinimum(0);
        shovpos->setMaximum(100);
        shovpos->setSingleStep(2.5f);
        shovpos->setEnabled(false);


        layout->addWidget( this->top_dialog_button_box, 13, 1, 1, 2 );
        layout->addWidget( this->bottom_dialog_button_box, 14, 1, 1, 2);

        this->setFixedSize( this->sizeHint() );

        this->Reset();
        this->Apply();
    }

    this->setLayout( layout );

}
/////SLOTS
void C2DSleeveDialog::typeselect( int cindex )
{
    if(cindex == 2)
        shovpos->setEnabled(true);
    else
        shovpos->setEnabled(false);
}

void C2DSleeveDialog::pposchange()
{
    if ( this->radio_returns.at( 0 )->isChecked() )
    {
        this->returns.at( 1 )->setEnabled( true );
        this->returns.at( 1 )->setText( this->edit_str );

        this->edit_str = this->returns.at( 2 )->text();
        this->returns.at( 2 )->setEnabled( false );
        this->returns.at( 2 )->clear();

    }
    else
    {
        this->returns.at( 2 )->setEnabled( true );
        this->returns.at( 2 )->setText( this->edit_str );

        this->edit_str = this->returns.at( 1 )->text();
        this->returns.at( 1 )->setEnabled( false );
        this->returns.at( 1 )->clear();
    }
}
//////END
void C2DSleeveDialog::Apply()
{
    qDebug() << "Apply.";
    this->dialog_list.clear();
    this->dialog_list << this->returns.at( 0 )->text().toDouble()
                      << this->returns.at( 1 )->text().toDouble()
                      << this->returns.at( 2 )->text().toDouble()
                      << this->radio_returns.at( 0 )->isChecked()
                      << this->combobox_returns.at( 0 )->currentIndex()
                      << this->edit_str
                      << this->shovpos->value();


    this->values.insert( QString( "%1%2" ).arg( this->prefix() ).arg( "Koef" ), QVariant( this->dialog_list.at( 0 ) ) );
    this->values.insert( QString( "%1%2" ).arg( this->prefix() ).arg( "H" ), QVariant( this->dialog_list.at( 1 ) ) );
    this->values.insert( QString( "%1%2" ).arg( this->prefix() ).arg( "Pos" ), QVariant( this->dialog_list.at( 2 ) ) );
    //this->values.insert( QString( "%1%2" ).arg( this->prefix() ).arg( "Combo" ), QVariant( this->dialog_list.at( 3 ). ) );
    this->values.insert( QString( "%1%2" ).arg( this->prefix() ).arg( "Type" ), QVariant( this->dialog_list.at( 4 ) ) );
    this->values.insert( QString( "%1%2" ).arg( this->prefix() ).arg( "Shovpos" ), QVariant( this->dialog_list.at( 6 ) ) );

    this->transmitData( this->values );
}

void C2DSleeveDialog::Reject()
{
    if ( this->dialog_list.isEmpty() )
        this->Reset();
    else
    {
        this->returns.at( 0 )->setText( this->dialog_list.at( 0 ).toString() );
        this->radio_returns.at( 0 )->setChecked( this->dialog_list.at( 3 ).toBool() );
        this->returns.at( 1 )->setText( this->dialog_list.at( 1 ).toString() );
        this->returns.at( 2 )->setText( this->dialog_list.at( 2 ).toString() );
        this->combobox_returns.at( 0 )->setCurrentIndex( this->dialog_list.at( 4 ).toInt() );
        this->edit_str = this->dialog_list.at( 5 ).toString();
        shovpos->setValue( dialog_list.at( 6 ).toDouble() );
    }
}

void C2DSleeveDialog::Reset()
{
    this->returns.at( 0 )->setText( "1.20" );
    //this->returns.at( 1 )->setText( "0.7" );
    this->edit_str = "0.7";
    shovpos->setValue( 40 );

    this->combobox_returns.at( 0 )->setCurrentIndex( 0 );

    this->radio_returns.at( 0 )->setChecked( true );

}

QList< QList< double > > C2DSleeveDialog::defaults()
{

}
void C2DSleeveDialog::requiredVariables()
{



}
