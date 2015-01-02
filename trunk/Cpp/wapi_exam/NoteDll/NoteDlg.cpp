#include "NoteDlg.h"

NoteDlg* NoteDlg::ptr = nullptr;

NoteDlg::NoteDlg(std::wstring action)
{
	ptr = this;
	mAction = action;
	mNote.clear();
}

BOOL CALLBACK NoteDlg::DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hWnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hWnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hWnd, WM_COMMAND, ptr->Cls_OnCommand);
	}

	return FALSE;
}


BOOL NoteDlg::Cls_OnInitDialog(HWND hWnd, HWND hwndFocus, LPARAM lParam)
{
	mhDlg = hWnd;
	mhEdit = GetDlgItem(hWnd, IDC_NOTECONTENT);

	if (mAction==L"Edit")
	{
		SetWindowText(mhDlg, L"Edit note");
		SetWindowText(mhEdit, mNote.c_str());		
	}
	else if (mAction == L"View")
	{
		SetWindowText(mhDlg, L"View note");
		SetWindowText(mhEdit, mNote.c_str());
		EnableWindow(mhEdit, FALSE);
	}

	return TRUE;
}

void NoteDlg::Cls_OnCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify)
{
	if (id == IDC_OK)
	{
		if (mAction == L"View") EndDialog(hWnd, 0);

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
	}

}

void NoteDlg::Cls_OnClose(HWND hWnd)
{
	mNote.clear();
	EndDialog(mhDlg, 0);
}

bool NoteDlg::SetNote(std::wstring note)
{
	if (note.empty()) return false;

	mNote = note;

	return true;
}