#include "sharedlib.h"
#include <QMessageBox>

Sharedlib::Sharedlib()
{
    QMessageBox::warning(0, "Sharedlib::Sharedlib", "Sharedlib::Sharedlib");
}

MyClass *getMyClass()
{
    return new MyClass;
}
