/*************************************************************************
  Created Time: 2020-04-24 11:02:30
 ************************************************************************/
#include <iostream>
#include <vector>
#include <stdio.h>
#include <unistd.h>
#include "WholeSaler.h"
using namespace std;
const int gProCount = 100;
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
			usleep(10000*(1+mDelay));
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
		usleep(10000);
		printf("%dc%d\t%d\n",*pro, mName, productIndex);
	}
private:
	const int mName;
};
int main()
{
	vector<Producer*> pros;
	pros.push_back(new IntProducer(0, 1));
	pros.push_back(new IntProducer(1, 2));
	pros.push_back(new IntProducer(2, 3));
	//pros.push_back(new IntProducer(3, 3));
	//pros.push_back(new IntProducer(4, 3));
	vector<Consumer*> cons;
	cons.push_back(new IntConsumer(0));
	cons.push_back(new IntConsumer(1));
	vector<void*> rep(10, NULL);
	for(int i=0; i<rep.size(); i++)rep.at(i) = new int(0);

	WholeSaler ws(pros, cons, rep);
	ws.run();
	return 0;
}
