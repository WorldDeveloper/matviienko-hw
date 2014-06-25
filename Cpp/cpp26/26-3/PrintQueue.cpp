#include "PrintQueue.h"

PrintQueue::PrintQueue(const PrintQueue& source)
{
	mMaxSize = source.mMaxSize;
	mCurSize = source.mCurSize;
	mClient = new Client[mMaxSize];
	for (int i = 0; i < mCurSize; ++i)
	{
		mClient[i] = source.mClient[i];
	}
}

PrintQueue& PrintQueue::operator=(const PrintQueue& source)
{
	if (this == &source) return *this;

	if (mMaxSize != source.mMaxSize)
	{
		delete[] mClient;
		mClient = new Client[source.mMaxSize];
	}

	mMaxSize = source.mMaxSize;
	mCurSize = source.mCurSize;
	for (int i = 0; i < mCurSize; ++i)
	{
		mClient[i] = source.mClient[i];
	}

	return *this;
}

void PrintQueue::Push(const Client& client)
{
	if (Full())
	{
		PrintQueue tmp = *this;
		tmp.mMaxSize += 10;
		*this = tmp;
	}

	int i = mCurSize;
	for (; i > 0 && mClient[i - 1].priority < client.priority; --i)
	{
		mClient[i] = mClient[i - 1];
	}

	mClient[i] = client;
	mCurSize++;
}


Client PrintQueue::Pop()
{
	Client tmp = mClient[0];
	for (int i = 1; i < mCurSize; ++i)
	{
		mClient[i - 1] = mClient[i];
	}
	mCurSize--;

	return tmp;
}
