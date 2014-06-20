#include "menu.h"
#include <cstring>
#include <iostream>
#include <Windows.h>
using namespace std;

menu::menu(char *name, const char size, const char length)
{
	strcpy(mTitle, name);
	mItemsNumber = size;
	mItemMaxLength = length;
	mItem = new char*[mItemsNumber];
	mStatus = new bool[mItemsNumber];
	for (int i = 0; i < size; ++i)
	{
		mStatus[i] = false;
	}
}

menu::~menu()
{
	for (int i = 0; i < mItemsNumber; i++)
	{
		if (mItem[i]) delete[] mItem[i];
	}
	if (mItem) { delete[] mItem; }
	delete[] mStatus;
}

void menu::addItems(char* name[])
{

	for (int i = 0; i < mItemsNumber; i++)
	{
		mItem[i] = new char[mItemMaxLength];
		strcpy(mItem[i], name[i]);
	}
}

void menu::setStatus(const bool* status)
{
	for (int i = 0; i < mItemsNumber; ++i)
	{
		mStatus[i] = status[i];
	}
}

void menu::showMenu(char x)
{
	const short activeItemColor = 0x70;
	const short inactiveItemColor = 0x20;
	const short menuColor = 0x27;
	const short systemColor = 0x20;
	system("cls");
	system("color 20"); //AAA
	//top-left border
	gotoxy(x, 0);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), menuColor);

	for (int j = 0; j < 3; j++)
	{
		for (int i = 0; i < 80; i++) cout << " ";
	}
	gotoxy(x, 0);
	int menuWidth = 3;

	for (int i = 0; i < mItemsNumber; i++) { menuWidth += strlen(mItem[i]) + 3; }

	cout << (char)218 << mTitle;
	line(196, menuWidth - strlen(mTitle) - 2);
	cout << (char)191;
	gotoxy(x, 1);
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
	gotoxy(x, 2);
	cout << (char)192;
	line(196, menuWidth - 2);
	cout << (char)217;

	gotoxy(0, 4);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), systemColor);
}

void menu::gotoxy(short x, short y)
{
	COORD coord = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


void menu::line(unsigned const char c, const int length)
{
	for (int i = 0; i < length; i++) { cout << c; }
}