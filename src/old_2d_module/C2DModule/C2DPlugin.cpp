#include "C2DPlugin.h"

C2DPlugin::C2DPlugin()
{
}

const QAction * C2DPlugin::action() const
{
    return new QAction( "Dummy", NULL );
}

C2DPlugin * C2DPlugin::plugin()
{
    return this;
}

void C2DPlugin::init()
{

}
