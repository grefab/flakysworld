#include "surface.h"
#include "ui_surface.h"
#include <QGLWidget>

Surface::Surface(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::Surface)
{
	ui->setupUi(this);

	scene_.setItemIndexMethod(QGraphicsScene::NoIndex);
	scene_.setBackgroundBrush(Qt::white);
	scene_.setSceneRect(-1, -1, 2, 2);

	/* greatly enhances speed. */
	ui->graphicsView->setScene(&scene_);
	ui->graphicsView->setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers)));
	ui->graphicsView->setRenderHint(QPainter::Antialiasing);
	ui->graphicsView->scale(400, 400);
	ui->graphicsView->show();
}

Surface::~Surface()
{
	delete ui;
}

GraphicsView* Surface::view()
{
	return ui->graphicsView;
}
