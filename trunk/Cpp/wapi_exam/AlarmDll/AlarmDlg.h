#pragma once
#include <windowsx.h>
#include <Windows.h>
#include <string>
#include <vector>
#include <ctime>

#include "resource.h"

class AlarmDlg
{
	HWND mhDlg;
	HWND mhYear;
	HWND mhMonth;
	HWND mhDay;
	HWND mhHour;
	HWND mhMin;

	time_t mAlarm;
	std::wstring mAction;

	int LastDayInMonth(const int year, const int month) const;
	bool  SetMonth(const int month);
	bool  SetDay(const int year,  const int month, const int curDay);
	void SetDateTime(const time_t dateTime=0);

public:
	AlarmDlg(std::wstring action);

	static AlarmDlg* ptr;
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void Cls_OnClose(HWND hWnd);
	BOOL Cls_OnInitDialog(HWND hWnd, HWND hwndFocus, LPARAM lParam);
	void Cls_OnCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify);

};