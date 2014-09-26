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
	bool SetDetails(Event& event)
	{		
		event.id = mId++;
		
		cout << "\n Event name: ";
		fflush(stdin);
		getline(cin, event.eventName);

		cout << "\n Begin date...";
		SetDate(event.fromDate);

		cout << "\n Begin time...";
		SetTime(event.fromTime);

		cout << "\n End date...";
		SetDate(event.toDate);

		cout << "\n End time...";
		SetTime(event.toTime);

		if (event.fromDate > event.toDate ||
			(event.fromDate == event.toDate && event.fromTime > event.toTime)) return false;

		fflush(stdin);
		cout << "\n Where: ";
		getline(cin, event.where);

		cout << "\n Event description: ";
		getline(cin, event.desctiption);

		return true;
	}

	void SetDate(Date& date)
	{
		while (true)
		{
			cout << "\n\tYear: ";
			short year;
			cin >> year;

			cout << "\tMonth: ";
			short month;
			cin >> month;

			cout << "\tDay: ";
			short day;
			cin >> day;

			if (date.SetDate(year, month, day)) break;
			else cout << "Error: incorrect date. Enter correct date.\n";
		}
	}
	void SetTime(Time& time)
	{
		while (true)
		{
			cout << "\n\tHour: ";
			short hour;
			cin >> hour;

			cout << "\tMinute: ";
			short minute;
			cin >> minute;

			if (time.SetTime(hour, minute)) break;
			else cout << "Error: incorrect time. Enter correct time.\n";
		}
	}
public:
	Events():mId(1){
		OpenDB(mDBname);
		if (mEvents.size()) Today();
	}
	bool AddDetails()
	{
		cout << "Fill in the following fields\n\n";
		Event event;
		if (!SetDetails(event)) return false;

		mEvents.push_back(event);
		sort(mEvents.begin(), mEvents.end());
		mSelectedEvent = find(mEvents.begin(), mEvents.end(), event);

		SaveDB(mDBname);
		return true;
	}
	bool EditDetails()
	{
		if (mEvents.empty()) return false;

		cout << "Edit the following fields\n\n";
		Event event;
		if (!SetDetails(event)) return false;

		*mSelectedEvent = event;
		sort(mEvents.begin(), mEvents.end());
		mSelectedEvent = find(mEvents.begin(), mEvents.end(), event);

		SaveDB(mDBname);
		return true;
	}

	bool DeleteDetails()
	{
		if (mEvents.empty()) return false;

		mSelectedEvent = mEvents.erase(mSelectedEvent);
		if (mSelectedEvent == mEvents.end() && !mEvents.empty()) mSelectedEvent--;

		SaveDB(mDBname);
		return true;
	}
	int GetSize() const { return mEvents.size(); }
	int GetIndexOfSelectedItem() const
	{
		if (mEvents.empty()) return -1;

		return mSelectedEvent - mEvents.begin();
	}
	string GetItemInLine(const int itemIndex) const
	{
		if (mEvents.empty() || itemIndex < 0 || itemIndex >= mEvents.size()) throw "out of range";

		vector<Event>::const_iterator item= mEvents.begin()+itemIndex;
		string output= item->fromDate.GetDate();
		if (itemIndex && item->fromDate==(item-1)->fromDate)
		{
			output = "          ";
		}

		output += "  "+item->fromTime.GetTime();
		output += "  " + item->eventName.substr(0, 55);

		return output;
	}

	string GetItemInWindow(const int itemIndex) const
	{
		if (mEvents.empty() || itemIndex < 0 || itemIndex >= mEvents.size()) throw "out of range";

		vector<Event>::const_iterator item = mEvents.begin() + itemIndex;
		string output = "From: " + item->fromDate.GetDate() + "  " + item->fromTime.GetTime();
		output += "\tTo: " + item->toDate.GetDate() + "  " + item->toTime.GetTime();
		output += "\n\n Event name: " + item->eventName;
		output += "\n\n Description: " + item->desctiption;
		output += "\n\n Where: " + item->where;

		return output;
	}

	bool SetIndexOfSelectedItem(const int itemIndex)
	{
		if (mEvents.empty() || itemIndex < 0 || itemIndex >= mEvents.size()) return false;

		mSelectedEvent = mEvents.begin() + itemIndex;
		return true;
	}
	virtual ~Events(){}

	void Today()
	{
		time_t rawtime;
		struct tm * timeinfo;
		time(&rawtime);
		timeinfo = localtime(&rawtime);
		Date today;
		today.SetDate(timeinfo->tm_year+1900, timeinfo->tm_mon+1, timeinfo->tm_mday);

		for (vector<Event>::iterator event=mEvents.begin(); event!= mEvents.end(); ++event)
		{
			mSelectedEvent = event; 
			if (event->fromDate >= today) break;
		}
	}

	void SaveDB(const char* name)
	{
		ofstream out(name);
		if (out.is_open())
		{
			for (vector<Event>::iterator event = mEvents.begin(); event != mEvents.end(); ++event)
			{
				out << event->id << "\n";
				out << event->eventName << "\n";
				out << event->fromDate.GetDate() << "\n";
				out << event->fromTime.GetTime() << "\n";
				out << event->toDate.GetDate() << "\n";
				out << event->toTime.GetTime() << "\n";
				out << event->where << "\n";
				out << event->desctiption << "\n";
			}
		}
		else
		{
			throw "unable to open file";
		}
		out.close();
	}

	void OpenDB(const char* name)
	{
		ifstream in(name);

		if (in.is_open())
		{
			while(!in.eof())
			{
				Event event;
				event.id = mId++;
				string tmp;
				if (!getline(in, tmp)) break;
				getline(in, event.eventName);
				
				getline(in, tmp);
				if (!event.fromDate.SetDate(tmp)) throw "reading error";

				getline(in, tmp);
				if (!event.fromTime.SetTime(tmp)) throw "reading error";

				getline(in, tmp);
				if (!event.toDate.SetDate(tmp)) throw "reading error";

				getline(in, tmp);
				if (!event.toTime.SetTime(tmp)) throw "reading error";

				getline(in, event.where);
				getline(in, event.desctiption);
				mEvents.push_back(event);
			}
			
		}
		else
		{
			throw "unable to open file.";
		}

		in.close();
	}
};

