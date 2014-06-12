#pragma once
#include <ostream>
using namespace std;

class Time
{
	short mHour;
	short mMin;
	short mSec;
	bool mAmerican;
	bool SetTime(const short hour, const short min, const short sec, const bool american = false);
public:
	Time()
		:mHour(0), mMin(0), mSec(0), mAmerican(false) {}
	Time(const short hour, const short min, const short sec, const bool american = 0);
	bool operator()(const short hour, const short min, const short sec, const bool american = false);

	Time operator+(const Time& operand2);
	Time operator-(const Time& operand2);
	Time& operator=(const Time& result);

	bool operator==(const Time& operand2) const;
	bool operator!=(const Time& operand2) const;
	bool operator>(const Time& operand2) const;
	bool operator>=(const Time& operand2) const;
	bool operator<(const Time& operand2) const;
	bool operator<=(const Time& operand2) const;

	int ConvertToSeconds(const Time& source) const;
	Time MakeTime(int seconds) const;
	void ChangeFormat(){ mAmerican = !mAmerican; }
	friend ostream &operator<<(ostream &stream, const Time &pOutput);
};