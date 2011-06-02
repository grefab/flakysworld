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

QVariantMap NeuronSerializer::serializeSensor(QString beingId, QString sensorId, const QList<qreal>& sensorNeurons)
{
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
	return saveme;
}

void NeuronSerializer::deserializeActuator(const QVariant& actuatorSerialized, QString* actuatorBeingId, QString* actuatorId, QList<qreal>* actuatorNeurons)
{
	QVariantMap parsedDataMap = actuatorSerialized.toMap();

	/* find which being is concerned */
	const QString beingId = parsedDataMap[KEY_BEING].toString();
	const QVariantMap actuatorMap = parsedDataMap[KEY_BEINGS_ACTUATORS].toMap();

	/* we interpret every item in that map as a sensor with an array as data. */
	foreach(QString id, actuatorMap.keys()) {
		/* this is our data */
		const QVariantList v_actuatorNeurons = actuatorMap[id].toList();

		/* convert QVariantList to QList<qreal> */
		QList<qreal> neuronValues;
		foreach(QVariant v, v_actuatorNeurons) {
			neuronValues.append(v.toReal());
		}

		/* fill the pointers */
		*actuatorBeingId = beingId;
		*actuatorId = id;
		*actuatorNeurons = neuronValues;
	}
}
