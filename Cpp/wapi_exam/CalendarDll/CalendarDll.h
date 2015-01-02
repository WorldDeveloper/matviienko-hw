
#include <Windows.h>
#include <fstream>
#include <codecvt>
#include <algorithm>

#include "IOrganizer.h"
#include "resource.h"
#include "CalendarDlg.h"




class Calendar : public IOrganizer
{
	HWND mPluginWindow;
	HWND mhList;

	std::vector<CalendarEvent> mEvents;
	wchar_t* mDBname = L"events";

	std::wstring GetPluginName() const { return L"Calendar"; }
	HWND GetPluginWindow() const { return mPluginWindow; }
	void SetPluginWindow(HWND hWnd);
	bool AddItem();
	bool EditItem();
	bool DeleteItem();

	void ShowSingleItem() const;
	void ShowAllItems() const;
	void ResizePlugin() const;

	void OpenDB();
	void SaveDB();

	int Today() const;

public:
	Calendar(HWND pluginWindow);
};