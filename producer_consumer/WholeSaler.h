/*************************************************************************
  Created Time: 2020-04-24 11:02:30
 ************************************************************************/
#ifndef WHOLESALER_H
#define WHOLESALER_H
#include <iostream>
#include <vector>
#include <pthread.h>
#include <assert.h>
#include <unistd.h>
#include <stdio.h>
using namespace std;
class LG
{
public:
	LG(pthread_mutex_t& mut):mmut(mut);
	~LG();
private:
	pthread_mutex_t& mmut;
};
class Producer
{
public:
	Producer(int flag);
	bool produce(int &p);
private:
	int i;
	const int flag;
};
class Consumer
{
public:
	void consume(const int &p);
};
class WholeSaler
{
public:
    WholeSaler(const vector<Producer*> &producers, const vector<Consumer*> &consumers, vector<int> repository);
	void Run(bool async=false);
private:
	static void* produceThread(void*);
	static void* consumeThread(void*);

	pthread_mutex_t mMut;
	pthread_cond_t mProCond, mConCond;
    const vector<Producer*> &mProducers;
    const vector<Consumer*> &mPonsumers;
	vector<int> mRepository;
    vector<int> mRepStatus;
	const int mProCount, mConCount, mRepSize;
    int mProTidNo, mConTidNo;
	long long mProPos, mConPos;
};
#endif // WHOLESALER_H
