//Main Class of ElastiCas 2D Graphics FrameWork;
//
//Task: Is 2D Viewport and i/o handler;
//

#ifndef C2DMODULE_H
#define C2DMODULE_H

#include <QMenu>
#include <QTimer>
#include <QLabel>
#include <QToolBar>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGraphicsView>
#include <QUndoView>
#include <QWheelEvent>
#include <QApplication>
#include <QDesktopWidget>

#include "elcore/elplugin.h"

#include "C2DAbstractObject.h"
#include "C2DViewport.h"

#if defined( C2D_DXF )
    #include <QLibrary>
    #include <LibDXF.h>
#endif

class Preload : public QWidget
{
    Q_OBJECT

public:
    Preload(QWidget *parent = 0);
    ~Preload();

    void SetScreenGeometry(QRect);

    void paintEvent(QPaintEvent *);
private:
    QRect screenGeometry;
    QPixmap myPixmap;
};


class C2DModule : public QWidget, public Elasticas::Plugin
{
    Q_OBJECT
public:
    C2DModule();
    void Initialize();
    ~C2DModule();

    void Update();

public slots:
    void showPreload();
    void hidePreload();

protected:

private:
    void setMenus();

    Preload * p;


#if defined( C2D_UNDO )
    QUndoView * View;
#endif

    C2DWidget * widget;

};

extern "C" EXPORTSPEC Elasticas::Plugin * GetPlugin();

#endif // C2DModule_H
