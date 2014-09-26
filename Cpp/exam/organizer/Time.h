#pragma once
#include <ostream>
#include <string>
using namespace std;

class Time
{
	short mHour;
	short mMin;
public:
	Time() :mHour(0), mMin(0) {}
	Time(const short hour, const short min);

	bool SetTime(const short hour, const short min);
	bool SetTime(const string& time);
	string GetTime() const;

	bool operator==(const Time& operand2) const;
	bool operator!=(const Time& operand2) const;
	bool operator>(const Time& operand2) const;
	bool operator>=(const Time& operand2) const;
	bool operator<(const Time& operand2) const;
	bool operator<=(const Time& operand2) const;

	int ConvertToMinutes(const Time& source) const;
};