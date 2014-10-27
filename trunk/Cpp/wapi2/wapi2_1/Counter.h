#pragma once
#include <Windows.h>
#include <iostream>
#include <tchar.h>

class Counter
{
	HWND mhWnd;
	LPWSTR mszWindowName;
	UINT muLeftClicks;
	UINT muRightClicks;
	UINT muMiddleClicks;
public:
	Counter(LPWSTR szWindowName)
		:mhWnd(NULL), mszWindowName(szWindowName), muLeftClicks(0), muRightClicks(0), muMiddleClicks(0){}
	
	void SetHandle(HWND hWnd) {mhWnd=hWnd;}

	void SetWindowHeader()
	{
		TCHAR szClicks[100];
		wsprintf(szClicks, L" - Left clicks:%u, Right clicks:%u, Middle clicks:%u", muLeftClicks, muRightClicks, muMiddleClicks);
		TCHAR szCaption[200];
		lstrcpy(szCaption, mszWindowName);
		lstrcat(szCaption, szClicks);
		SetWindowText(mhWnd, szCaption);
	}

	void LeftClick() 
	{
		++muLeftClicks;
		SetWindowHeader();
	}
	void RightClick() 
	{
		++muRightClicks;
		SetWindowHeader();
	}
	void MiddleClick(const UINT uClicksNumber = 1) 
	{
		++muMiddleClicks;
		SetWindowHeader();
	}
};

