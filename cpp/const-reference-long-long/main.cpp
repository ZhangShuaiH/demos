#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <map>
#include <algorithm>
#include <set>
#include <typeinfo>
#include <string.h>
#include <map>
#include "timeing.h"

using namespace std;

void func(long long ll)
{
    int i=ll;
}

void cfunc(const long long ll)
{
    int i=ll;
}
void rfunc(long long &ll)
{
    int i=ll;
}

void crfunc(const long long &ll)
{
    int i=ll;
}
const size_t SIZE=10000000;
int main()
{ 
    long long ll=100ll;

    TIMEING(
	for(size_t i=0; i<SIZE; i++)
	{
	    func(ll);
	}
    )

    TIMEING(
	for(size_t i=0; i<SIZE; i++)
	{
	    cfunc(ll);
	}
    )
    TIMEING(
	for(size_t i=0; i<SIZE; i++)
	{
	    rfunc(ll);
	}
    )

    TIMEING(
	for(size_t i=0; i<SIZE; i++)
	{
	    crfunc(ll);
	}
    )

    return 0;
}
