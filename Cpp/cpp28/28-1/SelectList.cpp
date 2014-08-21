#include <iomanip>
#include "SelectList.h"
using namespace std;



SelectList::SelectList(PhoneBook* phoneBook, const int baseX, const int baseY)
:mPhoneBook(phoneBook), mBaseX(baseX), mBaseY(baseY)
{
	mFirstContact = phoneBook->Min();
	mSelectedContact = mFirstContact;
	mLastContact = phoneBook->Max();
	mCurY = mBaseY;
	mMessage = new char[80];
	strcpy(mMessage, "Type surname or press UP and DOWN arrow to select the contact");
	mErrorMessage = false;
	mask[0] = '\0';
}

void SelectList::Reset()
{

	mFirstContact = mPhoneBook->Min();
	mSelectedContact = mFirstContact;
	mLastContact = mPhoneBook->Max();
	mCurY = mBaseY;
	mMessage = new char[80];
	strcpy(mMessage, "Type surname or press UP and DOWN arrow to select the contact");
	mErrorMessage = false;
	mask[0] = '\0';
}

void SelectList::ShowList()
{
	HideCursor(true);
	GotoXY(mBaseX, mBaseY);
	SetColour(mInactiveColour);

	Contact* contact = mFirstContact;
	int itemsCount = 0;

	if (mPhoneBook->IsEmpty())
	{
		cout << "Phone book is empty.\n";
		return;
	}

	if (!mSelectedContact) { mSelectedContact = mFirstContact; }

	while (contact)
	{
		GotoXY(mBaseX, mBaseY + itemsCount++);
		cout << contact;
		contact = mPhoneBook->Next(contact);
	}

	contact = mFirstContact;
	mCurY = mBaseY;

	while (contact && contact != mSelectedContact)
	{
		contact = mPhoneBook->Next(contact);
		mCurY++;
	}

	if (contact)
	{
		mSelectedContact = contact;
		SetColour(mActiveColour);
		GotoXY(mBaseX, mCurY);
		cout << mSelectedContact;
		SetColour(mInactiveColour);
	}
	else
	{
		mCurY = mBaseY;
		cout << "Error: selected contact wasn't found.\n";
		strcpy(mMessage, "Error: selected contact wasn't found.\n");
		mErrorMessage = true;
	}

}

void SelectList::NextNode()
{
	if (mPhoneBook->IsEmpty())
	{
		return;
	}

	if (mSelectedContact != mLastContact)
	{
		mask[0] = '\0';
		GotoXY(mBaseX, mCurY);
		cout << mSelectedContact;

		mSelectedContact = mPhoneBook->Next(mSelectedContact);
		GotoXY(mBaseX, ++mCurY);
		SetColour(mActiveColour);
		cout << mSelectedContact;
		SetColour(mInactiveColour);
	}
}

void SelectList::PreviousNode()
{
	if (mPhoneBook->IsEmpty())
	{
		return;
	}

	if (mSelectedContact != mFirstContact)
	{
		mask[0] = '\0';
		GotoXY(mBaseX, mCurY);
		cout << mSelectedContact;

		mSelectedContact = mPhoneBook->Previous(mSelectedContact);
		GotoXY(mBaseX, --mCurY);
		SetColour(mActiveColour);
		cout << mSelectedContact;
		SetColour(mInactiveColour);
	}
}

void SelectList::DeleteNode()
{
	if (ListIsEmpty()) return;

	Contact* tmpContact = mSelectedContact;

	if (mSelectedContact == mLastContact)
	{
		mSelectedContact = mPhoneBook->Previous(mSelectedContact);
		mLastContact = mSelectedContact;
		mCurY--;
	}
	else
	{
		mSelectedContact = mPhoneBook->Next(mSelectedContact);
		if (tmpContact == mFirstContact) mFirstContact = mSelectedContact;
	}

	mPhoneBook->Delete(tmpContact);
	strcpy(mMessage, "Contact has been deleted");
	mErrorMessage = false;
}


