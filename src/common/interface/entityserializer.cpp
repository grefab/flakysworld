#include "entityserializer.h"
#include "constants.h"
#include "persistence.h"

#include <QDebug>

EntitySerializer::EntitySerializer(QObject *parent) :
	QObject(parent)
{
	qRegisterMetaType< QList<qreal> >("QList<qreal>");
}

EntitySerializer::~EntitySerializer()
{
}

QVariantMap EntitySerializer::serializeSensor(QString beingId, QString sensorId, const QList<qreal>& sensorNeurons) const
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

	/* finally insert sensors into the map */
	saveme.insert(KEY_BEINGS_SENSORS, v_sensors);

	/* tell everyone who is interested */
	return saveme;
}

void EntitySerializer::deserializeSensor(const QVariant& sensorSerialized, QString* sensorBeingId, QString* sensorId, QList<qreal>* sensorNeurons) const
{
	QVariantMap parsedDataMap = sensorSerialized.toMap();

	/* find which being is concerned */
	const QString beingId = parsedDataMap[KEY_BEING].toString();
	const QVariantMap sensorMap = parsedDataMap[KEY_BEINGS_SENSORS].toMap();

	/* we interpret every item in that map as a sensor with an array as data. */
	foreach(QString id, sensorMap.keys()) {
		/* this is our data */
		const QVariantList v_sensorNeurons = sensorMap[id].toList();

		/* convert QVariantList to QList<qreal> */
		QList<qreal> neuronValues;
		foreach(QVariant v, v_sensorNeurons) {
			neuronValues.append(v.toReal());
		}

		/* fill the pointers */
		*sensorBeingId = beingId;
		*sensorId = id;
		*sensorNeurons = neuronValues;
	}
}

QVariantMap EntitySerializer::serializeActuator(QString beingId, QString actuatorId, const QList<qreal>& actuatorNeurons) const
{
	/* here we will store everything */
	QVariantMap saveme;

	/* convert actuator neurons to QVariants */
	QVariantList v_actuatororNeurons;
	foreach(qreal r, actuatorNeurons) {
		v_actuatororNeurons.append(r);
	}

	/* store actuator data */

	/* tell who sent it */
	saveme.insert(KEY_BEING, beingId);

	/* we may have multiple actuators, so store the actuator in a map. */
	QVariantMap v_actuators;
	v_actuators.insert(actuatorId, v_actuatororNeurons);

	/* finally insert actuators into the map */
	saveme.insert(KEY_BEINGS_ACTUATORS, v_actuators);

	/* tell everyone who is interested */
	return saveme;
}


void EntitySerializer::deserializeActuator(const QVariant& actuatorSerialized, QString* actuatorBeingId, QString* actuatorId, QList<qreal>* actuatorNeurons) const
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

void EntitySerializer::deserializeActuators(const QVariant& actuatorSerialized, QString* actuatorBeingId, QMap< QString, QList<qreal> >* actuators) const
{
	QVariantMap parsedDataMap = actuatorSerialized.toMap();

	/* find which being is concerned */
	const QString beingId = parsedDataMap[KEY_BEING].toString();
	const QVariantMap actuatorMap = parsedDataMap[KEY_BEINGS_ACTUATORS].toMap();

	*actuatorBeingId = beingId;

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
		(*actuators).insert(id, neuronValues);
	}
}


QVariantMap EntitySerializer::serializeThing(QString thingId, const QPolygonF& shape, const QPointF& position, qreal rotation) const
{
	/* we need to serailize everything, i.e. id, shape, position and rotation. */
	QVariantMap resultMap;

	resultMap.insert(KEY_THING_ID, thingId);
	if(!shape.isEmpty()) {
		resultMap.insert(KEY_THING_SHAPE, qpolygonf2qvariant(shape));
	}
	resultMap.insert(KEY_THING_POSITION, qpointf2qvariant(position));
	resultMap.insert(KEY_THING_ROTATION, rotation);

	return resultMap;
}

void EntitySerializer::deserializeThing(const QVariant& thingSerialized, QString* thingId, QPolygonF* thingShape, QPointF* thingPosition, qreal* thingRotation) const
{
	QVariantMap serializedMap = thingSerialized.toMap();

	QString id = serializedMap[KEY_THING_ID].toString();
	QPolygonF shape = qvariant2qpolygonf(serializedMap[KEY_THING_SHAPE]);
	QPointF position = qvariant2qpointf(serializedMap[KEY_THING_POSITION]);
	bool rotationFound;
	qreal rotation = serializedMap[KEY_THING_ROTATION].toReal(&rotationFound);

	*thingId = id;
	*thingShape = shape;
	*thingPosition = position;
	*thingRotation = rotationFound ? rotation : QREAL_INVALID;
}
