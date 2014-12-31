#include <Windows.h>
#include <string>
#include <fstream>
#include <codecvt>
#include <algorithm>

#include "IOrganizer.h"
#include "resource.h"
#include "AlarmDlg.h"

using namespace std;

class Alarms : public IOrganizer
{
	HWND mPluginWindow;
	HWND mhList;
	vector<time_t> mAlarms;
	wchar_t* mDBname = L"alarms";
	
	wstring GetPluginName() const { return L"Alarms"; }
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

	std::wstring Format2Digit(const int number) const;
	std::wstring GetTimeString(const time_t alarm) const;
public:
	Alarms(HWND pluginWindow);
};