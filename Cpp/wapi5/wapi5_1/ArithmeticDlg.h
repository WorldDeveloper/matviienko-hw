#pragma once
#include <windowsx.h>
#include <Windows.h>
#include "resource.h"
#include <string>
#include <sstream>



class ArithmeticDlg
{
	HWND mhList;
	HWND mhResult;
	void Sum();
	void Product();
	void Average();
public:
	ArithmeticDlg();

	static ArithmeticDlg* ptr;
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void Cls_OnClose(HWND hWnd) { EndDialog(hWnd, 0); }
	void Cls_OnCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify);
	BOOL Cls_OnInitDialog(HWND hWnd, HWND hwndFocus, LPARAM lParam);
};