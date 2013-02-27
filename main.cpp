#include "purrwindow.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PurrWindow w;
    w.show();
    
    return a.exec();
}
