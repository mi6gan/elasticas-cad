#include "C2DFlaredSkirtKMProperties.h"

C2DFlaredSkirtKMProperties::C2DFlaredSkirtKMProperties( const QString            & name,
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
        l->addWidget( new QLabel( QString( "Yz:" ), this ), 0, 0 );
        l->addWidget( new QLabel( QString( "Gamma z persent:" ), this ), 1, 0 );
        l->addWidget( new QLabel( QString( "Ss:" ), this ), 3, 0 );
        l->addWidget( new QLabel( QString( "Ssb:" ), this ), 2, 0 );
        l->addWidget( new QLabel( QString( "Sns:" ), this ), 4, 0 );

        QLineEdit * le = NULL;

        l->addWidget( le = new QLineEdit( this ), 0, 1 );
        this->connect( le, SIGNAL( textChanged( QString) ), this, SLOT( checkVariant() ) );
        this->input.append( le );
        l->addWidget( le = new QLineEdit( this ), 1, 1 );
        this->connect( le, SIGNAL( textChanged( QString) ), this, SLOT( checkVariant() ) );
        this->input.append( le );
        l->addWidget( le = new QLineEdit( this ), 2, 1 );
        this->connect( le, SIGNAL( textChanged( QString) ), this, SLOT( checkVariant() ) );
        this->input.append( le );
        l->addWidget( le = new QLineEdit( this ), 3, 1 );
        this->connect( le, SIGNAL( textChanged( QString) ), this, SLOT( checkVariant() ) );
        this->input.append( le );
        l->addWidget( le = new QLineEdit( this ), 4, 1 );
        this->connect( le, SIGNAL( textChanged( QString) ), this, SLOT( checkVariant() ) );
        this->input.append( le );

        l->addWidget( this->top_dialog_button_box,    5, 0, 1, 2 );
        l->addWidget( this->bottom_dialog_button_box, 6, 0, 1, 2 );

        this->setFixedSize( this->sizeHint() );

        this->Reset();
        this->Apply();
    }

    this->setLayout( l );
}


void C2DFlaredSkirtKMProperties::Apply()
{

}

void C2DFlaredSkirtKMProperties::Reject()
{

}

void C2DFlaredSkirtKMProperties::Reset()
{

}

QList< QList< double > > C2DFlaredSkirtKMProperties::defaults()
{

}

void C2DFlaredSkirtKMProperties::checkVariant()
{  //Gamma Ssb Yz Ss Sns
    bool set[ 5 ][ 5 ] =
    { {  true,  true,  true, false,  true },
      {  true,  true,  true,  true,  true },
      {  true,  true,  true,  true,  true },
      { false,  true,  true,  true,  true },
      {  true,  true,  true,  true,  true } };

    if ( this->input.count() > 5 )
    {
        qWarning() << "C2DFlaredSkirtKMProperties::checkVariant() - input field count exceeds matrix dimension.";
        return;
    }

    QList< int > value;

    for( int i = 0; i < this->input.count(); i++ )
        if ( this->input.at( i )->text() != QString( "" ) )
            value.append( i );

    if ( value.isEmpty() )
    {
        for( int i = 0; i < this->input.count(); i++ )
            this->input.at( i )->setEnabled( true );

        return;
    }

    if ( ( ( value.count() == 2 ) && ( !value.contains( 0 ) ) ) ||
         ( ( value.count() == 3 ) && ( value.contains( 0 ) ) ) )
    {
        for ( int i = 1; i < this->input.count(); i++ )
            if ( !value.count( i ) )
                this->input.at( i )->setEnabled( false );
        return;
    }

    qDebug() << "Values: " << value;

    foreach( int i, value )
        for( int j = 1; j < input.count(); j++ )
        {
            this->input.at( j )->setEnabled( value.contains( j ) || set[ i ][ j ] && this->input.at( j )->isEnabled() );
            qDebug() << "Bool: " << "( " << i << ", " << j << ") " << ( value.contains( j ) || set[ i ][ j ] );
        }
}

void C2DFlaredSkirtKMProperties::requiredVariables()
{

}
