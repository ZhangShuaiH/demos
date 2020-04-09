#include <climits>
using namespace std;

template <class T>
void printTypeInfo(){

    cout<<"字节数："<<sizeof(T)<<endl;
    cout<<"最小值："<<(numeric_limits<T>::min)()<<endl;
    cout<<"最大值："<<(numeric_limits<T>::max)()<<endl;
    cout<<endl;
}

int main(int argc, char *argv[])
{
    printTypeInfo<float>();
    printTypeInfo<double>();
    printTypeInfo<long long>();
    printTypeInfo<long>();

    return 0;
}
