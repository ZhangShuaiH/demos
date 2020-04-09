#include <iostream>

using namespace std;

class Sub
{
public:
    Sub() {
        cout<<"Sub"<<endl;
    }
    virtual void show()=0;
    virtual ~Sub(){
        cout<<"~Sub"<<endl;
    }
};
class Sub1 : public Sub
{
public:
    Sub1() {
        cout<<"Sub1"<<endl;
    }
    virtual void show(){
        cout<<"Sub1::show"<<endl;
    }
    virtual ~Sub1(){
        cout<<"~Sub1"<<endl;
    }
};
class Sub2 : public Sub
{
public:
    Sub2() {
        cout<<"Sub2"<<endl;
    }
    virtual void show(){
        cout<<"Sub2::show"<<endl;
    }virtual ~Sub2(){
        cout<<"~Sub2"<<endl;
    }
};
class Sub3 : public Sub
{
public:
    Sub3() {
        cout<<"Sub3"<<endl;
    }
    virtual void show(){
        cout<<"Sub3::show"<<endl;
    }
    virtual ~Sub3(){
        cout<<"~Sub3"<<endl;
    }
};

class Factory
{
public:
    Factory() {}
    Sub *createSub(string name){
        Sub *ss=nullptr;
        if(name=="sub1"){
            ss = new Sub1;
        }else if (name=="sub2") {
            ss = new Sub2;
        }else if(name=="sub3"){
            ss = new Sub3;
        }else{
            ss = nullptr;
        }
        return ss;
    }
};
/*******************************
 * 扩展：若要添加新的子类，只需添加 Sub4, 并修改 Factory::createSub, 轻微违反开闭原则
 * 示例1：报表工具，报表分为日报表、月报表、年报表，以后可能扩展周报表。
 * 示例2：数据库工具，数据库分为MySQL、oracle，以后可能扩展MongoDB。
********************************/
int main(){
    Factory ff;
    Sub *ss = ff.createSub("sub1");// 解耦客户端对 Sub 子类的依赖，封装对象的创建过程
    ss->show();

    return 0;
}
