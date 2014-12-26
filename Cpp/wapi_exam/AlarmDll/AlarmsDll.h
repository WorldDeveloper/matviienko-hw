#include <Windows.h>
#include "IOrganizer.h"
#include <string>


class Alarms : public IOrganizer
{

	std::wstring GetPluginName() const { return L"Alarms"; }
	void SetWindow(HWND destWindow);
	bool AddItem();
	bool EditItem(const int id);
	bool DeleteItem(const int id);

	void ShowSingleItem(const int id) const;
	void ShowAllItems() const;
public:
	Alarms(HWND pluginWindow);
};