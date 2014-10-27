/*
Написать приложение, в котором ведется подсчет количества "кликов"
левой, правой и средней кнопки мыши. Обновляемую статистику необходимо
выводить в заголовок окна.
*/
#include <Windows.h>
#include <tchar.h>
#include "Counter.h"

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

WCHAR szClassWindow[] = TEXT("Clicks counter");
Counter counter(szClassWindow);

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int nCmdShow)
{
	HWND hWnd;
	MSG lpMsg;
	WNDCLASSEX wcl;

	wcl.cbSize = sizeof(wcl);
	wcl.style = CS_HREDRAW | CS_VREDRAW|CS_DBLCLKS;
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
	case WM_CREATE:
		counter.SetHandle(hWnd);
		break;
	case WM_LBUTTONDOWN:
		counter.LeftClick();
		break;
	case WM_RBUTTONDOWN:
		counter.RightClick();
		break;
	case WM_MBUTTONDOWN:
		counter.MiddleClick();
		break;
	case WM_LBUTTONDBLCLK:
		counter.LeftClick();
		break;
	case WM_RBUTTONDBLCLK:
		counter.RightClick();
		break;
	case WM_MBUTTONDBLCLK:
		counter.MiddleClick();
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, uMessage, wParam, lParam);
	}

	return 0;
}