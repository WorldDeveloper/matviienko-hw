#pragma once
#include "Organizer.h"

const vector<string> const contactTitles = { "Surname", "Name", "Address", "Phone", "E-mail", "Notes" };

struct Contact
{
	long id;
	vector<string> data;
	bool operator==(const Contact& operand2) const 	{ return (data[0] + data[1] == operand2.data[0] + operand2.data[1]) && id == operand2.id; }
	bool operator!=(const Contact& operand2) const { return !(*this == operand2); }
	bool operator>(const Contact& operand2) const  { return (data[0] + data[1] > operand2.data[0] + operand2.data[1]); }
	bool operator<(const Contact& operand2) const	{ return (data[0] + data[1] < operand2.data[0] + operand2.data[1]); }
	bool operator>=(const Contact& operand2) const { return !(*this < operand2); }
	bool operator<=(const Contact& operand2) const { return !(*this > operand2); }
};

class Contacts :public Organizer
{
	vector<Contact> mContacts;
	vector<Contact>::iterator mSelectedContact;
	long mId;
	char* mDBname = "contacts";
public:
	Contacts() :mId(1)
	{
		OpenDB(mDBname);
		mSelectedContact = mContacts.begin();
	}
	virtual ~Contacts(){}

	bool AddDetails();
	bool EditDetails();
	bool DeleteDetails();

	int GetSize() const { return mContacts.size(); }
	int GetIndexOfSelectedItem() const;
	bool SetIndexOfSelectedItem(const int itemIndex);

	string GetItemInLine(const int itemIndex) const;
	string GetItemInWindow(const int itemIndex) const;

	void SaveDB(const char* name);
	void OpenDB(const char* name);
};
