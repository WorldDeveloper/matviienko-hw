#include "ElementsDlg.h"


ElementsDlg* ElementsDlg::ptr = nullptr;

ElementsDlg::ElementsDlg() :mControlWidth(100)
{
	ptr = this;
	mControlHeight[0] = 30;
	mControlHeight[1] = 30;
	mControlHeight[2] = 70;
	mControlHeight[3] = 70;
	mControlHeight[4] = 30;

	mhControls.resize(5);
}

BOOL CALLBACK ElementsDlg::DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hWnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hWnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hWnd, WM_COMMAND, ptr->Cls_OnCommand);
	}

	return FALSE;
}

void ElementsDlg::Cls_OnCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify)
{
	switch (id)
	{
	case IDC_CREATE:
	{
		int index = SendMessage(mhControlsCombo, CB_GETCURSEL, 0, 0);
		if (index == CB_ERR) return;

		RECT rcClient;
		GetClientRect(hWnd, &rcClient);
		rcClient.right -= mControlWidth;
		rcClient.bottom -= mControlHeight[index];
		const int rLeft = std::rand() % rcClient.right;
		int rTop = 0;
		do
		{
			rTop = std::rand() % rcClient.bottom;
		} while (rLeft < 190 && rTop < 100);

		int len = SendMessage(mhControlsCombo, CB_GETLBTEXTLEN, index, 0);
		TCHAR* buffer = new TCHAR[len + 1];
		SendMessage(mhControlsCombo, CB_GETLBTEXT, index, LPARAM(buffer));

		DWORD style = WS_CHILD | WS_VISIBLE;
		if (index == 3) style |= CBS_DROPDOWNLIST;
		mhControls[index].push(CreateWindowEx(WS_EX_CLIENTEDGE, buffer, buffer,
			style, rLeft, rTop, mControlWidth, mControlHeight[index], hWnd, 0, GetModuleHandle(0), 0));
		delete[] buffer;

		break;
	}
	case IDC_DELETE:
	{
		int index = SendMessage(mhControlsCombo, CB_GETCURSEL, 0, 0);
		if (index == CB_ERR) return;

		if (mhControls[index].empty()) return;

		DestroyWindow(mhControls[index].top());
		mhControls[index].pop();
		break;

	}

	}
}

BOOL ElementsDlg::Cls_OnInitDialog(HWND hWnd, HWND hwndFocus, LPARAM lParam)
{
	std::srand(time(NULL));

	mhControlsCombo = GetDlgItem(hWnd, IDC_COMBO);

	wchar_t* controls[] = { L"BUTTON", L"EDIT", L"LISTBOX", L"COMBOBOX", L"STATIC" };
	for (int i = 0; i < 5; ++i)
	{
		SendMessage(mhControlsCombo, CB_ADDSTRING, 0, LPARAM(controls[i]));

	}


	return TRUE;
}
