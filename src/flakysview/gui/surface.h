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

protected:
	QGraphicsScene scene_;

private:
	Ui::Surface *ui;

};

#endif // SURFACE_H
