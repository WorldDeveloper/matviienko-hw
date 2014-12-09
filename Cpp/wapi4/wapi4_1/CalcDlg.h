#pragma once
#include <windowsx.h>
#include <Windows.h>
#include "resource.h"
#include <iostream>
#include <string>
#include <sstream>

class CalcDlg
{
	HWND mhCalc;
	HWND mhClear;
	HWND mh1stOperand;
	HWND mh2ndOperand;
	HWND mhOperator;
	HWND mhResult;

	bool IsValidNumber(HWND hWnd);
	std::wstring GetString(HWND hWnd);

public:
	CalcDlg();

	static CalcDlg* ptr;
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void Cls_OnClose(HWND hWnd) { EndDialog(hWnd, 0); }
	void Cls_OnCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify);
	BOOL Cls_OnInitDialog(HWND hWnd, HWND hwndFocus, LPARAM lParam);
};