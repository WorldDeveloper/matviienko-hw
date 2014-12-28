#include "DlgCracker.h"

DlgCracker* DlgCracker::ptr = nullptr;

DlgCracker::DlgCracker(std::wstring action)
{
	ptr = this;
	mAction = action;
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

	return TRUE;
}

void DlgCracker::Cls_OnCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify)
{

}

void DlgCracker::Cls_OnClose(HWND hWnd)
{

	EndDialog(mhDlg, 0);
}
