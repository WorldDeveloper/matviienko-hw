/*
Написать приложение, обладающее следующей функциональностью:
- при нажатии клавиши Enter  главное окно позиционируется
в левый верхний угол экрана с размерами (300х300) и начинает перемещаться
по периметру экрана с определённой скоростью;
- при нажатии клавиши Esc  перемещение окна прекращается.
*/

#include <Windows.h>
#include <tchar.h>

#define IDT_TIMER 1

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
void AutoMoveWindow(HWND);

TCHAR szClassWindow[] = TEXT("Auto move");

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int nCmdShow)
{
	HWND hWnd;
	MSG lpMsg;
	WNDCLASSEX wcl;

	wcl.cbSize = sizeof(wcl);
	wcl.style = CS_HREDRAW | CS_VREDRAW;
	wcl.lpfnWndProc = WindowProc;
	wcl.cbClsExtra = 0;
	wcl.cbWndExtra = 0;
	wcl.hInstance = hInst;
	wcl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcl.hIconSm = NULL;
	wcl.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcl.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wcl.lpszMenuName = NULL;
	wcl.lpszClassName = szClassWindow;

	if (!RegisterClassEx(&wcl)) return 0;

	hWnd = CreateWindowEx(0, szClassWindow, szClassWindow, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL, hInst, NULL);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&lpMsg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&lpMsg);
		DispatchMessage(&lpMsg);
	}

	return lpMsg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	switch (uMessage)
	{
	case WM_TIMER:
	{
		AutoMoveWindow(hWnd);
		break;
	}
	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_RETURN:
			SetWindowPos(hWnd, NULL, 0, 0, 300, 300, SWP_NOZORDER);
			SetTimer(hWnd, IDT_TIMER, 20, NULL);
			break;
		case VK_ESCAPE:
			KillTimer(hWnd, IDT_TIMER);
			break;
		}

		break;
	}
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		break;
	}
	default:
		return DefWindowProc(hWnd, uMessage, wParam, lParam);
	}

	return 0;
}

void AutoMoveWindow(HWND hWnd)
{
	const HWND hDesktop = GetDesktopWindow();
	RECT rcDesktop;
	GetWindowRect(hDesktop, &rcDesktop);

	RECT rcWindow;
	GetWindowRect(hWnd, &rcWindow);

	const int shift = 5;
	const int windowWidth = rcWindow.right - rcWindow.left;
	const int windowHeight = rcWindow.bottom - rcWindow.top;

	if (rcWindow.top <= 0 && rcWindow.right < rcDesktop.right)
	{
		rcWindow.left += shift;
	}
	else if (rcWindow.right >= rcDesktop.right && rcWindow.bottom  < rcDesktop.bottom)
	{
		rcWindow.top += shift;
	}
	else if (rcWindow.bottom >= rcDesktop.bottom && rcWindow.left>0)
	{
		rcWindow.left -= shift;
	}
	else if (rcWindow.left <= 0 && rcWindow.top > 0)
	{
		rcWindow.top -= shift;
	}

	SetWindowPos(hWnd, NULL, rcWindow.left, rcWindow.top, windowHeight, windowWidth, SWP_NOZORDER);
}