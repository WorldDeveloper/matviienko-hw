#include "Menu.h"
#include <cstring>
#include <iostream>
#include <Windows.h>
using namespace std;

Menu::Menu(char *name, const char size, const char length, const char* items[], const int xCoord, const int yCoord)
:mItemsNumber(size), mItemMaxLength(length), mX(xCoord), mY(yCoord)
{
	strcpy(mTitle, name);
	mItem = new char*[mItemsNumber];
	
	for (int i = 0; i < mItemsNumber; i++)
	{
		mItem[i] = new char[mItemMaxLength];
		strcpy(mItem[i], items[i]);
	}

	mStatus = new bool[mItemsNumber];
	for (int i = 0; i < size; ++i)
	{
		mStatus[i] = false;
	}
}

Menu::~Menu()
{
	for (int i = 0; i < mItemsNumber; i++)
	{
		if (mItem[i]) delete[] mItem[i];
	}
	if (mItem) { delete[] mItem; }
	delete[] mStatus;
}

void Menu::setStatus(const int activeItem)
{
	bool itemsStatus = false;
	if (activeItem == -2)
	{
		itemsStatus = true;
	}

	for (int i = 0; i < mItemsNumber; ++i)
	{
		mStatus[i] = itemsStatus;
	}

	if (activeItem >= mItemsNumber)
	{
		cout << "Error: item out of range\n";
		exit(1);
	}
	else if (activeItem >= 0)
	{
		mStatus[activeItem] = true;
	}
}

void Menu::showMenu(const int activeItem /*=-2*/)
{
	setStatus(activeItem);

	const short activeItemColor = 0x70;
	const short inactiveItemColor = 0x78;
	const short menuColor = 0x37;
	const short systemColor = 0xF0;
	
	//top-left border
	gotoxy(mX, mY);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), menuColor);

	for (int j = 0; j < 3; j++)
	{
		gotoxy(mX, mY+j);
		for (int i = mX; i < 80; i++)
		{
			cout << " ";
		}
	}
	gotoxy(mX, mY);
	int menuWidth = 3;

	for (int i = 0; i < mItemsNumber; i++) { menuWidth += strlen(mItem[i]) + 3; }

	cout << (char)218 << mTitle;
	line(196, menuWidth - strlen(mTitle) - 2);
	cout << (char)191;
	gotoxy(mX, mY+1);
	cout << (char)179 << " ";

	//items output
	char **curItem = mItem;
	bool* curStatus = mStatus;
	int itemColor;
	while (curItem < mItem + mItemsNumber)
	{
		if (*curStatus) itemColor = activeItemColor;
		else itemColor = inactiveItemColor;

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), itemColor);
		cout << " " << *curItem << " ";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), menuColor);
		cout << " ";
		curItem++;
		curStatus++;
	}

	//bottom-right border
	cout << (char)179;
	gotoxy(mX, mY+2);
	cout << (char)192;
	line(196, menuWidth - 2);
	cout << (char)217;

	gotoxy(0, mY+5);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), systemColor);
}

void Menu::gotoxy(short x, short y)
{
	COORD coord = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


void Menu::line(unsigned const char c, const int length)
{
	for (int i = 0; i < length; i++) { cout << c; }
}