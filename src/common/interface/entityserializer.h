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
	QVariantMap serializeSensor(QString beingId, QString sensorId, const QList<qreal>& sensorNeurons) const;
	void deserializeSensor(const QVariant& sensorSerialized, QString* sensorBeingId, QString* sensorId, QList<qreal>* sensorNeurons) const;

	QVariantMap serializeActuator(QString beingId, QString actuatorId, const QList<qreal>& actuatorNeurons) const;
	void deserializeActuator(const QVariant& actuatorSerialized, QString* actuatorBeingId, QString* actuatorId, QList<qreal>* actuatorNeurons) const;

	QVariantMap serializeThing(QString thingId, const QPolygonF& shape, const QPointF& position, qreal rotation) const;
	void deserializeThing(const QVariant& thingSerialized, QString* thingId, QPolygonF* thingShape, QPointF* thingPosition, qreal* thingRotation) const;
};

#endif // ENTITYSERIALIZER_H
