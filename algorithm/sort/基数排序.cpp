
void print(int a[], const int &size){
    for(int i=0; i<size; i++){
        cout<<a[i]<<" ";
    }
    cout<<endl;
}

int getNumOf(int num, int d){// 获取第 d 位数的数值，从低位到高位
    int radio = 1;
    while (--d) {
        radio *= 10;
    }
    return num/radio%10;
}
// 基数排序
void radixSort(int a[], int size){
    int maxWidth = 2;// 数的最大长度
    int i;
    int *temp = new int[size];
    int counter[10];
    for(int d=1; d<=maxWidth; d++) {
        // 初始化计数器
        for(i=0; i<10; i++) counter[i] = 0;
        // 计数
        for(i=0; i<size; i++)counter[getNumOf(a[i], d)]++;
        // 分配位序
        for(i=1; i<10; i++)counter[i] += counter[i-1];
        // 倒序存到 temp 中
        for(i=size-1; i>=0; i--)temp[ --counter[getNumOf(a[i], d)] ] = a[i];
        // 复制到 a 中
        for(i=0; i<size; i++)a[i] = temp[i];
    }
    delete []temp;
}

int main(int argc, char *argv[])
{
    QApplication a123(argc, argv);

    int a[] = {48 , 61 , 82 , 24 , 74 , 37 , 89 , 24 , 44 , 43 , 35 , 9 , 32 , 18 , 42 , 39 , 88 , 43 , 42 , 18 , 31 , 28 , 90 , 1 , 93 , 43 , 59 , 12 , 96 , 89};
    int size = sizeof(a)/sizeof(int);
    radixSort(a, size);
    print(a, size);

    return 0;
    return a123.exec();
}
