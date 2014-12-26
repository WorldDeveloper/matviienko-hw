#include "FrameWnd.h"
#include "IOrganizer.h"

typedef IOrganizer*(*PluginMaker)();
typedef void(*PluginReleaser)(IOrganizer*);


FrameWnd* FrameWnd::handler = nullptr;
HWND FrameWnd::mhMdiClient = NULL;
HWND FrameWnd:: mhCalendar = NULL;
HWND FrameWnd:: mhNote = NULL;
HWND FrameWnd:: mhAlarm = NULL;

FrameWnd::FrameWnd() 
{
	handler = this;
	wcscpy(szChildWindow,  L"ChildWindow");
}

LRESULT CALLBACK FrameWnd::WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hWnd, WM_CLOSE, handler->Cls_OnClose);
		HANDLE_MSG(hWnd, WM_CREATE, handler->Cls_OnCreate);
		HANDLE_MSG(hWnd, WM_COMMAND, handler->Cls_OnCommand);
		HANDLE_MSG(hWnd, WM_SIZE, handler->Cls_OnSize);

	default:
		return DefFrameProc(hWnd, mhMdiClient, message, wParam, lParam);
	}

	return FALSE;
}

void FrameWnd::Cls_OnClose(HWND hWnd)
{
	for (HINSTANCE hInst : mModules)
		FreeLibrary(hInst); 
	
	PostQuitMessage(0);
}

BOOL FrameWnd::Cls_OnCreate(HWND hWnd, LPCREATESTRUCT lpCreateStruct)
{
	mhWnd = hWnd;
	mhInst = GetModuleHandle(0);

	InitCommonControls();

	CreateMainMenu(hWnd);
	CreateToolbar(hWnd);
	CreateStatusbar(hWnd);
	
	CLIENTCREATESTRUCT ccs;
	memset(&ccs, 0, sizeof(CLIENTCREATESTRUCT));
	ccs.idFirstChild = ID_MDI_FIRSTCHILD;
	mhMdiClient = CreateWindowEx(WS_EX_CLIENTEDGE, L"mdiclient", 0,
				WS_CHILD | WS_CLIPCHILDREN | WS_VSCROLL | WS_HSCROLL | WS_VISIBLE, 0, 50, 500, 500,
				hWnd, NULL, mhInst, (LPVOID)&ccs);
	ShowWindow(mhMdiClient, SW_SHOW);

	return TRUE;
}

void FrameWnd::Cls_OnCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify)
{
	switch (id)
	{
	case ID_PAGE_CALENDAR:
		if (!mhCalendar) mhCalendar = CreateChildWindow(L"Calendar");
		else
		{
			SetFocus(mhCalendar);
			HWND butt = CreateWindowEx(WS_EX_CLIENTEDGE, L"Button", L"Button",
				WS_CHILD | WS_VISIBLE, 50, 50, 100, 50, mhCalendar, 0, mhInst, 0);
		}
		break;
	case ID_PAGE_NOTE:
	{
		if (!mhNote) mhNote = CreateChildWindow(L"Notes");
		else
		{
			SetFocus(mhNote);
		}
		break;
	}
	case ID_PAGE_ALARM:
		if (!mhAlarm) mhAlarm = CreateChildWindow(L"Alarms");
		else
		{			
			SetFocus(mhAlarm);
		}
		break;
	case ID_ACTION_ADD:
		try
		{
			if (LoadPlugins()) MessageBox(hWnd, std::to_wstring(mModules.size()).c_str(), NULL, MB_OK);
			else MessageBox(hWnd, L"There is no plugins!", NULL, MB_OK);

			for (int i = 0; i < mModules.size(); ++i)
			{
				PluginMaker MakerFunc = (PluginMaker)GetProcAddress(mModules[i], "CreatePlugin");
				PluginReleaser ReleaserFunc = (PluginReleaser)GetProcAddress(mModules[i], "FreePlugin");

				IOrganizer* pCalendar = MakerFunc();
				MessageBox(hWnd, pCalendar->GetPluginName().c_str(), NULL, MB_OK);

			}

		}
		catch (wchar_t* err)
		{
			MessageBox(hWnd, err, NULL, MB_OK|MB_ICONERROR);
		}
		break;
	default: return (void)DefFrameProc(hWnd, mhMdiClient, WM_COMMAND, MAKEWPARAM(id,codeNotify) , (LPARAM)hwndCtl);
	}

}

void FrameWnd::Cls_OnSize(HWND hwnd, UINT state, int cx, int cy)
{
	ReSize(hwnd, mhMdiClient);
}

void FrameWnd::CreateMainMenu(HWND hWnd)
{
	HMENU hMenu, hSubMenu;
	hMenu = CreateMenu();
		   hSubMenu = CreatePopupMenu();
		   AppendMenu(hSubMenu, MF_STRING, ID_PAGE_CALENDAR, L"&Calendar");
		   AppendMenu(hSubMenu, MF_STRING, ID_PAGE_NOTE, L"&Notes");
		   AppendMenu(hSubMenu, MF_STRING, ID_PAGE_ALARM, L"&Alarms");
		   AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, L"&Navigation");
		   
		   hSubMenu = CreatePopupMenu();
		   AppendMenu(hSubMenu, MF_STRING, ID_ACTION_ADD, L"&Add");
		   AppendMenu(hSubMenu, MF_STRING, ID_ACTION_EDIT, L"&Edit");
		   AppendMenu(hSubMenu, MF_STRING, ID_ACTION_DELETE, L"&Delete");
		   AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, L"&Action");
		   SetMenu(hWnd, hMenu);
}

