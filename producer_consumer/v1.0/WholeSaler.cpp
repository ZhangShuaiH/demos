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
Producer::Producer(const int name):mName(name){}
bool Producer::produce(int &product, const long long productIndex)
{
	usleep(10000);
	if(mI++ >= 30)return false;
	product = mI;
	printf("%dp%d\n",mI, mName);
	return true;
}
void Consumer::consume(const int &product, const long long productIndex)
{
	usleep(10000);
	printf("%dc%d\n",product, productIndex);
}
WholeSaler::WholeSaler(const vector<Producer*> &producers, const vector<Consumer*> &consumers, vector<int> &repository):
                        mProducers(producers),mConsumers(consumers),mRepository(repository),mProCount(producers.size()),mConCount(mConsumers.size()),mRepSize(repository.size())
{
}
void* WholeSaler::produceThread(void *param)
{
    WholeSaler* pIns = reinterpret_cast<WholeSaler*>(param);
    Producer *pro = NULL;
    {
        LG lg(pIns->mMut);
        pro = pIns->mProducers.at(pIns->mProTidNo++);
    }
	while(true)
	{
		int tppos = -1;
		{
			LG lg(pIns->mMut);
			while(pIns->mProPos-pIns->mConPos >= pIns->mRepSize)
				pthread_cond_wait(&pIns->mProCond, &pIns->mMut);
			tppos = pIns->mProPos++;
		}
		if(pro->produce(pIns->mRepository.at(tppos%pIns->mRepSize), tppos))
        {
            pIns->mRepStatus.at(tppos%pIns->mRepSize) = 0;
        }else
		{
			pIns->mRepStatus.at(tppos%pIns->mRepSize) = -2;
			pthread_cond_broadcast(&pIns->mConCond);
			break;
		}
		pthread_cond_broadcast(&pIns->mConCond);
	}
	return NULL;
}
void* WholeSaler::consumeThread(void *param)
{
    WholeSaler* pIns = reinterpret_cast<WholeSaler*>(param);
    Consumer *con = NULL;
    {
        LG lg(pIns->mMut);
        con = pIns->mConsumers.at(pIns->mConTidNo++);
    }
	int exitCount = 0;
	while(true)
	{
		{
			LG lg(pIns->mMut);
			while(pIns->mProPos-pIns->mConPos<=0 || pIns->mRepStatus.at(pIns->mConPos%pIns->mRepSize)==-1)
			{
				pthread_cond_wait(&pIns->mConCond, &pIns->mMut);
			}
		}
		switch(pIns->mRepStatus.at(pIns->mConPos%pIns->mRepSize))
		{
            case 0:
                con->consume(pIns->mRepository.at(pIns->mConPos%pIns->mRepSize), pIns->mConPos);
                break;
			case -2:
				if(++exitCount == pIns->mProCount)
					return NULL;
				break;
			default:
				assert(false);
		}
		pIns->mRepStatus.at(pIns->mConPos%pIns->mRepSize) = -1;
		{
			LG lg(pIns->mMut);
			++pIns->mConPos;
			pthread_cond_broadcast(&pIns->mProCond);
		}
	}
	return NULL;
}

void WholeSaler::run(bool async)
{
    mProPos = mConPos = mProTidNo = mConTidNo = 0;
    assert(mConCount == 1);
	pthread_t ptids[mProCount];
	pthread_t ctids[mConCount];
	pthread_cond_init(&mProCond, NULL);
	pthread_cond_init(&mConCond, NULL);
	pthread_mutex_init(&mMut, NULL);
	mRepStatus.resize(mRepSize, -1);
	for(int i=0; i<mProCount; i++)
	{
		pthread_create(&ptids[i], NULL, produceThread, this);
	}
    for(int i=0; i<mConCount; i++)
    {
        pthread_create(&ctids[i], NULL, consumeThread, this);
    }
	if(async)
	{
	}else
	{
		for(int i=0; i<mProCount; i++)
		{
			pthread_join(ptids[i], NULL);
		}
	    for(int i=0; i<mConCount; i++)
	    {
	        pthread_join(ctids[i], NULL);
	    }
	}
}
