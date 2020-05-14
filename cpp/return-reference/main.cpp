/*************************************************************************
  Created Time: 2020-04-24 11:02:30
 ************************************************************************/

#include <iostream>
#include <vector>
#include <set>
#include <list>

using namespace std;

class A
{
public:
	A(){cout<<"A"<<endl;}
	A(const A &other){cout<<"copy A"<<endl;}
	A operator=(const A &other){cout<<"= A"<<endl;}
};

class B
{
public:
	A getA(){return a;}
	A& getrA(){return a;};
	const A& getcrA(){return a;};
private:
	A a;
};

int main()
{
	B b;
	cout<<endl;
	{
		A a = b.getA();// copy A
		//A &a2 = b.getA();// 无法引用右值
		const A &a3 = b.getA();// copy A
	}
	cout<<endl;
	{
		A a = b.getrA();// copy A
		a = b.getrA();// = A
		A &a2 = b.getrA();// no copy A
		b.getrA() = A();// = A 可作为左值
		const A &a3 = b.getrA();// no copy A
	}

	cout<<endl;
	{
		A a = b.getcrA();// copy A
		a = b.getcrA();// = A
		//A &a2 = b.getcrA();// 语法错误
		const A &a3 = b.getcrA();// no copy A
	}

	return 0;
}
