/*************************************************************************
  Created Time: 2020-04-15 11:41:00
 ************************************************************************/

#include<iostream>
#include<vector>
using namespace std;
int main()
{
	vector<int> v1={1,2,3};
	vector<int> v2={4,5,6};
	v1.insert(v1.end(), v2.begin(), v2.end());
	for(size_t i=0; i<v1.size(); i++)
	{
		cout<<v1[i]<<endl;
	}
	return 0;
}
