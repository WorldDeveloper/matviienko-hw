#pragma once
#include <ctime>
using namespace std;

class PassQueue
{
	int mMaxSize;
	int mCurSize;
	time_t* passengers;
public:
	PassQueue() : mMaxSize(100), mCurSize(0), passengers(new time_t[mMaxSize]){}
	~PassQueue(){ delete[] passengers; }
	PassQueue(const PassQueue& source)
	{
		mMaxSize = source.mMaxSize;
		mCurSize = source.mCurSize;
		passengers = new time_t[mMaxSize];
		for (int i = 0; i < mCurSize; ++i)
		{
			passengers[i] = source.passengers[i];
		}
	}

	PassQueue& operator=(const PassQueue& source)
	{
		if (this == &source) { return *this; }

		if (mMaxSize != source.mMaxSize)
		{
			delete[] passengers;
			passengers = new time_t[source.mMaxSize];
		}

		mMaxSize = source.mMaxSize;
		mCurSize = source.mCurSize;

		for (int i = 0; i < mCurSize; ++i)
		{
			passengers[i] = source.passengers[i];
		}

		return *this;
	}

	bool IsFull() const { return mCurSize == mMaxSize; }
	bool IsEmpty() const { return mCurSize == 0; }

	void Push(const time_t comingTime)
	{
		if (IsFull())
		{
			mMaxSize += 100;
			PassQueue tmp = *this;
			mMaxSize += 1;
			*this = tmp;
		}
		passengers[mCurSize] = comingTime;
		mCurSize++;
	}

	time_t Pop()
	{
		if (IsEmpty()) 	{	return 0;	}

		time_t tmp=passengers[0];

		for (int i = 1; i < mCurSize; ++i)
		{
			passengers[i - 1] = passengers[i];
		}
		mCurSize--;

		return tmp;
	}

	int Count() const { return mCurSize; }
};
