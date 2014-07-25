/*
Создать телефонный справочник для осуществления следующих операций:
Добавление абонентов в базу.
Удаление абонентов из базы.
Модификация данных абонента.
Поиск абонентов по телефонному номеру или фамилии.
Распечатка в алфавитном порядке абонентов из заданного диапазона номеров или фамилий;
например, для номеров диапазон может быть: 222222 - 333333,
а для фамилий: Иванаускас - Иванов (то есть Иванова в диапазон не входит).
Возможность сохранения найденной информации в файл.
Сохранение базы в файл.
Загрузка базы из файла.
*/

#include <iostream>
#include <iomanip>
#include <conio.h>
#include <io.h>

#include "PhoneBook.h"
#include "SelectList.h"
#include "Menu.h"

using namespace std;

const int systemColour = 0xF0;

ostream& operator<<(ostream& stream, const Contact* const contact);
void PrintContacts(const Contact* const root);
void Print(PhoneBook& phoneBook);

PhoneBook FindSurname(const PhoneBook& phoneBook, const char* surname);
PhoneBook FindPhone(const PhoneBook& phoneBook, const char* phone);
void Search(PhoneBook& phoneBook);

void MessageBox(const char* message, const bool error = false);
int SubMenu(const char* items[], const int itemsCount, const int itemMaxLen, const int baseX, const int baseY);
int PressAnyKey(PhoneBook& phoneBook);

bool WriteContactToFile(Contact* contact, FILE* pFile);
bool SaveDB(PhoneBook& phoneBook);
PhoneBook OpenDB();


void InitPhoneBook(PhoneBook& phoneBook);

void main()
{
	system("color F0");
	const char contactItemsNumber = 5;
	const char contactItemMaxLength = 10;
	const char* contactItems[contactItemsNumber] = { "F1 Add", "F2 Edit", "F3 Delete", "F4 Find", "F5 Print" };
	const int contactX = 0;
	const int contactY = 0;
	Menu contactMenu("Contact", contactItemsNumber, contactItemMaxLength, contactItems, contactX, contactY);

	const char dbItemsNumber = 2;
	const char dbItemMaxLength = 10;
	const char* dbItems[dbItemsNumber] = { "F9 Load", "F10 Save" };
	const int dbX = 55;
	const int dbY = 0;
	Menu dbMenu("Database", dbItemsNumber, dbItemMaxLength, dbItems, 55, 0);

	PhoneBook phoneBook;
	InitPhoneBook(phoneBook);

	enum { INACTIVE = -1, ADD = 0, EDIT, DEL, FIND, PRINT, LOAD = 0, SAVE };


	SelectList list(&phoneBook, 0, 5);
	while (true)
	{
		system("cls");
		contactMenu.showMenu();
		dbMenu.showMenu();
		list.ShowList();

		MessageBox(list.GetListMessage(), list.GetErrorStatus());
		list.ResetMessage();
		while (true)
		{


			enum{ KEY_ENTER = 13, KEY_ESCAPE = 27, KEY_F1 = 59, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F9 = 67, KEY_F10, KEY_UP = 72, KEY_DOWN = 80, KEY_DELETE = 83 };
			unsigned char control = getch();

			if (control == 0 || control == 224 && kbhit())
			{
				unsigned char secondByte = getch();
				if (secondByte == KEY_F1)
				{
					system("cls");
					contactMenu.showMenu(ADD);
					dbMenu.showMenu(INACTIVE);
					HideCursor(false);
					list.AddNode();
					break;
				}
				else if (secondByte == KEY_F2)
				{
					contactMenu.showMenu(EDIT);
					dbMenu.showMenu(INACTIVE);
					list.EditNode();
					break;
				}
				else if (secondByte == KEY_F3 || secondByte == KEY_DELETE)
				{
					list.DeleteNode();
					break;
				}
				else if (secondByte == KEY_F4)
				{
					system("cls");
					contactMenu.showMenu(FIND);
					dbMenu.showMenu();
					Search(phoneBook);
					list.Reset();
					break;
				}
				else if (secondByte == KEY_F5)
				{
					system("cls");
					contactMenu.showMenu(PRINT);
					dbMenu.showMenu();
					Print(phoneBook);
					list.Reset();
					break;
				}
				else if (secondByte == KEY_F9)
				{
					system("cls");
					contactMenu.showMenu(INACTIVE);
					dbMenu.showMenu(LOAD);

					phoneBook = OpenDB();
					list.Reset();
					break;
				}
				else if (secondByte == KEY_F10)
				{
					system("cls");
					contactMenu.showMenu(INACTIVE);
					dbMenu.showMenu(SAVE);

					SaveDB(phoneBook);
					PressAnyKey(phoneBook);
					list.Reset();
					break;
				}
				else if (secondByte == KEY_UP)
				{
					list.PreviousNode();
				}
				else if (secondByte == KEY_DOWN)
				{
					list.NextNode();
				}

			}
			else if ((control > 64 && control<91) || (control>96 && control < 123) || (control > 47 && control < 58) || control == 8)
			{

				list.MaskSearch(control);
				MessageBox(list.GetListMessage(), list.GetErrorStatus());
			}
			else if (control == KEY_ESCAPE)
			{
				GotoXY(0, 4);
				exit(1);
			}
		}
		SetColour(systemColour);
	}
}

