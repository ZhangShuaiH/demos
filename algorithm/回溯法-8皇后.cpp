#include <iostream>
#include <vector>
#include <typeinfo>
#include <string>
#include <stack>
#include <map>
#include <set>
#include <windows.h>
#include "mydebug.h"
#include <QString>

using namespace std;

const int NUM = 8;

void print2Array(int a[NUM][NUM]){
    for(int r=0; r<NUM; r++){
        for(int c=0; c<NUM; c++)cout<<a[r][c]<<",";
        cout<<""<<endl;
    }
    cout<<"**************************************"<<endl;
}
bool isConflict(int pan[NUM][NUM], const int row, const int col){
    for(int m=0; m<col; m++)
        if(pan[row][m]==1) return true;
    for(int m=0; m<row; m++)
        if(pan[m][col]==1) return true;
    for(int r=row-1,c=col-1; r>=0 && c>=0; r--,c--)
        if(pan[r][c]==1)return true;
    for(int r=row-1,c=col+1; r>=0 && c<NUM; r--,c++)
        if(pan[r][c]==1)return true;
    return false;
}
void backTrace(int &res, int pan[NUM][NUM], int row, int col){
    if(row==NUM){// 回溯条件
        res++;
        print2Array(pan);
        int c;
        for(c=0; pan[row-1][c]!=1; c++);
        pan[row-1][c]=0;
        backTrace(res, pan, row-1, c+1);// 回溯
        return;
    }
    int c1;
    for(c1=col; c1<NUM && isConflict(pan, row, c1); c1++);
    if(c1!=NUM){// 剪枝 
        pan[row][c1] = 1;
        backTrace(res, pan, row+1, 0);
    }else{// 回溯条件 c1==8
        if(row==0)return;
        int c;
        for(c=0; pan[row-1][c]!=1; c++);
        pan[row-1][c]=0;
        backTrace(res, pan, row-1, c+1);// 回溯
    }
}

void backTrace1(int &res, int pan[NUM][NUM], int row, int col){
    if(row==NUM){
        res++;
        print2Array(pan);
    }else{
        int c;
        for(c=col; c<NUM && isConflict(pan, row, c); c++);
        if(c!=NUM){
            pan[row][c] = 1;
            backTrace(res, pan, row+1, 0);
            return;
        }
    }
    int c;
    if(row-1<0) return;
    for(c=0; pan[row-1][c]!=1; c++);
    pan[row-1][c]=0;// 
    backTrace(res, pan, row-1, c+1);// 回溯函数
}

int queen(){
    int pan[NUM][NUM];
    for(int r=0; r<NUM; r++)
        for(int c=0; c<NUM; c++)
            pan[r][c] = 0;
    int res = 0;
    backTrace(res, pan, 0, 0);
    return res;
}
int main()
{
    cout<<queen()<<endl;
    
    return 0;
}
