#include "neuronserializer.h"

#include <QVariant>
#include <QDebug>

#include "external/qjson/src/serializer.h"
#include "external/qjson/src/parser.h"

#include "being/sensor.h"

/* string definitions needed later */
static const QString KEY_BEING = "being";
static const QString KEY_BEINGS_SENSORS = "sensors";
static const QString KEY_BEINGS_ACTUATORS = "actuators";


NeuronSerializer::NeuronSerializer(QObject *parent) :
	QThread(parent)
{
	qRegisterMetaType< QList<qreal> >("QList<qreal>");

	moveToThread(this);
	start();
}

NeuronSerializer::~NeuronSerializer()
{
	quit();
	wait();
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

	/* finally insert the map */
	saveme.insert(KEY_BEINGS_SENSORS, v_sensors);

	/* perform serialization */
	QJson::Serializer serializer;
	QByteArray result = serializer.serialize(saveme);

	/* tell everyone who is interested */
	emit sensorSerialized(result);
}

void NeuronSerializer::deserializeActuator(QByteArray actuatorSerialized)
{
	/* perform some consistency checks first to ignore HTTP stuff. */
	if ( !looksLikeJSON(actuatorSerialized) ) {
		return;
	}

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

	/* find which being is concerned */
	const QString beingId = parsedDataMap[KEY_BEING].toString();
	const QVariantMap actuatorMap = parsedDataMap[KEY_BEINGS_ACTUATORS].toMap();

	/* we interpret every item in that map as a sensor with an array as data. */
	foreach(QString actuator, actuatorMap.keys()) {
		/* this is our data */
		const QVariantList v_actuatorNeurons = actuatorMap[actuator].toList();

		/* convert QVariantList to QList<qreal> */
		QList<qreal> result;
		foreach(QVariant v, v_actuatorNeurons) {
			result.append(v.toReal());
		}

		/* tell everyone who is interested */
		emit actuatorDeserialized(beingId, actuator, result);
	}
}

bool NeuronSerializer::looksLikeJSON(const QByteArray& data)
{
	/* no data? no json. */
	if ( data.size() <= 0 ) {
		return false;
	}

	/* let's hope there's nothing except json that is included in curly brackets. */
	if (data.at(0) != '{' || data.at(data.size()-1) != '}') {
		return false;
	}

	/* if we reach this point, it seems we have a JSON object. */
	return true;
}
