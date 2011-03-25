#ifndef NEURONSERIALIZER_H
#define NEURONSERIALIZER_H

#include <QThread>
#include <QList>
#include <QVariant>

class NeuronSerializer : public QThread
{
	Q_OBJECT

public:
	explicit NeuronSerializer(QObject *parent = 0);
	~NeuronSerializer();

signals:
	void sensorSerialized(QVariant sensorSerialized);
	void actuatorDeserialized(QString beingId, QString actuatorId, QList<qreal> actuatorNeurons);

public slots:
	void serializeSensor(QList<qreal> sensorNeurons);
	void deserializeActuator(QVariant actuatorSerialized);

};

#endif // NEURONSERIALIZER_H
