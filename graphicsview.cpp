#include "graphicsview.h"
#include <QKeyEvent>

GraphicsView::GraphicsView(QGraphicsScene * scene, QWidget* parent) :
		QGraphicsView(scene, parent)
{
}

GraphicsView::GraphicsView(QWidget* parent) :
		QGraphicsView(parent)
{
}

void GraphicsView::keyPressEvent( QKeyEvent * event )
{
	emit keyPressed((Qt::Key)event->key());
}

void GraphicsView::keyReleaseEvent( QKeyEvent * event )
{
	emit keyReleased((Qt::Key)event->key());
}

void GraphicsView::wheelEvent(QWheelEvent *event)
{
	double numSteps = 1.0f;// + (event->delta() / 100.0f);

	if (event->orientation() == Qt::Vertical) {
		if ( event->delta() > 0 ) {
			scale(1.1f * numSteps, 1.1f * numSteps);
		} else {
			scale(1.0f/(1.1f * numSteps), 1.0f/(1.1f * numSteps));
		}

		event->accept();
	} else {
		event->ignore();
	}
}

void GraphicsView::resizeEvent(QResizeEvent * event)
{
	/* keep view roughly the same when resizing */
	const int border = 2;
	QPointF topLeft = mapToScene( border, border );
	QPointF bottomRight = mapToScene( event->oldSize().width() -border -1, event->oldSize().height() -border -1 );
	QRectF rect = QRectF( topLeft, bottomRight );

	fitInView(rect, Qt::KeepAspectRatio);
}
