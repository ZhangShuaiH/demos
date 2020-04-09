#include "mainwindow.h"
#include <QApplication>
#include <QLibrary>
#include "interface/imyclass.h"
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QLibrary mylib("sharedlib.dll");
    if(!mylib.load()){
        QMessageBox::warning(0, "����", "���� sharedlib.dll ʧ��!");
        return -1;
    }

    typedef IMyClass *(*GetMyClass)();

    GetMyClass getMyClass = (GetMyClass)mylib.resolve("getMyClass");

    if(0 == getMyClass){
        QMessageBox::warning(0, "����", "���غ��� getMyClass ����!");
        return -1;
    }

    IMyClass *m = getMyClass();

    m->test();

    mylib.unload();

    return 0;
    return a.exec();
}
