#include "FifteenDlg.h"
#include <ctime>

FifteenDlg* FifteenDlg::ptr = nullptr;

FifteenDlg::FifteenDlg()
{
	ptr = this;
}

BOOL CALLBACK FifteenDlg::DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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

void FifteenDlg::Cls_OnCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify)
{
	if (id < IDC_FIRSTTILE && id >= IDC_FIRSTTILE + mGame.GetTilesCount()) return;

	int index = id - IDC_FIRSTTILE;

	try
	{
		int newPos = mGame.GetMissingTile();
		if (mGame.SwapTile(index))
		{
			ShowWindow(mhTile[index], SW_HIDE);
			SetWindowText(mhTile[newPos], mGame.GetTile(newPos).c_str());
			ShowWindow(mhTile[newPos], SW_SHOW);

			SendMessage(mhProgress, PBM_SETPOS, mGame.GetSolvedSquaresNumber(), 0);
		}

		if (mGame.IsFinished())
		{
			KillTimer(hWnd, IDT_TIMER);
			
			std::wstring elapsedTime = mGame.GetElapsedTime();
			SendMessage(mhStatus, SB_SETTEXT, 0, (LPARAM)elapsedTime.c_str());
			
			std::wstringstream mes;
			mes << "Well done!\n\r Your time: " << elapsedTime;

			MessageBox(hWnd, mes.str().c_str(), L"You have won!", MB_OK);

			ShowWindow(mhTile[mGame.GetMissingTile()], SW_SHOW);
			mGame.NewGame();

			const int end = mGame.GetTilesCount();
			for (int i = 0; i < end; ++i)
			{
				if (mGame.GetTile(i) == L"0") ShowWindow(mhTile[i], SW_HIDE);
				else SetWindowText(mhTile[i], mGame.GetTile(i).c_str());
			}
		}
	}
	catch (wchar_t* error)
	{
		MessageBox(hWnd, error, L"Error", MB_OK | MB_ICONERROR);
	}

}

BOOL FifteenDlg::Cls_OnInitDialog(HWND hWnd, HWND hwndFocus, LPARAM lParam)
{
	const int buttonSize = 50;

	std::wstring caption;
	const int frameSize = (int)std::sqrt(mGame.GetTilesCount());
	const int end = mGame.GetTilesCount();
	for (int i = 0; i < end; ++i)
	{
		try
		{
			DWORD style = WS_CHILD | WS_VISIBLE;
			if (mGame.GetTile(i) == L"0") style = WS_CHILD;

			mhTile.push_back(CreateWindowEx(0, L"Button", mGame.GetTile(i).c_str(),
				style, i%frameSize*buttonSize+2, i / frameSize*buttonSize+2, buttonSize, buttonSize, hWnd, (HMENU)(IDC_FIRSTTILE + i), GetModuleHandle(0), 0));
		}
		catch (wchar_t* error)
		{
			MessageBox(hWnd, error, L"Error", MB_OK | MB_ICONERROR);
		}
	}
	SetTimer(hWnd, IDT_TIMER, 1000, NULL);
	CreateStatusbar(hWnd);


	return TRUE;
}

void FifteenDlg::Cls_OnTimer(HWND hWnd, UINT id)
{
	SendMessage(mhStatus, SB_SETTEXT, 0, (LPARAM)mGame.GetElapsedTime().c_str());
}

void FifteenDlg::CreateStatusbar(HWND hWnd)
{
	InitCommonControls();
	mhStatus = CreateWindowEx(0, STATUSCLASSNAME, NULL, WS_CHILD | WS_VISIBLE | SBARS_SIZEGRIP, 0, 0, 0, 0,
		hWnd, (HMENU)IDC_STATUS, GetModuleHandle(NULL), NULL);

	int statWidths[] = { 50, -1 };

	SendMessage(mhStatus, SB_SETPARTS, sizeof(statWidths) / sizeof(int), (LPARAM)statWidths);
	SendMessage(mhStatus, SB_SETTEXT, 1, (LPARAM)TEXT("Hi there"));

	CreateProgressbar();
}

void FifteenDlg::CreateProgressbar()
{
	const int timerWidth = 50;
	RECT rStatus;
	GetClientRect(mhStatus, &rStatus);

	mhProgress = CreateWindowEx(0, PROGRESS_CLASS, NULL, WS_CHILD | WS_VISIBLE, timerWidth, 0, rStatus.right-timerWidth, rStatus.bottom, mhStatus, NULL, NULL, NULL);
	SendMessage(mhProgress, PBM_SETRANGE, 0, MAKELPARAM(0, 15));
	SendMessage(mhProgress, PBM_SETSTEP, 1, 0);
	SendMessage(mhProgress, PBM_SETPOS, mGame.GetSolvedSquaresNumber(), 0);
}
