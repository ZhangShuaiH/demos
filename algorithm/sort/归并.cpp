#include <stdio.h>
#include <iostream>

using namespace std;

/*************************
 * 经典排序算法总结
**************************/
void print(int a[], int size){
    for(int i = 0; i < size; i++)cout<<a[i]<<" ";
    cout<<endl;
}

/***********************************
**************归并排序***************
空间复杂度：O(n)
时间复杂度：O(nlogn)
稳定。
用于排列整体无序，局部有序的序列
**************工作原理****************
第一步：申请空间，使其大小为两个已经排序序列之和，该空间用来存放合并后的序列
第二步：设定两个指针，最初位置分别为两个已经排序序列的起始位置
第三步：比较两个指针所指向的元素，选择相对小的元素放入到合并空间，并移动指针到下一位置
重复步骤3直到某一指针超出序列尾
将另一序列剩下的所有元素直接复制到合并序列尾
************************************/
// 合并排序
void merge_sort(int src[], int temp[], const int low, const int mid, const int high){
    int i = low, j = mid+1, k = low;
    while (i<mid+1 && j<high+1)
        if(src[i]<src[j]) temp[k++] = src[i++];
        else temp[k++] = src[j++];
    while(j < high+1)temp[k++] = src[j++];
    while (i < mid+1)temp[k++] = src[i++];
    for(int i = low; i < high+1; i++)src[i] = temp[i];
}
// 分治，递归
void divide(int src[], int temp[], const int low, const int high){
    int mid = (low + high)/2;
    if(low < high){
        divide(src, temp, low, mid);
        divide(src, temp, mid+1, high);
        merge_sort(src, temp, low, mid, high);
    }
}

int main()
{
    int src[] = {83, 82, 23, 14, 65, 82, 68, 21, 32, 74};
    int temp[] = {0,0,0,0,0 ,0,0,0,0,0};
    divide(src, temp, 0, 9);
    print(temp, 10);
}
