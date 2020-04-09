#include <QCoreApplication>
#include "staticlib.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Staticlib sb;
    sb.test();

    return a.exec();
}