void FrameWnd::CreateToolbar(HWND hWnd)
{
	InitCommonControls();
	HWND hTool = CreateWindowEx(0, TOOLBARCLASSNAME, NULL, WS_CHILD | WS_VISIBLE | TBSTYLE_FLAT,  0, 0, 0, 0, hWnd, (HMENU)IDC_MAIN_TOOL, GetModuleHandle(NULL), NULL);

	SendMessage(hTool, TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0);
	
	HIMAGELIST hImg = ImageList_Create(64, 64, ILC_COLOR32 | ILC_MASK, 10, 10);
	for (int i = 0; i < 6; ++i)
	{
		ImageList_AddIcon(hImg, LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_CALENDAR+i)));
	}

	SendMessage(hTool, TB_SETIMAGELIST, (WPARAM)0, (LPARAM)hImg);

	TBBUTTON tbb[7];
	ZeroMemory(tbb, sizeof(tbb));

	const wchar_t toolTip[6][10] = { L"Calendar", L"Notes", L"Alarms", L"Add", L"Edit", L"Delete" };
	int bitmap = 0;
	for (int i = 0; i < 7; ++i)
	{
		if (i == 3)
		{
			tbb[3].iBitmap = 0;
			tbb[3].fsState = 0;
			tbb[3].fsStyle = TBSTYLE_SEP;
			tbb[3].idCommand = 0;
			continue;
		}
		tbb[i].iBitmap = bitmap;// ++
		tbb[i].fsState = TBSTATE_ENABLED;
		tbb[i].fsStyle = TBSTYLE_BUTTON;
		tbb[i].idCommand = ID_PAGE_CALENDAR+bitmap;
		tbb[i].iString = (INT_PTR)toolTip[bitmap++];
	}

	SendMessage(hTool, TB_ADDBUTTONS, sizeof(tbb) / sizeof(TBBUTTON), (LPARAM)&tbb);
}

void FrameWnd::CreateStatusbar(HWND hWnd)
{
	InitCommonControls(); 
	HWND hStatus = CreateWindowEx(0, STATUSCLASSNAME, NULL, WS_CHILD | WS_VISIBLE | SBARS_SIZEGRIP, 0, 0, 0, 0,
		hWnd, (HMENU)IDC_MAIN_STATUS, GetModuleHandle(NULL), NULL);

	int statWidths[] = { 100,200, -1};

	SendMessage(hStatus, SB_SETPARTS, sizeof(statWidths) / sizeof(int), (LPARAM)statWidths);
	SendMessage(hStatus, SB_SETTEXT, 1, (LPARAM)TEXT("Hi there"));
}

void FrameWnd::ReSize(HWND hWnd, HWND hClient)
{
	HWND hTool;
	RECT rcTool;
	int iToolHeight;

	HWND hStatus;
	RECT rcStatus;
	int iStatusHeight;


	RECT rcClient; 
	int iClientHeight;

	hTool = GetDlgItem(hWnd, IDC_MAIN_TOOL);
	SendMessage(hTool, TB_AUTOSIZE, 0, 0);

	GetWindowRect(hTool, &rcTool);
	iToolHeight = rcTool.bottom - rcTool.top;

	hStatus = GetDlgItem(hWnd, IDC_MAIN_STATUS);
	SendMessage(hStatus, WM_SIZE, 0, 0);

	GetWindowRect(hStatus, &rcStatus);
	iStatusHeight = rcStatus.bottom - rcStatus.top;

	GetClientRect(hWnd, &rcClient);
	iClientHeight = rcClient.bottom - iToolHeight - iStatusHeight;


	SetWindowPos(hClient, NULL, 0, iToolHeight, rcClient.right, iClientHeight, SWP_NOZORDER);	
}

HWND FrameWnd::CreateChildWindow(wchar_t* title)
{
	return CreateMDIWindow(szChildWindow, title, WS_HSCROLL | WS_VSCROLL, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, mhMdiClient, mhInst, 0);
}


bool FrameWnd::LoadPlugins()
{
	mModules.clear();

	wchar_t buffer[MAX_PATH];
	GetModuleFileName(NULL, buffer, MAX_PATH);
	std::wstring::size_type pos = std::wstring(buffer).find_last_of(L"\\/");
	
	std::wstring pluginDir = std::wstring(buffer).substr(0, pos) + L"\\";	
	std::wstring mask = pluginDir+L"*.dll";

	_wfinddata_t fileinfo;
	long result = _wfindfirst(mask.c_str(), &fileinfo);
	long findNext = result;

	while (findNext != -1)
	{
		HMODULE mod = LoadLibrary((pluginDir + std::wstring(fileinfo.name)).c_str());

		if (!mod)
		{
			throw (L"Library " + std::wstring(fileinfo.name) + L" wasn't loaded successfully!").c_str();
			continue;
		}
		mModules.push_back(mod);
		findNext = _wfindnext(result, &fileinfo);
	}
	_findclose(result);
	
	return true;
}

