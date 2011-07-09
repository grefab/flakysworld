#include "surface.h"
#include "ui_surface.h"

#include "client.h"


Surface::Surface(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::Surface)
{
	ui->setupUi(this);

	client_ = new Client(this);
	client_->start(QHostAddress::LocalHost, 2345);

}

Surface::~Surface()
{
	delete ui;
}

void Surface::on_pushButton_clicked()
{
	client_->send(ui->lineEdit->text().toAscii());

}