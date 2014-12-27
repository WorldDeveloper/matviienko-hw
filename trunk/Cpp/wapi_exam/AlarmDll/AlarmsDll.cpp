#include "AlarmsDll.h"

Alarms::Alarms(HWND pluginWindow)
{
	mPluginWindow = pluginWindow;

	RECT rcClient;
	GetClientRect(mPluginWindow, &rcClient);
	mhList = CreateWindowEx(WS_EX_CLIENTEDGE, L"LISTBOX", NULL,
		WS_CHILD | WS_VISIBLE | WS_VSCROLL, 0, 0, rcClient.right, rcClient.bottom, mPluginWindow, 0, GetModuleHandle(0), 0);
}


bool Alarms::AddItem()
{

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