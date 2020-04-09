void swap(int &a, int &b){
    if(&a == &b)return;// 这是一个大陷阱
    a = a^b;
    b = a^b;
    a = a^b;
}
