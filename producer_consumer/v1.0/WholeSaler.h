/*************************************************************************
  Created Time: 2020-04-24 11:02:30
 ************************************************************************/
#ifndef WHOLESALER_H
#define WHOLESALER_H
#include <vector>
#include <pthread.h>
class LG
{
public:
	LG(pthread_mutex_t& mut);
	~LG();
private:
	pthread_mutex_t& mmut;
};
class Producer
{
public:
	Producer(const int name);
	bool produce(int &product, const long long productIndex);
private:
	int mI;
	int mName;
};
class Consumer
{
public:
	void consume(const int &product, const long long productIndex);
};
class WholeSaler
{
public:
    WholeSaler(const std::vector<Producer*> &producers, const std::vector<Consumer*> &consumers, std::vector<int> &repository);
	void run(bool async=false);
private:
	static void* produceThread(void*);
	static void* consumeThread(void*);

	pthread_mutex_t mMut;
	pthread_cond_t mProCond, mConCond;
    const std::vector<Producer*> &mProducers;
    const std::vector<Consumer*> &mConsumers;
	std::vector<int> mRepository;
    std::vector<int> mRepStatus;
	const int mProCount, mConCount, mRepSize;
    int mProTidNo, mConTidNo;
	long long mProPos, mConPos;
};
#endif // WHOLESALER_H
