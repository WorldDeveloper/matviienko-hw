#include "AlarmsDll.h"

void Alarm::SetWindow(HWND destWindow)
{

}

bool Alarm::AddItem()
{

	return true;
}

bool Alarm::EditItem(const int id)
{
	return true;
}
bool Alarm::DeleteItem(const int id)
{
	return true;
}

void Alarm::ShowSingleItem(const int id) const
{
	
}

void Alarm::ShowAllItems() const
{

}


extern "C" __declspec(dllexport) IOrganizer* CreatePlugin()
{
	return new Alarm;
}

extern "C" __declspec(dllexport) void FreePlugin(IOrganizer* pPlugin)
{
	delete pPlugin;
}