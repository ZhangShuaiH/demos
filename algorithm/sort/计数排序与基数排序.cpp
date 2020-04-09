#include <iostream>
#include <vector>

using namespace std;

void printArray(int a[], int size){
    for(int i=0; i<size; i++)
        cout<<a[i]<<",";
    cout<<""<<endl;
}
// 计数排序
void countSort(int a[], int size){// 计数排序是特殊的基数排序
    int min=a[0], max=a[0];
    for(int i=0; i<size; i++){
        if(a[i]<min)
            min = a[i];
        else if(a[i]>max)
            max = a[i];
    }
    int csize = max-min+1;
    vector<int> bucket(csize, 0);
    for(int i=0; i<size; i++)bucket[a[i]-min]++;
    for(int i=1; i<csize; i++)bucket[i]+=bucket[i-1];
    vector<int> temp(size, 0);
    for(int i=size-1; i>=0; i--)temp[--bucket[a[i]-min]] = a[i];
    for(int i=0; i<size; i++)a[i]=temp[i];
}
// 基数排序
void radixSort(int a[], int size){
    const int bucketSize = 10;
    for(int n=0, radix=1; n<3; n++, radix*=10){
        int bucket[bucketSize] = {};
        for(int i=0; i<size; i++)bucket[a[i]/radix%10]++;
        for(int i=1; i<bucketSize; i++)bucket[i] += bucket[i-1];
        vector<int> tmp(size, 0);
        for(int i=size-1; i>=0; i--)tmp[--bucket[a[i]/radix%10]] = a[i];
        for(int i=0; i<size; i++)a[i]=tmp[i];
    }
}

int main(){
    int a[] = {409, 320, 180, 303, 238, 422, 346, 211, 108, 450};
    int size = sizeof(a)/sizeof(int);
//    countSort(a, size);
    radixSort(a, size);
    printArray(a, size);
    return 0;
}
