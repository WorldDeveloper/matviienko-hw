#include "RunningStaticDlg.h"
#include <sstream>
#include <ctime>

RunningStaticDlg* RunningStaticDlg::handler = nullptr;

RunningStaticDlg::RunningStaticDlg()
{
	handler = this;
}


BOOL CALLBACK RunningStaticDlg::DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hWnd, WM_INITDIALOG, handler->Cls_OnInitDialog);
		HANDLE_MSG(hWnd, WM_CLOSE, handler->Cls_OnClose);
		HANDLE_MSG(hWnd, WM_MOUSEMOVE, handler->Cls_OnMouseMove);
	}

	return FALSE;
}

BOOL RunningStaticDlg::Cls_OnInitDialog(HWND hWnd, HWND hwndFocus, LPARAM lParam)
{
	mX = 10;
	mY = 10;
	mSize = 50;
	mhStatic = CreateWindowExW(0, L"STATIC", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | WS_EX_CLIENTEDGE | SS_CENTER,
		mX, mY, mSize, mSize, hWnd, 0, GetModuleHandle(NULL), 0);
	return TRUE;
}

void RunningStaticDlg::Cls_OnClose(HWND hWnd)
{
	EndDialog(hWnd, 0);
}

void RunningStaticDlg::Cls_OnMouseMove(HWND hWnd, int x, int y, UINT keyFlags)
{
	std::srand(time(NULL));

	RECT rcClient;
	GetClientRect(hWnd, &rcClient);

	int rX = std::rand() % rcClient.right;
	int rY = std::rand() % rcClient.bottom;

	while (abs(mX - x) < 100 && abs(mY - y) < 100)
	{

		mX = (mX + rX) % (rcClient.right-mSize);
		mY = (mY + rY) % (rcClient.bottom-mSize);
	}

	SetWindowPos(mhStatic, NULL, mX, mY, mSize, mSize, SWP_NOZORDER);
}
