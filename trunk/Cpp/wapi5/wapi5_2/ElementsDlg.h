#pragma once
#include <windowsx.h>
#include <Windows.h>
#include "resource.h"
#include <stack>
#include <vector>
#include <ctime>


class ElementsDlg
{
	HWND mhControlsCombo;
	std::vector<std::stack<HWND>> mhControls;
	int mControlHeight[5];
	const int mControlWidth;
public:
	ElementsDlg();

	static ElementsDlg* ptr;
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void Cls_OnClose(HWND hWnd) { EndDialog(hWnd, 0); }
	void Cls_OnCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify);
	BOOL Cls_OnInitDialog(HWND hWnd, HWND hwndFocus, LPARAM lParam);
};