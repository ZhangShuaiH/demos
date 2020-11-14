#include <malloc.h>
#include <pthread.h>
#include <stdio.h>
#include <sstream>
#include <iostream>
#include <limits.h>
#include <map>

#include "A.h"
#include "reflect.h"

using namespace std;

int main ()
{
    cout<<"hello"<<endl;
    A* a = (A*) ReflectFactory::instace()->getObjectByClassName("A");
    a->show();

    return 0;
}
