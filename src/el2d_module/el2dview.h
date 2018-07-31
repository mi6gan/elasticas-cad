#ifndef EL2DVIEW_H
#define EL2DVIEW_H

#include <QGraphicsView>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QDebug>

class El2dView : public QGraphicsView
{
    virtual void wheelEvent(QWheelEvent *event);
    QPointF last_mouse_pos;
    bool last_mouse_pos_inited;
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
public:
    El2dView();

};

#endif // EL2DVIEW_H
