#include <string>
#include <ctime>

struct Event
{
	std::wstring mName;
	std::wstring mDescription;
	std::wstring mWhere;
	time_t mFromDate;
	time_t mToDate;

	Event(std::wstring name, std::wstring description, std::wstring where, time_t fromDate, time_t toDate)
	{
		mFromDate = { 0 };
		mToDate = { 0 };

		if (name.empty()) throw L"empty event name";

		if (!fromDate || !toDate || toDate - fromDate<0) throw L"incorrect date/time";

		mName = name;
		mDescription = description;
		mWhere = where;
		mFromDate = fromDate;
		mToDate = toDate;
	}
};