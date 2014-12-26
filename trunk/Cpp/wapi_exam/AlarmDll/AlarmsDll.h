#include <Windows.h>
#include "IOrganizer.h"
#include <string>

using namespace std;

class Alarms : public IOrganizer
{
	HWND mPluginWindow;
	HWND mhList;

	wstring GetPluginName() const { return L"Alarms"; }
	void SetWindow(HWND destWindow);
	HWND GetPluginWindow() const { return mPluginWindow; }
	bool AddItem();
	bool EditItem(const int id);
	bool DeleteItem(const int id);

	void ShowSingleItem(const int id) const;
	void ShowAllItems() const;
public:
	Alarms(HWND pluginWindow);
};