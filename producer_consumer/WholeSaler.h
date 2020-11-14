/*************************************************************************
  Created Time: 2020-04-24 11:02:30
 ************************************************************************/
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
	void Run(bool async=false);
private:
	static void* produceThread(void*);
	static void* consumeThread(void*);

	pthread_mutex_t mMut;
	pthread_cond_t mPcond; 
	pthread_cond_t mCcond;
	int mPpos=0;
	int mCpos=0;
	int mPcount = 3;
	vector<int> mBuffs;
};

