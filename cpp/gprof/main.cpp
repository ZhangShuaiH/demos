/*************************************************************************
  Created Time: 2020-04-26 11:36:07
 ************************************************************************/

#include <iostream>
#include <unistd.h>
using namespace std;

void func()
{
	int i=789;
	i*=100;
}
int feb(int n)
{
	if(n<=1) return 1;
	static int ii=0;
	ii+=1;
	func();
	return feb(n-2)+feb(n-1);
}

int main()
{
	cout<<feb(40)<<endl;
	func();

	return 0;
}
