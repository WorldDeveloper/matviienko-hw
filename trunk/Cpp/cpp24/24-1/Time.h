#pragma once
#include <ostream>
using namespace std;

class Time
{
	short mHour;
	short mMin;
	short mSec;
	bool mAmerican;
	bool SetTime(short hour, short min, short sec, bool american = 0);
public:
	Time()
		:mHour{ 0 }, mMin{ 0 }, mSec{ 0 }, mAmerican{ false } {}
	Time(short hour, short min, short sec, bool american = 0);
	bool operator()(short hour, short min, short sec, bool american = 0);

	Time operator+(Time operand2);
	Time operator-(Time operand2);
	Time operator=(Time result);

	bool operator==(Time operand2);
	bool operator!=(Time operand2);
	bool operator>(Time operand2);
	bool operator>=(Time operand2);
	bool operator<(Time operand2);
	bool operator<=(Time operand2);

	int ConvertToSeconds(Time source);
	Time MakeTime(int seconds);
	void ChangeFormat(){ mAmerican = !mAmerican; }
	friend ostream &operator<<(ostream &stream, const Time &pOutput);
};