/***************************************************
题目：
    给定一个数组，除了一个数出现1次之外，其余数都出现3次。
    找出出现一次的数。如：{1, 2, 1, 2, 1, 2, 7}, 找出7.
格式：
    第一行输入一个数n，代表数组的长度，接下来一行输入数组A[n],
    (输入的数组必须满足问题描述的要求),最后输出只出现一次的数。
要求：
    你的算法只能是线性时间的复杂度，并且不能使用额外的空间哦～
样例输入
    4
    0 0 0 5
样例输出
    5

感悟：
    进制还能这样用，真是神奇
***************************************************/
/****************************************************
转化成二进制，是因为二进制简单，每位数不是0就是1。
当i=0时，可求得n个数的第0位（最低位）的和：
m=3a*0+3b*1+X，其中a指数组a[]中第0位为0的数的个数，b指数组a[]中第0位为1的数的个数，X指数组a[]中出现一次的数的第0位的值（0或1）。
后面m%3后得到的数就是X的值。

其实转化成三进制也行，此时m=3a*0+3b*1+3c*2+X，m%3=X，X为0,1或2；
但是转化成四进制就不行了，此时m=3a*0+3b*1+3c*2+3d*3+X，m%3!=X，因为m%3为0,1或2，,而X可以为0,1,2或3。
同理转换成更高进制也不行。
小弟语言表达能力有限，若还有不懂的可加我qq2010296739
*****************************************************/
#include <stdio.h>
#include <math.h>

int main()
{
    int a[] = {1,2,3,1,2,1,3,2,7,3};
    int n = 10;
    int res, i, j, m;

    res = 0;
    for(i = 0; i < 32; i++)//32是int的二进制位数
    {
        m = 0;
        for(j = 0; j < n; j++)
        {
            if(a[j] % 2 == 1) m++;
            a[j] = a[j] >> 1;
        }
        res += (m % 3) * pow(2, i);//3指其余数都出现3次
    }

    printf("%d", res);
}
