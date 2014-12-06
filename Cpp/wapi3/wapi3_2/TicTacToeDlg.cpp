#include "TicTacToeDlg.h"
#include <sstream>

TicTacToeDlg* TicTacToeDlg::handler = nullptr;

TicTacToeDlg::TicTacToeDlg() :mGameStarted(false), mFirstSquaresID(1015), mHumanFirst(false)
{
	handler = this;
}

BOOL CALLBACK TicTacToeDlg::DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hWnd, WM_INITDIALOG, handler->Cls_OnInitDialog);
		HANDLE_MSG(hWnd, WM_CLOSE, handler->Cls_OnClose);
		HANDLE_MSG(hWnd, WM_COMMAND, handler->Cls_OnCommand);
	}

	return FALSE;
}


BOOL TicTacToeDlg::Cls_OnInitDialog(HWND hWnd, HWND hwndFocus, LPARAM lParam)
{
	mhInst = GetModuleHandle(0);
	mhDialog = hWnd;
	mhHumanFirst = GetDlgItem(hWnd, IDC_HUMANFIRST);
	for (int i = 0; i < 3; ++i)
	{
		mhDifficulty[i] = GetDlgItem(hWnd, IDC_RADIO1 + i);
	}
	SendDlgItemMessage(hWnd, IDC_RADIO2, BM_SETCHECK, WPARAM(BST_CHECKED), 0);

	mhStart = GetDlgItem(hWnd, IDC_START);

	const int buttonSize = 80;
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			mhBoard[i][j] = CreateWindowEx(0, L"Button", NULL,
				WS_CHILD | WS_VISIBLE | BS_BITMAP, j*buttonSize, 150 + i*buttonSize, buttonSize, buttonSize, hWnd, (HMENU)(mFirstSquaresID + i * 3 + j), mhInst, 0);
		}
	}

	return TRUE;
}

void TicTacToeDlg::Cls_OnClose(HWND hWnd)
{
	EndDialog(hWnd, 0);
}

void TicTacToeDlg::Cls_OnCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify)
{
	if (id == IDC_START)
	{
		StartGame();
	}
	else if (id >= mFirstSquaresID && id < mFirstSquaresID + 9)
	{
		int row = (id - mFirstSquaresID) / 3;
		int col = (id - mFirstSquaresID) % 3;

		if (!mGameStarted || !mGame.SquareIsEmpty(row, col)) return;


		SendMessage(mhBoard[row][col], BM_SETIMAGE, WPARAM(IMAGE_BITMAP), LPARAM(mBmpHumanMark));

		if (mGame.HumanMove(row, col))
		{
			ShowResult(mHumanFirst);
			MessageBox(hWnd, L"You have won the game!", L"Victory!", MB_OK);
			return;
		}
		else if (!mGame.BoardIsFull())
		{
			if (mGame.ComputerMove(row, col))
			{
				ShowResult(!mHumanFirst);
				MessageBox(hWnd, L"You have lost the game!", L"Loss!", MB_OK);
				return;
			}

			SendMessage(mhBoard[row][col], BM_SETIMAGE, WPARAM(IMAGE_BITMAP), LPARAM(mBmpComputerMark));
		}

		if (mGame.BoardIsFull())
		{
			StopGame();
			MessageBox(hWnd, L"It's a draw!", L"Draw!", MB_OK);
		}
	}
}


void TicTacToeDlg::EnableBoard(const bool enable)
{
	EnableWindow(mhHumanFirst, !enable);
	for (int i = 0; i < 3; ++i)
	{
		EnableWindow(mhDifficulty[i], !enable);
	}
}

void TicTacToeDlg::ClearBoard()
{
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			SendMessage(mhBoard[i][j], BM_SETIMAGE, NULL, NULL);
		}
	}
}

void TicTacToeDlg::StartGame()
{
	if (mGameStarted)
	{
		StopGame();
	}
	else
	{
		SetWindowText(mhStart, L"Resign");
		EnableBoard(true);
		ClearBoard();

		LRESULT lResult;
		int i = 0;
		for (; i < 3; ++i)
		{
			lResult = SendMessage(mhDifficulty[i], BM_GETCHECK, 0, 0);
			if (lResult == BST_CHECKED) break;
		}
		mGame.SetDifficulty(i);


		lResult = SendMessage(mhHumanFirst, BM_GETCHECK, 0, 0);
		if (lResult != BST_CHECKED)
		{
			mHumanFirst = false;
			mBmpHumanMark = LoadBitmap(mhInst, MAKEINTRESOURCE(IDB_NOUGHT));
			mBmpComputerMark = LoadBitmap(mhInst, MAKEINTRESOURCE(IDB_CROSS));
			int row = 0;
			int col = 0;
			mGame.ComputerMove(row, col);
			SendMessage(mhBoard[row][col], BM_SETIMAGE, WPARAM(IMAGE_BITMAP), LPARAM(mBmpComputerMark));
		}
		else
		{
			mHumanFirst = true;
			mBmpHumanMark = LoadBitmap(mhInst, MAKEINTRESOURCE(IDB_CROSS));
			mBmpComputerMark = LoadBitmap(mhInst, MAKEINTRESOURCE(IDB_NOUGHT));

		}

		mGameStarted = true;
	}

}

void TicTacToeDlg::StopGame()
{
	mGame.Reset();
	mGameStarted = false;
	SetWindowText(mhStart, L"Start new game");
	EnableBoard(false);
}



void TicTacToeDlg::ShowResult(const bool cross)
{
	HBITMAP winMark;
	if (cross)
	{
		winMark = LoadBitmap(mhInst, MAKEINTRESOURCE(IDB_CROSSWIN));
	}
	else
	{
		winMark = LoadBitmap(mhInst, MAKEINTRESOURCE(IDB_NOUGHTWIN));
	}
	Line result = mGame.GetResult();

	if (result.x1 == 0 && result.y1 == 0 && result.x2 == 2 && result.y2 == 2)
	{
		for (int i = 0; i < 3; ++i)
		{
			SendMessage(mhBoard[i][i], BM_SETIMAGE, WPARAM(IMAGE_BITMAP), LPARAM(winMark));
		}
	}
	else if (result.x1 == 2 && result.y1 == 0 && result.x2 == 0 && result.y2 == 2)
	{
		for (int i = 0; i < 3; ++i)
		{
			SendMessage(mhBoard[2 - i][i], BM_SETIMAGE, WPARAM(IMAGE_BITMAP), LPARAM(winMark));
		}
	}
	else
	{
		for (int i = result.x1; i <= result.x2; ++i)
		{
			for (int j = result.y1; j <= result.y2; ++j)
			{
				SendMessage(mhBoard[i][j], BM_SETIMAGE, WPARAM(IMAGE_BITMAP), LPARAM(winMark));
			}
		}
	}
	StopGame();
}