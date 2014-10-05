#include "menu.h"
#include "Graphics.h"
#include <string>
#include <iostream>
#include <Windows.h>
using namespace std;

Menu::Menu(string title, vector<string> items, const int xCoord, const int yCoord)
:mTitle(title), mItems(items), mX(xCoord), mY(yCoord)
{
	for (int i = 0; i < items.size(); ++i)
	{
		mStatus.push_back(false);
	}
}

void Menu::SetStatus(const int activeItem)
{
	bool itemsStatus = false;
	if (activeItem == -2)	itemsStatus = true;

	for (int i = 0; i < mItems.size(); ++i)
	{
		mStatus[i] = itemsStatus;
	}
	
	if (activeItem >= 0 || activeItem < mItems.size())  mStatus[activeItem] = true;
}

void Menu::ShowMenu()
{
	SetColour(mMenuColour);
	for (int j = 0; j < 3; j++)
	{
		GotoXY(mX, mY + j);
		for (int i = mX; i < 80; i++)
		{
			cout << " ";
		}
	}

	GotoXY(mX, mY);
	int menuWidth = 3;

	for (int i = 0; i < mItems.size(); i++) { menuWidth += mItems[i].size() + 3; }

	//top-left border
	const char topLeftCorner = 218;
	cout << topLeftCorner << mTitle;
	Line(196, menuWidth - mTitle.size() - 2);

	const char topRightCorner = 191;
	cout << topRightCorner;
	GotoXY(mX, mY + 1);

	const char vertLine = 179;
	cout << vertLine << " ";

	//items output
	vector<string>::iterator curItem = mItems.begin();
	vector<bool>::iterator curStatus = mStatus.begin();

	while (curItem != mItems.end())
	{
		int itemColour;
		if (*curStatus) itemColour = mActiveItemColour;
		else itemColour = mInactiveItemColour;

		SetColour(itemColour);
		cout << " " << *curItem << " ";
		SetColour(mMenuColour);
		cout << " ";
		curItem++;
		curStatus++;
	}

	//bottom-right border
	cout << vertLine;
	GotoXY(mX, mY + 2);
	const char bottomLeftCorner = 192;
	cout << bottomLeftCorner;
	Line(196, menuWidth - 2);
	const char bottomRightCorner = 217;
	cout << bottomRightCorner;

	GotoXY(0, mY + 5);
	SetColour(mSystemColour);
}


void Menu::Line(unsigned const char c, const int length)
{
	for (int i = 0; i < length; i++) { cout << c; }
}

int Menu::GetStatus() const
{
	for (int i = 0; i < mStatus.size(); ++i)
	{
		if (mStatus[i])
		{
			return i;
		}
	}
	
	return -1;
}