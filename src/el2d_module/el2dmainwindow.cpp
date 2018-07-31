#include "el2dmainwindow.h"

El2DMainWindow::El2DMainWindow(QGraphicsScene* scene)
{
    this->setLayout(new QVBoxLayout);
    this->layout()->addWidget(header=new QLabel(trUtf8("Конструкция изделия")));
    this->layout()->addWidget(toolbar=new QToolBar);
    this->layout()->addWidget(viewport=new El2dView);
    header->setStyleSheet("*{font-weight:bold;}");
    viewport->setScene(scene);
    viewport->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    viewport->setRenderHint(QPainter::Antialiasing,true);
    viewport->setSceneRect(-1000,-1000,2000,2000);
    viewport->show();

    action=toolbar->addAction(QIcon("images/show_grid.png"),trUtf8("Отображать сетку"));
    action->setCheckable(true);
    QObject::connect(action,SIGNAL(triggered(bool)),this,SLOT(showGrid(bool)));
    action->trigger(); action->trigger();
}

void El2DMainWindow::showGrid(bool show)
{
    QBrush brush;
    if(show) brush.setTexture(QPixmap("images/background1.png"));
    else
    {
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(QColor(128,128,128));
    }
    this->viewport->setBackgroundBrush(brush);
}

void El2DMainWindow::resizeEvent(QResizeEvent *event)
{
    QFrame::resizeEvent(event);
    this->viewport->centerOn(QPointF(0,0));
}
