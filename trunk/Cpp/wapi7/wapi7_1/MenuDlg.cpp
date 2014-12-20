#include "MenuDlg.h"
#include <ctime>

MenuDlg* MenuDlg::ptr = nullptr;

MenuDlg::MenuDlg()
{
	ptr = this;
	mRuTitle = { L"&Файл", L"&Создать\tCtrl+N", L"&Открыть...\tCtrl+O", L"Со&хранить\tCtrl+S", L"&Выход\tCtrl+Q" };
	mEnTitle = { L"&File", L"&New\tCtrl+N", L"&Open...\tCtrl+O", L"&Save\tCtrl+S", L"&Quit\tCtrl+Q" };
}

BOOL CALLBACK MenuDlg::DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hWnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hWnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hWnd, WM_COMMAND, ptr->Cls_OnCommand);
	}

	return FALSE;
}


BOOL MenuDlg::Cls_OnInitDialog(HWND hWnd, HWND hwndFocus, LPARAM lParam)
{
	mhDlg = hWnd;
	mhEnMenu = GetMenu(hWnd);
	mhRuMenu = LoadMenu(GetModuleHandle(0), MAKEINTRESOURCE(IDR_MENURU));
	mhReplace = GetDlgItem(hWnd, IDC_REPLACE);
	mhTranslate = GetDlgItem(hWnd, IDC_TRANSLATE);

	return TRUE;
}

void MenuDlg::Cls_OnCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify)
{
	if (id == IDC_REPLACE)
	{
		const int size = 25;
		wchar_t caption[25];
		GetWindowText(mhReplace, caption, size);

		if (!wcscmp(caption, L"Replace with Russian"))
		{
			SetMenu(hWnd, mhRuMenu);
			SetWindowText(mhReplace, L"Заменить на Английский");
		}
		else
		{
			SetMenu(hWnd, mhEnMenu);
			SetWindowText(mhReplace, L"Replace with Russian");
		}
	}
	else if (id == IDC_TRANSLATE)
	{
		const int size = 25;
		wchar_t caption[25];
		GetWindowText(mhTranslate, caption, size); 
		
		if (!wcscmp(caption, L"Translate into Russian"))
		{
			mhDynamicMenu=CreateMainMenu();
			SetWindowText(mhTranslate, L"Перевести на Английский");
		}
		else
		{
			TranslateMainMenu();
			SetWindowText(mhTranslate, L"Translate into Russian");
		}
	}
	else if (id == IDM_NEW)
	{
		MessageBox(hWnd, L"New", L"Menu", MB_OK);
	}
	else if (id == IDM_OPEN)
	{
		MessageBox(hWnd, L"Open", L"Menu", MB_OK);
	}
	else if (id == IDM_SAVE)
	{
		MessageBox(hWnd, L"Save", L"Menu", MB_OK);
	}
	else if (id == IDM_QUIT)
	{
		MessageBox(hWnd, L"Quit", L"Menu", MB_OK);
	}
}

HMENU MenuDlg::CreateMainMenu()
{
	HMENU subFileMenu = CreatePopupMenu();
	for (int i = 1; i < mRuTitle.size(); ++i)
	{
		AppendMenu(subFileMenu, MF_STRING, IDM_NEW + i-1, mRuTitle[i] );
	}
	HMENU menu = CreateMenu();
	AppendMenu(menu, MF_POPUP, (UINT_PTR)subFileMenu, mRuTitle[0]);
	SetMenu(mhDlg, menu);

	return menu;
}

void MenuDlg::TranslateMainMenu()
{
	if (mEnTitle.size() != mRuTitle.size()) return;

	MENUITEMINFO mii;
	mii.cbSize = sizeof(MENUITEMINFO);
	mii.fMask = MIIM_STRING;
	mii.dwTypeData = mEnTitle[0];
	SetMenuItemInfo(mhDynamicMenu, 0, TRUE, &mii);


	HMENU hMenuPopup = GetSubMenu(mhDynamicMenu, 0);
	int subCount = GetMenuItemCount(hMenuPopup);
	for (int i = 0; i < subCount; ++i)
	{
		MENUITEMINFO mii;
		mii.cbSize=  sizeof(MENUITEMINFO);
		mii.fMask = MIIM_STRING;
		mii.dwTypeData =mEnTitle[i+1];

		SetMenuItemInfo(hMenuPopup, i, TRUE, &mii);
	}
	DrawMenuBar(mhDlg);
}