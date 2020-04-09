#include <iostream>
#include <vector>

using namespace std;

const vector<int> getNext(const char pattern[]){
    int size = strlen(pattern);
    vector<int> next(size, -1);
    for(int i=1,j=0; i<size-1;){
        if(j==-1){
            i++,j++;
        }else if(pattern[i]==pattern[j]){
            i++,j++;
            next[i] = pattern[i]==pattern[j]?next[j]:j;// 优化后的 next 数组
//            next[i] = j;// 未优化的 next 数组
        }else{
            j = next[j];
        }
    }
    return next;
}
int KMP(const char pattern[], const char data[], const vector<int> &next){
    int i,j;
    int dsize=strlen(data), psize=strlen(pattern);
    for(i=0,j=0; i<dsize && j<psize;){
        if(j==-1 || data[i]==pattern[j])i++,j++;
        else j=next[j];
    }
    if(j==psize)return i-j;
    else return -1;
}
void printVector(const vector<int> &vv){
    for(auto itr=vv.begin(); itr!=vv.end(); itr++)cout<<*itr<<",";
    cout<<""<<endl;
}
int main(){
    char pattern[] = "ababaca";
    char data[] = "bacbababadababacambabacaddababacasdsd";
    const vector<int> next = getNext(pattern);
    printVector(next);
    cout<<KMP(pattern, data, next)<<endl;

    return 0;
}
