#pragma once
#include "Organizer.h"

class Notes :public Organizer
{
	vector<string> mNotes;
	vector<string>::iterator mSelectedNote;
	char* mDBname = "notes";
public:
	Notes();
	bool AddDetails();
	bool EditDetails();
	bool DeleteDetails();

	int GetSize() const { return mNotes.size(); }
	int GetIndexOfSelectedItem() const;

	string GetItemInLine(const int itemIndex) const;
	string GetItemInWindow(const int itemIndex) const;
	bool SetIndexOfSelectedItem(const int itemIndex);

	void SaveDB();
	void OpenDB();

	virtual ~Notes(){}
};