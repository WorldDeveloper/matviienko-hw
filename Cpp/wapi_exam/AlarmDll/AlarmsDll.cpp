#include "AlarmsDll.h"

Alarms::Alarms(HWND pluginWindow)
{
	mPluginWindow = pluginWindow;
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