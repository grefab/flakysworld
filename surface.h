#ifndef SURFACE_H
#define SURFACE_H

#include <QMainWindow>
#include <QGraphicsScene>
#include "graphicsview.h"
#include <QLabel>

namespace Ui {
	class Surface;
}

class Surface : public QMainWindow
{
	Q_OBJECT

public:
	explicit Surface(QWidget *parent = 0);
	~Surface();

	/* needed for connecting signals */
	QGraphicsScene* scene() { return &scene_; }
	GraphicsView* view();
	QLabel* fpsLabel();

signals:
	void engageTriggered(qreal leftThruster, qreal rightThruster);

protected:
	QGraphicsScene scene_;

private:
	Ui::Surface *ui;

private slots:
	void on_btn_engage_clicked();
};

#endif // SURFACE_H
