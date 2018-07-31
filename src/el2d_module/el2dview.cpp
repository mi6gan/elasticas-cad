#include "el2dview.h"

El2dView::El2dView()
{
    this->last_mouse_pos_inited=false;
}
void El2dView::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton) this->setDragMode(QGraphicsView::ScrollHandDrag);
    QGraphicsView::mousePressEvent(event);
}

void El2dView::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton) this->setDragMode(QGraphicsView::NoDrag);
    QGraphicsView::mouseReleaseEvent(event);
}

void El2dView::wheelEvent(QWheelEvent *event)
{
    this->scale(1.0-double(event->delta())/1000.0f,1.0-double(event->delta())/1000.0f);
}
