/*************************************************************************
  Created Time: 2020-04-24 11:02:30
 ************************************************************************/
#include <iostream>
#include <vector>
#include <stdio.h>
#include <unistd.h>
#include "WholeSaler.h"
using namespace std;
const int gProCount = 501;
const int gt = 10;
class IntProducer:public Producer
{
public:
	IntProducer(const int name, int delay):mName(name),mDelay(delay){}
	virtual bool produce(void *product, const long long productIndex)
	{
		if(productIndex>=gProCount)
		{
			return false;
		}else
		{
			int *pro = reinterpret_cast<int*>(product);
			usleep(gt*(1+mDelay));
			*pro = productIndex;
			printf("%dp%d\t%d\n",*pro, mName, productIndex);
			return true;
		}
	}
private:
	const int mName;
	const int mDelay;
};
class IntConsumer:public Consumer
{
public:
	IntConsumer(const int name):mName(name){}
	virtual	void consume(const void *product, const long long productIndex)
	{
		const int *pro = reinterpret_cast<const int*>(product);
		usleep(gt);
		printf("%dc%d\t%d\n",*pro, mName, productIndex);
	}
private:
	const int mName;
};
int main()
{
	vector<Producer*> pros;
	pros.push_back(new IntProducer(0, 0));
	pros.push_back(new IntProducer(1, 0));
	pros.push_back(new IntProducer(2, 0));
	pros.push_back(new IntProducer(3, 0));
	vector<Consumer*> cons;
	cons.push_back(new IntConsumer(0));
	//cons.push_back(new IntConsumer(1));
	//cons.push_back(new IntConsumer(2));
	vector<void*> rep(5, NULL);
	for(int i=0; i<rep.size(); i++)rep.at(i) = new int(0);

	WholeSaler ws(pros, cons, rep);
	ws.run();
	return 0;
}
