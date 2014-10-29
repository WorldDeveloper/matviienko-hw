/*
Написать приложение, обладающее следующей функциональностью:
- при нажатии кнопки Enter окно приложение позиционируется в левый верхний угол экрана с размерами (300х300);
- с помощью клавиш управления курсором осуществляется перемещение окна
*/

#include <Windows.h>
#include <tchar.h>

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

TCHAR szClassWindow[] = TEXT("WindowPos");

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
	case WM_KEYDOWN:
	{
		RECT rcWindow;
		GetWindowRect(hWnd, &rcWindow);
		int curWidth = rcWindow.right - rcWindow.left;
		int curHeight = rcWindow.bottom - rcWindow.top;

		const int defHeight = 300;
		const int defWidth = 300;
		const int shift = 5;
		switch (wParam)
		{
		case VK_RETURN:
			rcWindow.left = 0;
			rcWindow.top = 0;
			curWidth= defWidth;
			curHeight = defHeight;
			break;
		case VK_LEFT:
			rcWindow.left -= shift;
			break;
		case VK_RIGHT:
			rcWindow.left += shift;
			break;
		case VK_UP:
			rcWindow.top -= shift;
			break;
		case VK_DOWN:
			rcWindow.top += shift;
			break;
		}
		SetWindowPos(hWnd, NULL, rcWindow.left, rcWindow.top, curWidth,curHeight, SWP_NOZORDER);
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