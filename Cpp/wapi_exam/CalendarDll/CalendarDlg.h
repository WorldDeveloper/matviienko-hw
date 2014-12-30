#pragma once
#include <windowsx.h>
#include <Windows.h>
#include "resource.h"
#include <string>
#include <vector>
#include <ctime>

class CalendarDlg
{
	HWND mhDlg;
	HWND mhTitle;
	HWND mhDescription;
	HWND mhWhere;
	HWND mhFromYear;
	HWND mhFromMonth;
	HWND mhFromDay;
	HWND mhFromHour;
	HWND mhFromMin;
	HWND mhToYear;
	HWND mhToMonth;
	HWND mhToDay;
	HWND mhToHour;
	HWND mhToMin;	

	std::wstring mAction;

	int LastDayInMonth(const int year, const int month) const;
	bool  SetMonth(const int month);
	bool  SetDay(const int year, const int month, const int curDay);
	void SetDateTime(const time_t dateTime = 0);

public:
	CalendarDlg(std::wstring action);

	static CalendarDlg* ptr;
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void Cls_OnClose(HWND hWnd);
	BOOL Cls_OnInitDialog(HWND hWnd, HWND hwndFocus, LPARAM lParam);
	void Cls_OnCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify);

	/*std::wstring GetNote() const { return mNote; }
	bool SetNote(std::wstring note);*/
};