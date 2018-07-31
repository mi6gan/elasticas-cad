#ifndef C2DRULLER_H
#define C2DRULLER_H

#include <QGraphicsPathItem>
#include <QPen>
#include <QPainter>
#include <math.h>

class C2DRuller : public QGraphicsPathItem
{
public:
    enum { Type = UserType + 100 } ;

    C2DRuller(QPointF startPoint, QGraphicsItem *parent, QGraphicsScene *scene);

    QRectF boundingRect() const;
    QPainterPath shape() const;
    double Length();
    int type();

QPointF GetPolarCoordinates();
void SetEndPoint(QPointF);

protected:
void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

private:
    QPointF myStartPoint, myEndPoint, CurrentPosition;
    QLineF RullerSide;
    QPainterPath SmallStroke, BigStroke;
};

#endif // C2DRULLER_H
