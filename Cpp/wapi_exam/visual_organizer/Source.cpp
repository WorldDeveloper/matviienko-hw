#include <Windows.h>
#include <tchar.h>
#include <iostream>


#include <CommCtrl.h>
#pragma comment(lib,"comctl32.lib")
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include "resource.h"


LRESULT CALLBACK FrameWndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK MDIChildWndProc(HWND, UINT, WPARAM, LPARAM);

void CreateMenu(HWND hWnd);
void CreateToolbar(HWND hWnd);
void CreateStatusbar(HWND hWnd);
void ReSize(HWND hWnd, HWND hClient);


TCHAR szClassWindow[] = TEXT("Organizer");
TCHAR szChildWindow[] = TEXT("ChildWindow");
HWND hMDIClient;
HWND hMDIClientWnd2=0;

HWND hMDIClientWnd=0;
HWND hFrameWindow;
HINSTANCE hInstance;


INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int nCmdShow)
{
	HINSTANCE hInstance=hInst; 
	HWND hWnd;
	MSG lpMsg;
	WNDCLASSEX wcl;
	wcl.cbSize = sizeof(wcl);
	wcl.style = CS_HREDRAW | CS_VREDRAW;
	wcl.lpfnWndProc = FrameWndProc;
	wcl.cbClsExtra = 0;
	wcl.cbWndExtra = 0;
	wcl.hInstance = hInst;
	wcl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcl.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcl.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wcl.lpszMenuName = NULL;
	wcl.lpszClassName = szClassWindow;
	wcl.hIconSm = NULL;


	if (!RegisterClassEx(&wcl)) return 0;



	wcl.lpfnWndProc = MDIChildWndProc;
	wcl.lpszClassName = szChildWindow;
	wcl.lpszMenuName = NULL;
	wcl.hIconSm = NULL;

	if (!RegisterClassEx(&wcl)) return 0;




	hWnd = CreateWindow(szClassWindow, szClassWindow, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInst, NULL);
	hFrameWindow = hWnd;

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&lpMsg, NULL, 0, 0) > 0)
	{
		if (!TranslateMDISysAccel(hMDIClient, &lpMsg))
		{
			TranslateMessage(&lpMsg);
			DispatchMessage(&lpMsg);
		}
	}

	return lpMsg.wParam;
}

LRESULT CALLBACK FrameWndProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	switch (uMessage)
	{
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_FILE_NEW:
			
			hMDIClientWnd = CreateMDIWindow(szChildWindow, _T("Unknown Document"), WS_HSCROLL | WS_VSCROLL, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, hMDIClient, hInstance, 0);

			break;
		case ID_FILE_OPEN:
		{

			break;
		}
		case ID_FILE_SAVE:
		{
			HWND hChild = (HWND)SendMessage(hMDIClient, WM_MDIGETACTIVE, 0, 0);
			SendMessage(hMDIClient, WM_MDIRESTORE, (WPARAM)hChild, 0);
			break;
		}
		default:
				DefFrameProc(hWnd, hMDIClient, uMessage, wParam, lParam);
				break;
			
		}
		break;
	case WM_CREATE:
	{
		CreateMenu(hWnd);
		CreateToolbar(hWnd);
		CreateStatusbar(hWnd);

		CLIENTCREATESTRUCT ccs;
		memset(&ccs, 0, sizeof(CLIENTCREATESTRUCT));
		ccs.hWindowMenu = GetSubMenu(GetMenu(hWnd), 1);
		ccs.idFirstChild = ID_MDI_FIRSTCHILD;
		hMDIClient = CreateWindowEx(WS_EX_CLIENTEDGE, L"mdiclient", 0,
			WS_CHILD | WS_CLIPCHILDREN | WS_VSCROLL | WS_HSCROLL | WS_VISIBLE, 0, 50, 500, 500,
			hWnd, NULL, hInstance, (LPVOID)&ccs);
		ShowWindow(hMDIClient, SW_SHOW);

		break;
	}
		
	case WM_SIZE:
	{
		ReSize(hWnd, hMDIClient);
	}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefFrameProc(hWnd, hMDIClient,  uMessage, wParam, lParam);
	}
	return 0;
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


