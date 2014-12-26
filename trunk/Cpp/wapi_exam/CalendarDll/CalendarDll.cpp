#include "CalendarDll.h"
Calendar::Calendar(HWND pluginWindow)
{
	mPluginWindow = pluginWindow;

	RECT rcClient;
	GetClientRect(mPluginWindow, &rcClient);
	mhList = CreateWindowEx(WS_EX_CLIENTEDGE, L"LISTBOX", NULL,
		WS_CHILD | WS_VISIBLE, 0, 0, rcClient.right, rcClient.bottom, mPluginWindow, 0, GetModuleHandle(0), 0);
}

void Calendar::SetWindow(HWND destWindow)
{

}

bool Calendar::AddItem()
{

	return true;
}

bool Calendar::EditItem(const int id)
{
	return true;
}
bool Calendar::DeleteItem(const int id)
{
	return true;
}

void Calendar::ShowSingleItem(const int id) const
{

}

void Calendar::ShowAllItems() const
{

}




extern "C" __declspec(dllexport) IOrganizer* CreatePlugin(HWND pluginWindow)
{
	return new Calendar(pluginWindow);
}

extern "C" __declspec(dllexport) void FreePlugin(IOrganizer* pPlugin)
{
	delete pPlugin;
}