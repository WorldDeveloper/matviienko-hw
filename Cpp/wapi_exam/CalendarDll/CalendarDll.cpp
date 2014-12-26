#include "CalendarDll.h"

void Calendar::SetWindow(HWND destWindow)
{

}

bool Calendar::AddItem()
{
	MessageBoxA(NULL, "This is calculator plugin", "About plugin", MB_OK | MB_ICONINFORMATION);
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


extern "C" __declspec(dllexport) IOrganizer* CreatePlugin()
{
	return new Calendar;
}

extern "C" __declspec(dllexport) void FreePlugin(IOrganizer* pPlugin)
{
	delete pPlugin;
}