int PressAnyKey(PhoneBook& phoneBook)
{
	MessageBox("Press any key to return to main menu, F9- open new DB, F10 - save current DB");
	int key = 0;
	char tmp = getch();
	if (tmp == 0 || tmp == 224 && kbhit())
	{
		switch (getch())
		{
		case 67:
			system("cls");
			phoneBook = OpenDB();
			key = 1;
			break;
		case 68:
			system("cls");
			SaveDB(phoneBook);
			key = PressAnyKey(phoneBook);
			break;
		}
	}
	return key;
}


ostream& operator<<(ostream& stream, const Contact* const contact)
{
	stream << ' ' << setw(20) << left << contact->surname << " ";
	stream << setw(20) << left << contact->name << "\t";
	stream << contact->phone;
	return stream;
}

void PrintContacts(const Contact* const root)
{
	if (root)
	{
		cout << root << endl;
		PrintContacts(root->GetLeft());
		PrintContacts(root->GetRight());
	}
}


void Print(PhoneBook& phoneBook)
{
	if (phoneBook.IsEmpty())
	{
		cout << "Phone book is empty";
		return;
	}

	const int subItemsCount = 3;
	const char* subItems[subItemsCount] = { "Print all", "Contacts", "Phones" };
	int index = SubMenu(subItems, subItemsCount, 10, 43, 3);

	if (index == -1){
		return;
	}

	PhoneBook searchResult;
	PhoneBook* activeDB = &searchResult;
	switch (index)
	{
	case 0:
		activeDB = &phoneBook;
		break;
	case 1:
	{
		HideCursor(false);
		cout << "Enter first surname: ";
		char surnameBegin[20];
		cin.getline(surnameBegin, 20);

		cout << "Enter last  surname: ";
		char surnameEnd[20];
		cin.getline(surnameEnd, 20);
		cout << endl;
		HideCursor(true);

		if (strcmp(surnameBegin, surnameEnd) > 0)
		{
			cout << setw(80) << "Error: incorrect range.\n";
			break;
		}

		Contact* contact = phoneBook.Min();
		while (contact && strcmp(contact->GetSurname(), surnameBegin) < 0)
		{
			contact = phoneBook.Next(contact);
		}

		while (contact && strcmp(contact->GetSurname(), surnameEnd) <= 0)
		{
			searchResult.Add(contact);
			contact = phoneBook.Next(contact);
		}
	}
		break;
	case 2:
	{
		HideCursor(false);
		cout << "Enter first phone number: ";
		char phoneBegin[15];
		cin.getline(phoneBegin, 15);

		cout << "Enter last  phone number: ";
		char phoneEnd[15];
		cin.getline(phoneEnd, 15);
		cout << endl;
		HideCursor(true);

		if (strcmp(phoneBegin, phoneEnd) > 0)
		{
			cout << setw(80) << "Error: incorrect range.\n";
			break;
		}

		Contact* contact = phoneBook.Min();
		while (contact)
		{
			if (strcmp(contact->GetPhone(), phoneBegin) >= 0
				&& strcmp(contact->GetPhone(), phoneEnd) <= 0)
			{
				searchResult.Add(contact);
			}
			contact = phoneBook.Next(contact);
		}

	}
		break;
	}

	if (activeDB->IsEmpty())
	{
		cout << setw(80) << "Contacts wasn't found.\n";
	}
	else
	{
		PrintContacts(activeDB->Root());
	}

	int key = PressAnyKey(*activeDB);
	if (key == 1) phoneBook = *activeDB;
}
PhoneBook FindSurname(const PhoneBook& phoneBook, const char* surname)
{
	PhoneBook searchResult;
	Contact* contact = phoneBook.SearchSurname(surname);
	while (contact && !strcmp(surname, contact->GetSurname()))
	{
		searchResult.Add(contact);
		contact = phoneBook.Next(contact);
	}
	return searchResult;
}

