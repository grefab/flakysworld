#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>

class GraphicsView : public QGraphicsView
{
	Q_OBJECT
public:
	explicit GraphicsView(QGraphicsScene * scene, QWidget* parent = 0);

signals:
	void keyPressed( Qt::Key key );
	void keyReleased( Qt::Key key );

protected:
	void keyPressEvent( QKeyEvent * event );
	void keyReleaseEvent( QKeyEvent * event );
};

#endif // GRAPHICSVIEW_H
