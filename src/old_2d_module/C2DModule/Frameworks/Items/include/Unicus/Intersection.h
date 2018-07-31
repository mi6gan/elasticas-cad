#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <QLineF>
#include <QPointF>
#include <QDebug>

#include "./Unicus.h"
#include "./Geometry.h"

#include <math.h>
#include "QPainterPath"
namespace Unicus
{
    const QPointF CircCirc( const QPointF & center1, double R1,
                            const QPointF & center2, double R2,
                            bool right );
    QPointF splinepointonx( QPainterPath spline , double xx,double n );
    QPointF splinepointony( QPainterPath spline , double yy,double n);
}

#endif // INTERSECTION_H
