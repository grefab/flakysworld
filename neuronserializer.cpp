#include "neuronserializer.h"

#include <QVariant>
#include <QDebug>

#include "qjson/src/serializer.h"
#include "qjson/src/parser.h"

NeuronSerializer::NeuronSerializer(QObject *parent) :
	QThread(parent)
{
	moveToThread(this);
	start();
}

NeuronSerializer::~NeuronSerializer()
{
	quit();
	wait();
}

void NeuronSerializer::serializeSensor(QString sensorId, QList<qreal> sensorNeurons)
{
	/* here we will store everything */
	QVariantMap saveme;

	/* convert sensor neurons to QVariants */
	QVariantList v_sensorNeurons;
	foreach(qreal r, sensorNeurons) {
		v_sensorNeurons.append(r);
	}

	/* store sensor data */
	saveme.insert(sensorId, v_sensorNeurons);

	/* perform serialization */
	QJson::Serializer serializer;
	QByteArray result = serializer.serialize(saveme);

	/* tell everyone who is interested */
	emit sensorSerialized(result);
}

void NeuronSerializer::deserializeActuator(QByteArray actuatorSerialized)
{
	/* convert JSON to something we can handle */
	QJson::Parser parser;
	bool ok;
	QVariant parsedData = parser.parse(actuatorSerialized, &ok);

	if ( !ok ) {
		/* we have a problem. */
		qDebug() << "Error parsing raw data. Assumed JSON.";
		return;
	}
	QVariantMap parsedDataMap = parsedData.toMap();

	/* we interpret every item in that map as a sensor with an array as data. */
	foreach(QString actuator, parsedDataMap.keys()) {
		/* this is our data */
		const QVariantList v_actuatorNeurons = parsedDataMap[actuator].toList();

		/* convert QVariantList to QList<qreal> */
		QList<qreal> result;
		foreach(QVariant v, v_actuatorNeurons) {
			result.append(v.toReal());
		}

		/* tell everyone who is interested */
		emit actuatorDeserialized(actuator, result);
	}
}
