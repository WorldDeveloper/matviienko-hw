#include <string>
#include <ctime>
#include <sstream>

struct CalendarEvent
{
	std::wstring mName;
	std::wstring mDescription;
	std::wstring mWhere;
	time_t mFromDate;
	time_t mToDate;

	CalendarEvent();
	CalendarEvent(std::wstring name, std::wstring description, std::wstring where, time_t fromDate, time_t toDate);
	bool Empty() const { return mName.empty() || mFromDate <= 0 || mToDate <= 0; }
	void Clear();
	bool operator<(const CalendarEvent& operand2) const;
	bool operator>=(const CalendarEvent& operand2) const;

	time_t GetFromDate() const;
	std::wstring CalendarEvent::GetEventString() const;
	std::wstring CalendarEvent::GetEventShortString() const;
	std::wstring CalendarEvent::Format2Digit(const int number) const;
};