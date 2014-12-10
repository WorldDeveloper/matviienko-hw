#include "DowDlg.h"
#include <ctime>

DowDlg* DowDlg::ptr = nullptr;

DowDlg::DowDlg()
{
	ptr = this;
}

BOOL CALLBACK DowDlg::DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hWnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hWnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hWnd, WM_COMMAND, ptr->Cls_OnCommand);
	}

	return FALSE;
}

void DowDlg::Cls_OnCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify)
{
	if (id == IDC_DEFINEDOW)
	{
		SetWindowText(mhDOW, NULL);

		int day = _wtoi(GetString(mhDay).c_str());
		int month = _wtoi(GetString(mhMonth).c_str());
		int year = _wtoi(GetString(mhYear).c_str());

		try
		{
			if (!IsValidInt(mhYear))
			{
				throw L"Incorrect year";
			}
			else if (year < 1900) throw L"Enter year earlier than 1900";

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

		const wchar_t* weekday[] = { L"Sunday", L"Monday",
			L"Tuesday", L"Wednesday", L"Thursday", L"Friday", L"Saturday" };

		time_t rawtime;
		struct tm* timeinfo;
		time(&rawtime);
		timeinfo = localtime(&rawtime);
		timeinfo->tm_year = year - 1900;
		timeinfo->tm_mon = month - 1;
		timeinfo->tm_mday = day;
		mktime(timeinfo);

		SetWindowText(mhDOW, weekday[timeinfo->tm_wday]);
		SetFocus(mhDay);
	}
}

BOOL DowDlg::Cls_OnInitDialog(HWND hWnd, HWND hwndFocus, LPARAM lParam)
{
	mhDefineDOW = GetDlgItem(hWnd, IDC_DEFINEDOW);
	mhDay = GetDlgItem(hWnd, IDC_DAY);
	mhMonth = GetDlgItem(hWnd, IDC_MONTH);
	mhYear = GetDlgItem(hWnd, IDC_YEAR);
	mhDOW = GetDlgItem(hWnd, IDC_DOW);
	SetFocus(mhDay);

	return TRUE;
}


std::wstring DowDlg::GetString(HWND hWnd)
{
	int len = GetWindowTextLength(hWnd) + 1;
	wchar_t* string = new wchar_t[len];
	GetWindowText(hWnd, string, len);

	return string;
}

bool DowDlg::IsValidInt(HWND hWnd)
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

int DowDlg::DaysInMonth(const int month, const int year)
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