#include "constants.h"
#include "world.h"

World::World(QObject *parent) :
	QObject(parent)
{
}

void World::thingUpdated(Thing::Model thingModel)
{
	Thing* newThing = updateThing(thingModel);

	if( newThing ) {
		/* this thing is new, needs to be connected to a view. let somebodfy else care for that. */
		emit newThingArrived(newThing);
	}
}

Thing* World::updateThing(const Thing::Model& thingModel)
{
	if( things_.contains(thingModel.id_) )	{
		/* is already there. update. */
		Thing* thing = things_.value(thingModel.id_);

		/* note that for now shape is ignored when thing already exists. */

		/* only update what's needed. */
		if(thingModel.position_ != QPOINTF_INVALID && thingModel.rotation_ != QREAL_INVALID) {
			thing->setPosRot(thingModel.position_, thingModel.rotation_);
		} else {
			if(thingModel.position_ != QPOINTF_INVALID) {
				thing->setPosition(thingModel.position_);
			}

			if(thingModel.rotation_ != QREAL_INVALID) {
				thing->setRotation(thingModel.rotation_);
			}
		}

		/* tell the caller that nothing new was created. */
		return NULL;
	} else {
		/* we hope that the newly received thing is fully described. shape change is not possible afterwards. */
		Thing* thing = new Thing(thingModel, this);
		things_.insert(thing->id(), thing);

		return thing;
	}
}
