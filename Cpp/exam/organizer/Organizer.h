#pragma once
#include <iostream>
#include <string>
#include "Graphics.h"
#include "menu.h"
#include <conio.h>
using namespace std;

enum{ ACTIVE = -2, INACTIVE, ADD, EDIT, DEL };

class Organizer// create settings in separate file
{
	Menu mMainMenu;
	Menu mItemsControlMenu;
	const short mBaseX = 1;
	const short mBaseY = 5;
	const short mSystemColour = 0xF0;
	const short mActiveColour=0x70;
	const short mInactiveColour=0xF0;
	const short mListItemLen = 77;
	bool mSelectedItemReview;
public:
	Organizer() :
		mSelectedItemReview(false),
		mMainMenu("Organizer", { " F1 Events ", " F2 Contacts ", " F3 Notes " }, 0, 0), // create settings in separate file
		mItemsControlMenu("Items management", { "F5 Add", "F6 Edit", "F7 Delete" }, 46, 0)
	{}
	virtual int GetSize() const = 0;
	virtual int GetIndexOfSelectedItem() const = 0;
	virtual bool SelectItem(const int itemIndex) = 0;
	virtual string GetItemInLine(const int itemIndex) const = 0;
	//virtual string GetItemInWindow(const int itemIndex) const = 0;
	~Organizer(){}

	void MessageBox(const string& message, const bool error)
	{
		HideCursor(true);
		int indent = (80-message.size())/2;
		int colour = 0x2F;
		if (error) colour = 0x4F;
		SetColour(colour);

		GotoXY(0, 9);
		cout << setw(400) << " ";
		GotoXY(indent, 10);
		cout << message;
		GotoXY(38, 12);
		SetColour(0x70);
		cout << " OK ";
		while (true){ if (getch()) break; }
		SetColour(mSystemColour);
	}
	void RepaintWindow(const int mainMenuStatus, const int itemsControlMenuStatus, const bool hideCursor)
	{
		system("cls");
		mMainMenu.ShowMenu(mainMenuStatus);
		mItemsControlMenu.ShowMenu(itemsControlMenuStatus);
		HideCursor(hideCursor);
	}
	void Add()
	{
		RepaintWindow(INACTIVE, ADD, false);

		if (!AddDetails()) MessageBox("Item has not been added.", true);
		
		RepaintWindow(ACTIVE, ACTIVE, true);
		ShowList();
	}
	void Edit()
	{
		if (!GetSize())
		{
			MessageBox("There are no items to edit.", true);
		}
		else
		{		
			RepaintWindow(INACTIVE, EDIT, false);

			if (!EditDetails()) MessageBox("Item has not been changed.", true);
		}

		RepaintWindow(ACTIVE, ACTIVE, false);
		ShowList();
	}
	void Delete()
	{
		if (!GetSize())
		{
			MessageBox("There are no items to delete.", true);
		}
		else
		{
			if (!DeleteDetails()) MessageBox("Item has not been deleted.", true);
		}

		RepaintWindow(ACTIVE, ACTIVE, false);
		if (GetSize()) ShowList();
	}
	virtual bool AddDetails() = 0;
	virtual bool EditDetails() = 0;
	virtual bool DeleteDetails() = 0;

	void ShowItemInLine(const int itemIndex) const
	{
		GotoXY(mBaseX, mBaseY + itemIndex);
		cout << setw(mListItemLen)<<left<<GetItemInLine(itemIndex).substr(0, mListItemLen) << endl;
	}
	void ShowSelectedItemInLine() const
	{
		SetColour(mActiveColour);
		ShowItemInLine(GetIndexOfSelectedItem());
		SetColour(mInactiveColour);
	}
	void ShowList() const
	{
		if (!GetSize()) return;

		HideCursor(true);
		SetColour(mInactiveColour);

		for (int i=0; i<GetSize(); ++i)
		{
			ShowItemInLine(i);
		}

		ShowSelectedItemInLine();
	}
};

