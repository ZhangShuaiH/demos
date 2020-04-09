#include <iostream>
#include <fstream>
#include <time.h>
#include <typeinfo>

using namespace std;

string fileName = "testData.txt";
const unsigned gSize = 50;
const unsigned gMaxValue = 200;

void printArray(int a[], const unsigned int size){
    for(unsigned int i=0; i<size; i++)
        cout<<a[i]<<" ";
    cout<<endl;
}

void createTestData(){
    ofstream out(fileName);
    if(!out.is_open()){
        cout<<"打开文件 "<<fileName<<" 失败！"<<endl;
        return;
    }
    srand((int)time(0));

    for(unsigned int i=0; i<gSize; i++){
        out<<rand()%gMaxValue<<" ";
    }out<<endl;

    out.close();
}
int *readTestData(){
    ifstream in(fileName);
    if(!in.is_open()){
        cout<<"打开文件 "<<fileName<<" 失败！"<<endl;
        return NULL;
    }

    int *res = new int[gSize];
    for(unsigned int i=0; i<gSize && !in.eof(); i++){
        in>>res[i];
    }

    in.close();
    return res;
}

void myswap(int a[], const int m, const int n){
    if(m == n)return;
    a[m] = a[m]^a[n];
    a[n] = a[m]^a[n];
    a[m] = a[m]^a[n];
}
// 冒泡
void bubbleSort(int a[], const unsigned int size){
    cout<<"bubbleSort"<<endl;
    for(unsigned int i=0; i<size; i++)
        for(unsigned int j=0; j+1<size-i; j++)
            if(a[j]>a[j+1])
                myswap(a, j, j+1);
}
// 插排
void insertSort(int a[], const unsigned int size){
    cout<<"insertSort"<<endl;
    int temp,j;
    for(unsigned int i=0; i<size; i++){
        temp = a[i];
        j=i;
        for(; j-1>=0; j--){
            if(a[j-1]>temp)
                a[j] = a[j-1];
            else
                break;
        }
        a[j] = temp;
    }
}
// 希尔
void shellSort(int a[], const unsigned int size){
    cout<<"shellSort"<<endl;
    for(int step=size; step>=1; step/=2){
        int temp,j;
        for(unsigned i=0; i<size; i++){
            temp = a[i];
            j=i;
            for(; j-step>=0; j-=step){
                if(a[j-step]>temp)
                    a[j] = a[j-step];
                else
                    break;
            }
            a[j] = temp;
        }
    }
}
// 选排
void selectSort(int a[], const unsigned int size){
    cout<<"selectSort"<<endl;
    unsigned min;
    for(unsigned i=0; i<size; i++){
        min = i;
        for(unsigned j=i+1; j<size; j++){
            if(a[j]<a[min])
                min = j;
        }
        myswap(a, i, min);
    }
}
// 堆排
void heapSort(int a[], const unsigned size){
    cout<<"heapSort"<<endl;
    unsigned par,cur,max,left,right;
    for(unsigned i=0; i<size; i++){// 建立大顶堆
        cur = i;
        while (cur) {
            par = (cur-1)/2;
            if(a[cur] > a[par]) {
                myswap(a, cur, par);
                cur = par;
            }else
                break;
        }
    }
    for(int i=size-1; i>=0; i--){
        myswap(a, 0, i);
        cur=0;
        while (cur<i) {
            max = cur;
            left = cur*2+1;
            right= cur*2+2;
            if(left<i && a[left]>a[max])
                max = left;
            if(right<i && a[right]>a[max])
                max = right;
            if(max == cur)
                break;
            else {
                myswap(a, cur, max);
                cur = max;
            }
        }
    }
}
// 快排
void quickSort(int a[], const unsigned low, const unsigned hig){
    if(low>=hig) return;
    unsigned i=low, j=hig;
    int axis = a[i];
    while(i<j){
        for(; i<j && a[j]>=axis; j--);
        a[i] = a[j];
        for(; i<j && a[i]<=axis; i++);
        a[j] = a[i];
    }
    a[i] = axis;
    quickSort(a, low, i-1);
    quickSort(a, i+1, hig);
}
// 计排
void countSort(int a[], const unsigned int size){
    // todo
    cout<<"countSort"<<endl;
    int *counter = (int*)malloc(sizeof(int)*gMaxValue);// 计数器
    for(unsigned i=0; i<gMaxValue; i++) counter[i]=0;
    for(unsigned i=0; i<size; i++) counter[a[i]]++;
    for(unsigned i=0, j=0; i<gMaxValue;i++){
        while(counter[i] != 0){
            a[j] = i;
            counter[i]--;
            j++;
        }
    }
    free(counter);
}
// 归并
void merge(int a[], int temp[], const unsigned low, const unsigned mid, const unsigned hig){
    unsigned i=low, k=low,j=mid+1;
    while (i<=mid && j<=hig) {
        if(a[i] <= a[j]) temp[k++] = a[i++];
        else temp[k++] = a[j++];
    }
    while (i <= mid) temp[k++] = a[i++];
    while(j <= hig) temp[k++] = a[j++];
    k = low;
    while(k<=hig) a[k] = temp[k++];
}
void mergeSort(int a[], int temp[], const unsigned low, const unsigned hig){
    if(low>=hig)return;
    const unsigned mid = low + (hig-low)/2;
    mergeSort(a, temp, low, mid);
    mergeSort(a, temp, mid+1, hig);
    merge(a, temp, low, mid, hig);
}
bool validate(int a[], unsigned size){
    for(unsigned i=1; i<size; i++){
        if(a[i-1]>a[i]){
            return false;
        }
    }
    return true;
}
void testSort(void sort(int a[], const unsigned gSize)){
    int *a = readTestData();
    sort(a, gSize);
    if(!validate(a, gSize))cout<<"error????????????????????"<<endl;
    else cout<<"succ!"<<endl;
}
void testQuickSort(){
    int *a = readTestData();
    quickSort(a, 0, gSize-1);
    if(!validate(a, gSize))cout<<"error: quickSort????????????????????"<<endl;
    else cout<<"succ: quickSort!"<<endl;
}
void testMergeSort(){
    int *a = readTestData();
    int *temp = (int*)malloc(sizeof(int)*gSize);
    mergeSort(a, temp, 0, gSize-1);
    if(!validate(a, gSize))cout<<"error: mergeSort????????????????????"<<endl;
    else cout<<"succ: mergeSort!"<<endl;
    free(temp);
}

// 测试
void testAll(){
    testSort(bubbleSort);
    testSort(insertSort);
    testSort(shellSort);
    testSort(selectSort);
    testSort(heapSort);
    testQuickSort();
    testMergeSort();
    testSort(countSort);
}

int main(int argc, char *argv[])
{
//    createTestData();
    testAll();

    return 0;
}
