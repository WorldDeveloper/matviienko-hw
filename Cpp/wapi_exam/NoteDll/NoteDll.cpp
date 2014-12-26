#include "NoteDll.h"

void Note::SetWindow(HWND destWindow)
{

}

bool Note::AddItem()
{
	MessageBoxA(NULL, "This is calculator plugin", "About plugin", MB_OK | MB_ICONINFORMATION);
	return true;
}

bool Note::EditItem(const int id)
{
	return true;
}
bool Note::DeleteItem(const int id)
{
	return true;
}

void Note::ShowSingleItem(const int id) const
{
	
}

void Note::ShowAllItems() const
{

}


extern "C" __declspec(dllexport) IOrganizer* CreatePlugin()
{
	return new Note;
}

extern "C" __declspec(dllexport) void FreePlugin(IOrganizer* pPlugin)
{
	delete pPlugin;
}