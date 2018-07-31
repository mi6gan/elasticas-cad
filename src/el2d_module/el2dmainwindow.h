#ifndef EL2DMAINWINDOW_H
#define EL2DMAINWINDOW_H

#include <QtGui>
#include "el2dview.h"

class El2DMainWindow : public QFrame
{
    Q_OBJECT
    El2dView* viewport;
    QLabel* header;
    QToolBar* toolbar;
    QAction * action;
public:
    El2DMainWindow(QGraphicsScene* scene);
    void resizeEvent(QResizeEvent *event);
private slots:
    void showGrid(bool);
};

#endif // EL2DMAINWINDOW_H
