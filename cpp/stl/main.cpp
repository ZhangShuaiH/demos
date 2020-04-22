/*************************************************************************
  Created Time: 2020-04-22 16:22:03
 ************************************************************************/

#include<iostream>
using namespace std;

template<class T>
void func()
{
	cout<<__LINE__<<endl;
}
template<>
void func<int>()
{
	cout<<__LINE__<<endl; // 模板特化
}

int main()
{
	func<int>();
	func<string>();

	return 0;
}
