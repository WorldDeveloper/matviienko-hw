#include "MenuDlg.h"
#include <ctime>

MenuDlg* MenuDlg::ptr = nullptr;

MenuDlg::MenuDlg()
{
	ptr = this;
	mElementCount = { 3, 3, 3 };
	mElementTitle = { L"Button", L"Edit", L"Static" };
}

BOOL CALLBACK MenuDlg::DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hWnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hWnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hWnd, WM_COMMAND, ptr->Cls_OnCommand);
		HANDLE_MSG(hWnd, WM_CONTEXTMENU, ptr->Cls_OnContextMenu);
	}

	return FALSE;
}


BOOL MenuDlg::Cls_OnInitDialog(HWND hWnd, HWND hwndFocus, LPARAM lParam)
{
	mhDlg = hWnd;
	mhContextMenu = CreateContextMenu();
	return TRUE;
}

void MenuDlg::Cls_OnCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify)
{
	if (id<IDM_BUTTON || id>IDM_STATIC) return;

	const int index = id - IDM_BUTTON;

	std::wstring caption = mElementTitle[index] + std::to_wstring(mElementCount[index]);
	CreateWindowEx(WS_EX_CLIENTEDGE, mElementTitle[index].c_str(), caption.c_str(),
		WS_CHILD | WS_VISIBLE, mX, mY, 60, 30, mhDlg, 0, GetModuleHandle(0), 0);

	--mElementCount[index];
	int position = index;
	for (int i = 0; i < index; ++i)
	{
		if (!mElementCount[i]) position--;
	}

	if (!mElementCount[index])
	{
		DeleteMenu(mhContextMenu, position, MF_BYPOSITION);
	}
	else
	{
		MENUITEMINFO mii;
		mii.cbSize = sizeof(MENUITEMINFO);
		mii.fMask = MIIM_STRING;
		TCHAR* item = new TCHAR[10];
		_tcscpy(item, (mElementTitle[index] + std::to_wstring(mElementCount[index])).c_str());
		mii.dwTypeData = item;
		SetMenuItemInfo(mhContextMenu, position, TRUE, &mii);
		delete[] item;
	}
}

void MenuDlg::Cls_OnContextMenu(HWND hWnd, HWND hwndContext, UINT xPos, UINT yPos)
{
	RECT rect;
	rect.left = xPos;
	rect.top = yPos;
	rect.right = xPos;
	rect.bottom = yPos;
	MapWindowPoints(HWND_DESKTOP, mhDlg, (LPPOINT)&rect, 2);

	mX = rect.left;
	mY = rect.top;
	TrackPopupMenu(mhContextMenu, TPM_LEFTALIGN, xPos, yPos, 0, mhDlg, NULL);
}

HMENU MenuDlg::CreateContextMenu()
{
	HMENU subMenu = CreatePopupMenu();

	for (int i = 0; i < mElementTitle.size(); ++i)
	{
		AppendMenu(subMenu, MF_STRING, IDM_BUTTON+i, (mElementTitle[i]+std::to_wstring(mElementCount[i])).c_str());
	}
	SetMenu(mhDlg, subMenu);

	return subMenu;
}