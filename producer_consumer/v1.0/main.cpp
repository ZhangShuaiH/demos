/*************************************************************************
  Created Time: 2020-04-24 11:02:30
 ************************************************************************/
#include <iostream>
#include <vector>
#include "WholeSaler.h"
using namespace std;

int main()
{
	cout<<"hello world!"<<endl;
	vector<Producer*> pros;
	pros.push_back(new Producer(0));
	pros.push_back(new Producer(1));
	vector<Consumer*> cons;
	cons.push_back(new Consumer);
	vector<int> rep(5,0);

	WholeSaler ws(pros, cons, rep);
	ws.run();
	return 0;
}
