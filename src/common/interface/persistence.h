#ifndef PERSISTENCE_H
#define PERSISTENCE_H

#include <QList>
#include <QVariant>
#include <QPointF>
#include <QRectF>
#include <QPolygonF>
#include "constants.h"

QVariantMap qpointf2qvariant(const QPointF& point);
QPointF qvariant2qpointf(const QVariant& var);

QVariantMap qrectf2qvariant(const QRectF& rect);
QRectF qvariant2qrectf(const QVariant& var);

QVariantList qpolygonf2qvariant(const QPolygonF& polygon);
QPolygonF qvariant2qpolygonf(const QVariant& var);

#endif // PERSISTENCE_H
