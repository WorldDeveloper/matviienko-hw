#pragma once
#include <Windows.h>
#include <WindowsX.h>
#include "resource.h"


class RunningStaticDlg
{
	HWND mhStatic;
	int mX;
	int mY;
	int mSize;
public:
	RunningStaticDlg();
	static RunningStaticDlg* handler;
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	BOOL Cls_OnInitDialog(HWND hWnd, HWND hwndFocus, LPARAM lParam);
	void Cls_OnClose(HWND hWnd);
	void Cls_OnMouseMove(HWND hWnd, int x, int y, UINT keyFlags);
};