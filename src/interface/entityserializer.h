#ifndef ENTITYSERIALIZER_H
#define ENTITYSERIALIZER_H

#include <QObject>
#include <QList>
#include <QVariant>

class EntitySerializer : public QObject
{
	Q_OBJECT

public:
	explicit EntitySerializer(QObject *parent = 0);
	~EntitySerializer();

public:
	QVariantMap serializeSensor(QString beingId, QString sensorId, const QList<qreal>& sensorNeurons);
	void deserializeActuator(const QVariant& actuatorSerialized, QString* actuatorBeingId, QString* actuatorId, QList<qreal>* actuatorNeurons);

};

#endif // ENTITYSERIALIZER_H
