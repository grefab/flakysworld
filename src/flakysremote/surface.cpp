#include "surface.h"
#include "ui_surface.h"

#include "client.h"


Surface::Surface(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Surface)
{
    ui->setupUi(this);

    ui->lineEdit->setText(
            "{ " \
            "\"type\" : \"actuatorinput\", "\
            "\"being\" : \"flaky\", "\
            "\"actuators\" : "\
            "{ "\
                "\"thrl\" : [0.3], "\
                "\"thrr\" : [0.3] "\
            "} "\
            "}");

    client_ = new Client(QHostAddress::LocalHost, 2345, this);
    client_->start();

}

Surface::~Surface()
{
    delete ui;
}

void Surface::on_pushButton_clicked()
{
    client_->send(ui->lineEdit->text().toLocal8Bit());
}
