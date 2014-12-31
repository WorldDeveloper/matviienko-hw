#include <string>
#include <ctime>

struct CalendarEvent
{
	std::wstring mName;
	std::wstring mDescription;
	std::wstring mWhere;
	time_t mFromDate;
	time_t mToDate;

	CalendarEvent() : mFromDate(0), mToDate(0)
	{}

	CalendarEvent(std::wstring name, std::wstring description, std::wstring where, time_t fromDate, time_t toDate)
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
	bool Empty() const { return mName.empty() || mFromDate <= 0 || mToDate <= 0; }
	void Clear()
	{
		mName.clear();
		mDescription.clear();
		mWhere.clear();
		mFromDate = 0;
		mToDate = 0;
	}
};