#include "GameDlg.h"
#include <ctime>

GameDlg* GameDlg::ptr = nullptr;

GameDlg::GameDlg()
{
	ptr = this;
}

BOOL CALLBACK GameDlg::DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hWnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hWnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hWnd, WM_COMMAND, ptr->Cls_OnCommand);
		HANDLE_MSG(hWnd, WM_TIMER, ptr->Cls_OnTimer);
	}

	return FALSE;
}

void GameDlg::Cls_OnCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify)
{
	if (id == IDC_START)
	{
		const int seconds = SendMessage(mhTimeSpin, UDM_GETPOS32, 0, 0);
		if (!mGame.NewGame(seconds)) return;

		SendMessage(mhProgress, PBM_SETRANGE, 0, MAKELPARAM(0, seconds));
		InitControls(L"Restart", false);
		SetTimer(mhDlg, IDT_TIMER, 1000, NULL);
	}
	else if (id >= IDC_FIRSTTILE && id < IDC_FIRSTTILE + mGame.GetTilesCount())
	{
		const int index = id - IDC_FIRSTTILE;
		if (mGame.LegalMove(index))
		{
			SendMessage(mhList, LB_ADDSTRING, 0, LPARAM(mGame.GetTile(index).c_str()));
			EnableWindow(mhTile[index], false);

			if (mGame.IsFinished())
			{
				KillTimer(mhDlg, IDT_TIMER);
				MessageBox(mhDlg, L"You win!", L"Victory", MB_OK | MB_ICONASTERISK);
				InitControls(L"Start", true);
			}
		}
	}
}

BOOL GameDlg::Cls_OnInitDialog(HWND hWnd, HWND hwndFocus, LPARAM lParam)
{
	mhDlg = hWnd;
	const int frameSize = (int)std::sqrt(mGame.GetTilesCount());
	const int end = mGame.GetTilesCount();
	for (int i = 0; i < end; ++i)
	{
		mhTile.push_back(CreateWindowEx(0, L"Button", NULL,
			WS_CHILD | WS_VISIBLE | WS_TABSTOP, i%frameSize*mButtonSize + mPadding, i / frameSize*mButtonSize + mPadding, mButtonSize, mButtonSize, hWnd, (HMENU)(IDC_FIRSTTILE + i), GetModuleHandle(0), 0));
	}

	int x = mButtonSize*frameSize + mPadding * 2;
	int y = mPadding;
	int width = 70;
	int height = mButtonSize * 2;
	mhList = CreateWindowEx(WS_EX_CLIENTEDGE, L"LISTBOX", NULL,
		WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_TABSTOP, x, y, width, height, hWnd, 0, GetModuleHandle(0), 0);

	y += height + mPadding;
	height = 30;
	mhStart = CreateWindowEx(0, L"BUTTON", L"Start",
		WS_CHILD | WS_VISIBLE | WS_TABSTOP, x, y, width, height, hWnd, (HMENU)IDC_START, GetModuleHandle(0), 0);

	y += height + mPadding;
	height = 50;

	mhTimeEdit = CreateWindowEx(0, L"Button", L"Time",
		WS_CHILD | WS_VISIBLE | BS_GROUPBOX, x, y, width, height, hWnd, 0, GetModuleHandle(0), 0);

	y += mPadding * 2;
	x += mPadding;
	width -= mPadding * 2;
	height -= mPadding * 3;
	mhTimeEdit = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", NULL,
		WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_NUMBER, x, y, width, height, hWnd, 0, GetModuleHandle(0), 0);

	mhTimeSpin = CreateWindowEx(0, UPDOWN_CLASS, NULL, WS_CHILD | WS_VISIBLE | WS_TABSTOP | UDS_WRAP | UDS_ARROWKEYS | UDS_ALIGNRIGHT | UDS_SETBUDDYINT, 0, 0, 0, 0, hWnd, (HMENU)IDC_TIMESPIN, GetModuleHandle(0), 0);
	SendMessage(mhTimeSpin, UDM_SETBUDDY, (WPARAM)mhTimeEdit, 0);
	SendMessage(mhTimeSpin, UDM_SETBASE, 10, 0);
	SendMessage(mhTimeSpin, UDM_SETRANGE, 0, MAKELPARAM(100, 1));
	SendMessage(mhTimeSpin, UDM_SETPOS, 0, 60);

	CreateProgressbar();

	return TRUE;
}

void GameDlg::Cls_OnTimer(HWND hWnd, UINT id)
{
	if (mGame.TimeIsUp())
	{
		KillTimer(hWnd, IDT_TIMER);
		MessageBox(hWnd, L"Time is up! You lost the game!", L"Loss", MB_OK | MB_ICONSTOP);
		InitControls(L"Start", true);

		return;
	}

	const int time = mGame.GetElapsedTimeInt();
	SendMessage(mhProgress, PBM_SETPOS, time, 0);
	SetWindowText(hWnd, mGame.GetElapsedTime().c_str());
}



void GameDlg::CreateProgressbar()
{
	const int timerWidth = 50;
	RECT rClient;
	GetClientRect(mhDlg, &rClient);

	const int height = 30;
	mhProgress = CreateWindowEx(0, PROGRESS_CLASS, NULL, WS_CHILD | WS_VISIBLE, mPadding, rClient.bottom - height - mPadding, rClient.right - 2 * mPadding, height, mhDlg, NULL, NULL, NULL);
	SendMessage(mhProgress, PBM_SETSTEP, 1, 0);
	SendMessage(mhProgress, PBM_SETPOS, 0, 0);
}

void GameDlg::InitControls(wchar_t* action, const bool emptyTiles)
{
	SetWindowText(mhDlg, L"Game");
	SetWindowText(mhStart, action);

	const int end = mGame.GetTilesCount();
	if (emptyTiles)
	{
		for (int i = 0; i < end; ++i)
		{
			SetWindowText(mhTile[i], NULL);
			EnableWindow(mhTile[i], true);
		}
	}
	else
	{
		for (int i = 0; i < end; ++i)
		{
			SetWindowText(mhTile[i], mGame.GetTile(i).c_str());
			EnableWindow(mhTile[i], true);
		}
	}

	SendMessage(mhProgress, PBM_SETPOS, 0, 0);
	SendMessage(mhList, LB_RESETCONTENT, 0, 0);
}