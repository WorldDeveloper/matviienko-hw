#pragma once
#include <windowsx.h>
#include <Windows.h>
#include "resource.h"
#include <iostream>
#include <string>
#include <sstream>

class TimeToDateDlg
{
	HWND mhDefineTime;
	HWND mhDay;
	HWND mhMonth;
	HWND mhYear;
	HWND mhResult;

	bool IsValidInt(HWND hWnd)const;
	std::wstring GetString(HWND hWnd)const;
	int DaysInMonth(const int month, const int year)const;

public:
	TimeToDateDlg();

	static TimeToDateDlg* ptr;
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void Cls_OnClose(HWND hWnd) { EndDialog(hWnd, 0); }
	void Cls_OnCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify);
	BOOL Cls_OnInitDialog(HWND hWnd, HWND hwndFocus, LPARAM lParam);
};