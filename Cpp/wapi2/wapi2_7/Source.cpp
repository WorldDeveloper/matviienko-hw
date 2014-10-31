/*
Написать приложение, обладающее следующей функциональностью:
-	при последовательном нажатии клавиши Enter  дочерние окна
главного окна приложения “Калькулятор» минимизируются;
-	при последовательном нажатии клавиши Esc дочерние окна
восстанавливаются в обратном порядке
*/

#include <Windows.h>
#include <tchar.h>
#include <iostream>
#include <stack>

std::stack<HWND> windowsStack;

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK EnumChildProc(HWND, LPARAM);
void HideChildWindows(HWND);
void ShowChildWindow();

TCHAR szClassWindow[] = TEXT("Hide child windows");
TCHAR szCalculator[] = TEXT("Калькулятор");

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
		CW_USEDEFAULT, CW_USEDEFAULT, 300, 300,
		NULL, NULL, hInst, NULL);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&lpMsg, hWnd, 0, 0) > 0)
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
		switch (wParam)
		{
		case VK_RETURN:
			HideChildWindows(hWnd);
			break;
		case VK_ESCAPE:
			ShowChildWindow();
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, uMessage, wParam, lParam);
	}
}

BOOL CALLBACK EnumChildProc(HWND hWnd, LPARAM lParam)
{
	HWND hCalc = (HWND)lParam;
	TCHAR caption[MAX_PATH];
	GetWindowText(hWnd, caption, MAX_PATH - 1);

	TCHAR className[100] = { 0 };
	GetClassName(hWnd, className, 100);

	if (!lstrcmp(className, TEXT("Button")))
	{
		windowsStack.push(hWnd);
		ShowWindow(hWnd, SW_MINIMIZE);
	}

	return TRUE;
}

void HideChildWindows(HWND hWnd)
{
	while (!windowsStack.empty()) windowsStack.pop();

	HWND hCalc;
	hCalc = FindWindow(TEXT("CalcFrame"), szCalculator);

	if (!hCalc)
	{
		MessageBox(hWnd, TEXT("Откройте \"Калькулятор\""), TEXT("Error"), MB_OK | MB_ICONSTOP);
	}
	else
	{
		EnumChildWindows(hCalc, EnumChildProc, (LPARAM)hCalc);
		RedrawWindow(hCalc, NULL, NULL, RDW_INVALIDATE);
	}
}

void ShowChildWindow()
{
	HWND hCalc;
	hCalc = FindWindow(TEXT("CalcFrame"), szCalculator);

	if (windowsStack.empty())
	{
		InvalidateRect(hCalc, NULL, TRUE);
		return;
	}

	HWND restoredWindow = windowsStack.top();
	windowsStack.pop();

	ShowWindow(restoredWindow, SW_SHOWNORMAL);
	InvalidateRect(hCalc, NULL, TRUE);
}