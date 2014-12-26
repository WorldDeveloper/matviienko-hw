
#include <Windows.h>
#include "IOrganizer.h"
#include <string>


class Calendar : public IOrganizer
{
	HWND mPluginWindow;
	HWND mhList;

	std::wstring GetPluginName() const { return L"Calendar"; }
	void SetWindow(HWND destWindow);
	HWND GetPluginWindow() const { return mPluginWindow; }
	bool AddItem();
	bool EditItem(const int id);
	bool DeleteItem(const int id);

	void ShowSingleItem(const int id) const;
	void ShowAllItems() const;
public:
	Calendar(HWND pluginWindow);
};