#include "CalendarDlg.h"

DlgCracker* DlgCracker::ptr = nullptr;

DlgCracker::DlgCracker(std::wstring action)
{
	ptr = this;
	mAction = action;
	mNote.clear();
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
	/*mhEdit = GetDlgItem(hWnd, IDC_NOTECONTENT);
	SetWindowText(hWnd, (mAction + L" note").c_str());

	if (mNote.size()) SetWindowText(mhEdit, mNote.c_str());
	if (mAction == L"View") EnableWindow(mhEdit, FALSE);*/
	return TRUE;
}

void DlgCracker::Cls_OnCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify)
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

void DlgCracker::Cls_OnClose(HWND hWnd)
{
	/*mNote.clear();*/
	EndDialog(mhDlg, 0);
}

bool DlgCracker::SetNote(std::wstring note)
{
	/*if (note.empty()) return false;

	mNote = note;*/

	return true;
}