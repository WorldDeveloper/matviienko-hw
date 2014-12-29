#include <Windows.h>
#include "IOrganizer.h"
#include "resource.h"
#include "AlarmDlg.h"
#include <string>

using namespace std;

class Alarms : public IOrganizer
{
	HWND mPluginWindow;
	HWND mhList;

	wstring GetPluginName() const { return L"Alarms"; }
	HWND GetPluginWindow() const { return mPluginWindow; }
	bool AddItem();
	bool EditItem();
	bool DeleteItem();

	void ShowSingleItem() const;
	void ShowAllItems() const;
	void ResizePlugin() const;
public:
	Alarms(HWND pluginWindow);
};