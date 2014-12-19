#include "SliderDlg.h"
#include <ctime>

SliderDlg* SliderDlg::ptr = nullptr;

SliderDlg::SliderDlg() :mRed(0), mGreen(0), mBlue(0)
{
	ptr = this;
}

BOOL CALLBACK SliderDlg::DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hWnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hWnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hWnd, WM_HSCROLL, ptr->Cls_OnHScroll);
	}

	return FALSE;
}

void SliderDlg::Cls_OnHScroll(HWND hWnd, HWND hwndCtl, UINT code, int pos)
{
	if (hwndCtl == mhRed)
		mRed = SendMessage(hwndCtl, TBM_GETPOS, TRUE, MAKELPARAM(0, 255));
	else if (hwndCtl == mhGreen)
		mGreen = SendMessage(hwndCtl, TBM_GETPOS, TRUE, MAKELPARAM(0, 255));
	else if (hwndCtl == mhBlue)
		mBlue = SendMessage(hwndCtl, TBM_GETPOS, TRUE, MAKELPARAM(0, 255));

	SendMessage(mhProgress, PBM_SETBKCOLOR, 0, LPARAM(RGB(mRed, mGreen, mBlue)));
}

BOOL SliderDlg::Cls_OnInitDialog(HWND hWnd, HWND hwndFocus, LPARAM lParam)
{
	mhDlg = hWnd;
	mhRed = GetDlgItem(hWnd, IDC_RED);
	SendMessage(mhRed, TBM_SETRANGE, TRUE, MAKELPARAM(0, 255));

	mhGreen = GetDlgItem(hWnd, IDC_GREEN);
	SendMessage(mhGreen, TBM_SETRANGE, TRUE, MAKELPARAM(0, 255));

	mhBlue = GetDlgItem(hWnd, IDC_BLUE);
	SendMessage(mhBlue, TBM_SETRANGE, TRUE, MAKELPARAM(0, 255));

	mhProgress = GetDlgItem(hWnd, IDC_PROGRESS);
	SendMessage(mhProgress, PBM_SETRANGE, 0, MAKELPARAM(0, 100));
	SendMessage(mhProgress, PBM_SETPOS, 0, 0);

	return TRUE;
}