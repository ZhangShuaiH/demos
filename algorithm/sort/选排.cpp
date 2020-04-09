#include <stdio.h>
#include <iostream>

using namespace std;

/*****************************************************
时间复杂度：O(n^2)
空间复杂度：O(1)
******************************************************/
// 不稳定，选择排序。找出【数组无序部分】的最小值，放到【数组无序部分】的开头
void selection_sort(int a[], int size){
    // i：未排序数组的第一个数的下标
    for(int i = 0; i < size; i++){
        // 【数组无序部分】的下标，从第二个数开始
        // 找到【数组无序部分】的最小值
        for(int j = i+1; j < size; j++){
            // 将较小值放到【数组无序部分】的开头
            if(a[i]>a[j]){
                int temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }
    }
}
// 交换次数较少，效率较高
void select_sort1(int a[], int n) {
    int min_index;
    for (int i = 0; i < n; i++) {
        min_index = i;
        for (int j = i + 1; j < n; j++) {
            if (a[j] < a[min_index])
                min_index = j;
        }
        if (min_index != i) {
            a[i] = a[i] ^ a[min_index];
            a[min_index] = a[i] ^ a[min_index];
            a[i] = a[i] ^ a[min_index];
        }
    }
}

// 优化，二元选择排序(貌似并没有提高多少效率)
void selectSort2(int a[], int size){
    int time = 0;
    for(int i=1; i<=size/2; i++){
        int min = i-1;
        int max = size-i;
        for(int j=i-1; j<=size-i; j++){
            if(a[j] > a[max]){
                max = j;
                continue;// 减少比较次数，实测效果不明显
            }
            if(a[j] < a[min])
                min = j;
            time+=2;
        }
        if(max == i-1)// 排除max被换掉的情况
            max = min;
        swap(a, i-1, min);
        swap(a, max, size-i);
    }
    myDebug(time);
}
int main()
{
    int a[] = {6,4,5,3,2,1};
    int n = sizeof(a)/sizeof(int);
    selection_sort(a, n);
    print(a, n);
}
