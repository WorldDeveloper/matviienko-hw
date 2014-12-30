#pragma once
#include <windowsx.h>
#include <Windows.h>
#include <string>
#include <vector>

#include "resource.h"
#include "DateTime.h"

class AlarmDlg
{
	HWND mhDlg;
	DateTime* mAlarmTime;

	time_t mAlarm;
	std::wstring mAction;

public:
	AlarmDlg(std::wstring action, const time_t alarmTime);
	~AlarmDlg()
	{
		delete mAlarmTime;
	}

	static AlarmDlg* ptr;
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void Cls_OnClose(HWND hWnd);
	BOOL Cls_OnInitDialog(HWND hWnd, HWND hwndFocus, LPARAM lParam);
	void Cls_OnCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify);
	
	time_t GetAlarm() const { return mAlarm; }
};