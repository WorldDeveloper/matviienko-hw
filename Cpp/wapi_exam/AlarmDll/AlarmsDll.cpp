#include "AlarmsDll.h"

Alarms::Alarms(HWND pluginWindow)
{
	mPluginWindow = pluginWindow;

	RECT rcClient;
	GetClientRect(mPluginWindow, &rcClient);
	mhList = CreateWindowEx(WS_EX_CLIENTEDGE, L"LISTBOX", NULL,
		WS_CHILD | WS_VISIBLE, 0, 0, rcClient.right, rcClient.bottom, mPluginWindow, 0, GetModuleHandle(0), 0);
}

void Alarms::SetWindow(HWND destWindow)
{

}

bool Alarms::AddItem()
{

	return true;
}

bool Alarms::EditItem(const int id)
{
	return true;
}
bool Alarms::DeleteItem(const int id)
{
	return true;
}

void Alarms::ShowSingleItem(const int id) const
{
	
}

void Alarms::ShowAllItems() const
{

}



extern "C" __declspec(dllexport) IOrganizer* CreatePlugin(HWND pluginWindow)
{
	return new Alarms(pluginWindow);
}

extern "C" __declspec(dllexport) void FreePlugin(IOrganizer* pPlugin)
{
	delete pPlugin;
}