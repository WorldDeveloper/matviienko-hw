
#include <Windows.h>
#include "IOrganizer.h"
#include <string>
#include <vector>
#include <ctime>


struct Event
{
	std::wstring mName;
	std::wstring mDescription;
	std::wstring mWhere;
	tm mFromDate;
	tm mToDate;

	Event(std::wstring name, std::wstring description, std::wstring where, tm fromDate, tm toDate)
	{
		mFromDate = { 0 };
		mToDate = { 0 };

		if (name.empty()) throw "empty event name";

		time_t difference = mktime(&toDate) - mktime(&fromDate);
		if (!fromDate.tm_year || !toDate.tm_year || difference<0) throw "incorrect date";

		mName = name;
		mDescription = description;
		mWhere = where;
		mFromDate = fromDate;
		mToDate = toDate;
	}
};




class Calendar : public IOrganizer
{
	HWND mPluginWindow;
	HWND mhList;

	std::vector<Event> mEvents;
	char* mDBname = "events";

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