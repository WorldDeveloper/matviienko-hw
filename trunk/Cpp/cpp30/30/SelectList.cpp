#include <iomanip>
#include "SelectList.h"
using namespace std;

void SelectList::ResetList()
{
	mFirstLeaf = mBTree->Min();
	mSelectedLeaf = mFirstLeaf;
	mLastLeaf = mBTree->Max();
	mCurY = mBaseY;
	mMessage = new char[80];
	strcpy(mMessage, "Type a phrase or press UP and DOWN arrow to select an item. ENTER - review mode");
	mErrorMessage = false;
	mMask[0] = '\0';
	mSelectedLeafReview = false;
}

SelectList::SelectList(BTree* bTree, const int baseX, const int baseY)
:mBTree(bTree), mBaseX(baseX), mBaseY(baseY)
{
	ResetList();
}

bool SelectList::ListIsEmpty()
{
	if (mBTree->IsEmpty())
	{
		strcpy(mMessage, "Database is empty");
		cout << "Database is empty\n";
		mErrorMessage = true;
		return true;
	}

	return false;
}

void SelectList::SelectActiveItem()
{
	if (mSelectedLeafReview)
	{
		ShowSelectedItem();
	}
	else
	{
		SetColour(mActiveColour);
		GotoXY(mBaseX, mCurY);
		ShowItem(mSelectedLeaf);
		GotoXY(60, mCurY);
		SetColour(0x7C);
		cout << " " << setw(19) << left << mMask;
		SetColour(mInactiveColour);
	}
}

void SelectList::DeselectActiveItem()
{
	if (!mSelectedLeafReview)
	{
		GotoXY(mBaseX, mCurY);
		cout << setw(80) << " ";
		GotoXY(mBaseX, mCurY);
		ShowItem(mSelectedLeaf);
	}
}

void SelectList::ShowItem(const Leaf* const leaf) const
{
	cout << ' ' << setw(FIRM_LEN) << left << leaf->GetFirm() << ' ';
	printf("%-22.22s", leaf->GetBranch());
}

void SelectList::ShowSelectedItem()
{
	cout << "Mask: " << mMask << "\n\n";
	cout << mSelectedLeaf;
	mSelectedLeafReview = true;
}


void SelectList::ShowList()
{
	mSelectedLeafReview = false;
	HideCursor(true);
	GotoXY(mBaseX, mBaseY);
	SetColour(mInactiveColour);

	Leaf* leaf = mFirstLeaf;
	int itemsCount = 0;

	if (ListIsEmpty()) return;

	if (!mSelectedLeaf) { mSelectedLeaf = mFirstLeaf; }

	while (leaf)
	{
		GotoXY(mBaseX, mBaseY + itemsCount++);
		ShowItem(leaf);
		leaf = mBTree->Next(leaf);
	}

	leaf = mFirstLeaf;
	mCurY = mBaseY;

	while (leaf && leaf != mSelectedLeaf)
	{
		leaf = mBTree->Next(leaf);
		mCurY++;
	}

	if (leaf)
	{
		mSelectedLeaf = leaf;
		SelectActiveItem();
	}
	else
	{
		mCurY = mBaseY;
		cout << "Error: selected item wasn't found.\n";
		strcpy(mMessage, "Error: selected item wasn't found.\n");
		mErrorMessage = true;
	}

}

void SelectList::NextNode()
{
	if (mBTree->IsEmpty() || mSelectedLeafReview)
	{
		return;
	}

	if (mSelectedLeaf != mLastLeaf)
	{
		mMask[0] = '\0';
		DeselectActiveItem();

		mSelectedLeaf = mBTree->Next(mSelectedLeaf);
		++mCurY;
		SelectActiveItem();
	}
}

void SelectList::PreviousNode()
{
	if (mBTree->IsEmpty() || mSelectedLeafReview)
	{
		return;
	}

	if (mSelectedLeaf != mFirstLeaf)
	{
		mMask[0] = '\0';
		DeselectActiveItem();

		mSelectedLeaf = mBTree->Previous(mSelectedLeaf);
		--mCurY;
		SelectActiveItem();
	}
}

bool SelectList::DeleteNode()
{
	if (ListIsEmpty()) return false;

	Leaf* tmpLeaf = mSelectedLeaf;

	if (mSelectedLeaf == mLastLeaf)
	{
		mSelectedLeaf = mBTree->Previous(mSelectedLeaf);
		mLastLeaf = mSelectedLeaf;
		mCurY--;
	}
	else
	{
		mSelectedLeaf = mBTree->Next(mSelectedLeaf);
		if (tmpLeaf == mFirstLeaf) mFirstLeaf = mSelectedLeaf;
	}

	mBTree->Delete(tmpLeaf);
	strcpy(mMessage, "Item has been deleted");
	mErrorMessage = false;
	mSelectedLeafReview = false;

	return true;
}


