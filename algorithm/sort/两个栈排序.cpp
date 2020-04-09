#include <iostream>
#include <stack>

using namespace std;

void stackSort(int a[], int size)
{
    stack<int> sta1, sta2;
    for(int i=0; i<size; i++){
        while (!sta2.empty() && sta2.top()>a[i]) {
            sta1.push(sta2.top());
            sta2.pop();
        }
        sta2.push(a[i]);
        while (!sta1.empty()) {
            sta2.push(sta1.top());
            sta1.pop();
        }
    }
    for(int i=size-1; i>=0; i--){
        a[i] = sta2.top();
        sta2.pop();
    }
}

int main(){
    int a[] = {1,2,5,3};
    int size = sizeof(a)/sizeof(int);
    stackSort(a, size);
    for(int i=0; i<size; i++)cout<<a[i]<<endl;

    return 0;
}
