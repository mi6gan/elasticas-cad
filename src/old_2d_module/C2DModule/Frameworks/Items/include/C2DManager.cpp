#include "C2DManager.h"

C2DManager::C2DManager( const QString & name, QObject * parent)
    : QObject( parent )
{
    this->setObjectName( name );
}

C2DManager::~C2DManager()
{

}

void C2DManager::invokeDialog()
{
    if ( this->dialog )
        this->dialog->show();
}

void C2DManager::setActions()
{
    QAction * dialog_action = new QAction( this->objectName(), this );

    QObject::connect( dialog_action, SIGNAL( triggered() ), this, SLOT( invokeDialog() ) );

    this->actions.append( dialog_action );
}
