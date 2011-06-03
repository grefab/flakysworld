#ifndef ENTITYSERIALIZER_H
#define ENTITYSERIALIZER_H

#include <QObject>
#include <QList>
#include <QVariant>
#include <QPolygonF>

class EntitySerializer : public QObject
{
	Q_OBJECT

public:
	explicit EntitySerializer(QObject *parent = 0);
	~EntitySerializer();

public:
	QVariantMap serializeSensor(QString beingId, QString sensorId, const QList<qreal>& sensorNeurons);
	void deserializeActuator(const QVariant& actuatorSerialized, QString* actuatorBeingId, QString* actuatorId, QList<qreal>* actuatorNeurons);

	QVariantMap serializeThing(QString thingId, const QPolygonF& shape, const QPointF& position, qreal rotation);
	void deserializeThing(const QVariant& thingSerialized, QString* thingId, QPolygonF* thingShape, QPointF* thingPosition, qreal* thingRotation);
};

#endif // ENTITYSERIALIZER_H
