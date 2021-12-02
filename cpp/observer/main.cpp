#include <iostream>
#include <vector>
#include <functional>
#include <iomanip>
#include <unordered_set>
#include <string>

#define ddd(expr) std::cout<<__FUNCTION__<<"::"<<__LINE__<<"::"<<#expr<<"->"<<expr<<std::endl

using namespace std;

class QObject{
public:
    virtual void signal(int val){
        ddd("");
        for(auto pobj : pobjs){
            pobj->slot(val);
        }
    }
    virtual void slot(int val){ddd(val);}
    virtual void regist(QObject *pobj)final{
        pobjs.insert(pobj);
    }
    static void connect(QObject *sender, QObject *reciver){
        sender->regist(reciver);
    }
private:
    unordered_set<QObject*> pobjs;
};

class A:public QObject{
public:
    virtual void slot(int val){ddd(val);}
};
int main()
{
    QObject sender1;
    A reciver1, reciver2;
    QObject::connect(&sender1, &reciver1);
    QObject::connect(&sender1, &reciver2);

    sender1.signal(12);

    return 0;
}
