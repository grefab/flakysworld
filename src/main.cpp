#include <QtGui>

#include "infrastructure/universe.h"

#include "gui/surface.h"
#include "gui/bodyviews/circlebodyview.h"
#include "gui/bodyviews/polygonbodyview.h"
#include "gui/flakyviews/eyeview.h"

#include "interface/neuronserializer.h"
#include "interface/tcpserver.h"

Surface* setupGUI(Universe* universe)
{
	Surface* surface = new Surface();
	surface->show();

	QObject::connect(universe->engine(), SIGNAL(updatedFPS(int)), surface->fpsLabel(), SLOT(setNum(int)));

	/* build a corresponding view for each body. */
	foreach(Body* body, universe->world()->bodies()) {
		CircleBody* circleBody = dynamic_cast<CircleBody*>(body);
		if ( circleBody ) {
			surface->scene()->addItem( new CircleBodyView(*circleBody) );
		}

		PolygonBody* polygonBody = dynamic_cast<PolygonBody*>(body);
		if ( polygonBody ) {
			surface->scene()->addItem( new PolygonBodyView(*polygonBody) );
		}
	}

	/* build a corresponding view for flaky's eyes. */
	foreach(Sensor* sensor, universe->being("flaky")->sensors()) {
		Eye* eye = dynamic_cast<Eye*>(sensor);
		if ( eye ) {
			surface->scene()->addItem( new EyeView(*eye) );
		}
	}

	/* show everything */
	surface->view()->fitInView(surface->scene()->sceneRect(), Qt::KeepAspectRatio);

	/* connect our key events */
	QObject::connect(surface->view(), SIGNAL(keyPressed(Qt::Key)), universe, SLOT(keyPressHandler(Qt::Key)));
	QObject::connect(surface->view(), SIGNAL(keyReleased(Qt::Key)), universe, SLOT(keyReleaseHandler(Qt::Key)));

	/* and our engage button */
	// TODO: Just provide motoric information and let flaky handle the consequences.
	QObject::connect(surface, SIGNAL(engageTriggered(qreal,qreal)), universe->being("flaky"), SLOT(accelerate(qreal,qreal)));

	return surface;
}

NeuronSerializer* setupNeuronIO(Universe* universe)
{
	/* the neuron serializer is a thread itself. */
	NeuronSerializer* neuronSerializer = new NeuronSerializer();

	/* this thread handles our network activity. */
	QThread* networkThread = new QThread();
	TcpServer* tcpServer = new TcpServer(2345);
	tcpServer->moveToThread(networkThread);
	networkThread->start();

	/* allow for data exchange */
	QObject::connect(tcpServer, SIGNAL(dataArrived(QByteArray)), neuronSerializer, SLOT(deserializeActuator(QByteArray)));
	QObject::connect(neuronSerializer, SIGNAL(sensorSerialized(QByteArray)), tcpServer, SLOT(publish(QByteArray)));

	/* we'd like to output all our sensors. */
	foreach(Being* being, universe->beings()) {
		foreach(Sensor* sensor, being->sensors()) {
			QObject::connect(sensor, SIGNAL(sensed(QList<qreal>)), neuronSerializer, SLOT(serializeSensor(QList<qreal>)));
		}
	}

	return neuronSerializer;

	/* note that networkThread and tcpServer will never get deleted. this can be improved.
	 * however, they will die at the end of the program and they are idle once neuronSerializer
	 * is deleted. so there will be no problem here.
	 */
}

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	qsrand(time(0));

	/* our universe. it manages world and engine that keeps world alive. */
	Universe* universe = new Universe();

	/* make everything visible */
	Surface* surface = setupGUI(universe);

	/* start neuron IO */
	NeuronSerializer* neuronSerializer = setupNeuronIO(universe);

	/* preparation is done. let if flow! */
	return app.exec();

	delete neuronSerializer;
	delete surface;
	delete universe;
}
