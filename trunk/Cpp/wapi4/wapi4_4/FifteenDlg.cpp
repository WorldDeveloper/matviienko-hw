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
		}

		if (mGame.IsFinished())
		{
			MessageBox(hWnd, L"Well done!", L"You have won!", MB_OK);

			ShowWindow(mhTile[mGame.GetMissingTile()], SW_SHOW);
			mGame.Randomize();

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

			mhTile.push_back(CreateWindowEx(WS_EX_CLIENTEDGE, L"Button", mGame.GetTile(i).c_str(),
				style, i%frameSize*buttonSize, i / frameSize*buttonSize, buttonSize, buttonSize, hWnd, (HMENU)(IDC_FIRSTTILE + i), GetModuleHandle(0), 0));
		}
		catch (wchar_t* error)
		{
			MessageBox(hWnd, error, L"Error", MB_OK | MB_ICONERROR);
		}
	}

	return TRUE;
}