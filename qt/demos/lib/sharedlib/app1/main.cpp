#include <QCoreApplication>
#include <QLibrary>
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    typedef int (*Add)(int a, int b);

    QLibrary mylib("sharedlib.dll");

    if(!mylib.load()){// º”‘ÿ dll  ß∞‹
        cout<<"º”‘ÿ sharedlib.dll  ß∞‹!"<<endl;
        return -1;
    }
    Add add = (Add)mylib.resolve("add");
    if(0 == add){// º”‘ÿ ß∞‹
        cout<<"º”‘ÿ∫Ø ˝ add  ß∞‹!"<<endl;
        return -1;
    }

    int sum = add(1,2);// µ˜”√ add ∫Ø ˝

    cout<<sum<<endl;

    return 0;

    return a.exec();
}
