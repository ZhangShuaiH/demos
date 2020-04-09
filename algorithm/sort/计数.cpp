
void print(int a[], const int &size){
    for(int i=0; i<size; i++){
        cout<<a[i]<<" ";
    }
    cout<<endl;
}
// 适合数据最值差距较小，元素密度较大的数据
void countSort(int a[], int size){
    int min = 0,max = size-1;
    for(int i=0; i<size; i++){// 求最大最小值
        if(a[i] > a[max])
            max = i;
        if(a[i] < a[min])
            min = i;
    }
    min = a[min];
    max = a[max];
    int *count = new int[max-min+1];// 计数器
    for(int i=0; i<max-min+1; i++){// 初始化计数器
        count[i] = 0;
    }
    for(int i=0; i<size; i++){// 计数
        count[a[i]-min]++;
    }
    for(int i=0, j=0; i<max-min+1; i++){// 放回来
        while (count[i]--) {
            a[j++] = i+min;
        }
    }
    delete []count;
}
int main(int argc, char *argv[])
{
    QApplication a123(argc, argv);

    int a[] = {48 , 61 , 82 , 24 , 74 , 37 , 89 , 24 , 44 , 43 , 35 , 9 , 32 , 18 , 42 , 39 , 88 , 43 , 42 , 18 , 31 , 28 , 90 , 1 , 93 , 43 , 59 , 12 , 96 , 89};
    int size = sizeof(a)/sizeof(int);
    countSort(a, size);
    print(a, size);

    return 0;
    return a123.exec();
}

