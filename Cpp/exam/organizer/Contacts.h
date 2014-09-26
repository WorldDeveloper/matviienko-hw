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
	bool AddDetails()
	{
		cout << "Fill in the following fields\n\n";
		Contact contact;
		contact.id = mId++;
		for (int i = 0; i < contactTitles.size(); ++i)
		{
			cout << "\n " << contactTitles[i] << ": ";
			string tmp;
			fflush(stdin);
			getline(cin, tmp);
			contact.data.push_back(tmp);
		}
		mContacts.push_back(contact);
		sort(mContacts.begin(), mContacts.end());
		mSelectedContact = find(mContacts.begin(), mContacts.end(), contact);

		SaveDB(mDBname);
		return true;
	}
	bool EditDetails()
	{
		if (mContacts.empty()) return false;

		cout << "Edit the following fields\n\n";
		Contact contact;
		contact.id = mId++;
		for (int i = 0; i < contactTitles.size(); ++i)
		{
			cout << "\n " << contactTitles[i] << ": ";
			string tmp;
			fflush(stdin);
			getline(cin, tmp);
			contact.data.push_back(tmp);
		}
		*mSelectedContact = contact;
		sort(mContacts.begin(), mContacts.end());
		mSelectedContact = find(mContacts.begin(), mContacts.end(), contact);

		SaveDB(mDBname);
		return true;
	}

	bool DeleteDetails()
	{
		if (mContacts.empty()) return false;

		mSelectedContact = mContacts.erase(mSelectedContact);
		if (mSelectedContact == mContacts.end() && !mContacts.empty()) mSelectedContact--;
		
		SaveDB(mDBname); 
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

		return mContacts[itemIndex].data[0].substr(0, 35) + " " + mContacts[itemIndex].data[1];
	}

	string GetItemInWindow(const int itemIndex) const
	{
		if (mContacts.empty() || itemIndex < 0 || itemIndex >= mContacts.size()) throw "out of range";
		string output;
		for (int i = 0; i < contactTitles.size(); ++i)
		{
			output += "\n " + contactTitles[i] + ": " + mContacts[itemIndex].data[i] + "\n";
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

	void SaveDB(const char* name)
	{
		ofstream out(name);
		if (out.is_open())
		{

			for (vector<Contact>::iterator contact = mContacts.begin(); contact != mContacts.end(); ++contact)
			{
				out << contact->id << '\n';
				for (int i = 0; i < contactTitles.size(); ++i)
				{
					out << contact->data[i] << '\n';
				}
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
			while (!in.eof())
			{
				Contact contact;
				contact.id = mId++;
				string tmp;
				if (!getline(in, tmp)) break;

				for (int i = 0; i < contactTitles.size(); ++i)
				{
					getline(in, tmp);
					contact.data.push_back(tmp);
				}
				mContacts.push_back(contact);
			}
		}
		else
		{
			throw "unable to open file.";
		}

		in.close();
	}
};

