#include "VTKDataAttributes.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    VTKDataAttributes w;
    w.show();
    return a.exec();
}
