#include "Lab2.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Lab2 w;
    w.setWindowTitle("Lab2");
    w.show();
    
    return a.exec();
}
