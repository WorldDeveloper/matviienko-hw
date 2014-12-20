#pragma once
#include <windowsx.h>
#include <Windows.h>
#include "resource.h"
#include <commctrl.h>
#include <vector>
#include <string>

#pragma comment(lib,"comctl32")

class MenuDlg
{
	HMENU mhEnMenu;
	HMENU mhRuMenu;
	HMENU mhDynamicMenu;
	HWND mhReplace;
	HWND mhTranslate;
	HWND mhDlg;
	std::vector<LPWSTR> mEnTitle;
	std::vector<LPWSTR> mRuTitle;
	HMENU CreateMainMenu();
	void TranslateMainMenu();
public:
	MenuDlg();

	static MenuDlg* ptr;
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void Cls_OnClose(HWND hWnd) {
		DestroyWindow(hWnd);
		PostQuitMessage(0);
	}
	BOOL Cls_OnInitDialog(HWND hWnd, HWND hwndFocus, LPARAM lParam);
	void Cls_OnCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify);

};