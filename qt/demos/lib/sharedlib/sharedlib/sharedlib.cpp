#include "sharedlib.h"

#include <QMessageBox>


Sharedlib::Sharedlib()
{
}

void Sharedlib::test()
{
    QMessageBox::warning(0, "Sharedlib::test", "Sharedlib::test2");
}

int add(int a, int b)
{
    return a+b+1;
}
