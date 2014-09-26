#include "Organizer.h"


void Organizer::ShowItemInLine(const int itemIndex) const
{
	string output = GetItemInLine(itemIndex);
	replace(output.begin(), output.end(), '\t', ' ');
	GotoXY(mBaseX, mBaseY + itemIndex);
	cout << setw(mListItemLen) << left << output.substr(0, mListItemLen) << endl;
}

void Organizer::ShowSelectedItemInLine() const
{
	SetColour(mActiveColour);
	ShowItemInLine(GetIndexOfSelectedItem());
	SetColour(mSystemColour);
}

void Organizer::ShowSelectedItemInWindow() const
{
	GotoXY(mBaseX, mBaseY);
	cout << GetItemInWindow(GetIndexOfSelectedItem()) << endl;
}

void Organizer::SelectActiveItem()
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

void Organizer::DeselectActiveItem()
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

void Organizer::Add()
{
	mItemsControlMenu.SetStatus(ADD);
	RepaintWindow(false);

	if (!AddDetails()) MessageBox("Item has not been added.", true);

	mItemsControlMenu.SetStatus(ACTIVE);
	RepaintWindow(true);
	ShowList();
}
void Organizer::Edit()
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

void Organizer::Delete()
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

void Organizer::ShowList()
{
	if (!GetSize()) return;

	HideCursor(true);
	SetColour(mSystemColour);
	mSelectedItemReview = false;

	for (int i = 0; i < GetSize(); ++i)
	{
		ShowItemInLine(i);
	}

	ShowSelectedItemInLine();
}

void Organizer::ReviewSelectedItem()
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

void Organizer::NextItem()
{
	const int curIndex = GetIndexOfSelectedItem();
	const int size = GetSize();
	if (!size || curIndex >= size - 1) return;

	DeselectActiveItem();
	SetIndexOfSelectedItem(curIndex + 1);
	SelectActiveItem();
}

void Organizer::PreviousItem()
{
	const int curIndex = GetIndexOfSelectedItem();
	const int size = GetSize();
	if (!size || curIndex <= 0) return;

	DeselectActiveItem();
	SetIndexOfSelectedItem(curIndex - 1);
	SelectActiveItem();
}

void Organizer::MessageBox(const string& message, const bool error)
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

void Organizer::RepaintWindow(const bool hideCursor/* = true*/)
{
	system("cls");
	mMainMenu.ShowMenu();
	mItemsControlMenu.ShowMenu();
	HideCursor(hideCursor);
}

void Organizer::SetActivePage(const int page)
{
	mMainMenu.SetStatus(page);
}
