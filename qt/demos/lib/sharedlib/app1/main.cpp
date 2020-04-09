#include <QCoreApplication>
#include <QLibrary>
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    typedef int (*Add)(int a, int b);

    QLibrary mylib("sharedlib.dll");

    if(!mylib.load()){// ���� dll ʧ��
        cout<<"���� sharedlib.dll ʧ��!"<<endl;
        return -1;
    }
    Add add = (Add)mylib.resolve("add");
    if(0 == add){// ����ʧ��
        cout<<"���غ��� add ʧ��!"<<endl;
        return -1;
    }

    int sum = add(1,2);// ���� add ����

    cout<<sum<<endl;

    return 0;

    return a.exec();
}
