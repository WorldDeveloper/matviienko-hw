#include "Contacts.h"

bool Contacts::AddDetails()
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
	if (contact.data[0].empty() && contact.data[1].empty()) return false;

	mContacts.push_back(contact);
	sort(mContacts.begin(), mContacts.end());
	mSelectedContact = find(mContacts.begin(), mContacts.end(), contact);

	SaveDB(mDBname);
	return true;
}

bool Contacts::EditDetails()
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
	if (contact.data[0].empty() && contact.data[1].empty()) return false;

	*mSelectedContact = contact;
	sort(mContacts.begin(), mContacts.end());
	mSelectedContact = find(mContacts.begin(), mContacts.end(), contact);

	SaveDB(mDBname);
	return true;
}

bool Contacts::DeleteDetails()
{
	if (mContacts.empty()) return false;

	mSelectedContact = mContacts.erase(mSelectedContact);
	if (mSelectedContact == mContacts.end() && !mContacts.empty()) mSelectedContact--;

	SaveDB(mDBname);
	return true;
}


int Contacts::GetIndexOfSelectedItem() const
{
	if (mContacts.empty()) return -1;

	return mSelectedContact - mContacts.begin();
}

string Contacts::GetItemInLine(const int itemIndex) const
{
	if (mContacts.empty() || itemIndex < 0 || itemIndex >= mContacts.size()) throw "out of range";

	return mContacts[itemIndex].data[0].substr(0, 35) + " " + mContacts[itemIndex].data[1];
}

string Contacts::GetItemInWindow(const int itemIndex) const
{
	if (mContacts.empty() || itemIndex < 0 || itemIndex >= mContacts.size()) throw "out of range";
	string output;
	for (int i = 0; i < contactTitles.size(); ++i)
	{
		output += "\n " + contactTitles[i] + ": " + mContacts[itemIndex].data[i] + "\n";
	}
	return output;
}

bool Contacts::SetIndexOfSelectedItem(const int itemIndex)
{
	if (mContacts.empty() || itemIndex < 0 || itemIndex >= mContacts.size()) return false;

	mSelectedContact = mContacts.begin() + itemIndex;
	return true;
}

void Contacts::SaveDB(const char* name)
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

void Contacts::OpenDB(const char* name)
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



