#include "persistence.h"

QVariantMap qpointf2qvariant(const QPointF& point)
{
	QVariantMap result;

	result.insert("x", point.x());
	result.insert("y", point.y());

	return result;
}

QPointF qvariant2qpointf(const QVariant& var)
{
	QVariantMap map = var.toMap();

	QPointF point = QPointF(map["x"].toFloat(), map["y"].toFloat());

	return point;
}

QVariantMap qrectf2qvariant(const QRectF& rect)
{
	QVariantMap result;

	result.insert("topleft", qpointf2qvariant(rect.topLeft()));
	result.insert("bottomright", qpointf2qvariant(rect.bottomRight()));

	return result;
}

QRectF qvariant2qrectf(const QVariant& var)
{
	QVariantMap map = var.toMap();

	QRectF rect = QRectF(
			qvariant2qpointf(map["topleft"].toMap()),
			qvariant2qpointf(map["bottomright"].toMap())
			);

	return rect;
}

QVariantList qpolygonf2qvariant(const QPolygonF& polygon)
{
	QVariantList result;

	foreach(QPointF point, polygon.toList()) {
		result << qpointf2qvariant(point);
	}

	return result;
}

QPolygonF qvariant2qpolygonf(const QVariant& var)
{
	QVariantList list = var.toList();

	QPolygonF poly;

	foreach(QVariant item, list) {
		poly.append(qvariant2qpointf(item));
	}

	return poly;
}
