#include "C2DPropertiesDialog.h"

C2DPropertiesDialog::C2DPropertiesDialog( QWidget * parent )
    : C2DDialog( QString( "Properties" ), QString( "Not tabbed" ), true, parent )
{
    l = new QVBoxLayout( this );

    m = new QStandardItemModel( 0, 2, this );

    v = new QTableView( this );
    v->setModel( m );
    v->setCornerButtonEnabled( false );
    v->setSortingEnabled( false );
    v->setSelectionMode( QAbstractItemView::NoSelection );

    l->addWidget( v );

    this->header = false;

    this->setMaximumWidth( 280 );
    this->setMinimumWidth( 280 );
    this->setMinimumHeight( 400 );

    this->v->verticalHeader()->hide();

    connect( this, SIGNAL( finished(int) ), this, SLOT( closed() ) );
}

C2DPropertiesDialog::~C2DPropertiesDialog()
{

}

void C2DPropertiesDialog::addSection( QString name )
{
    if ( !this->header )
    {
        QStandardItem * h1 = new QStandardItem( "Property" );
        QStandardItem * h2 = new QStandardItem( "Value" );

        m->setHorizontalHeaderItem( 0, h1 );
        m->setHorizontalHeaderItem( 1, h2 );

        v->setColumnWidth( 0, this->width() * 0.30f );
        v->setColumnWidth( 1, this->width() * 0.55f );
    }

    QStandardItem * i = new QStandardItem( name );
    i->setEditable( false );
    m->appendRow( i );
    v->setSpan( m->rowCount() - 1, 0, 1, 2 );
}

void C2DPropertiesDialog::addString( QString property, QVariant value )
{
    QList< QStandardItem * > l;
    QStandardItem * i1 = new QStandardItem( property );
    QStandardItem * i2 = new QStandardItem( value.toString() );
    i1->setEditable( false );
    i2->setEditable( false );
    l.append( i1 );
    l.append( i2 );
    m->appendRow( l );
}

void C2DPropertiesDialog::resizeEvent( QResizeEvent * e )
{
    v->setColumnWidth( 0, e->size().width() * 0.30f );
    v->setColumnWidth( 1, e->size().width() * 0.55f );
    QDialog::resizeEvent( e );
}

void C2DPropertiesDialog::closed()
{
    m->clear();
}


