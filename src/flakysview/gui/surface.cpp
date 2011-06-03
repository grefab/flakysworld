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

	/* greatly enhances speed. */
	ui->graphicsView->setScene(&scene_);
	ui->graphicsView->setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers)));
	ui->graphicsView->setRenderHint(QPainter::Antialiasing);
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

QLabel* Surface::fpsLabel()
{
	return ui->lFPS;
}

void Surface::on_btn_engage_clicked()
{
	qreal left = (qreal)ui->dial_left->value() / (qreal)ui->dial_left->maximum();
	qreal right = (qreal)ui->dial_right->value() / (qreal)ui->dial_right->maximum();

	emit engageTriggered( left * 0.01, right * 0.01 );
}
