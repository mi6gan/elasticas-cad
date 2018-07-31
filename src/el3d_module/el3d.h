#include "elcore/elplugin.h"
#include "el3dmainwindow.h"
#include "el3dpythonbindings.h"
class El3dPlugin:public QObject,public Elasticas::Plugin
{
    Q_OBJECT
    El3dPythonBindings * python_bindings;
    El3dMainWindow* mainwindow;
public:
    El3dPlugin();
    virtual void update();
private slots:
    void meshVisiblityChanged(const QString & name,bool visible);
};
extern "C" EXPORTSPEC Elasticas::Plugin* GetPlugin();
