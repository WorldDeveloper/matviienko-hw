#include "Date.h"
#include <iostream>
#include <iomanip>
using namespace std;

Date::Date()
{
	day = 0;
	month = 0;
	year = 0;
}

Date::Date(int iDay, int iMonth, int iYear)
{
	day = iDay;
	month = iMonth;
	year = iYear;
}

Date Date::operator+(int addedDays)
{
	int daysInMonth[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	Date tmp = *this;

		while (true)
		{
			if (tmp.day + addedDays > daysInMonth[tmp.month - 1])
			{
				addedDays -= daysInMonth[tmp.month - 1] - tmp.day+1; 
				tmp.day = 1;
				tmp.month++;				
			}
			else if (addedDays>0)
			{
				tmp.day += addedDays;
				break;
			}
			else
			{
				break;
			}

			if (tmp.month > 12)
			{
				tmp.month = 1;
				tmp.year++;
			}
		}
	return tmp;
}

int Date::operator-(Date secondOperator)
{
	return year - secondOperator.year;
}

ostream &operator<<(ostream &stream, Date tmp)
{
	stream <<setw(2)<<setfill('0')<< tmp.day << ".";
	stream << setw(2)<<setfill('0')<<tmp.month << ".";
	stream << tmp.year << endl;
	return stream;
}