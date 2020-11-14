/*************************************************************************
  Created Time: 2020-04-24 11:02:30
 ************************************************************************/
#include <iostream>
#include <vector>
#include <pthread.h>
#include <assert.h>
#include <unistd.h>
#include <stdio.h>
//#include "cpp/include/timeing.h"
using namespace std;
pthread_mutex_t mut;
pthread_cond_t pcond, ccond;
int ppos=0;int cpos=0;
int pcount = 3;
vector<int> buffs;
class LG
{
public:
	LG(pthread_mutex_t& mut):mmut(mut)
	{
		pthread_mutex_lock(&mmut);
	}
	~LG()
	{
		pthread_mutex_unlock(&mmut);
	}
private:
	pthread_mutex_t& mmut;
};
class Producer
{
public:
	Producer(int flag):i(0),flag(flag){}
	bool produce(int &p)
	{
		usleep(flag*10000+10000);
		//usleep(10000);
		if(i++ >= 30)return false;
		p = i;
		printf("%dp%d\n",i,flag);
		return true;
	}
	int i;
	const int flag;
};
class Consumer
{
public:
	void consume(const int &p)
	{
		usleep(10000);
		printf("%dc\n",p);
	}
};
void* produceThread(void*)
{
	static int flag=0;
	Producer pro(flag++);
	while(true)
	{
		int tppos = -1;
		{
			LG lg(mut);
			while(ppos-cpos >= buffs.size())
				pthread_cond_wait(&pcond, &mut);
			tppos = ppos++;
		}
		if(!pro.produce(buffs.at(tppos%buffs.size())))
		{
			buffs.at(tppos%buffs.size()) = -2;
			pthread_cond_broadcast(&ccond);
			break;
		}
		pthread_cond_broadcast(&ccond);
	}
	return NULL;
}
void* consumeThread(void*)
{
	int exitCount = 0;
	Consumer con;
	while(true)
	{
		{
			LG lg(mut);
			while(ppos-cpos<=0 || buffs.at(cpos%buffs.size())==-1)
			{
				pthread_cond_wait(&ccond, &mut);
			}
		}
		switch(buffs.at(cpos%buffs.size()))
		{
			case -1:
				assert(false);
				break;
			case -2:
				if(++exitCount == pcount)
					return NULL;
				break;
			default:
				con.consume(buffs.at(cpos%buffs.size()));
		}
		buffs.at(cpos%buffs.size()) = -1;
		{
			LG lg(mut);
			++cpos;
			pthread_cond_broadcast(&pcond);
		}
	}
	return NULL;
}

int main()
{
	pthread_t ptids[pcount];
	pthread_t ctid;
	pthread_cond_init(&pcond, NULL);
	pthread_cond_init(&ccond, NULL);
	pthread_mutex_init(&mut, NULL);
	buffs.resize(7);
	for(int i=0; i<buffs.size(); i++)buffs.at(i) = -1;
	for(int i=0; i<pcount; i++)
	{
		pthread_create(&ptids[i], NULL, produceThread, NULL);
	}
	pthread_create(&ctid, NULL, consumeThread, NULL);
	for(int i=0; i<pcount; i++)
	{
		pthread_join(ptids[i], NULL);
	}
	pthread_join(ctid, NULL);

	return 0;
}
