#include <iostream>
#include <vector>

using namespace std;

int findDividingLine(const int sortedArray[], const int size, const int target){
    int i=0, j=size-1;
    while (i<=j) {
        int mid = i+(j-i)/2;
        if(sortedArray[mid]<=target) i=mid+1;// 找到小于等于target和大于target的分界线
        else j=mid-1;
    }
    if(size==0 || i>size-1)return -1;
    else return i;// 第一个大于 target 的位序
}
void printArray(const int a[], const int size){
    for(int i=0; i<size; i++)cout<<i<<":"<<a[i]<<", ";
    cout<<""<<endl;
}

int main(){
    int a[]={10, 10, 11, 11, 12, 12, 12, 13, 14, 16, 17, 17, 17, 18, 19, 19, 19, 20, 20, 20};
    int size = sizeof(a)/sizeof(int);
    printArray(a, size);
    cout<<findDividingLine(a, size, 20)<<endl;
    cout<<findDividingLine(a, size, 21)<<endl;
    cout<<findDividingLine(a, size, 10)<<endl;
    cout<<findDividingLine(a, size, 9)<<endl;

    cout<<findDividingLine(a, size, 12)<<endl;
    cout<<findDividingLine(a, size, 15)<<endl;

    return 0;
}











