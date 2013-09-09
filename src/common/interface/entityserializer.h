#ifndef ENTITYSERIALIZER_H
#define ENTITYSERIALIZER_H

#include <QObject>
#include <QMap>
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
    QVariantMap serializeSensors(QString beingId, QMap< QString, QList<qreal> > sensors) const;
    QVariantMap serializeSensor(QString beingId, QString sensorId, const QList<qreal>& sensorNeurons) const;
    void deserializeSensors(const QVariant& sensorSerialized, QString* sensorBeingId, QMap< QString, QList<qreal> >* sensors) const;
    void deserializeSensor(const QVariant& sensorSerialized, QString* sensorBeingId, QString* sensorId, QList<qreal>* sensorNeurons) const;

    QVariantMap serializeActuators(QString beingId, QMap< QString, QList<qreal> > actuators) const;
    QVariantMap serializeActuator(QString beingId, QString actuatorId, const QList<qreal>& actuatorNeurons) const;
    void deserializeActuators(const QVariant& actuatorSerialized, QString* actuatorBeingId, QMap< QString, QList<qreal> >* actuators) const;
    void deserializeActuator(const QVariant& actuatorSerialized, QString* actuatorBeingId, QString* actuatorId, QList<qreal>* actuatorNeurons) const;

    QVariantMap serializeThing(QString thingId, const QPolygonF& shape, const QPointF& position, qreal rotation) const;
    void deserializeThing(const QVariant& thingSerialized, QString* thingId, QPolygonF* thingShape, QPointF* thingPosition, qreal* thingRotation) const;
};

#endif // ENTITYSERIALIZER_H
