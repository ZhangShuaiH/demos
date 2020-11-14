#include "A.h"
#include <iostream>
#include "reflect.h"

A::A()
{
    //ctor
}

A::~A()
{
    //dtor
}
void A::show()
{
    std::cout<<"A::show"<<std::endl;
}

REFLECT(A);
