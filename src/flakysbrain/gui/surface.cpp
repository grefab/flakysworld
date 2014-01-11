#include "surface.h"
#include "ui_surface.h"

Surface::Surface(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Surface)
{
    ui->setupUi(this);
}

Surface::~Surface()
{
    delete ui;
}
