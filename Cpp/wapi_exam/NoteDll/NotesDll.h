#include <Windows.h>
#include "IOrganizer.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <codecvt>

using namespace std;

class Notes : public IOrganizer
{	
	HWND mPluginWindow;
	vector<wstring> mNotes;
	int mId;
	char* mDBname = "notes";



	wstring GetPluginName() const { return L"Notes"; }
	void SetWindow(HWND destWindow);
	HWND GetPluginWindow() const { return mPluginWindow; }
	bool AddItem();
	bool EditItem(const int id);
	bool DeleteItem(const int id);

	void ShowSingleItem(const int id) const;
	void ShowAllItems() const;

	void OpenDB();
	void SaveDB();
public:
	Notes(HWND pluginWindow);
};