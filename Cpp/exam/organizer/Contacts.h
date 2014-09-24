#pragma once
#include "Organizer.h"

const vector<string> const title = { "Surname", "Name", "Address", "Phone", "E-mail", "Notes" };

struct Contact
{	
	long id;
	vector<string> data;
	bool operator==(const Contact& operand2) const 	{return (data[0]+data[1] == operand2.data[0]+operand2.data[1]) && id==operand2.id; 	}
	bool operator!=(const Contact& operand2) const { return !(*this == operand2); }
	bool operator>(const Contact& operand2) const  { return (data[0]+data[1] > operand2.data[0]+operand2.data[1]); }
	bool operator<(const Contact& operand2) const	{ return (data[0]+data[1] < operand2.data[0]+operand2.data[1]); }
	bool operator>=(const Contact& operand2) const { return !(*this < operand2); }
	bool operator<=(const Contact& operand2) const { return !(*this > operand2); }
};

class Contacts:public Organizer
{
	vector<Contact> mContacts;
	vector<Contact>::iterator mSelectedContact;
	long mId;
public:
	Contacts()
		:mId(0){}
	bool AddDetails()
	{		
		cout << "Fill in the following fields\n\n";
		Contact contact;
		contact.id = mId++;
		for (int i = 0; i < title.size(); ++i)
		{
			cout <<title[i]<<": ";
			string tmp;
			getline(cin, tmp);
			contact.data.push_back(tmp);
		}
		mContacts.push_back(contact);
		sort(mContacts.begin(), mContacts.end());
		mSelectedContact = find(mContacts.begin(), mContacts.end(), contact);
		
		return true;
	}
	bool EditDetails()
	{
		if (mContacts.empty()) return false;

		cout << "Edit the following fields\n\n";
		Contact contact;
		for (int i = 0; i < title.size(); ++i)
		{
			cout << title[i] << ": ";
			string tmp;
			getline(cin, tmp);
			contact.data.push_back(tmp);
		}
		*mSelectedContact = contact;
		sort(mContacts.begin(), mContacts.end());
		mSelectedContact = find(mContacts.begin(), mContacts.end(), contact);
		
		return true;
	}

	bool DeleteDetails()
	{
		if (mContacts.empty()) return false; 
		
		mSelectedContact = mContacts.erase(mSelectedContact);
		if (mSelectedContact == mContacts.end() && !mContacts.empty()) mSelectedContact--;
		return true;
	}
	int GetSize() const { return mContacts.size(); }
	int GetIndexOfSelectedItem() const 
	{
		if (mContacts.empty()) return -1;

		return mSelectedContact - mContacts.begin();
	}
	string GetItemInLine(const int itemIndex) const
	{
		if (mContacts.empty() || itemIndex < 0 || itemIndex >= mContacts.size()) throw "out of range";

		return mContacts[itemIndex].data[0].substr(0,35)+" "+mContacts[itemIndex].data[1];
	}

	string GetItemInWindow(const int itemIndex) const
	{
		if (mContacts.empty() || itemIndex < 0 || itemIndex >= mContacts.size()) throw "out of range";
		string output="\n";
		for (int i = 0; i < title.size(); ++i)
		{
			output += " "+title[i] + ": " + mContacts[itemIndex].data[i] + "\n";
		}
		return output;
	}
	
	bool SetIndexOfSelectedItem(const int itemIndex)
	{
		if (mContacts.empty() || itemIndex < 0 || itemIndex >= mContacts.size()) return false;

		mSelectedContact = mContacts.begin() + itemIndex;
		return true;
	}
	virtual ~Contacts(){}
};

