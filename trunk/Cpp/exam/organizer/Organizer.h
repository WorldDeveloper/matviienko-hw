#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
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
	const short mSystemAnticolour = 0xFF;
	const short mActiveColour = 0x70;
	const short mInactiveColour = 0xF0;
	const short mListItemLen = 77;
	bool mSelectedItemReview;

	virtual int GetSize() const = 0;
	virtual int GetIndexOfSelectedItem() const = 0;
	virtual bool SetIndexOfSelectedItem(const int itemIndex) = 0;
	virtual string GetItemInLine(const int itemIndex) const = 0;
	virtual string GetItemInWindow(const int itemIndex) const = 0;

	virtual bool AddDetails() = 0;
	virtual bool EditDetails() = 0;
	virtual bool DeleteDetails() = 0;

	void ShowItemInLine(const int itemIndex) const
	{
		string output = GetItemInLine(itemIndex);
		replace(output.begin(), output.end(), '\t', ' ');
		GotoXY(mBaseX, mBaseY + itemIndex);
		cout << setw(mListItemLen) << left << output.substr(0, mListItemLen) << endl;
	}
	void ShowSelectedItemInLine() const
	{
		SetColour(mActiveColour);
		ShowItemInLine(GetIndexOfSelectedItem());
		SetColour(mInactiveColour);
	}
	void ShowSelectedItemInWindow() const
	{
		GotoXY(mBaseX, mBaseY);
		cout << GetItemInWindow(GetIndexOfSelectedItem()) << endl;
	}


	void SelectActiveItem()
	{
		if (mSelectedItemReview)
		{
			ShowSelectedItemInWindow();
		}
		else
		{
			ShowSelectedItemInLine();
		}
	}
	void DeselectActiveItem()
	{
		if (mSelectedItemReview)
		{
			SetColour(mSystemAnticolour);
			ShowSelectedItemInWindow();
			SetColour(mSystemColour);
		}
		else
		{
			ShowItemInLine(GetIndexOfSelectedItem());
		}
	}

public:
	Organizer() :
		mSelectedItemReview(false),
		mMainMenu("Organizer", { " F1 Events ", " F2 Contacts ", " F3 Notes " }, 0, 0), // create settings in separate file
		mItemsControlMenu("Items management", { "F5 Add", "F6 Edit", "F7 Delete" }, 46, 0)
	{
		mMainMenu.SetStatus(0);
		mItemsControlMenu.SetStatus(ACTIVE);
	}
	~Organizer(){}

	void Add()
	{
		mItemsControlMenu.SetStatus(ADD);
		RepaintWindow(false);

		if (!AddDetails()) MessageBox("Item has not been added.", true);

		mItemsControlMenu.SetStatus(ACTIVE);
		RepaintWindow(true);
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
			mItemsControlMenu.SetStatus(EDIT);
			RepaintWindow(false);

			if (!EditDetails()) MessageBox("Item has not been changed.", true);
		}
		mItemsControlMenu.SetStatus(ACTIVE);
		RepaintWindow(true);
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

		RepaintWindow();
		if (GetSize()) ShowList();
	}

	void ShowList()
	{
		if (!GetSize()) return;

		HideCursor(true);
		SetColour(mInactiveColour);
		mSelectedItemReview = false;

		for (int i = 0; i < GetSize(); ++i)
		{
			ShowItemInLine(i);
		}

		ShowSelectedItemInLine();
	}
	void ReviewSelectedItem()
	{
		if (!GetSize()) return;

		RepaintWindow();
		if (!mSelectedItemReview)
		{
			ShowSelectedItemInWindow();
			mSelectedItemReview = true;
		}
		else
		{
			ShowList();
			mSelectedItemReview = false;
		}
	}

	void NextItem()
	{
		const int curIndex = GetIndexOfSelectedItem();
		const int size = GetSize();
		if (!size || curIndex >= size - 1) return;

		DeselectActiveItem();
		SetIndexOfSelectedItem(curIndex + 1);
		SelectActiveItem();
	}
	void PreviousItem()
	{
		const int curIndex = GetIndexOfSelectedItem();
		const int size = GetSize();
		if (!size || curIndex <= 0) return;

		DeselectActiveItem();
		SetIndexOfSelectedItem(curIndex - 1);
		SelectActiveItem();
	}

	void MessageBox(const string& message, const bool error)
	{
		HideCursor(true);
		int indent = (80 - message.size()) / 2;
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
	void RepaintWindow(const bool hideCursor = true)
	{
		system("cls");
		mMainMenu.ShowMenu();
		mItemsControlMenu.ShowMenu();
		HideCursor(hideCursor);
	}
	void SetActivePage(const int page)
	{
		mMainMenu.SetStatus(page);
	}
	virtual void Today(){}
};

