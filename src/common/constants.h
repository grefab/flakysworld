#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QString>
#include <limits>

/* needed to check if serialization worked */
#define QPOINTF_INVALID QPointF(LONG_MIN, LONG_MIN)
#define QREAL_INVALID LONG_MIN

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

JSON Communication Spec
=======================

Note that the characters  {}[]":  used here mean the actual characters (map, array,
string delimiters), whereas  ()  group elements as entity.  +*  mean “one or more”
and “zero or more” of the previously described entity (where entities have to be
comma separated).  |  describes a set of optional elements, from which one has to
be chosen.


These objects can be received by flakysworld:

{ "type" : "register",
  "concerns" : ( "sensors" | "world" ) }
{ "type" : "unregister",
  "concerns" : ( "sensors" | "world" ) }
{ "type" : "actuatorinput",
  "being" : "BEING_ID",
  "actuators" : { ( "ACTUATOR_ID" : [ REAL* ] )+ } }


If registered to corresponding updates, a client will recieve:

{ "type" : "sensoroutput",
  "being" : "BEING_ID",
  "sensors" : { ( "SENSOR_ID" : [ REAL* ] )+ } }
{ "type" : "thing",
  "thing" : "THING_ID",
  "shape" : [ ( { "x" : REAL, "y" : REAL } )* ],
  "position" : { "x" : REAL, "y" : REAL },
  "rotation" : REAL }

* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


/* these are the constants for the things described above */
const QString KEY_TYPE = "type";
const QString TYPE_SENSOROUTPUT = "sensoroutput";
const QString TYPE_THING = "thing";
const QString KEY_CONCERNS = "concerns";
const QString TYPE_REGISTER = "register";
const QString TYPE_UNREGISTER = "unregister";
const QString TYPE_ACTUATORINPUT = "actuatorinput";
const QString CONCERNS_SENSORS = "sensors";
const QString CONCERNS_WORLD = "world";


#endif // CONSTANTS_H
