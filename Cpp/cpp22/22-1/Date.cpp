#include "Date.h"
#include <iostream>
#include <iomanip>
#include <ctime>
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
	
	struct tm date = { 0 };
	date.tm_year = year-1900;
	date.tm_mon = month - 1;
	date.tm_mday = day;

	time_t tmpTime = mktime(&date) + addedDays *60 * 60 * 24;
	struct tm* result= localtime(&tmpTime);

	Date tmp;
	tmp.year = result->tm_year+1900;
	tmp.month = result->tm_mon + 1;
	tmp.day = result->tm_mday;

	return tmp;
}

int Date::operator-(Date secondOperand)
{	
	struct tm operand1 = { 0 };
	operand1.tm_year = year-1900;
	operand1.tm_mon = month - 1;
	operand1.tm_mday = day;

	struct tm operand2 = { 0 };
	operand2.tm_year = secondOperand.year-1900;
	operand2.tm_mon = secondOperand.month-1;
	operand2.tm_mday = secondOperand.day;
	
	time_t d1 = mktime(&operand1);
	time_t d2 = mktime(&operand2);
	int result=(int)difftime(d1,d2 )/(60*60*24);
	return result;
}

ostream &operator<<(ostream &stream, Date tmp)
{
	stream <<setw(2)<<setfill('0')<< tmp.day << ".";
	stream << setw(2)<<setfill('0')<<tmp.month << ".";
	stream << tmp.year << endl;
	return stream;
}