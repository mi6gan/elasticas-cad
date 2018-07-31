#include "C2DSimpleItem.h"

C2DSimpleItem::C2DSimpleItem( C2DLayerManager * LayerManager, QGraphicsScene * scene )
    : C2DItem( LayerManager, scene )
{
    this->setPrefix( QString( "SimpleItem" ) );
    this->Constructed = false;
    this->requiredVariables();
}

void C2DSimpleItem::Update()
{
    this->getVariables();
    this->setVariables();
    this->UpdatePoints();
    this->DrawOnWidget();
}

void C2DSimpleItem::requiredVariables()
{

}

void C2DSimpleItem::getVariables()
{

}

void C2DSimpleItem::setVariables()
{

}


void C2DSimpleItem::UpdatePoints()
{
    P["P0"] = QPointF( 0.0f, 0.0f );
}

void C2DSimpleItem::DrawOnWidget()
{
    this->point( MakeSync( "Point name", Sync::Point, MakeList( "P0" ), LM->bold_solid() ), true );
}
