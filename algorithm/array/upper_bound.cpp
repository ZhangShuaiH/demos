#include <malloc.h>
#include <pthread.h>
#include <stdio.h>
#include <sstream>
#include <iostream>
#include <limits.h>
#include <map>
#include <vector>

using namespace std;
// 找到第一个大于tar的值的位序
int find_upper_bound(const int a[], const int size, const int tar)
{
    int i=0,j=size;
    while(i<j)
    {
        int mid = (j-i)/2+i;
        if(a[mid] <= tar)
            i=mid+1;
        else
            j=mid;
    }
    cout<<"tar "<<tar<<" index "<<i<<endl;
    return i;
}

int main ()
{
    //         0 1 2 3 4 5 6
    int a[] = {1,2,4,7,9,9,10};
    int size=sizeof(a)/sizeof(int);

    find_upper_bound(a,size,0);
    find_upper_bound(a,size,1);
    find_upper_bound(a,size,3);
    find_upper_bound(a,size,9);
    find_upper_bound(a,size,10);
    find_upper_bound(a,size,11);


    return 0;
}
