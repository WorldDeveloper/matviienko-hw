#pragma once
#include <windowsx.h>
#include <Windows.h>
#include "resource.h"
#include <iostream>
#include <string>
#include <sstream>

class DowDlg
{
	HWND mhDefineDOW;
	HWND mhDay;
	HWND mhMonth;
	HWND mhYear;
	HWND mhDOW;

	bool IsValidInt(HWND hWnd);
	std::wstring GetString(HWND hWnd);
	int DaysInMonth(const int month, const int year);

public:
	DowDlg();

	static DowDlg* ptr;
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void Cls_OnClose(HWND hWnd) { EndDialog(hWnd, 0); }
	void Cls_OnCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify);
	BOOL Cls_OnInitDialog(HWND hWnd, HWND hwndFocus, LPARAM lParam);
};