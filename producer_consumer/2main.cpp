/*************************************************************************
  Created Time: 2020-04-24 11:02:30
 ************************************************************************/
#include <iostream>
#include <vector>
#include <stdio.h>
#include <unistd.h>
#include "WholeSaler.h"
using namespace std;
class IntProducer:public Producer
{
public:
	IntProducer(const int name, int delay, int proCount):mName(name),mDelay(delay),mProCount(proCount){}
	virtual bool produce(void *product, const long long productIndex)
	{
		if(mI<mProCount)
		{
			int *pro = reinterpret_cast<int*>(product);
			usleep(10000*(1+mDelay));
			*pro = mI++;
			printf("%dp%d\t%d\n",mI, mName, productIndex);
			return true;
		}else
		{
			return false;
		}
	}
private:
	int mI;
	const int mName;
	const int mDelay;
	const int mProCount;
};
class IntConsumer:public Consumer
{
public:
	virtual	void consume(const void *product, const long long productIndex)
	{
		const int *pro = reinterpret_cast<const int*>(product);
		usleep(10000);
		printf("%dc%d\n",*pro, productIndex);
	}
};
int main()
{
	vector<Producer*> pros;
	pros.push_back(new IntProducer(0, 0, 200));
	pros.push_back(new IntProducer(1, 1, 100));
	pros.push_back(new IntProducer(2, 2, 100));
	vector<Consumer*> cons;
	cons.push_back(new IntConsumer);
	vector<void*> rep(5, NULL);
	for(int i=0; i<rep.size(); i++)rep.at(i) = new int(0);

	WholeSaler ws(pros, cons, rep);
	ws.run();
	return 0;
}
