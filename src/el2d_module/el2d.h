#include "plot.h"
#include "plots/blouseplot.h"
#include "plots/skirtplot.h"
#include "elcore/elplugin.h"
#include "el2dmainwindow.h"
#include <QtSvg/QSvgWidget>
#include <QtSvg/QGraphicsSvgItem>
#include <QAction>
class El2dPlugin: public QObject, public Elasticas::Plugin
{
    Q_OBJECT
    El2DMainWindow* mainwindow;
    QGraphicsScene* scene;
    QHash<QString,Plot*> plots;
public:
    El2dPlugin();
private slots:
    virtual void update();
};
extern "C" EXPORTSPEC Elasticas::Plugin* GetPlugin();
