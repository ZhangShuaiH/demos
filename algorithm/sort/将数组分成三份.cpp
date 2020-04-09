#include <iostream>
#include <vector>

using namespace std;

void printArray(int a[], int size){
    for(int i=0; i<size; i++)
        cout<<a[i]<<",";
    cout<<""<<endl;
}
// 将数组分成三份
void divide(int a[], int size){
    int i=0, min=0, max=size-1;
    while (i<=max) {
        if(a[i]<0)swap(a[i++], a[min++]);
        else if(a[i]>0)swap(a[i], a[max--]);
        else i++;
    }
}
int main(){
    int a[] = {-4, 1, -3, -1, -5, 5, 0, -2, -5, 5};
    int size = sizeof(a)/sizeof(int);
    divide(a, size);
    printArray(a, size);
    return 0;
}
