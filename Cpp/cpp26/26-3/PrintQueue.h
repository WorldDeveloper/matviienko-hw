#pragma once
#include <ctime>
using namespace std;

struct Client
{
	char name[20];
	time_t printTime;
	int priority;
};

class PrintQueue
{
	int mMaxSize;
	int mCurSize;
	Client* mClient;

	PrintQueue(const PrintQueue& source);
	PrintQueue& operator=(const PrintQueue& source);
public:
	PrintQueue() : mMaxSize(10), mCurSize(0), mClient(new Client[mMaxSize]) {}
	~PrintQueue() { delete[] mClient; }
	bool Empty() const { return mCurSize == 0; }
	bool Full() const { return mCurSize == mMaxSize; }
	void Push(const Client& client);
	Client Pop();
	int Count() const { return mCurSize; }
};

