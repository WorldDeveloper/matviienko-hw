#pragma once
#include <Windows.h>
#include <ctime>
#include <string>
#include <sstream>

class DateTime
{
	HWND mhYear;
	HWND mhMonth;
	HWND mhDay;
	HWND mhHour;
	HWND mhMin;

	std::wstring Format2Digit(const int number) const;
	int GetIntFromEdit(HWND hEdit) const;
public:
	DateTime(HWND hYear, HWND hMonth, HWND hDay, HWND hHour, HWND hMin, const time_t time = 0);

	int LastDayInMonth(const int year, const int month) const;
	bool  SetMonth(const int month);
	bool  SetDay(const int year, const int month, const int curDay);
	void SetDateTime(const time_t dateTime = 0);
	bool CheckLastDay();
	time_t GetDateTime() const;	
};

