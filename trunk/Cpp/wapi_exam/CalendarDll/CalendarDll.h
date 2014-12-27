
#include <Windows.h>
#include "IOrganizer.h"
#include <string>


class Calendar : public IOrganizer
{
	HWND mPluginWindow;
	HWND mhList;

	std::wstring GetPluginName() const { return L"Calendar"; }
	HWND GetPluginWindow() const { return mPluginWindow; }
	bool AddItem();
	bool EditItem();
	bool DeleteItem();

	void ShowSingleItem() const;
	void ShowAllItems() const;
	void ResizePlugin() const;
public:
	Calendar(HWND pluginWindow);
};