void CreateMenu(HWND hWnd)
{
	HMENU hMenu, hSubMenu;
	hMenu = CreateMenu();
		   hSubMenu = CreatePopupMenu();
		   AppendMenu(hSubMenu, MF_STRING, ID_FILE_NEW, _T("&New"));
		   AppendMenu(hSubMenu, MF_STRING, ID_FILE_OPEN, _T("&Open"));
		   AppendMenu(hSubMenu, MF_STRING, ID_FILE_SAVE, _T("&Save"));
		   AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, TEXT("&File"));
		   
		   hSubMenu = CreatePopupMenu();
		   AppendMenu(hSubMenu, MF_STRING, ID_NAV_CALENDAR, _T("&Calendar"));
		   AppendMenu(hSubMenu, MF_STRING, ID_NAV_NOTE, _T("N&ote"));
		   AppendMenu(hSubMenu, MF_STRING, ID_NAV_ALARM, _T("&Alarm"));
		   AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, _T("&Navigation"));
		   SetMenu(hWnd, hMenu);
}

void CreateToolbar(HWND hWnd)
{
	InitCommonControls();
	HWND hTool = CreateWindowEx(0, TOOLBARCLASSNAME, NULL, WS_CHILD | WS_VISIBLE, 0, 0, 0, 0, hWnd,(HMENU)IDC_MAIN_TOOL, GetModuleHandle(NULL), NULL);

	SendMessage(hTool, TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0);
	
	
	TBBUTTON tbb[2];
	TBADDBITMAP tbab;

	tbab.hInst = HINST_COMMCTRL;
	tbab.nID = IDB_STD_LARGE_COLOR;
	SendMessage(hTool, TB_ADDBITMAP, 0, (LPARAM)&tbab);


	ZeroMemory(tbb, sizeof(tbb));
	tbb[0].iBitmap = STD_FILEOPEN;
	tbb[0].fsState = TBSTATE_ENABLED;
	tbb[0].fsStyle = TBSTYLE_BUTTON;
	tbb[0].idCommand = ID_FILE_OPEN;

	tbb[1].iBitmap = STD_FILESAVE;
	tbb[1].fsState = TBSTATE_ENABLED;
	tbb[1].fsStyle = TBSTYLE_BUTTON;
	tbb[1].idCommand = ID_FILE_SAVE;

	SendMessage(hTool, TB_ADDBUTTONS, sizeof(tbb) / sizeof(TBBUTTON), (LPARAM)&tbb);
}

void CreateStatusbar(HWND hWnd)
{
	InitCommonControls(); 
	HWND hStatus = CreateWindowEx(0, STATUSCLASSNAME, NULL, WS_CHILD | WS_VISIBLE | SBARS_SIZEGRIP, 0, 0, 0, 0,
		hWnd, (HMENU)IDC_MAIN_STATUS, GetModuleHandle(NULL), NULL);

	int statWidths[] = { 100,200, -1};

	SendMessage(hStatus, SB_SETPARTS, sizeof(statWidths) / sizeof(int), (LPARAM)statWidths);
	SendMessage(hStatus, SB_SETTEXT, 1, (LPARAM)TEXT("Hi there"));
}

void ReSize(HWND hWnd, HWND hClient)
{
	HWND hTool;
	RECT rcTool;
	int iToolHeight;

	HWND hStatus;
	RECT rcStatus;
	int iStatusHeight;


	RECT rcClient; 
	int iEditHeight;

	hTool = GetDlgItem(hWnd, IDC_MAIN_TOOL);
	SendMessage(hTool, TB_AUTOSIZE, 0, 0);

	GetWindowRect(hTool, &rcTool);
	iToolHeight = rcTool.bottom - rcTool.top;

	hStatus = GetDlgItem(hWnd, IDC_MAIN_STATUS);
	SendMessage(hStatus, WM_SIZE, 0, 0);

	GetWindowRect(hStatus, &rcStatus);
	iStatusHeight = rcStatus.bottom - rcStatus.top;

	GetClientRect(hWnd, &rcClient);
	iEditHeight = rcClient.bottom - iToolHeight - iStatusHeight;


	SetWindowPos(hClient, NULL, 0, iToolHeight, rcClient.right, iEditHeight, SWP_NOZORDER);	
}
