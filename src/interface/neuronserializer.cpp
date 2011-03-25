#include "neuronserializer.h"

#include <QDebug>

#include "being/sensor.h"

/* string definitions needed later */
static const QString KEY_BEING = "being";
static const QString KEY_BEINGS_SENSORS = "sensors";
static const QString KEY_BEINGS_ACTUATORS = "actuators";


NeuronSerializer::NeuronSerializer(QObject *parent) :
	QObject(parent)
{
	qRegisterMetaType< QList<qreal> >("QList<qreal>");
}

NeuronSerializer::~NeuronSerializer()
{
}

void NeuronSerializer::serializeSensor(QList<qreal> sensorNeurons)
{
	/* find IDs we need to work in our JSON response */
	const Sensor* sensor = static_cast<Sensor*>(sender());
	const QString sensorId = sensor->id();
	const QString beingId = sensor->being().id();

	/* here we will store everything */
	QVariantMap saveme;

	/* convert sensor neurons to QVariants */
	QVariantList v_sensorNeurons;
	foreach(qreal r, sensorNeurons) {
		v_sensorNeurons.append(r);
	}

	/* store sensor data */

	/* tell who sent it */
	saveme.insert(KEY_BEING, beingId);

	/* we may have multiple sensors, so store the sensor in a map. */
	QVariantMap v_sensors;
	v_sensors.insert(sensorId, v_sensorNeurons);

	/* finally insert sensor into the map */
	saveme.insert(KEY_BEINGS_SENSORS, v_sensors);

	/* tell everyone who is interested */
	emit sensorSerialized(saveme);
}

void NeuronSerializer::deserializeActuator(QVariant parsedData)
{
	QVariantMap parsedDataMap = parsedData.toMap();

	/* find which being is concerned */
	const QString beingId = parsedDataMap[KEY_BEING].toString();
	const QVariantMap actuatorMap = parsedDataMap[KEY_BEINGS_ACTUATORS].toMap();

	/* we interpret every item in that map as a sensor with an array as data. */
	foreach(QString actuatorId, actuatorMap.keys()) {
		/* this is our data */
		const QVariantList v_actuatorNeurons = actuatorMap[actuatorId].toList();

		/* convert QVariantList to QList<qreal> */
		QList<qreal> neuronValues;
		foreach(QVariant v, v_actuatorNeurons) {
			neuronValues.append(v.toReal());
		}

		/* tell everyone who is interested */
		emit actuatorDeserialized(beingId, actuatorId, neuronValues);
	}
}
