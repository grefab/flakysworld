#include "entityserializer.h"

#include <QDebug>

#include "persistence.h"

/* string definitions needed later */
static const QString KEY_BEING = "being";
static const QString KEY_BEINGS_SENSORS = "sensors";
static const QString KEY_BEINGS_ACTUATORS = "actuators";

const QString KEY_THING_ID = "thing";
const QString KEY_THING_SHAPE = "shape";
const QString KEY_THING_POSITION = "position";
const QString KEY_THING_ROTATION = "rotation";


EntitySerializer::EntitySerializer(QObject *parent) :
	QObject(parent)
{
	qRegisterMetaType< QList<qreal> >("QList<qreal>");
}

EntitySerializer::~EntitySerializer()
{
}

QVariantMap EntitySerializer::serializeSensor(QString beingId, QString sensorId, const QList<qreal>& sensorNeurons)
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

void EntitySerializer::deserializeActuator(const QVariant& actuatorSerialized, QString* actuatorBeingId, QString* actuatorId, QList<qreal>* actuatorNeurons)
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

QVariantMap EntitySerializer::serializeThing(QString thingId, const QPolygonF& shape, const QPointF& position, qreal rotation)
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

void EntitySerializer::deserializeThing(const QVariant& thingSerialized, QString* thingId, QPolygonF* thingShape, QPointF* thingPosition, qreal* thingRotation)
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
