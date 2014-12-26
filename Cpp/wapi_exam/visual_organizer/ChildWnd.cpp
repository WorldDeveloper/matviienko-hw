#include "ChildWnd.h"

ChildWnd* ChildWnd::handler = nullptr;

ChildWnd::ChildWnd()
{
	handler=this;
}

LRESULT CALLBACK ChildWnd::MdiChildWinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hWnd, WM_CLOSE, handler->Cls_OnClose);
		HANDLE_MSG(hWnd, WM_COMMAND, handler->Cls_OnCommand);	
		HANDLE_MSG(hWnd, WM_SIZE, handler->Cls_OnSize);
	default:
			return DefMDIChildProc(hWnd, message, wParam, lParam);
	}

	return FALSE;
}

void ChildWnd::Cls_OnClose(HWND hWnd)
{
		ShowWindow(hWnd, SW_HIDE);


	/*if (hWnd == mhCalendar) mhCalendar = NULL;
	else if (hWnd == mhNote) mhNote = NULL;
	else if (hWnd == mhAlarm) mhAlarm = NULL;*/

	//FORWARD_WM_CLOSE(hWnd, DefMDIChildProc);
}

void ChildWnd::Cls_OnCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify)
{
	//MessageBox(hWnd, L"Button", NULL, MB_OK);
}


void ChildWnd::Cls_OnSize(HWND hWnd, UINT state, int cx, int cy)
{

	
	FORWARD_WM_SIZE(hWnd, state, cx, cy, DefMDIChildProc);
}



