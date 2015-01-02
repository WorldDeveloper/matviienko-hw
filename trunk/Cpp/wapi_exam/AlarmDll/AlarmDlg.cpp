#include "AlarmDlg.h"

AlarmDlg* AlarmDlg::ptr = nullptr;

AlarmDlg::AlarmDlg(std::wstring action, const time_t alarmTime)
{
	ptr = this;
	mAction = action;
	mAlarm = alarmTime;
}

BOOL CALLBACK AlarmDlg::DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hWnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hWnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hWnd, WM_COMMAND, ptr->Cls_OnCommand);
	}

	return FALSE;
}


BOOL AlarmDlg::Cls_OnInitDialog(HWND hWnd, HWND hwndFocus, LPARAM lParam)
{
	mhDlg = hWnd;
	HWND hYear = GetDlgItem(hWnd, IDC_YEAR);
	HWND hMonth = GetDlgItem(hWnd, IDC_MONTH);
	HWND hDay = GetDlgItem(hWnd, IDC_DAY);
	HWND hHour = GetDlgItem(hWnd, IDC_HOUR);
	HWND hMin = GetDlgItem(hWnd, IDC_MIN);	
	
	if (mAction == L"Add")
	{
		SetWindowText(mhDlg, L"Add alarm");
		mAlarmTime = new DateTime(hYear, hMonth, hDay, hHour, hMin);
	}
	else if (mAction == L"Edit")
	{
		SetWindowText(mhDlg, L"Edit alarm");
		mAlarmTime = new DateTime(hYear, hMonth, hDay, hHour, hMin, mAlarm);
	}
	else if (mAction == L"View")
	{
		SetWindowText(mhDlg, L"View alarm");
		mAlarmTime = new DateTime(hYear, hMonth, hDay, hHour, hMin, mAlarm);
		for (int i = 0; i < 5; ++i)
		{
			EnableWindow(GetDlgItem(mhDlg, IDC_YEAR+i), FALSE);
		}
	}

	return TRUE;
}

void AlarmDlg::Cls_OnCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify)
{
	if (codeNotify == CBN_SELCHANGE || codeNotify == EN_KILLFOCUS)
	{
		mAlarmTime->CheckLastDay();
		return;
	}

	if (id == IDC_OK)
	{
		if (mAction == L"View") EndDialog(hWnd, 0);

		try
		{
			mAlarm = mAlarmTime->GetDateTime();

			time_t now;
			time(&now);
			if (mAlarm <= now)
			{
				MessageBox(hWnd, L"Time is up!", L"Correct record", MB_OK | MB_ICONEXCLAMATION);
					return;
			}
		}
		catch (wchar_t* err)
		{
			MessageBox(hWnd, L"Incorrect date/time!", L"Error", MB_OK | MB_ICONEXCLAMATION);
			mAlarm = 0;
			return;
		}

		EndDialog(hWnd, 0);
	}
	else if (id == IDC_CANCEL)
	{
		mAlarm = 0;
		EndDialog(hWnd, 0);
	}
}

void AlarmDlg::Cls_OnClose(HWND hWnd)
{
	mAlarm = 0;
	EndDialog(mhDlg, 0);
}
