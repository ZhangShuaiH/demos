#include <iostream>

using namespace std;

void print(int a[], int size){
    for(int i=0; i<size; i++){
        cout<<a[i]<<" ";
    }
    cout<<endl;
}

void swap(int a[], int i, int j){
    if(i==j)return;
    else {
        a[i] = a[i]^a[j];
        a[j] = a[i]^a[j];
        a[i] = a[i]^a[j];
    }
}

void heapify(int a[], const int low, const int high){// 大堆顶变化后，将其重新变成堆
    int cur, left, right, max;
    cur = low;
    while (cur<=high) {
        left = cur*2+1;
        right = cur*2+2;
        max = cur;
        if(left<=high && a[left]>a[max]) max = left;
        if(right<=high && a[right]>a[max]) max = right;
        if(cur == max){
            break;
        }else{
            swap(a, cur, max);
            cur = max;
        }
    }
}

/// 堆排序
void heapSort(int a[], int size){
    int cur,parent,max,left,right;
    /// 建大顶堆
    for(int i=0; i<size; i++){
        cur = i;
        while (cur != 0) {
            parent = (cur-1)/2;
            if(a[parent]<a[cur]){
                swap(a, parent, cur);
                cur = parent;
            }else {
                break;
            }
        }
    }

    for(int i=size-1; i >= 0; i--){
        swap(a, 0, i);
        cur = 0;
        while (cur*2+1<i) {
            max = cur;
            left = cur*2+1;
            right = left+1;
            if(a[left] > a[max]){
                max = left;
            }
            if(right<i && a[right]>a[max]){
                max = right;
            }
            if(cur != max){
                swap(a, max, cur);
                cur = max;
            }else{
                break;
            }
        }
    }
}

void heapSort1(int a[], const int size){// 更加工整，容易理解
    int cur, par, left, right, max;
    for(int i=0; i<size; i++){// 上浮，建堆
        cur = i;
        while (cur!=0) {
            par = (cur-1)/2;
            if(a[cur] > a[par]){
                swap(a, cur, par);
                cur = par;
            }else {
                break;
            }
        }
    }
    for(int i=size-1; i>=0; i--){// 下沉，堆化
        swap(a, 0, i);
        cur = 0;
        while (cur < i) {
            left = cur*2+1;
            right = cur*2+2;
            max = cur;
            if(left<i && a[left]>a[max]) max = left;
            if(right<i && a[right]>a[max]) max = right;
            if(max == cur){
                break;
            }else {
                swap(a, max, cur);
                cur = max;
            }
        }
    }
}

int main()
{
    int a[] = {12, 10, 23, 67, 8, 10};
    int size = sizeof(a)/sizeof(int);
    print(a, size);
    heapSort(a, size);
    print(a, size);
    return(0);
}
