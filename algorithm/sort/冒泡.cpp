#include <stdio.h>
#include <iostream>

using namespace std;

void print(int a[], int size){
    for(int i = 0; i < size; i++){
        cout<<a[i]<<" ";
    }
    cout<<endl;
}

/***********************************
 **************冒泡排序**************
 空间复杂度：O(1)
 时间复杂度：O(n^2)
************************************/
/*************************************************************************
1.比较相邻的元素。如果第一个比第二个大，就交换他们两个。
2.对每一对相邻元素做同样的工作，从开始第一对到结尾的最后一对。在这一点，最后的元素应该会是最大的数。
3.针对所有的元素重复以上的步骤，除了最后一个。
4.持续每次对越来越少的元素重复上面的步骤，直到没有任何一对数字需要比较。
**************************************************************************/
// 稳定。比较相邻俩数，大数放后面
void bubble_sort0(int a[], int size){
    /****************************************************************
     * 1.记录遍历次数（遍历前计数。若遍历后计数，则值域为0<=次数<=size-2），使用循环
     * 2.次数值域
     *      1<=次数<=size
     * 3.缩小次数值域
     *      遍历 size-1 次即可确定数组顺序
     *      次数值域：1<=次数<=size-1
    *****************************************************************/
    for(int ergodic_time = 1; ergodic_time <= size-1; ergodic_time++){
        /*********************************
         * 1.遍历数组，使用循环；
         * 2.下标
         *      []中的变量：j, j+1
         * 2.下标值域
         *      0<=下标<size
         * 3.缩小下标值域
         *      由于排好序的部分数组无需再次遍历，所以可以缩小下标的上边界
         *      用 ergodic_time 记录遍历次数，遍历第 ergodic_time 次，
         *      下标值域：0<=下标<size-ergodic_time+1
         *********************************/
        for(int j = 0; j+1 < size-ergodic_time+1; j++){
            // 比较相邻两个数，大数放后面
            if(a[j]>a[j+1]){
                int temp = a[j];
                a[j] = a[j+1];
                a[j+1] = temp;
            }
        }
    }
}

// 稳定。类似 bubble_sort0
void bubble_sort1(int a[], int size){
    int ergodic_time = 0;// 遍历次数，遍历结束时计数
    do{
        // 最大数排最后面
        for(int i = 0; i+1 < size-ergodic_time; i++){
            // 比较相邻俩数，将大数放后面
            if(a[i]>a[i+1]){
                int temp = a[i];
                a[i] = a[i+1];
                a[i+1] = temp;
            }
        }
        ergodic_time++;
    }while(ergodic_time<size-1);
}
// 优化后的冒泡排序，对于整体有序的序列，可大大减少比较次数
void bubble_sort_optimize(int a[], const int size){
    int comparedTime = 0;
    int swapped = true;// 若未发生移动，则完成全部排序
    int lastSwappedIndex;// 最后一次交换的位置，其后的元素完成排序
    for(int i = 0; i<size && swapped; i = size-(lastSwappedIndex+1)){
        swapped = false;
        for(int j = 0; j+1 < size-i; j++){
            comparedTime++;
            if(a[j]>a[j+1]){
                int temp = a[j];
                a[j] = a[j+1];
                a[j+1] = temp;
                swapped = true;
                lastSwappedIndex = j;
            }
        }
    }
    cout<<"compared time: "<<comparedTime<<endl;
    cout<<"saved time: "<<(size*(size-1)/2)-comparedTime<<endl;
}
// 标准冒泡排序
void bubble_sort_standard(int a[], const int size){
    for(int i = 0; i < size; i++){
        for(int j=0; j+1<size-i; j++){
            if(a[j]>a[j+1]){
                int temp = a[j];
                a[j] = a[j+1];
                a[j+1] = temp;
            }
        }
    }
}
int main()
{
    int a[] = {6,4,5,3,2,1};
    int n = sizeof(a)/sizeof(int);
    bubble_sort1(a, n);
    print(a, n);
}
