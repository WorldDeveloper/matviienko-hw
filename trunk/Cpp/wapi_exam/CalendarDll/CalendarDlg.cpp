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
	mhTitle = GetDlgItem(hWnd, IDC_TITLE);
	mhDescription = GetDlgItem(hWnd, IDC_DESCRIPTION);
	mhWhere = GetDlgItem(hWnd, IDC_WHERE);
	
	HWND hTmp[5];
	for(int i = 0; i < 5; ++i)
	{
		hTmp[i] = GetDlgItem(hWnd, IDC_FROM_YEAR+i);
	}
	mFromTime = new DateTime(hTmp[0], hTmp[1], hTmp[2], hTmp[3], hTmp[4]);

	time_t today;
	time(&today);

	for (int i = 0; i < 5; ++i)
	{
		hTmp[i] = GetDlgItem(hWnd, IDC_TO_YEAR + i);
	}
	mToTime = new DateTime(hTmp[0], hTmp[1], hTmp[2], hTmp[3], hTmp[4], today+60*60);


	return TRUE;
}

void CalendarDlg::Cls_OnCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify)
{
	if (codeNotify == CBN_SELCHANGE || codeNotify == EN_KILLFOCUS) 
	{
		mFromTime->CheckLastDay(); // split check
		mToTime->CheckLastDay();
	}


}

void CalendarDlg::Cls_OnClose(HWND hWnd)
{
	/*mNote.clear();*/
	EndDialog(mhDlg, 0);
}
