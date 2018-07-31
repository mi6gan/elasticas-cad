#include "C2DRuller.h"

C2DRuller::C2DRuller(QPointF startPoint, QGraphicsItem *parent, QGraphicsScene *scene):
        QGraphicsPathItem(parent, scene)
{
    myStartPoint=startPoint;
    myEndPoint=startPoint;
    RullerSide.setPoints(startPoint, startPoint);
}

QRectF C2DRuller::boundingRect() const
{
    return QRectF(RullerSide.p1(),RullerSide.p2());
}

QPainterPath C2DRuller::shape() const
{
return QPainterPath();
}

int C2DRuller::type()
{
return Type;
}

double C2DRuller::Length()
{
return RullerSide.length();
}

QPointF C2DRuller::GetPolarCoordinates()
{
    return QPointF(RullerSide.length(),RullerSide.angle());
}

void C2DRuller::SetEndPoint(QPointF End)
{
    myEndPoint=End;
    RullerSide.setP2(myEndPoint);
    CurrentPosition=GetPolarCoordinates();
}

void C2DRuller::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPainterPath Path;
    painter->setPen(QColor(Qt::green));
/**
    Path.moveTo(RullerSide.p1());
     Path.lineTo(RullerSide.p2());
      Path.lineTo(myEndPoint+QPointF(25*cos(-CurrentPosition.y()*M_PI/180),25*sin(-CurrentPosition.y()*M_PI/180)));
       Path.lineTo(Path.currentPosition()+QPointF(75*cos((-CurrentPosition.y()+90)*M_PI/180),75*sin((-CurrentPosition.y()+90)*M_PI/180)));
       Path.lineTo(Path.currentPosition()+QPointF(-25*cos((-CurrentPosition.y())*M_PI/180),-25*sin((-CurrentPosition.y())*M_PI/180)));
       Path.lineTo(RullerSide.p1()+QPointF(75*cos((-CurrentPosition.y()+90)*M_PI/180),75*sin((-CurrentPosition.y()+90)*M_PI/180)));
       Path.lineTo(Path.currentPosition()+QPointF(-25*cos((-CurrentPosition.y())*M_PI/180),-25*sin((-CurrentPosition.y())*M_PI/180)));
       Path.lineTo(Path.currentPosition()+QPointF(75*cos((-CurrentPosition.y()-90)*M_PI/180),75*sin((-CurrentPosition.y()-90)*M_PI/180)));
       Path.lineTo(Path.currentPosition()+QPointF(25*cos(-CurrentPosition.y()*M_PI/180),25*sin(-CurrentPosition.y()*M_PI/180)));
**/
    Path.moveTo(RullerSide.p1());
     Path.lineTo(RullerSide.p2());
    setPath(Path);
    painter->drawPath(Path);
}
