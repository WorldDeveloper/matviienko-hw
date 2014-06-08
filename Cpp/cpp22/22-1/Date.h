#pragma once
#include <iostream>
using namespace std;

class Date
{
	int day;
	int month;
	int year;
public:
	Date();
	Date(int iDay, int iMonth, int iYear);
	Date operator+(int addedDays);
	int operator-(Date date2);
	friend ostream &operator<<(ostream &stream, Date tmp);
};

