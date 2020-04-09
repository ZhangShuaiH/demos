#include <iostream>

using namespace std;

pair<int,int> partition(int a[], int low, int hig){
    int min=low, max=hig, axis=a[low];
    for(int i=low; i<=max;){
        if(a[i]<axis)swap(a[i++], a[min++]);
        else if(a[i]>axis)swap(a[i], a[max--]);
        else i++;
    }
    return make_pair(min, max);
}
void quickSort(int a[], int low, int hig){
    if(low>=hig)return;
    auto par = partition(a, low, hig);
    quickSort(a, low, par.first-1);
    quickSort(a, par.second+1, hig);
}
void printArray(int a[], int size){
    for(int i=0; i<size; i++)
        cout<<a[i]<<",";
    cout<<""<<endl;
}

int main(){
    int a[] = {46, 21, 91, 42, 35, 41, 18, 85, 96, 43, 48, 98, 28, 77, 70, 99, 41, 66, 15, 35, 68, 74, 52, 50, 13, 41, 33, 35, 57, 85};
    int low = 0;
    int hig = sizeof(a)/sizeof(int)-1;
    printArray(a, hig+1);
    quickSort(a, low, hig);
    printArray(a, hig+1);

    return 0;
}
