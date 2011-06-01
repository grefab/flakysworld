#ifndef NEURONSERIALIZER_H
#define NEURONSERIALIZER_H

#include <QObject>
#include <QList>
#include <QVariant>

class NeuronSerializer : public QObject
{
	Q_OBJECT

public:
	explicit NeuronSerializer(QObject *parent = 0);
	~NeuronSerializer();

public slots:
	QVariant serializeSensor(QString beingId, QString sensorId, const QList<qreal>& sensorNeurons);
	void deserializeActuator(const QVariant& actuatorSerialized, QString* actuatorBeingId, QString* actuatorId, QList<qreal>* actuatorNeurons);

};

#endif // NEURONSERIALIZER_H
