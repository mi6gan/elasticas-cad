/*
BlousePlot
"ComplexBlouse:";"Blouse:"
 */
#ifndef BLOUSE_PLOT_H
#define BLOUSE_PLOT_H
#include "../plot.h"
#include "elcore/elcore.h"
class BlousePlot : public Plot
{
    QHash<QString,Plot::Vertex*> P;
    double LPT1,LPT13,LPT16,LPT18,LPT19,LPT31,LPT39,LPT43,LPT45;
    double LPT45_,LPT46,LPT47,LPT57,LPT61,LPT68,LPTK0,LPTK1;
public:
    BlousePlot(QGraphicsScene* scene);
    virtual void update();
    QPointF splinepointonxBlouse( QPainterPath spline , double xx,double n);
};

#endif // BLOUSE_PLOT_H
