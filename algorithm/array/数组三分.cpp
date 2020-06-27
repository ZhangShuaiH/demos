void print(const int a[], const int size)
{
    for(size_t i=0; i<size; i++)
        cout<<a[i]<<"\t";
    cout<<endl;
}
// 将小于 axis 的数放左边， 等于的放中间， 大于的放右边
void partition(int a[], const int size, const int axis)
{
    int low=0, hig=size-1;
    for(size_t i=low; i<=hig && low<=hig;)
    {
        if(a[i] == axis)
            i++;
        else if(a[i] > axis)
            swap(a[i], a[hig--]);
        else
            swap(a[i++], a[low++]);
    }
}

int main()
{
    int a[] = {17, 13, 17, 12, 12, 20, 20, 16, 11, 16, 13, 20, 15, 13, 14, 15, 11, 16, 17, 11};
    int size = sizeof(a)/sizeof(int);
    partition(a, size, 15);
    print(a, size);

    return 0;
}
