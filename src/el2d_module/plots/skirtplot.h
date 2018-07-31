/*
 SkirtPlot
"ComplexSkirt:";"StraightSkirt:"
 */
#ifndef SKIRTPLOT_H
#define SKIRTPLOT_H
#include "../plot.h"
#include "elcore/elcore.h"
const QPointF rPoint( const QPointF &point, const QPointF &center, double angle );
const QLineF uNormal( QLineF line, bool right_pair );
class SkirtPlot: public Plot
{
    QHash<QString,Plot::Vertex*> P;
    QPointF FrontDartTopPosition( double width, const QPointF & SideDartTop, const QPointF & RightPoint );
    QPointF BackDartTopPosition( double width, const QPointF & SideDartTop, const QPointF & LeftPoint );
public:
    SkirtPlot(QGraphicsScene* scene);
    virtual void update();
};

#endif // SKIRTPLOT_H
