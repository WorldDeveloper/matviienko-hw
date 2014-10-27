/*
Предположим, что существует прямоугольник, границы которого на 10 пикселей
отстоят от границ клиентской области окна. Необходимо при нажатии левой
кнопки мыши выводить в заголовок окна сообщение о том, где произошел
щелчок мышью: внутри прямоугольника, снаружи или на границе прямоугольника.
При нажатии правой кнопки мыши необходимо выводить в заголовок окна информацию
о размере клиентской области окна (ширина и высота клиентской области окна).
*/

#include <Windows.h>
#include <tchar.h>

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

TCHAR szClassWindow[] = TEXT("Position of click");
void ShowWindowSize(HWND hWnd);
void ShowClickPosition(HWND hWnd, LPARAM lParam);

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
	case WM_LBUTTONDOWN:
		ShowClickPosition(hWnd, lParam);
		break;
	case WM_RBUTTONDOWN:
		ShowWindowSize(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, uMessage, wParam, lParam);
	}

	return 0;
}

void ShowWindowSize(HWND hWnd)
{
	RECT rcClient;
	GetClientRect(hWnd, &rcClient);

	TCHAR caption[50];
	wsprintf(caption, TEXT("width:%li  height:%li"), rcClient.right, rcClient.bottom);
	SetWindowText(hWnd, caption);
}

void ShowClickPosition(HWND hWnd, LPARAM lParam)
{
	RECT rcClient;
	GetClientRect(hWnd, &rcClient);

	const int x = LOWORD(lParam);
	const int y = HIWORD(lParam);

	TCHAR caption[9];
	const int shift = 10;
	if (x > rcClient.left + shift && x < rcClient.right - shift &&
		y > rcClient.top + shift && y < rcClient.bottom - shift)
	{
		lstrcpy(caption, TEXT("inside"));
	}
	else if (x < rcClient.left + shift || x > rcClient.right - shift ||
		y < rcClient.top + shift || y > rcClient.bottom - shift)
	{
		lstrcpy(caption, TEXT("outside"));
	}
	else
	{
		lstrcpy(caption, TEXT("border"));
	}

	SetWindowText(hWnd, caption);
}