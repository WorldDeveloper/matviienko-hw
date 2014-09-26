#include "Notes.h"

Notes::Notes()
{
	OpenDB();
	mSelectedNote = mNotes.begin();
}

bool Notes::AddDetails()
{
	cout << " Add note: ";
	string tmp;
	fflush(stdin);
	getline(cin, tmp);

	if (tmp.empty()) return false;
	mNotes.push_back(tmp);
	mSelectedNote = --mNotes.end();
	
	SaveDB();
	return true;
}
bool Notes::EditDetails()
{
	if (mNotes.empty()) return false;

	cout << " Edit note:";
	string tmp;
	fflush(stdin);
	getline(cin, tmp);

	if (tmp.empty()) return false;
	*mSelectedNote = tmp;

	SaveDB();
	return true;
}

bool Notes::DeleteDetails()
{
	if (mNotes.empty()) return false;

	mSelectedNote = mNotes.erase(mSelectedNote);
	if (mSelectedNote == mNotes.end() && !mNotes.empty()) mSelectedNote--;

	SaveDB();
	return true;
}

int Notes::GetIndexOfSelectedItem() const
{
	if (mNotes.empty()) return -1;

	return mSelectedNote - mNotes.begin();
}

string Notes::GetItemInLine(const int itemIndex) const
{
	if (mNotes.empty() || itemIndex < 0 || itemIndex >= mNotes.size()) throw "out of range";

	return mNotes[itemIndex];
}

string Notes::GetItemInWindow(const int itemIndex) const
{
	if (mNotes.empty() || itemIndex < 0 || itemIndex >= mNotes.size()) throw "out of range";

	return mNotes[itemIndex];
}

bool Notes::SetIndexOfSelectedItem(const int itemIndex)
{
	if (mNotes.empty() || itemIndex < 0 || itemIndex >= mNotes.size()) return false;

	mSelectedNote = mNotes.begin() + itemIndex;
	return true;
}

void Notes::SaveDB()
{
	ofstream out(mDBname);
	if (out.is_open())
	{
		for (vector<string>::iterator note = mNotes.begin(); note != mNotes.end(); ++note)
		{
			out << *note << "\n";
		}
	}
	else
	{
		throw "unable to open file";
	}
	out.close();
}

void Notes::OpenDB()
{
	ifstream in(mDBname);

	if (in.is_open())
	{
		while (!in.eof())
		{
			string note;
			if (!getline(in, note)) break;
			mNotes.push_back(note);
		}
	}
	else
	{
		throw "unable to open file.";
	}

	in.close();
}