#include <QApplication>
#include "surface.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Surface w;
    w.show();

    return a.exec();
}
