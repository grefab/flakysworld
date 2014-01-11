#ifndef SURFACE_H
#define SURFACE_H

#include <QMainWindow>

namespace Ui {
class Surface;
}

class Surface : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit Surface(QWidget *parent = 0);
    ~Surface();
    
private:
    Ui::Surface *ui;
};

#endif // SURFACE_H
