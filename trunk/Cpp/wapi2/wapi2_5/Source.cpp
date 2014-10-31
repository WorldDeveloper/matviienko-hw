/*
Написать приложение, обладающее следующей функциональностью:
- после нажатия клавиши Enter  через каждую секунду (или иной промежуток времени)
«прячется» одна из кнопок «Калькулятора», выбранная случайным образом;
- после нажатия клавиши Esc данный процесс останавливается.
*/

#include <Windows.h>
#include <tchar.h>
#include <iostream>
#include <vector>
#include <ctime>
#include <cmath>

#define IDT_TIMER1 1

int sec = 0;
std::vector<HWND> windowsArray;

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK EnumChildProc(HWND, LPARAM);
void HandleTimerEvent(HWND);

TCHAR szClassWindow[] = TEXT("Hide buttons");

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
	case WM_TIMER:
		HandleTimerEvent(hWnd);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_RETURN:
			SetTimer(hWnd, IDT_TIMER1, 1000, NULL);
			break;
		case VK_ESCAPE:
			KillTimer(hWnd, IDT_TIMER1);
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
	TCHAR caption[MAX_PATH];
	GetWindowText(hWnd, caption, MAX_PATH - 1);

	TCHAR className[100] = { 0 };
	GetClassName(hWnd, className, 100);

	if (!lstrcmp(className, TEXT("Button")) && IsWindowVisible(hWnd))
	{
		windowsArray.push_back(hWnd);
	}

	return TRUE;
}

void HandleTimerEvent(HWND hWnd)
{
	TCHAR out[10];
	wsprintf(out, TEXT("%d"), sec++);
	SetWindowText(hWnd, out);

	HWND hCalc;
	hCalc = FindWindow(TEXT("CalcFrame"), TEXT("Калькулятор"));

	if (!hCalc)
	{
		KillTimer(hWnd, IDT_TIMER1);
		MessageBox(hWnd, TEXT("Откройте \"Калькулятор\""), TEXT("Error"), MB_OK | MB_ICONSTOP);
	}
	else
	{
		EnumChildWindows(hCalc, EnumChildProc, (LPARAM)hCalc);

		if (windowsArray.empty())
		{
			KillTimer(hWnd, IDT_TIMER1);
			return;
		}

		std::srand(std::time(NULL));
		int randomIndex = std::rand() % windowsArray.size();

		ShowWindow(windowsArray[randomIndex], SW_HIDE);
		RedrawWindow(hCalc, NULL, NULL, RDW_INVALIDATE);

		windowsArray.clear();
	}
}
