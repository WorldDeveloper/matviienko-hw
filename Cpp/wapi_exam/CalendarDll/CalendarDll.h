
#include <Windows.h>
#include <fstream>
#include <codecvt>

#include "IOrganizer.h"
#include "Event.h"
#include "resource.h"
#include "CalendarDlg.h"




class Calendar : public IOrganizer
{
	HWND mPluginWindow;
	HWND mhList;

	std::vector<Event> mEvents;
	char* mDBname = "events";

	std::wstring GetPluginName() const { return L"Calendar"; }
	HWND GetPluginWindow() const { return mPluginWindow; }
	void SetPluginWindow(HWND hWnd);
	bool AddItem();
	bool EditItem();
	bool DeleteItem();

	void ShowSingleItem() const;
	void ShowAllItems() const;
	void ResizePlugin() const;

	void OpenDB(const char* name);
	void SaveDB(const char* name);

public:
	Calendar(HWND pluginWindow);
	//static BOOL CALLBACK CalendarDlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};