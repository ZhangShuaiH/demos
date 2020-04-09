#include <stdio.h>
#include <iostream>

using namespace std;

void print(const int a[], const int size){
    for(int i = 0; i < size; i++)cout<<a[i]<<" ";
    cout<<endl;
}
void print(const int a[], const int low, const int high){
    for(int i = low; i < high+1; i++)cout<<a[i]<<" ";
    cout<<endl;
}

/**************快速排序***************
空间复杂度：O(1)
时间复杂度：O(nlogn)
不稳定。
**************工作原理****************
通过一趟排序将要排序的数据分割成独立的两部分，
其中一部分的所有数据都比另外一部分的所有数据都要小，
然后再按此方法对这两部分数据分别进行快速排序，
整个排序过程可以递归进行，
以此达到整个数据变成有序序列。
************************************/
// 以首元素为轴
void quick_sort1(int a[], const int low, const int high){
    if(low >= high) return;
    int i=low, j=high, axis = a[i];// 空出中轴位
    while (i<j) {
        for(; i<j && a[j]>=axis; j--);// 从右边找一个小于轴的数
        a[i] = a[j];// 放到低端
        for(; i<j && a[i]<=axis; i++);// 从左边找一个大于轴的数
        a[j] = a[i];// 放到高端
    }
    a[i] = axis;// 填充中轴位
    quick_sort1(a, low, i-1);
    quick_sort1(a, i+1, high);
}

void quickSortThree(int a[], const int low, const int hig){// 三值取中值法
    if(low>=hig) return;
    int i=low, j=hig;
    int mid=low+(hig-low>>1);
    if((a[mid]>=a[low]&&a[mid]<=a[hig]) || // 将三值得中值换到 low
            (a[mid]<=a[low]&&a[mid]>=a[hig]))
        myswap(a, mid, low);
    else if((a[hig]>=a[low]&&a[hig]<=a[mid]) ||
            (a[hig]<=a[low]&&a[hig]>=a[mid]))
        myswap(a, hig, low);
    int axis = a[i];// 三中值法
    while (i<j) {
        for(; i<j && a[j]>=axis; j--);
        a[i] = a[j];
        for(; i<j && a[i]<=axis; i++);
        a[j] = a[i];
    }
    a[i] = axis;
    quickSortThree(a, low, i-1);
    quickSortThree(a, i+1, hig);
}

int main()
{
    int a[] = {19, 17, 92, 74, 84, 19, 9, 28, 77, 66};
    quick_sort0(a, 0, 9);
    print(a, 10);
}
