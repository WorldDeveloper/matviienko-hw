#pragma once
#include <windowsx.h>
#include <Windows.h>
#include "resource.h"
#include <commctrl.h>

#pragma comment(lib,"comctl32")

class SliderDlg
{
	HWND mhDlg;
	HWND mhProgress;
	HWND mhRed;
	HWND mhGreen;
	HWND mhBlue;
	int mRed;
	int mGreen;
	int mBlue;

public:
	SliderDlg();

	static SliderDlg* ptr;
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void Cls_OnClose(HWND hWnd) { EndDialog(hWnd, 0); }
	void Cls_OnHScroll(HWND hwWd, HWND hwndCtl, UINT code, int pos);
	BOOL Cls_OnInitDialog(HWND hWnd, HWND hwndFocus, LPARAM lParam);

};