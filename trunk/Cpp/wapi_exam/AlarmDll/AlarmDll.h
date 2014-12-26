#include <Windows.h>
#include "IOrganizer.h"
#include <string>


class Alarm : public IOrganizer
{
private:
	std::wstring GetPluginName() const { return L"Alarm"; }
	void SetWindow(HWND destWindow);
	bool AddItem();
	bool EditItem(const int id);
	bool DeleteItem(const int id);

	void ShowSingleItem(const int id) const;
	void ShowAllItems() const;
};