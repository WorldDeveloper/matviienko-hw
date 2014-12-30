#pragma once
#include <windowsx.h>
#include <Windows.h>
#include "resource.h"
#include <string>
#include <vector>

class NoteDlg
{
	HWND mhDlg;
	HWND mhEdit;
	std::wstring mNote;
	std::wstring mAction;
public:
	NoteDlg(std::wstring action);

	static NoteDlg* ptr;
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void Cls_OnClose(HWND hWnd);
	BOOL Cls_OnInitDialog(HWND hWnd, HWND hwndFocus, LPARAM lParam);
	void Cls_OnCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify);

	std::wstring GetNote() const { return mNote; }
	bool SetNote(std::wstring note);
};