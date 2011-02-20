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