bool SelectList::EditNode()
{
	if (ListIsEmpty()) return false;

	HideCursor(false);
	cout << "Enter folowing information (press Enter to skip current input).\n\n";

	Data input;
	cout << "Enter a new trade name: ";
	cin.getline(input.firm, FIRM_LEN);

	cout << "\nEnter a new owner details: ";
	cin.getline(input.owner, OWNER_LEN);

	cout << "\nEnter a new phone number: ";
	cin.getline(input.phone, PHONE_LEN);

	cout << "\nEnter a new address: ";
	cin.getline(input.address, ADDRESS_LEN);

	cout << "\nEnter a new branch details: ";
	cin.getline(input.branch, BRANCH_LEN);

	Data initial = mSelectedLeaf->GetData();
	if (!input.firm[0] && initial.firm[0]) { strcpy(input.firm, initial.firm); }
	if (!input.owner[0] && initial.owner[0]) { strcpy(input.owner, initial.owner); }
	if (!input.phone[0] && initial.phone[0]) { strcpy(input.phone, initial.phone); }
	if (!input.address[0] && initial.address[0]) { strcpy(input.address, initial.address); }
	if (!input.branch[0] && initial.branch[0]) { strcpy(input.branch, initial.branch); }


	Leaf* tmp = mSelectedLeaf;
	mSelectedLeaf = mBTree->Add(input);
	if (mSelectedLeaf)
	{
		mBTree->Delete(tmp);
	}
	else
	{
		mSelectedLeaf = tmp;
		strcpy(mMessage, "Item hasn't been changed");
		mErrorMessage = true;
		HideCursor(true);
		return false;
	}

	strcpy(mMessage, "Item has been changed");
	mErrorMessage = false;
	HideCursor(true);

	mCurY = mBaseY;
	mFirstLeaf = mBTree->Min();
	mLastLeaf = mBTree->Max();
	mSelectedLeafReview = false;

	return true;
}

bool SelectList::AddNode()
{
	HideCursor(false);
	cout << "Enter folowing information.\n\n";

	Data input;
	cout << "Enter a trade name: ";
	cin.getline(input.firm, FIRM_LEN);

	cout << "\nEnter an owner details: ";
	cin.getline(input.owner, OWNER_LEN);

	cout << "\nEnter a phone number: ";
	cin.getline(input.phone, PHONE_LEN);

	cout << "\nEnter an address: ";
	cin.getline(input.address, ADDRESS_LEN);

	cout << "\nEnter a branch details: ";
	cin.getline(input.branch, BRANCH_LEN);


	Leaf* tmp = mSelectedLeaf;
	if (mSelectedLeaf = mBTree->Add(input))
	{
		strcpy(mMessage, "Item has been successfully added.");
		mErrorMessage = false;
	}
	else
	{
		mSelectedLeaf = tmp;
		strcpy(mMessage, "Error: item hasn't been added.");
		mErrorMessage = true;
		return false;
	}

	mCurY = mBaseY;
	mFirstLeaf = mBTree->Min();
	mLastLeaf = mBTree->Max();
	mSelectedLeafReview = false;

	return true;
}

bool SelectList::Search(const int field, const bool findNext/*=false*/)
{
	int tmpY = mBaseY;
	Leaf* searchedLeaf = mFirstLeaf;
	if (findNext)
	{
		if (!strlen(mMask)) return false;
		searchedLeaf = mBTree->Next(mSelectedLeaf);
		tmpY = mCurY + 1;
	}

	while (searchedLeaf && strncmp(searchedLeaf->GetField(field), mMask, strlen(mMask)) != 0)
	{
		searchedLeaf = mBTree->Next(searchedLeaf);
		tmpY++;
	}

	if (!searchedLeaf)
	{
		SelectActiveItem();
		strcpy(mMessage, "Not found");
		mErrorMessage = true;
		ShowStatus();

		return false;
	}

	DeselectActiveItem();

	mSelectedLeaf = searchedLeaf;
	mCurY = tmpY;
	SelectActiveItem();

	if (strlen(mMask))
	{
		strcpy(mMessage, "F5 - find next.");
	}
	else
	{
		strcpy(mMessage, " ");
	}
	mErrorMessage = false;
	ShowStatus();

	return true;
}

void SelectList::MaskSearch(const unsigned char symbol, const int field)
{
	if (ListIsEmpty() || mSelectedLeafReview) return;

	const int maskLen = strlen(mMask);

	if ((symbol == 8) && maskLen > 0)
	{
		mMask[maskLen - 1] = '\0';
	}
	else if (maskLen < 19 && symbol != 8)
	{
		mMask[maskLen] = symbol;
		mMask[maskLen + 1] = '\0';
	}
	else if (maskLen>19) return;

	Search(field);
}

void SelectList::ResetMessage()
{
	mMask[0] = '\0';
	mMessage[0] = '\0';
	mErrorMessage = false;
	GotoXY(mBaseX, mCurY);
}

bool SelectList::QuitReview()
{
	if (mSelectedLeafReview)
	{
		mSelectedLeafReview = false;
		return true;
	}

	return false;
}

void SelectList::ShowStatus()
{
	if (mErrorMessage) SetColour(0xCF);
	else SetColour(0x2F);

	GotoXY(0, 3);
	cout << " " << setw(79) << left << mMessage;
	SetColour(0xF0);
}
