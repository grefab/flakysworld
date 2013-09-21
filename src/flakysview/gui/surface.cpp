#include "surface.h"
#include "ui_surface.h"
#include <QGLWidget>

Surface::Surface(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::Surface)
{
    ui->setupUi(this);

    ui->groupBox->hide();

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
