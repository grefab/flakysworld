#ifndef NEURONSERIALIZER_H
#define NEURONSERIALIZER_H

#include <QThread>
#include <QList>
#include <QByteArray>

class NeuronSerializer : public QThread
{
	Q_OBJECT


public:
	explicit NeuronSerializer(QObject *parent = 0);
	~NeuronSerializer();

signals:
	void sensorSerialized(QByteArray sensorSerialized);
	void actuatorDeserialized(QString actuatorId, QList<qreal> actuatorNeurons);

public slots:
	void serializeSensor(QList<qreal> sensorNeurons);
	void deserializeActuator(QByteArray actuatorSerialized);

};

#endif // NEURONSERIALIZER_H
