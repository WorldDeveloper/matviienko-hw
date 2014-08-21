#pragma once
#include "PhoneBook.h"
#include <Windows.h>
#include "Graphics.h"

class SelectList
{
	PhoneBook* mPhoneBook;
	Contact* mSelectedContact;
	Contact* mFirstContact;
	Contact* mLastContact;
	int mCurY;
	int mBaseX;
	int mBaseY;
	char* mMessage;
	bool mErrorMessage;
	const short mActiveColour = 0x70;
	const short mInactiveColour = 0xF0;
	char mask[20];
public:
	SelectList(PhoneBook* phoneBook, const int baseX, const int baseY);
	~SelectList() { delete[] mMessage; }

	void ShowList();
	void NextNode();
	void PreviousNode();
	void DeleteNode();
	void EditNode();
	void AddNode();
	void MaskSearch(const unsigned char symbol);

	char* GetListMessage() const { return mMessage; }
	bool GetErrorStatus() const { return mErrorMessage; }
	void ResetMessage();
	void Reset();
	bool ListIsEmpty();
};