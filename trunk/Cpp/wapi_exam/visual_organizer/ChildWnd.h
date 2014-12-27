#pragma once
#include "FrameWnd.h"

class ChildWnd: public FrameWnd
{
	
public:
	ChildWnd();
	static ChildWnd* handler;

	static LRESULT CALLBACK MdiChildWinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void Cls_OnClose(HWND hWnd);
	void Cls_OnCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify);
	void Cls_OnSize(HWND hWnd, UINT state, int cx, int cy);
	void Cls_OnSetFocus(HWND hWnd, HWND hwndOldFocus);
	void Cls_OnKillFocus(HWND hWnd, HWND hwndNewFocus);
};

