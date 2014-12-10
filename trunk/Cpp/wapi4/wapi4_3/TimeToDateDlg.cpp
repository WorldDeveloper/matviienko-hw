#include "TimeToDateDlg.h"
#include <ctime>

TimeToDateDlg* TimeToDateDlg::ptr = nullptr;

TimeToDateDlg::TimeToDateDlg()
{
	ptr = this;
}

BOOL CALLBACK TimeToDateDlg::DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hWnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hWnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hWnd, WM_COMMAND, ptr->Cls_OnCommand);
	}

	return FALSE;
}

void TimeToDateDlg::Cls_OnCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify)
{
	if (id == IDC_TIMELEFT)
	{
		SetWindowText(mhResult, NULL);

		time_t now;
		time(&now);
		struct tm* tmp = localtime(&now);
		struct tm curDate = { 0 };
		curDate.tm_year = tmp->tm_year;
		curDate.tm_mon = tmp->tm_mon;
		curDate.tm_mday = tmp->tm_mday;

		int day = _wtoi(GetString(mhDay).c_str());
		int month = _wtoi(GetString(mhMonth).c_str());
		int year = _wtoi(GetString(mhYear).c_str());

		try
		{
			if (!IsValidInt(mhYear))
			{
				throw L"Incorrect year";
			}
			else if (year < curDate.tm_year + 1900)
			{
				SetWindowText(mhResult, L"Time is up!");
				SetFocus(mhDay);
				return;
			}

			if (!IsValidInt(mhMonth) || month<1 || month >12)
			{
				throw L"Incorrect month";
			}

			if (!IsValidInt(mhDay) || day<1 || day>DaysInMonth(month, year))
			{
				throw L"Incorrect day";
			}
		}
		catch (wchar_t* error)
		{
			MessageBox(hWnd, error, L"Error", MB_OK | MB_ICONERROR);
			return;
		}

		struct tm nextDate = { 0 };
		nextDate.tm_year = year - 1900;
		nextDate.tm_mon = month - 1;
		nextDate.tm_mday = day;

		std::wstringstream result;

		time_t difference = mktime(&nextDate) - mktime(&curDate);

		if (difference <= 0)
		{
			result << "Time is up!";
		}
		else
		{
			int days = nextDate.tm_mday - curDate.tm_mday;
			if (days < 0)
			{
				if (!nextDate.tm_mon)
				{
					nextDate.tm_mon = 11;
					--nextDate.tm_year;
				}
				else --nextDate.tm_mon;

				days = nextDate.tm_mday + DaysInMonth(nextDate.tm_mon + 1, nextDate.tm_year) - curDate.tm_mday;
			}

			int months = nextDate.tm_mon - curDate.tm_mon;
			if (months < 0)
			{
				months = nextDate.tm_mon + 12 - curDate.tm_mon;
				--nextDate.tm_year;
			}

			int years = nextDate.tm_year - curDate.tm_year;

			if (years) result << years << " years\r\n";
			if (months) result << months << " months\r\n";
			if (days) result << days << " days";
			
		}

		SetWindowText(mhResult, result.str().c_str());
		SetFocus(mhDay);
	}
}

BOOL TimeToDateDlg::Cls_OnInitDialog(HWND hWnd, HWND hwndFocus, LPARAM lParam)
{
	mhDefineTime = GetDlgItem(hWnd, IDC_TIMELEFT);
	mhDay = GetDlgItem(hWnd, IDC_DAY);
	mhMonth = GetDlgItem(hWnd, IDC_MONTH);
	mhYear = GetDlgItem(hWnd, IDC_YEAR);
	mhResult = GetDlgItem(hWnd, IDC_RESULT);
	SetFocus(mhDay);

	return TRUE;
}


std::wstring TimeToDateDlg::GetString(HWND hWnd) const
{
	int len = GetWindowTextLength(hWnd) + 1;
	wchar_t* string = new wchar_t[len];
	GetWindowText(hWnd, string, len);

	return string;
}

bool TimeToDateDlg::IsValidInt(HWND hWnd) const
{
	std::wstring stringNumber = GetString(hWnd);
	if (stringNumber.empty()) return false;
	std::wstring::iterator it = stringNumber.begin();

	while (it != stringNumber.end())
	{
		if (!isdigit(*it))	return false;
		++it;
	}

	return true;
}

int TimeToDateDlg::DaysInMonth(const int month, const int year) const
{
	int daysInMonth[12] = { 31, 0, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if (month != 2)
		return daysInMonth[month - 1];
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
