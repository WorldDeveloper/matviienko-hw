#pragma once
#include "Organizer.h"
#include "Date.h";
#include "Time.h";

struct Event
{
	long id;
	string eventName;
	Date fromDate;
	Time fromTime;
	Date toDate;
	Time toTime;
	string where;
	string desctiption;
	string CompareString() const { return fromDate.GetDate() + fromTime.GetTime() + eventName; }
	bool operator==(const Event& operand2) const 	{ return id == operand2.id; }
	bool operator!=(const Event& operand2) const { return !(*this == operand2); }
	bool operator>(const Event& operand2) const  { return CompareString() > operand2.CompareString(); }
	bool operator<(const Event& operand2) const	{ return CompareString() < operand2.CompareString(); }
	bool operator>=(const Event& operand2) const { return !(*this < operand2); }
	bool operator<=(const Event& operand2) const { return !(*this > operand2); }
};

class Events :public Organizer
{
	vector<Event> mEvents;
	vector<Event>::iterator mSelectedEvent;
	char* mDBname = "events";
	long mId;

	bool SetDetails(Event& event);
	void SetDate(Date& date);
	void SetTime(Time& time);
public:
	Events():mId(1){
		OpenDB(mDBname);
		if (mEvents.size()) Today();
	}
	virtual ~Events(){}

	bool AddDetails();
	bool EditDetails();
	bool DeleteDetails();

	int GetSize() const { return mEvents.size(); }
	int GetIndexOfSelectedItem() const;
	bool SetIndexOfSelectedItem(const int itemIndex);

	string GetItemInLine(const int itemIndex) const;
	string GetItemInWindow(const int itemIndex) const;

	void Today();

	void SaveDB(const char* name);
	void OpenDB(const char* name);
};

