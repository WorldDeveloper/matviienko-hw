#pragma once
#include <windowsx.h>
#include <Windows.h>
#include "resource.h"
#include <sstream>
#include <ctime>


class LogicalDrivesDlg
{

public:
	LogicalDrivesDlg();

	static LogicalDrivesDlg* ptr;
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void Cls_OnClose(HWND hWnd) { EndDialog(hWnd, 0); }
	BOOL Cls_OnInitDialog(HWND hWnd, HWND hwndFocus, LPARAM lParam);
};