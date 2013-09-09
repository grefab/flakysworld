#ifndef SURFACE_H
#define SURFACE_H

#include <QMainWindow>

namespace Ui {
    class Surface;
}

class Client;

class Surface : public QMainWindow
{
    Q_OBJECT

public:
    explicit Surface(QWidget *parent = 0);
    ~Surface();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Surface *ui;

    Client* client_;
};

#endif // SURFACE_H
