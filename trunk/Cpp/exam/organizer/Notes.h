#pragma once
#include "Organizer.h"
#include <vector>
#include <string>
using namespace std;

class Notes :public Organizer
{
	vector<string> mNotes;
	vector<string>::iterator mSelectedNote;
	char* mDBname = "notes";
public:
	Notes();
	bool AddDetails()
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
	bool EditDetails()
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

	bool DeleteDetails()
	{
		if (mNotes.empty()) return false;

		mSelectedNote = mNotes.erase(mSelectedNote);
		if (mSelectedNote == mNotes.end() && !mNotes.empty()) mSelectedNote--;
		
		SaveDB();
		return true;
	}
	int GetSize() const { return mNotes.size(); }
	int GetIndexOfSelectedItem() const
	{
		if (mNotes.empty()) return -1;

		return mSelectedNote - mNotes.begin();
	}
	string GetItemInLine(const int itemIndex) const
	{
		if (mNotes.empty() || itemIndex < 0 || itemIndex >= mNotes.size()) throw "out of range";

		return mNotes[itemIndex];
	}

	string GetItemInWindow(const int itemIndex) const
	{
		if (mNotes.empty() || itemIndex < 0 || itemIndex >= mNotes.size()) throw "out of range";

		return mNotes[itemIndex];
	}

	bool SetIndexOfSelectedItem(const int itemIndex)
	{
		if (mNotes.empty() || itemIndex < 0 || itemIndex >= mNotes.size()) return false;

		mSelectedNote = mNotes.begin() + itemIndex;
		return true;
	}
	virtual ~Notes(){}

		void SaveDB()
	{
		ofstream out(mDBname);
		if (out.is_open())
		{
			for (vector<string>::iterator note = mNotes.begin(); note != mNotes.end(); ++note)
			{
				out << *note<< "\n";
			}
		}
		else
		{
			throw "unable to open file";
		}
		out.close();
	}

	void OpenDB()
	{
		ifstream in(mDBname);

		if (in.is_open())
		{
			while(!in.eof())
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
};

