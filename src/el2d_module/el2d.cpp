#include "el2d.h"
#include "../plots.hxx"

El2dPlugin::El2dPlugin()
{
    this->AddViewport(mainwindow=new El2DMainWindow(scene=new QGraphicsScene));

    initPlots(this->plots,scene);
    qDebug()<<plots.keys();

    QPen pen(QColor(255,255,255));
    pen.setWidthF(0.5);
    QHashIterator<QString,Plot*> it(this->plots);
    while(it.hasNext())
    {
        it.next();
        Plot* plot=it.value();
        plot->setBrush(QBrush(QColor(255,255,255)));
        plot->setPen(pen);
    }
}

void El2dPlugin::update()
{

    bool some_enabled=false;
    Elasticas::Core::ObjectClass* object;
    foreach(object,Elasticas::Core::Instance()->objectClasses())
    {
        QString name=object->className();
        if(plots.contains(name))
        {
            plots[name]->setVisible(object->isEnabled());
            if(object->isEnabled()&&object->isChanged()) plots[name]->update();
            some_enabled=some_enabled|object->isEnabled();
        }
    }
    this->mainwindow->setVisible(some_enabled);

}

//-----------------------------------
Elasticas::Plugin* GetPlugin()
{
    return new El2dPlugin;
}
