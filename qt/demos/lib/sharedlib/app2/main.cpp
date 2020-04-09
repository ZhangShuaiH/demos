#include "mainwindow.h"
#include <QApplication>
#include "sharedlib.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
    Sharedlib sb;
    sb.test();

    return a.exec();
}
