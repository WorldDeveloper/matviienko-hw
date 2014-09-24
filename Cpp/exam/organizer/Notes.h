#pragma once
#include "Organizer.h"
#include <vector>
#include <string>
using namespace std;

class Notes:public Organizer
{
	vector<string> mNotes;
	vector<string>::iterator mSelectedNote;
public:
	Notes();
	bool AddDetails()
	{		
		cout << "Add note: ";
		char note[250];
		cin.getline(note, 250);
		mNotes.push_back(note);
		mSelectedNote =--mNotes.end();
		return true;
	}
	bool EditDetails()
	{
		if (mNotes.empty()) return false;

		cout << "Edit note:";
		char note[250];
		cin.getline(note, 250);
		*mSelectedNote = note;
		return true;
	}

	bool DeleteDetails()
	{
		if (mNotes.empty()) return false; 
		
		mSelectedNote = mNotes.erase(mSelectedNote);
		if (mSelectedNote == mNotes.end() && !mNotes.empty()) mSelectedNote--;
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
};