PhoneBook FindPhone(const PhoneBook& phoneBook, const char* phone)
{
	PhoneBook searchResult;
	Contact* contact = phoneBook.SearchPhone(phone, phoneBook.Min());
	while (contact)
	{
		searchResult.Add(contact);
		contact = phoneBook.Next(contact);
		if (contact)
		{
			contact = phoneBook.SearchPhone(phone, contact);
		}
	}
	return searchResult;
}

void Search(PhoneBook& phoneBook)
{
	if (phoneBook.IsEmpty())
	{
		cout << "Phone book is empty.\n";
		return;
	}

	const char* subItems[2] = { "Surname", "Phone" };
	int index = SubMenu(subItems, 2, 10, 33, 3);

	if (index == -1){
		return;
	}

	PhoneBook searchResult;
	if (!index)
	{
		HideCursor(false);
		cout << "Enter surname: ";
		char surname[20];
		cin.getline(surname, 20);
		cout << endl;

		searchResult = FindSurname(phoneBook, surname);
	}
	else
	{
		HideCursor(false);
		cout << "Enter phone number: ";
		char phone[15];
		cin.getline(phone, 15);
		cout << endl;

		searchResult = FindPhone(phoneBook, phone);
	}

	HideCursor(true);

	if (searchResult.IsEmpty()) {
		cout << "Contact wasn't found.\n";
	}
	else
	{
		PrintContacts(searchResult.Root());
	}

	int key = PressAnyKey(searchResult);
	if (key == 1) phoneBook = searchResult;
}


void MessageBox(const char* message, const bool error /* = false*/)
{
	if (error) SetColour(0xCF);
	else SetColour(0x2F);

	GotoXY(0, 3);
	cout << " " << setw(79) << message;
	SetColour(systemColour);
}

int SubMenu(const char* items[], const int itemsCount, const int itemMaxLen, const int baseX, const int baseY)
{
	if (itemsCount < 2) return -1;
	const short activeColour = 0x70;
	const short inactiveColour = 0x78;

	const int prevX = CurX();
	const int prevY = CurY();

	SetColour(activeColour);
	GotoXY(baseX, baseY);
	cout << setw(itemMaxLen) << left << items[0] << endl;
	SetColour(inactiveColour);
	for (int i = 1; i < itemsCount; ++i)
	{
		GotoXY(baseX, baseY + i);
		cout << setw(itemMaxLen) << left << items[i];
	}
	GotoXY(baseX, baseY);

	int selectedItem = -1;
	while (true)
	{
		unsigned char control = getch();
		enum{ KEY_ENTER = 13, KEY_ESCAPE = 27, KEY_UP = 72, KEY_DOWN = 80 };
		int curY = CurY();
		if (control == 224 && kbhit())
		{
			switch (getch())
			{
			case KEY_UP:
				if (curY > baseY)
				{
					GotoXY(baseX, curY);
					cout << setw(itemMaxLen) << left << items[curY - baseY];
					GotoXY(baseX, --curY);
					SetColour(activeColour);
					cout << setw(itemMaxLen) << left << items[curY - baseY];
					SetColour(inactiveColour);
				}
				break;
			case KEY_DOWN:
				if (curY < baseY + itemsCount - 1)
				{
					GotoXY(baseX, curY);
					cout << setw(itemMaxLen) << items[curY - baseY];
					GotoXY(baseX, ++curY);
					SetColour(activeColour);
					cout << setw(itemMaxLen) << items[curY - baseY];
					SetColour(inactiveColour);
				}
				break;
			}
		}
		else if (control == KEY_ENTER)
		{
			selectedItem = CurY() - baseY;
			break;
		}
		else if (control == KEY_ESCAPE)
		{
			selectedItem = -1;
			break;
		}
	}

	SetColour(systemColour);

	GotoXY(0, baseY);
	for (int i = 0; i < itemsCount; ++i)
	{
		cout << setw(79) << " " << endl;
	}
	GotoXY(prevX, prevY);

	return selectedItem;
}

int PressAnyKey(PhoneBook& phoneBook);

