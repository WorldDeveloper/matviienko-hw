/*
Написать приложение, позволяющее при нажатии левой кнопки мыши изменить
текст в заголовке окна стандартного приложения "Калькулятор",
а при нажатии правой кнопки мыши сместить вправо кнопку "Пуск",
изменив на ней надпись.
*/

#include <Windows.h>
#include <tchar.h>

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
void RenameCalculator(HWND hWnd);
void RenameStartButton(HWND hWnd);

TCHAR szClassWindow[] = TEXT("Object's names");

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

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_LBUTTONDOWN:
		RenameCalculator(hWnd);
		break;
	case WM_RBUTTONDOWN:
		RenameStartButton(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

void RenameCalculator(HWND hWnd)
{
	HWND hCalc;
	hCalc = FindWindow(L"CalcFrame", L"Калькулятор");
	if (hCalc)
	{
		SetWindowText(hCalc, TEXT("myCalc"));
		BringWindowToTop(hCalc);
	}
	else
	{
		MessageBox(hWnd, TEXT("Откройте \"Калькулятор\"."), TEXT("Can't find Calculator"), MB_OK | MB_ICONINFORMATION);
	}
}

void RenameStartButton(HWND hWnd)
{
	TCHAR name[2][10] = { L"Пуск", L"Стоп" };
	bool changed = false;

	HWND hStartButton;
	hStartButton = FindWindow(L"Button", name[0]);

	if (!hStartButton)
	{
		hStartButton = FindWindow(L"Button", name[1]);
		changed = true;
	}

	if (hStartButton)
	{
		SetWindowText(hStartButton, name[!changed]);

		RECT rcWindow;
		GetWindowRect(hStartButton, &rcWindow);
		const int shift = 100;
		MoveWindow(hStartButton, rcWindow.left + shift, rcWindow.top, rcWindow.right - rcWindow.left, rcWindow.bottom - rcWindow.top, TRUE);

		SendMessage(hStartButton, BM_SETSTATE, FALSE, NULL);
	}
	else
	{
		MessageBox(hWnd, TEXT("Can't find \"Start\" button"), TEXT("Error"), MB_OK | MB_ICONERROR);
	}
}



