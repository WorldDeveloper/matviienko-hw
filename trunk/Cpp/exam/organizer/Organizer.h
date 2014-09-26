#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Graphics.h"
#include "menu.h"
#include <conio.h>
#include <fstream>
using namespace std;

enum{ ACTIVE = -2, INACTIVE, ADD, EDIT, DEL };

class Organizer
{
	Menu mMainMenu;
	Menu mItemsControlMenu;
	const short mBaseX = 1;
	const short mBaseY = 5;
	const short mSystemColour = 0xF0;
	const short mSystemAnticolour = 0xFF;
	const short mActiveColour = 0x70;
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

	void ShowItemInLine(const int itemIndex) const;
	void ShowSelectedItemInLine() const;
	void ShowSelectedItemInWindow() const;

	void SelectActiveItem();
	void DeselectActiveItem();

public:
	Organizer() :
		mSelectedItemReview(false),
		mMainMenu("Organizer", { " F1 Events ", " F2 Contacts ", " F3 Notes " }, 0, 0),
		mItemsControlMenu("Items management", { "F5 Add", "F6 Edit", "F7 Delete" }, 46, 0)
	{
		mMainMenu.SetStatus(0);
		mItemsControlMenu.SetStatus(ACTIVE);
	}
	virtual ~Organizer(){}

	void Add();
	void Edit();
	void Delete();

	void ShowList();
	void ReviewSelectedItem();

	void NextItem();
	void PreviousItem();

	void MessageBox(const string& message, const bool error);
	void RepaintWindow(const bool hideCursor = true);
	void SetActivePage(const int page);

	virtual void Today(){}
};