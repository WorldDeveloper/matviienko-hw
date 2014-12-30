#include "AlarmsDll.h"

HINSTANCE hInst = NULL;

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
	)
{
	hInst = (HINSTANCE)hModule;
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}


Alarms::Alarms(HWND pluginWindow)
{
	mPluginWindow = pluginWindow;

	RECT rcClient;
	GetClientRect(mPluginWindow, &rcClient);
	mhList = CreateWindowEx(WS_EX_CLIENTEDGE, L"LISTBOX", NULL,
		WS_CHILD | WS_VISIBLE | WS_VSCROLL, 0, 0, rcClient.right, rcClient.bottom, mPluginWindow, 0, GetModuleHandle(0), 0);
}

void Alarms::SetPluginWindow(HWND hWnd)
{
	mPluginWindow = hWnd;

	RECT rcClient;
	GetClientRect(mPluginWindow, &rcClient);
	mhList = CreateWindowEx(WS_EX_CLIENTEDGE, L"LISTBOX", NULL,
		WS_CHILD | WS_VISIBLE | WS_VSCROLL, 0, 0, rcClient.right, rcClient.bottom, mPluginWindow, 0, GetModuleHandle(0), 0);
}


bool Alarms::AddItem()
{
	AlarmDlg dlg(L"Add");
	DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), mPluginWindow, AlarmDlg::DlgProc);

	return true;
}

bool Alarms::EditItem()
{
	return true;
}
bool Alarms::DeleteItem()
{
	return true;
}

void Alarms::ShowSingleItem() const
{

}

void Alarms::ShowAllItems() const
{

}

void Alarms::ResizePlugin() const
{
	RECT rcClient;
	GetClientRect(mPluginWindow, &rcClient);
	SetWindowPos(mhList, NULL, 0, 0, rcClient.right, rcClient.bottom, SWP_NOZORDER);
}



extern "C" __declspec(dllexport) IOrganizer* CreatePlugin(HWND pluginWindow)
{
	return new Alarms(pluginWindow);
}

extern "C" __declspec(dllexport) void FreePlugin(IOrganizer* pPlugin)
{
	delete pPlugin;
}