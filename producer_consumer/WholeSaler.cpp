/*************************************************************************
  Created Time: 2020-04-24 11:02:30
 ************************************************************************/
#include <iostream>
#include <vector>
#include <pthread.h>
#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include "WholeSaler.h"
using namespace std;
LG::LG(pthread_mutex_t& mut):mmut(mut)
{
	pthread_mutex_lock(&mmut);
}
LG::~LG()
{
	pthread_mutex_unlock(&mmut);
}
Producer::Producer(int flag):i(0),flag(flag)
{
}
bool Producer::produce(int &p)
{
	usleep(flag*10000+10000);
	//usleep(10000);
	if(i++ >= 30)return false;
	p = i;
	printf("%dp%d\n",i,flag);
	return true;
}
void Consumer::consume(const int &p)
{
	usleep(10000);
	printf("%dc\n",p);
}
void* WholeSaler::produceThread(void*)
{
	static int flag=0;
	Producer pro(flag++);
	while(true)
	{
		int tppos = -1;
		{
			LG lg(mMut);
			while(ppos-cpos >= mBuffs.size())
				pthread_cond_wait(&mPcond, &mMut);
			tppos = ppos++;
		}
		if(!pro.produce(mBuffs.at(tppos%buffs.size())))
		{
			mBuffs.at(tppos%buffs.size()) = -2;
			pthread_cond_broadcast(&mCcond);
			break;
		}
		pthread_cond_broadcast(&mCcond);
	}
	return NULL;
}
void* WholeSaler::consumeThread(void*)
{
	int exitCount = 0;
	Consumer con;
	while(true)
	{
		{
			LG lg(mMut);
			while(ppos-cpos<=0 || mBuffs.at(cpos%buffs.size())==-1)
			{
				pthread_cond_wait(&mCcond, &mMut);
			}
		}
		switch(mBuffs.at(cpos%buffs.size()))
		{
			case -1:
				assert(false);
				break;
			case -2:
				if(++exitCount == mPcount)
					return NULL;
				break;
			default:
				con.consume(mBuffs.at(cpos%buffs.size()));
		}
		mBuffs.at(cpos%buffs.size()) = -1;
		{
			LG lg(mMut);
			++cpos;
			pthread_cond_broadcast(&mPcond);
		}
	}
	return NULL;
}

void WholeSaler::Run(bool async)
{
	pthread_t ptids[mPcount];
	pthread_t ctid;
	pthread_cond_init(&mPcond, NULL);
	pthread_cond_init(&mCcond, NULL);
	pthread_mutex_init(&mMut, NULL);
	mBuffs.resize(7);
	for(int i=0; i<mBuffs.size(); i++)buffs.at(i) = -1;
	for(int i=0; i<mPcount; i++)
	{
		pthread_create(&ptids[i], NULL, produceThread, this);
	}
	pthread_create(&ctid, NULL, consumeThread, this);
	for(int i=0; i<mPcount; i++)
	{
		pthread_join(ptids[i], NULL);
	}
	pthread_join(ctid, NULL);

	return 0;
}
