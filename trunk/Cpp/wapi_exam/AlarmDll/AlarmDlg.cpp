#include "AlarmDlg.h"

DlgCracker* DlgCracker::ptr = nullptr;

DlgCracker::DlgCracker(std::wstring action)
{
	ptr = this;
	mAction = action;
	mAlarm = 0;
}

BOOL CALLBACK DlgCracker::DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hWnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hWnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hWnd, WM_COMMAND, ptr->Cls_OnCommand);
	}

	return FALSE;
}


BOOL DlgCracker::Cls_OnInitDialog(HWND hWnd, HWND hwndFocus, LPARAM lParam)
{
	mhDlg = hWnd;
	mhYear = GetDlgItem(hWnd, IDC_YEAR);
	mhMonth = GetDlgItem(hWnd, IDC_MONTH);
	mhDay = GetDlgItem(hWnd, IDC_DAY);
	mhHour = GetDlgItem(hWnd, IDC_HOUR);
	mhMin = GetDlgItem(hWnd, IDC_MIN);

	//if (mNote.size()) SetWindowText(mhEdit, mNote.c_str());
	//if (mAction == L"View") EnableWindow(mhEdit, FALSE);

	return TRUE;
}

void DlgCracker::Cls_OnCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify)
{

}

void DlgCracker::Cls_OnClose(HWND hWnd)
{

	EndDialog(mhDlg, 0);
}
