#pragma once
#include <windows.h>
#include <WindowsX.h>
#include "resource.h"
#include <vector>
#include <tchar.h>

class CrackersDlg
{
	HWND hDialog;
	TCHAR mDialogCaption[12];
	int mLeft;
	int mTop;
	int mWidth;
	int mHeight;
	const int mMinSize;
	int mCurrentNumber;
	std::vector<HWND> mStaticsHwnd;

	int ItemHasCoords(const int x,  const int y);	

public:
	CrackersDlg();	

	static CrackersDlg *handler;
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);	

	void Cls_OnClose(HWND hWnd);
	void Cls_OnLButtonDown(HWND hWnd, BOOL fDoubleClick, int x, int y, UINT keyFlags);
	void Cls_OnLButtonUp(HWND hWnd, int x, int y, UINT keyFlags);
	void Cls_OnRButtonDown(HWND hWnd, BOOL fDoubleClick, int x, int y, UINT keyFlags);
};

