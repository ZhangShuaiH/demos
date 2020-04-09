#include <iostream>

using namespace std;

class Sub
{
public:
    Sub() {}
    void show(){
        cout<<"Sub::show"<<endl;
    }
};

class Factory
{
public:
    Factory() {}
    Sub *createSub(){
        return new Sub;
    }
};

int main(){
    Factory ff;
    Sub *ss = ff.createSub();// 将创建对象的逻辑封装到工厂中，降低客户端对 Sub 的依赖
    ss->show();

    return 0;
}
