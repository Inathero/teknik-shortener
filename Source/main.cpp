#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    // For deployment
//    QCoreApplication::addLibraryPath("./");
    QApplication a(argc, argv);
    MainWindow w;

    return a.exec();
}
