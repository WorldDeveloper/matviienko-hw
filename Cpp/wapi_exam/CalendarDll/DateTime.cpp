#include "DateTime.h"


DateTime::DateTime(HWND hYear, HWND hMonth, HWND hDay, HWND hHour, HWND hMin, const time_t time/*=0*/) :
mhYear(hYear), mhMonth(hMonth), mhDay(hDay), mhHour(hHour), mhMin(hMin)
{
	SetDateTime(time);
}

int DateTime::LastDayInMonth(const int year, const int month) const
{
	if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
		return 31;
	else if (month == 4 || month == 6 || month == 9 || month == 11)
		return 30;
	else {
		if (year % 4 == 0) {
			if (year % 100 == 0) {
				if (year % 400 == 0)
					return 29;
				return 28;
			}
			return 29;
		}
		return 28;
	}
}

bool  DateTime::SetMonth(const int month)
{
	if (month<1 || month>12) return false;

	wchar_t* months[12] = { L"January", L"February", L"March", L"April", L"May", L"June", L"July", L"August", L"September", L"October", L"November", L"December" };
	for (int i = 0; i < 12; ++i)
	{
		int ind = SendMessage(mhMonth, CB_ADDSTRING, 0, (LPARAM)months[i]);
		SendMessage(mhMonth, CB_SETITEMDATA, ind, i);
	}
	SendMessage(mhMonth, CB_SETCURSEL, month - 1, 0);

	return true;
}

bool  DateTime::SetDay(const int year, const int month, const int curDay)
{
	if (year <= 0 || month<1 || month>12 || curDay<1) return false;

	const int daysInMonth = LastDayInMonth(year, month);
	SendMessage(mhDay, CB_RESETCONTENT, 0, 0);
	if (curDay>daysInMonth) return false;

	for (int i = 1; i <= daysInMonth; ++i)
	{
		const int ind = SendMessage(mhDay, CB_ADDSTRING, 0, (LPARAM)(std::to_wstring(i).c_str()));
		SendMessage(mhDay, CB_SETITEMDATA, ind, i);
	}
	SendMessage(mhDay, CB_SETCURSEL, curDay - 1, 0);

	return true;
}

void DateTime::SetDateTime(const time_t dateTime/*=0*/)
{
	time_t rawtime;
	struct tm * moment;

	if (dateTime) rawtime = dateTime;
	else time(&rawtime);
	moment = localtime(&rawtime);

	SetWindowText(mhYear, std::to_wstring(moment->tm_year + 1900).c_str());
	SetMonth(moment->tm_mon + 1);
	SetDay(moment->tm_year + 1900, moment->tm_mon + 1, moment->tm_mday);

	SetWindowText(mhHour, Format2Digit(moment->tm_hour).c_str());
	SetWindowText(mhMin, Format2Digit(moment->tm_min).c_str());
}

bool DateTime::CheckLastDay()
{
	int year = GetIntFromEdit(mhYear);
	if (year <= 0) return false;

	const int month = SendMessage(mhMonth, CB_GETCURSEL, 0, 0) + 1;
	const int day = SendMessage(mhDay, CB_GETCURSEL, 0, 0) + 1;
	if (!SetDay(year, month, day)) SetDay(year, month, 1);

	return true;
}

time_t DateTime::GetDateTime() const
{
	struct tm retTime = { 0 };

	const int year = GetIntFromEdit(mhYear) - 1900;
	const int month = SendMessage(mhMonth, CB_GETCURSEL, 0, 0);
	const int day = SendMessage(mhDay, CB_GETCURSEL, 0, 0) + 1;
	const int hour = GetIntFromEdit(mhHour);
	const int min = GetIntFromEdit(mhMin);

	if (year < 0 || month<0 || month>11 || day<1 || day>LastDayInMonth(year, month + 1)
		|| hour<0 || hour>23 || min<0 || min>59)
		throw  L"Incorrect date/time was inputed!";

	retTime.tm_year = year;
	retTime.tm_mon = month;
	retTime.tm_mday = day;
	retTime.tm_hour = hour;
	retTime.tm_min = min;

	return mktime(&retTime);
}

int DateTime::GetIntFromEdit(HWND hEdit) const
{
	int ret = 0;
	int length = SendMessage(hEdit, WM_GETTEXTLENGTH, 0, 0);
	if (length > 0)
	{
		wchar_t* buf = new wchar_t[length + 1];
		SendMessage(hEdit, WM_GETTEXT, (length + 1), (LPARAM)buf);
		ret = std::stoi(buf);
		delete[] buf;
	}
	else
	{
		throw L"Edit is Empty";
	}

	return ret;
}


std::wstring DateTime::Format2Digit(const int number) const
{
	if (number < 10) return L"0" + std::to_wstring(number);
	else return std::to_wstring(number);
}
