#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>
#include <QWheelEvent>
#include <QResizeEvent>

class GraphicsView : public QGraphicsView
{
    Q_OBJECT

public:
    explicit GraphicsView(QGraphicsScene * scene, QWidget* parent = 0);
    explicit GraphicsView(QWidget* parent = 0);

signals:
    void keyPressed( Qt::Key key );
    void keyReleased( Qt::Key key );

protected:
    void keyPressEvent( QKeyEvent *event );
    void keyReleaseEvent( QKeyEvent *event );

    void wheelEvent(QWheelEvent *event);
    void resizeEvent(QResizeEvent * event);
};

#endif // GRAPHICSVIEW_H
