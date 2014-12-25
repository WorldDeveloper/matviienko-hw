#include "FrameWnd.h"

LRESULT CALLBACK MDIChildWndProc(HWND, UINT, WPARAM, LPARAM);



TCHAR szClassWindow[] = L"Organizer";


FrameWnd frameWindow;

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int nCmdShow)
{
	
	HINSTANCE hInstance = hInst;
	HWND hWnd;
	MSG lpMsg;
	WNDCLASSEX wcl;
	wcl.cbSize = sizeof(wcl);
	wcl.style = CS_HREDRAW | CS_VREDRAW;


	
	wcl.lpfnWndProc = FrameWnd::WinProc;
	wcl.cbClsExtra = 0;
	wcl.cbWndExtra = 0;
	wcl.hInstance = hInst;
	wcl.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ORGANIZER32));
	wcl.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcl.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wcl.lpszMenuName = NULL;
	wcl.lpszClassName = szClassWindow;
	wcl.hIconSm = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ORGANIZER16));


	if (!RegisterClassEx(&wcl)) return 0;

	wcl.lpfnWndProc = MDIChildWndProc;
	wcl.lpszClassName = frameWindow.GetChildClassName();
	wcl.lpszMenuName = NULL;
	wcl.hIconSm = NULL;

	if (!RegisterClassEx(&wcl)) return 0;

	hWnd = CreateWindow(szClassWindow, szClassWindow, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInst, NULL);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&lpMsg, NULL, 0, 0) > 0)
	{
		if (!TranslateMDISysAccel(frameWindow.GetClient(), &lpMsg))
		{
			TranslateMessage(&lpMsg);
			DispatchMessage(&lpMsg);
		}
	}

	return lpMsg.wParam;
}


LRESULT CALLBACK MDIChildWndProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	switch (uMessage)
	{
		
	default:
		return DefMDIChildProc(hWnd, uMessage, wParam, lParam);
	}

	return 0;
}


