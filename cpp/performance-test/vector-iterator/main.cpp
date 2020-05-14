/*************************************************************************
  Created Time: 2020-04-24 11:02:30
 ************************************************************************/

#include <iostream>
#include <vector>
#include <set>
#include <list>
#include "../../include/timeing.h"

using namespace std;

int main()
{
	vector<int> vv;
	for(size_t i=0; i<100000; i++)
	{
		vv.push_back(i);
	}
	int n = vv.size();
	cout<<"int i"<<endl;
	TIMEING(
		for(size_t i=0; i<n; i++)
		{
			vv[i];
		}
	)
	cout<<"iterator"<<endl;
	TIMEING(
		for(vector<int>::iterator itr=vv.begin(); itr != vv.end(); itr++)
		{
			*itr;
		}
	)

	return 0;
}
