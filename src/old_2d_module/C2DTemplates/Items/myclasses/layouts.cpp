#include "layouts.h"
void vboxlayout::addrow( const char * str, double d1, double d2, double d3, double d4 )
{
    QHBoxLayout * bl1 = new QHBoxLayout;
    this->addLayout( bl1 );
    bl1->addWidget(  new QLabel(this->trUtf8( str ) ) );
    QDoubleSpinBox * spin=new QDoubleSpinBox();
    bl1->addWidget( spin );

    spin->setValue(d1);
    spin->setMinimum(d2);
    spin->setMaximum(d3);
    spin->setSingleStep(d4);
}
void vboxlayout::addrow( const char * str )
{
    QHBoxLayout * bl1 = new QHBoxLayout;
    this->addLayout( bl1 );
    bl1->addWidget(  new QLabel(this->trUtf8( str ) ) );
    QDoubleSpinBox * spin=new QDoubleSpinBox();
    bl1->addWidget( spin );
}
