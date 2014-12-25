#pragma once
#include "Header.h"


class FrameWnd
{
	HINSTANCE mhInst;
	HWND mhWnd;

	HWND mhCalendar;
	HWND mhNotes;
	HWND mhAlarms;
	wchar_t szChildWindow[12];

public:
	FrameWnd();

	static FrameWnd* handler;
	static 	HWND mhMdiClient;
	static LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	
	void Cls_OnClose(HWND hWnd);
	BOOL Cls_OnCreate(HWND hWnd, LPCREATESTRUCT lpCreateStruct);
	void Cls_OnCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify);
	void Cls_OnSize(HWND hWnd, UINT state, int cx, int cy);

	
	void CreateMainMenu(HWND hWnd);
	void CreateToolbar(HWND hWnd);
	void CreateStatusbar(HWND hWnd);
	void ReSize(HWND hWnd, HWND hClient);
	
	HWND GetClient() const { return mhMdiClient; }
	const wchar_t* GetChildClassName()const { return szChildWindow; }

};