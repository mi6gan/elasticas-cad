#include "C2DLayerManager.h"

C2DLayerManager::C2DLayerManager( QObject * parent )
    : C2DManager( QString( "Layer manager" ), parent )
{
    this->ID = 0;
    this->currentID = ID;
    this->layers.insert( ID++, new C2DLayer( QString( "Thich solid" ),
                                             QString( "This is a thick solid line layer." ),
                                             QPen( QBrush( Qt::white, Qt::SolidPattern ), 0,
                                                   Qt::SolidLine, Qt::RoundCap, Qt::BevelJoin ),
                                             QBrush( Qt::white, Qt::SolidPattern ),
                                             false, true ) );
    this->layers.insert( ID++, new C2DLayer( QString( "Thich dashed" ),
                                             QString( "This is a thick dashed line layer." ),
                                             QPen( QBrush( Qt::white, Qt::SolidPattern ) , 0,
                                                   Qt::DashLine,  Qt::RoundCap, Qt::BevelJoin ),
                                             QBrush( Qt::white, Qt::SolidPattern ),
                                             false, true ) );
    this->layers.insert(   ID++, new C2DLayer( QString( "Bold solid" ),
                                             QString( "This is a bold solid line layer." ),
                                             QPen( QBrush( Qt::white, Qt::SolidPattern ), 0.8f,
                                                   Qt::SolidLine, Qt::RoundCap, Qt::BevelJoin ),
                                             QBrush( Qt::white, Qt::SolidPattern ),
                                             true, false ) );
    this->layers.insert(   ID++, new C2DLayer( QString( "thick red" ),
                                             QString( "This is a thick red line layer." ),
                                             QPen( QBrush( Qt::red, Qt::SolidPattern ), 0,
                                                   Qt::SolidLine, Qt::RoundCap, Qt::BevelJoin ),
                                             QBrush( Qt::red, Qt::SolidPattern ),
                                             true, false ) );
    this->layers.insert(   ID++, new C2DLayer( QString( "thick yellow" ),
                                             QString( "This is a thick yellow line layer." ),
                                             QPen( QBrush( Qt::yellow, Qt::SolidPattern ), 0.6f,
                                                   Qt::SolidLine, Qt::RoundCap, Qt::BevelJoin ),
                                             QBrush( Qt::yellow, Qt::SolidPattern ),
                                             true, false ) );
    this->layers.insert(   ID++, new C2DLayer( QString( "thick blue" ),
                                             QString( "This is a thick blue line layer." ),
                                             QPen( QBrush( Qt::blue, Qt::SolidPattern ), 1.5,
                                                   Qt::SolidLine, Qt::RoundCap, Qt::BevelJoin ),
                                             QBrush( Qt::blue, Qt::SolidPattern ),
                                             true, false ) );
    this->layers.insert(   ID, new C2DLayer( QString( "thick green" ),
                                             QString( "This is a thick green line layer." ),
                                             QPen( QBrush( Qt::green, Qt::SolidPattern ), 1.4,
                                                   Qt::SolidLine, Qt::RoundCap, Qt::BevelJoin ),
                                             QBrush( Qt::green, Qt::SolidPattern ),
                                             true, false ) );
}

void C2DLayerManager::AddDefaultLayer()
{
    this->layers.insert( ID++, new C2DLayer() );
    this->currentID = ID;
}

void C2DLayerManager::DeleteLayerByID( int id )
{
    if ( this->currentID == id )
    {
        QMessageBox * message =
                new QMessageBox( QMessageBox::Warning,
                                 QString( "Attention" ),
                                 QString( "The Layer i've trying to delete is current at the moment." ),
                                 QMessageBox::Ok, 0, 0 );
        message->exec();
    }
    else
    {
     QMutableMapIterator< int, C2DLayer * > i( this->layers );
     while( i.hasNext() )
        if ( i.key() >= id )
            i.setValue( i.next().value() );

        this->layers[ --ID ];

        if ( this->currentID > id )
            this->currentID--;
    }
}

void C2DLayerManager::SetCurrentID( int id )
{
    if ( this->layers.contains( id) )
        this->currentID = id;
}
