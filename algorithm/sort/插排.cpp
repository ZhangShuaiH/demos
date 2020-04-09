#include <stdio.h>
#include <iostream>

using namespace std;

/*************************
 * 经典排序算法总结
**************************/
void print(int a[], int size){
    for(int i = 0; i < size; i++){
        cout<<a[i]<<" ";
    }
    cout<<endl;
}

/***********************************
 ***********插入排序-稳定*************
 空间复杂度：O(1)
 时间复杂度：O(n^2)
************************************/
/*************************************************************
                   直接插入排序
（1） 设置监视哨r[0]，将待插入记录的值赋值给r[0]；
（2） 设置开始查找的位置j；
（3） 在数组中进行搜索，搜索中将第j个记录后移，直至r[0].key≥r[j].key为止；
（4） 将r[0]插入r[j+1]的位置上。
*************************************************************/
void insertion_sort0(int a[], const int size){
    // 前 i 个数有序，后面无序
    for(int i = 0; i < size; i++){
        for(int j = 0; j < i; j++){
            // 找到第一个大于 a[i] 的数，将 a[i] 插到它前边
            if(a[i]<a[j]){
                int temp0 = a[i];
                // 依次后移一位
                for(int k = i; k > j; k--){
                    a[k] = a[k-1];
                }
                a[j] = temp0;
                break;
            }
        }
        print(a, size);
    }
}

void insertion_sort1(int a[], const int size){
    for(int i=0; i<size; i++){
        int temp = a[i];
        int j;
        // 倒序遍历有序部分，将大于 temp 的数依次后移
        for(j = i; j-1>=0 && a[j-1]>temp; j--){
            a[j] = a[j-1];// a[i] 被覆盖
        }
        // 将 temp 插入到小于等于 temp 的元素后面
        a[j] = temp;
    }
}

int main()
{
    int a[] = {6,4,5,3,2,1};
    int size = sizeof(a)/sizeof(int);
//    insertion_sort2(a, 0, size);
    insertion_sort1(a, size);
    print(a, size);
}
