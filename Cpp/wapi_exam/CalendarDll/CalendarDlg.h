#pragma once
#include <windowsx.h>
#include <Windows.h>
#include <string>
#include <vector>

#include "resource.h"
#include "DateTime.h"
#include "Event.h"

class CalendarDlg
{
	HWND mhDlg;
	HWND mhTitle;
	HWND mhDescription;
	HWND mhWhere;
	DateTime* mFromTime;
	DateTime* mToTime;

	CalendarEvent mEvent;
	std::wstring mAction;

	std::wstring GetStringFromEdit(HWND hEdit) const;
public:
	CalendarDlg(std::wstring action, CalendarEvent newEvent);
	~CalendarDlg()
	{
		delete mFromTime;
		delete mToTime;
	}
	static CalendarDlg* ptr;
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void Cls_OnClose(HWND hWnd);
	BOOL Cls_OnInitDialog(HWND hWnd, HWND hwndFocus, LPARAM lParam);
	void Cls_OnCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify);

	CalendarEvent GetEvent() { return mEvent; }
};