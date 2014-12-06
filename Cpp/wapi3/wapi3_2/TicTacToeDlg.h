#pragma once
#include <WindowsX.h>
#include <Windows.h>
#include "resource.h"
#include "TicTacToeGame.h"

class TicTacToeDlg
{
	const int mFirstSquaresID;
	HINSTANCE mhInst;
	HWND mhDialog;
	HWND mhStart;
	HWND mhBoard[3][3];
	HWND mhHumanFirst;
	HWND mhDifficulty[3];
	HBITMAP mBmpHumanMark;
	HBITMAP mBmpComputerMark;

	TicTacToeGame mGame;

	bool mGameStarted;
	bool mHumanFirst;
public:
	TicTacToeDlg();

	static TicTacToeDlg* handler;
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	BOOL Cls_OnInitDialog(HWND hWnd, HWND hwndFocus, LPARAM lParam);
	void Cls_OnClose(HWND hWnd);
	void Cls_OnCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify);

	void EnableBoard(const bool enable);
	void ClearBoard();
	void StartGame();
	void StopGame();
	void ShowResult(const bool cross);
};