#pragma once

class Rell
{
	int mSize;
	int mRoll[10];
public:
	Rell(const int size = 10) :mSize(size)
	{
		for (int i = 0; i < size; ++i)
		{
			mRoll[i] = i;
		}
	}

	int Pop()
	{
		int tmp = mRoll[0];
		for (int i = 1; i < mSize; ++i)
		{
			mRoll[i - 1] = mRoll[i];
		}
		mRoll[mSize-1] = tmp;
		
		return tmp;
	}
	int Begin() const { return mRoll[0]; }
};


