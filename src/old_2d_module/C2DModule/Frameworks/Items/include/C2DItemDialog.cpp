#include "C2DItemDialog.h"

C2DItemDialog::C2DItemDialog( const QString          & name,
                              const QString          & prefix,
                              const QString          & tab,
                              QPair<QString, double>   units,
                              QWidget                * parent )
    : C2DDialog( name, tab, true, parent ), dialog_prefix( prefix ), dialog_units( units )
{
    this->dialog_grid = NULL;

    this->top_dialog_button_box    = new QDialogButtonBox;
    this->bottom_dialog_button_box = new QDialogButtonBox;

    this->connect( this->top_dialog_button_box->addButton( trUtf8( "Ок" ),
                   QDialogButtonBox::ApplyRole ), SIGNAL( released() ), this, SLOT( Accept() ) );

    this->connect( this->top_dialog_button_box->addButton( trUtf8( "Отмена" ),
                   QDialogButtonBox::ApplyRole ), SIGNAL( released() ), this, SLOT( Cancel() ) );

    this->connect( this->top_dialog_button_box->addButton( trUtf8( "Применить" ),
                   QDialogButtonBox::ApplyRole ), SIGNAL( released() ), this, SLOT( Apply() ) );

    this->connect( this->bottom_dialog_button_box->addButton( trUtf8( "Сброс" ),
                   QDialogButtonBox::ApplyRole ), SIGNAL( released() ), this, SLOT( Reject() ) );

    this->connect( this->bottom_dialog_button_box->addButton( trUtf8( "По умолчанию" ),
                   QDialogButtonBox::ApplyRole ), SIGNAL( released() ), this, SLOT( Reset() ) );
}

void C2DItemDialog::kernelBusy( bool busy )
{
    if ( this->dialog_grid )
        this->dialog_grid->setEnabled( busy );
}

void C2DItemDialog::Accept()  {  this->Apply();  this->UpdateNeeded(); this->close();  }
void C2DItemDialog::Cancel()  {  this->Reject(); this->close();  }