void SelectList::EditNode()
{
	if (ListIsEmpty()) return;

	HideCursor(false);
	SetColour(0xB0);
	char fields[3][20] = { "Surname", "Name", "Phone" };
	for (int i = 0; i < 3; ++i)
	{
		GotoXY(0, mCurY);
		cout << setw(80) << ' ';
		GotoXY(0, mCurY);
		cout << fields[i] << ": ";
		int len = (i != 2) ? 20 : 15;
		cin.getline(fields[i], len);
	}

	enum{ SURNAME, NAME, PHONE };

	if (!fields[SURNAME][0]) { strcpy(fields[SURNAME], mSelectedContact->GetSurname()); }
	if (!fields[NAME][0]) { strcpy(fields[NAME], mSelectedContact->GetName()); }
	if (!fields[PHONE][0]) { strcpy(fields[PHONE], mSelectedContact->GetPhone()); }

	Contact* tmp = mSelectedContact;
	mSelectedContact = mPhoneBook->Add(fields[SURNAME], fields[NAME], fields[PHONE]);
	if (mSelectedContact)
	{
		mPhoneBook->Delete(tmp);
	}
	else
	{
		mSelectedContact = tmp;
		strcpy(mMessage, "Contact hasn't been changed");
		mErrorMessage = true;
		HideCursor(true);
		return;
	}

	strcpy(mMessage, "Contact has been changed");
	mErrorMessage = false;
	HideCursor(true);

	mCurY = mBaseY;
	mFirstContact = mPhoneBook->Min();
	mLastContact = mPhoneBook->Max();

}

void SelectList::AddNode()
{
	HideCursor(false);
	cout << "Enter folowing information:\n\n";
	cout << "Surname: ";
	char surname[20];
	cin.getline(surname, 20);
	cout << "Name: ";
	char name[20];
	cin.getline(name, 20);
	cout << "Phone: ";
	char phone[15];
	cin.getline(phone, 15);

	Contact* tmp = mSelectedContact;
	if (mSelectedContact = mPhoneBook->Add(surname, name, phone))
	{
		strcpy(mMessage, "Contact has been successfully added");
		mErrorMessage = false;
	}
	else
	{
		mSelectedContact = tmp;
		strcpy(mMessage, "Error: contact hasn't been added");
		mErrorMessage = true;
	}

	mCurY = mBaseY;
	mFirstContact = mPhoneBook->Min();
	mLastContact = mPhoneBook->Max();
}

void SelectList::MaskSearch(const unsigned char symbol)
{
	if (ListIsEmpty()) return;

	const int maskLen = strlen(mask);

	if ((symbol == 8) && maskLen > 0)
	{
		mask[maskLen - 1] = '\0';
	}
	else if (maskLen < 19 && symbol != 8)
	{
		mask[maskLen] = symbol;
		mask[maskLen + 1] = '\0';
	}

	strcpy(mMessage, "Search mask: ");
	strcat(mMessage, mask);
	mErrorMessage = false;


	const int prevY = mCurY;
	mCurY = mBaseY;
	Contact* prevContact = mSelectedContact;
	mSelectedContact = mFirstContact;

	while (mSelectedContact && strncmp(mSelectedContact->GetSurname(), mask, strlen(mask)) != 0)
	{
		mSelectedContact = mPhoneBook->Next(mSelectedContact);
		mCurY++;
	}

	if (!mSelectedContact)
	{
		mSelectedContact = prevContact;
		mCurY = prevY;
	}

	GotoXY(mBaseX, prevY);
	cout << prevContact;

	GotoXY(mBaseX, mCurY);
	SetColour(mActiveColour);
	cout << mSelectedContact;
	SetColour(mInactiveColour);
}

void SelectList::ResetMessage()
{
	mMessage[0] = '\0';
	mErrorMessage = false;
	GotoXY(mBaseX, mCurY);
}

bool SelectList::ListIsEmpty()
{
	if (mPhoneBook->IsEmpty())
	{
		strcpy(mMessage, "Database is empty");
		cout << "Database is empty\n";
		mErrorMessage = true;
		return true;
	}

	return false;
}
