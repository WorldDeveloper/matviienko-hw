#pragma once
#include <ostream>
#include <string>
using namespace std;

class Date
{
	short mYear;
	short mMonth;
	short mDay;
public:
	Date()
		:mYear(0), mMonth(0), mDay(0) {}
	bool SetDate(const short year, const short month, const short day);
	string GetDate() const;

	bool operator==(const Date& operand2) const;
	bool operator!=(const Date& operand2) const;
	bool operator>(const Date& operand2) const;
	bool operator>=(const Date& operand2) const;
	bool operator<(const Date& operand2) const;
	bool operator<=(const Date& operand2) const;

	int ConvertToSeconds() const;
	int LastDay();
};