bool WriteContactToFile(Contact* contact, FILE* pFile)
{
	if (contact)
	{
		ContactBuffer buffer(contact->GetSurname(), contact->GetName(), contact->GetPhone());
		if (fwrite(&buffer, sizeof(buffer), 1, pFile))
		{
			WriteContactToFile(contact->GetLeft(), pFile);
			WriteContactToFile(contact->GetRight(), pFile);
		}
		else
		{
			return false;
		}
	}
	return true;
}


bool SaveDB(PhoneBook& phoneBook)
{
	GotoXY(0, 5);

	if (phoneBook.IsEmpty())
	{
		cout << "Nothing to save. Phone book is empty.";
		return false;
	}

	HideCursor(false);
	cout << "Save file\nEnter file name: ";
	char name[250];
	cin.getline(name, 250);
	HideCursor(true);

	if (_access(name, 00) == 0)
	{
		cout << "The file already exist. Would you like to rewrite it?";

		const char* subItems[2] = { "Yes", "No" };
		const int index = SubMenu(subItems, 2, 5, CurX() + 2, CurY());

		if ((index == -1 || index == 1) && _access(name, 02) == 0)
		{
			cout << "\nDB hasn't been saved";
			return false;
		}
	}

	FILE* pFile = fopen(name, "w+");
	if (!pFile)
	{
		cout << "Error: write failure\n";
		exit(1);
	}
	WriteContactToFile(phoneBook.Root(), pFile);
	fclose(pFile);

	cout << "\nDB has been successfully saved\n";
	return true;
}

PhoneBook OpenDB()
{
	GotoXY(0, 5);

	HideCursor(false);
	cout << "Open file.\nEnter file name: ";
	char name[250];
	cin.getline(name, 250);
	HideCursor(true);

	PhoneBook openedDB;

	FILE* pFile = fopen(name, "r");
	if (!pFile)
	{
		cout << "Error: read failure\n";
		exit(1);
	}

	while (!feof(pFile))
	{
		ContactBuffer buffer("\0", "\0", "\0");
		fread(&buffer, sizeof(buffer), 1, pFile);
		openedDB.Add(buffer.surname, buffer.name, buffer.phone);
	}
	return openedDB;
}


void InitPhoneBook(PhoneBook& phoneBook)
{
	phoneBook.Add("King", "Avery", "+380976010188");
	phoneBook.Add("Kelly", "Ava", "+380978581788");
	phoneBook.Add("Jones", "Adam", "+380975519155");
	phoneBook.Add("Jones", "Chloe", "+380977710578");
	phoneBook.Add("Harris", "David", "+380977398392");
	phoneBook.Add("Brown", "Alexander", "+380972037066");
	phoneBook.Add("Brown", "Ella", "+380973071462");
	phoneBook.Add("Anderson", "Cameron", "+380976099574");
	phoneBook.Add("Anderson", "Olivia", "+380975793457");
	phoneBook.Add("Lee", "Dominic", "+380973802398");
	phoneBook.Add("Martin", "Brandon", "+380972152612");
	phoneBook.Add("Martin", "Mia", "+380972750515");
	phoneBook.Add("Morton", "Benjamin", "+380976229995");
	phoneBook.Add("Morton", "Isabella", "+380979343862");
	phoneBook.Add("Nguyen", "Christian", "+380971191517");
	phoneBook.Add("Robinson", "Abigail", "+380973304648");
	phoneBook.Add("Ryan", "Dylan", "+380971264149");
	phoneBook.Add("Smith", "Aaron", "+380979607321");
	phoneBook.Add("Smith", "Charlotte", "+380973415249");
	phoneBook.Add("Taylor", "Anthony", "+380979714494");
	phoneBook.Add("Taylor", "Emma", "+380972875718");
	phoneBook.Add("Thomas", "Christopher", "+380973177343");
	phoneBook.Add("Thomas", "Sofia", "+380979961536");
	phoneBook.Add("Thompson", "Charles", "+380974772781");
	phoneBook.Add("Walker", "Daniel", "+380976323565");
	phoneBook.Add("Walker", "Sophia", "+380978800896");
	phoneBook.Add("White", "Blake", "+380977328343");
	phoneBook.Add("White", "Madison", "+380978185414");
	phoneBook.Add("Williams", "Adrian", "+380977455244");
	phoneBook.Add("Williams", "Elizabeth", "+380979030210");
	phoneBook.Add("Wilson", "Andrew", "+380979965190");
	phoneBook.Add("Wilson", "Emily", "+380977271476");
}