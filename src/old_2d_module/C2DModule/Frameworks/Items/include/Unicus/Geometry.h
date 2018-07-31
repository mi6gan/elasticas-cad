#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <QDebug>
#include <QLineF>
#include <QPointF>
#include <QPolygonF>

#include "./Unicus.h"

#include <math.h>

namespace Unicus
{
    const QPointF rPoint( const QPointF & point, const QPointF & center, double angle );
    const QLineF  rLine ( const  QLineF & line,  const QPointF & center, double angle );

    double normalizeAngle( double angle );
    double angleOx( const QLineF & line );
    const QLineF uNormal( QLineF line, bool right_pair );

    double dPointPoint( const QPointF & point1, const QPointF & point2 );

    QPointF PointOnRay( const QPointF & center, double angle, double ray_length );
    QLineF sGuides(const QPointF & center, double offset, double angle);

    const QVector<QPointF> ArcToBezier( const QPointF & start, const QPointF & end, const QPointF & center );

    double Scalar( const QLineF & v1, const QLineF & v2 );
    QPointF circline( QLineF line1 , QPointF centr, double r, bool right );
}

#endif // GEOMETRY_H
