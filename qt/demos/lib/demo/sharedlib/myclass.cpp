#include "myclass.h"

#include <QMessageBox>

MyClass::MyClass()
{
    QMessageBox::warning(0, "MyClass::MyClass", "MyClass::MyClass");
}

void MyClass::test()
{
    QMessageBox::warning(0, "MyClass::test", "MyClass::test");
}
