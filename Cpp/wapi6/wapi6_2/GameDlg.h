#pragma once
#include <windowsx.h>
#include <Windows.h>
#include "resource.h"
#include "GameModel.h"

#include <CommCtrl.h>
#pragma comment(lib,"comctl32.lib")
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

class GameDlg
{
	std::vector<HWND> mhTile;
	HWND mhDlg;
	HWND mhList;
	HWND mhTimeEdit;
	HWND mhTimeSpin;
	HWND mhStart;
	HWND mhProgress;
	GameModel mGame;

	bool mGameStarted;
	const int mPadding = 10;
	const int mButtonSize = 50;

	void InitControls(wchar_t* action, bool emptyTiles);
	void CreateProgressbar();
public:
	GameDlg();

	static GameDlg* ptr;
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void Cls_OnClose(HWND hWnd) { EndDialog(hWnd, 0); }
	void Cls_OnCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify);
	BOOL Cls_OnInitDialog(HWND hWnd, HWND hwndFocus, LPARAM lParam);
	void Cls_OnTimer(HWND hWnd, UINT id);
};