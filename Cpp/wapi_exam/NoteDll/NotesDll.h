#include <Windows.h>
#include "IOrganizer.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <codecvt>
#include "NoteDlg.h"

using namespace std;

class Notes : public IOrganizer
{
	HWND mPluginWindow;
	HWND mhList;

	vector<wstring> mNotes;
	char* mDBname = "notes";

	wstring GetPluginName() const { return L"Notes"; }
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
public:
	Notes(HWND pluginWindow);
};