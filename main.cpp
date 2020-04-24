/*************************************************************************
  Created Time: 2020-04-07 19:38:48
 ************************************************************************/

#include <iostream>
//#include <unistd.h> // sleep
using namespace std;
int main()
{
	cout<<"Hello World!"<<endl;
	cout<<"good"<<endl;
	for(size_t i=0; i<1000000; i++)
	{
		new int(i);
	}

	cout<<clock()<<endl;

	
	return 0;
}
