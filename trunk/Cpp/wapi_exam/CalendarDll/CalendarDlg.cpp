#include "CalendarDlg.h"

CalendarDlg* CalendarDlg::ptr = nullptr;

CalendarDlg::CalendarDlg(std::wstring action)
{
	ptr = this;
	mAction = action;
	//mNote.clear();
}

BOOL CALLBACK CalendarDlg::DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hWnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hWnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hWnd, WM_COMMAND, ptr->Cls_OnCommand);
	}

	return FALSE;
}


BOOL CalendarDlg::Cls_OnInitDialog(HWND hWnd, HWND hwndFocus, LPARAM lParam)
{
	mhDlg = hWnd;
	/*mhEdit = GetDlgItem(hWnd, IDC_NOTECONTENT);
	SetWindowText(hWnd, (mAction + L" note").c_str());

	if (mNote.size()) SetWindowText(mhEdit, mNote.c_str());
	if (mAction == L"View") EnableWindow(mhEdit, FALSE);*/
	return TRUE;
}

void CalendarDlg::Cls_OnCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify)
{
	/*if (id == IDC_OK)
	{

		int length = SendMessage(mhEdit, WM_GETTEXTLENGTH, 0, 0);
		if (length > 0)
		{
			wchar_t* buf = new wchar_t[length + 1];
			SendMessage(mhEdit, WM_GETTEXT, (length + 1), (LPARAM)buf);
			mNote = std::wstring(buf);
			delete[] buf;
		}
		EndDialog(hWnd, 0);
	}
	else if (id == IDC_CANCEL)
	{
		mNote.clear();
		EndDialog(hWnd, 0);
	}*/

}

void CalendarDlg::Cls_OnClose(HWND hWnd)
{
	/*mNote.clear();*/
	EndDialog(mhDlg, 0);
}



int CalendarDlg::LastDayInMonth(const int year, const int month) const
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

bool  CalendarDlg::SetMonth(const int month)
{
	/*if (month<1 || month>12) return false;

	wchar_t* months[12] = { L"January", L"February", L"March", L"April", L"May", L"June", L"July", L"August", L"September", L"October", L"November", L"December" };
	for (int i = 0; i < 12; ++i)
	{
		int ind = SendMessage(mhMonth, CB_ADDSTRING, 0, (LPARAM)months[i]);
		SendMessage(mhMonth, CB_SETITEMDATA, ind, i);
	}
	SendMessage(mhMonth, CB_SETCURSEL, month - 1, 0);*/

	return true;
}

bool  CalendarDlg::SetDay(const int year, const int month, const int curDay)
{
	/*if (year <= 0 || month<1 || month>12 || curDay<1) return false;

	const int daysInMonth = LastDayInMonth(year, month);
	if (curDay>daysInMonth) return false;

	for (int i = 1; i < daysInMonth + 1; ++i)
	{
		const int ind = SendMessage(mhDay, CB_ADDSTRING, 0, (LPARAM)(std::to_wstring(i).c_str()));
		SendMessage(mhDay, CB_SETITEMDATA, ind, i);
	}
	SendMessage(mhDay, CB_SETCURSEL, curDay - 1, 0);*/

	return true;
}

void CalendarDlg::SetDateTime(const time_t dateTime/*=0*/)
{
	/*time_t rawtime;
	struct tm * moment;

	if (dateTime) rawtime = dateTime;
	time(&rawtime);
	moment = localtime(&rawtime);

	SetWindowText(mhYear, std::to_wstring(moment->tm_year + 1900).c_str());
	SetMonth(moment->tm_mon + 1);
	SetDay(moment->tm_year + 1900, moment->tm_mon + 1, moment->tm_mday);

	std::wstring hour;
	if (moment->tm_hour < 10) hour = L"0";
	hour += std::to_wstring(moment->tm_hour);
	SetWindowText(mhHour, hour.c_str());

	std::wstring min;
	if (moment->tm_min < 10) min = L"0";
	min += std::to_wstring(moment->tm_min);
	SetWindowText(mhMin, min.c_str());*/
}