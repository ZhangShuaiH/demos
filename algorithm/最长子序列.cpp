
void printList(list<int> ll){
    for(auto itr = ll.begin(); itr != ll.end(); itr++)
        cout<<*itr<<" ";
    cout<<endl;
}

void printArr(int a[], int size){
    cout<<"dp[]:";
    for(int i=0; i<size; i++) cout<<a[i]<<" ";
    cout<<endl;
}

// 最长递增子序列 O(size^2)
list<int> longestIncSubSequence(int a[], int size){
    int *longest = new int[size];// 以a[i]结尾的最长递增子序列的长度

    for(int i=0; i<size; i++) longest[i] = 0;
    longest[0] = 1;
    int maxIndex = 0;
    for(int i=1; i<size; i++){
        int j;
        int max_dp_index = i;
        for(j=i-1; j>=0; j--){
            if(a[i] >= a[j] && longest[j]>longest[max_dp_index]){
                max_dp_index = j;
            }
        }
        longest[i] = longest[max_dp_index] +1;
        if(longest[i] > longest[maxIndex])
            maxIndex = i;
    }
    printArr(longest, size);
    list<int> res;
    res.push_back(a[maxIndex]);// 由 dp 数组逆推出递增子序列
    while (true) {
        for(int j=maxIndex; j>=0; j--){
            if(a[maxIndex]>=a[j] && longest[j]==longest[maxIndex]-1){
                res.push_back(a[j]);
                maxIndex = j;
                break;
            }
        }
        if(longest[maxIndex]==1)break;
    }

    delete []longest;

    res.reverse();
    return res;
}

int main(int argc, char *argv[])
{
    QApplication a123(argc, argv);

    int a[] = {68 , 52 , 32 , 65 , 25 , 77 , 97 , 41 , 19 , 47};
    int size = sizeof(a)/sizeof(int);
    list<int> ll  = longestIncSubSequence(a, size);
    printList(ll);
    return 0;
    return a123.exec();
}
