#pragma once
#include <windowsx.h>
#include <Windows.h>
#include "resource.h"
#include <commctrl.h>
#include <string>
#include <vector>
#include <tchar.h>

#pragma comment(lib,"comctl32")

class MenuDlg
{
	HWND mhDlg; 
	HMENU mhContextMenu;
	std::vector<int> mElementCount;
	std::vector<std::wstring> mElementTitle;
	int mX;
	int mY;
	HMENU CreateContextMenu();
public:
	MenuDlg();

	static MenuDlg* ptr;
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void Cls_OnClose(HWND hWnd) {EndDialog(mhDlg, 0); }
	BOOL Cls_OnInitDialog(HWND hWnd, HWND hwndFocus, LPARAM lParam);
	void Cls_OnCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify);
	void Cls_OnContextMenu(HWND hWnd, HWND hwndContext, UINT xPos, UINT yPos);
};