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
#include "Menu.h"
#include "PhoneBook.h"
#include <iomanip>
#include <conio.h>
#include <Windows.h>
#include <io.h>
using namespace std;

const int xOutput = 4;
const int systemColour = 0xF0;


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

PhoneBook FindSurname(const PhoneBook& phoneBook, const char* surname)
{
	PhoneBook searchResult;
	Contact* contact = phoneBook.SearchSurname(surname);
	while (contact && !strcmp(surname, contact->GetSurname()))
	{
		searchResult.Add(contact->GetSurname(), contact->GetName(), contact->GetPhone());
		contact = phoneBook.Next(contact);
	}
	return searchResult; //copy constructor;
}

PhoneBook FindPhone(const PhoneBook& phoneBook, const char* phone)
{
	PhoneBook searchResult;
	Contact* contact = phoneBook.SearchPhone(phone, phoneBook.Min());
	while (contact)
	{
		searchResult.Add(contact->GetSurname(), contact->GetName(), contact->GetPhone());
		contact = phoneBook.Next(contact);
		if (contact)
		{
			contact = phoneBook.SearchPhone(phone, contact);
		}
	}
	return searchResult; //copy constructor;
}

void HideCursor(const bool hide = true)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO     cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = !hide; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}

inline void GotoXY(short x, short y)
{
	COORD coord = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

inline int CurX()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
		return -1;
	return csbi.dwCursorPosition.X;
}

inline int CurY()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
		return -1;
	return csbi.dwCursorPosition.Y;
}

inline void SetColour(const int colour)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colour);
}

void MessageBox(const char* message, const bool error = false)
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
	system("cls");
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
	system("cls");
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


void main()
{
	system("color F0"); //AAA
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
	phoneBook.Add("surname3", "name1", "01");
	phoneBook.Add("surname4", "name1", "03");
	phoneBook.Add("surname2", "name1", "01");
	phoneBook.Add("surname1", "name1", "05");
	phoneBook.Add("surname2", "name2", "02");
	phoneBook.Add("ta", "name1", "01");
	phoneBook.Add("te", "name1", "05");
	phoneBook.Add("tea", "name2", "02");
	phoneBook.Add("teb", "name2", "02");
	phoneBook.Add("ta", "name1", "05");
	phoneBook.Add("teb", "name2", "07");

	enum { F1 = 59, F2, F3, F4, F5, F9 = 67, F10 };
	enum { INACTIVE = -1, ADD = 0, EDIT, DEL, FIND, PRINT, LOAD = 0, SAVE };


	Contact* selectedContact = phoneBook.Min();//const
	char toolTipMessage[80];
	strcpy(toolTipMessage, "Type surname or press UP and DOWN arrow to select the contact");
	bool errorMessage = false;
	while (true)
	{
		system("cls");
		contactMenu.showMenu();
		dbMenu.showMenu();

		if (toolTipMessage[0]) MessageBox(toolTipMessage, errorMessage);
		HideCursor();

		Contact* firstContact = phoneBook.Min(); //const
		Contact* contact = firstContact; //const

		const int baseX = 0;
		const int baseY = 5;
		GotoXY(baseX, baseY);

		const short activeColour = 0x70;
		const short inactiveColour = 0xF0;
		SetColour(inactiveColour);

		int itemsCount = 0;

		if (phoneBook.IsEmpty())
		{
			cout << "Phone book is empty.\n";
		}
		else
		{
			if (!selectedContact) { selectedContact = firstContact; }

			while (contact)
			{
				GotoXY(baseX, baseY + itemsCount++);
				cout << contact;
				contact = phoneBook.Next(contact);
			}

			contact = firstContact;
			int selectedPosition = 0;

			while (contact && contact != selectedContact)
			{
				contact = phoneBook.Next(contact);
				selectedPosition++;
			}

			if (contact)
			{
				SetColour(activeColour);
				GotoXY(baseX, baseY + selectedPosition);
				cout << contact;
				SetColour(inactiveColour);
			}
			else
			{
				cout << "Error: selected contact wasn't found.\n";
				break;
			}
		}

		char mask[20];
		mask[0] = '\0';

		while (true)
		{
			bool inputExit = false;
			int curY = CurY();

			if (toolTipMessage[0]) MessageBox(toolTipMessage, errorMessage);
			toolTipMessage[0] = '\0';
			errorMessage = false;
			GotoXY(baseX, curY);
			enum{ KEY_ENTER = 13, KEY_ESCAPE = 27, KEY_F1 = 59, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F9 = 67, KEY_F10, KEY_UP = 72, KEY_DOWN = 80, KEY_DELETE = 83 };

			unsigned char control = getch();

			if (control == 0 || control == 224 && kbhit())
			{
				switch (getch())
				{
				case KEY_F1:
				{
					//if (contactMenu.status[ADD])
					system("cls");
					contactMenu.showMenu(ADD);
					dbMenu.showMenu(INACTIVE);
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

					if ((!strlen(surname) && !strlen(name)) || !strlen(phone))
					{
						strcpy(toolTipMessage, "Contact hasn't been added: empty fields");
						errorMessage = true;
					}
					else if (contact = phoneBook.Add(surname, name, phone))
					{
						strcpy(toolTipMessage, "Contact has been successfully added");
					}
					else
					{
						strcpy(toolTipMessage, "Error: contact hasn't been added");
						errorMessage = true;
					}
					inputExit = true;
				}
					break;

				case KEY_UP:
					if (curY > baseY)
					{
						mask[0] = '\0';
						GotoXY(baseX, curY);
						cout << contact;
						GotoXY(baseX, --curY);
						contact = phoneBook.Previous(contact);
						SetColour(activeColour);
						cout << contact;
						SetColour(inactiveColour);
					}
					break;
				case KEY_DOWN:
					if (curY < baseY + itemsCount - 1)
					{
						mask[0] = '\0';
						GotoXY(baseX, curY);
						cout << contact;
						GotoXY(baseX, ++curY);
						contact = phoneBook.Next(contact);
						SetColour(activeColour);
						cout << contact;
						SetColour(inactiveColour);
					}
					break;
				case KEY_DELETE:
				{
					if (phoneBook.IsEmpty())
					{
						strcpy(toolTipMessage, "Phone book is empty");
						errorMessage = true;
						inputExit = true;
						break;
					}

					Contact* tmp = contact;

					if (phoneBook.Next(tmp))
					{
						tmp = phoneBook.Next(tmp);
					}
					else if (phoneBook.Previous(tmp))
					{
						tmp = phoneBook.Previous(tmp);
					}
					else
					{
						tmp = phoneBook.Root();
					}

					if (phoneBook.Delete(contact))
					{
						strcpy(toolTipMessage, "Contact has been deleted");
					}
					else
					{
						strcpy(toolTipMessage, "Contact hasn't been deleted");
						errorMessage = true;
					}

					SetColour(systemColour);
					contact = tmp;
					inputExit = true;
					break;
				}
					break;

				case F4:
				{
					if (phoneBook.IsEmpty())
					{
						strcpy(toolTipMessage, "Phone book is empty");
						errorMessage = true;
						inputExit = true;
						break;
					}

					system("cls");
					contactMenu.showMenu(FIND);
					dbMenu.showMenu(INACTIVE); //**active??

					const char* subItems[2] = { "Surname", "Phone" };
					int index = SubMenu(subItems, 2, 10, 33, 3);

					if (index == -1){
						inputExit = true;
						break;
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
						errorMessage = true;
					}
					else
					{
						PrintContacts(searchResult.Root());
					}

					int key=PressAnyKey(searchResult);

					if (key == 1) phoneBook = searchResult;
					contact = phoneBook.Min();
					inputExit = true;
					break;
				}
					break;

				case F5:
				{
					if (phoneBook.IsEmpty())
					{
						strcpy(toolTipMessage, "Phone book is empty");
						errorMessage = true;
						inputExit = true;
						break;
					}

					system("cls");
					contactMenu.showMenu(PRINT);
					dbMenu.showMenu(INACTIVE);//******active??

					const int subItemsCount = 3;
					const char* subItems[subItemsCount] = { "Print all", "Contacts", "Phones" };
					int index = SubMenu(subItems, subItemsCount, 10, 43, 3);

					if (index == -1){
						inputExit = true;
						break;
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
							searchResult.Add(contact->GetSurname(), contact->GetName(), contact->GetPhone());
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
								searchResult.Add(contact->GetSurname(), contact->GetName(), contact->GetPhone());
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
					int key=PressAnyKey(*activeDB);

					if (key == 1) phoneBook = *activeDB;
					contact = phoneBook.Min();

					inputExit = true;
				}
					break;

				case F9:
				{
					phoneBook=OpenDB();
					contact = phoneBook.Min();
					inputExit = true;
				}
					break;

				case F10:
				{
					SaveDB(phoneBook);
					contact = phoneBook.Min();
					inputExit = true;
				}
					break;
				}
			}
			else if (control == KEY_ENTER)
			{
				if (phoneBook.IsEmpty())
				{
					strcpy(toolTipMessage, "Phone book is empty");
					errorMessage = true;
					break;
				}

				HideCursor(false);
				SetColour(0xB0);
				char fields[3][20] = { "Surname", "Name", "Phone" };
				for (int i = 0; i < 3; ++i)
				{
					GotoXY(0, curY);
					cout << setw(80) << ' ';
					GotoXY(0, curY);
					cout << fields[i] << ": ";
					int len = (i != 2) ? 20 : 15;
					cin.getline(fields[i], len);
				}

				enum{ SURNAME, NAME, PHONE };

				if (!phoneBook.ValidInput(contact, fields[SURNAME], fields[NAME], fields[PHONE]))
				{
					strcpy(toolTipMessage, "Contact hasn't been changed");
					errorMessage = true;
					HideCursor(true);
					break;
				}

				if (!fields[SURNAME][0] && !fields[NAME][0] && !fields[PHONE][0])
				{
					strcpy(toolTipMessage, "Contact hasn't been changed");
					errorMessage = true;
					HideCursor(true);
					break;
				}

				if (!fields[SURNAME][0]) { strcpy(fields[SURNAME], contact->GetSurname()); }
				if (!fields[NAME][0]) { strcpy(fields[NAME], contact->GetName()); }
				if (!fields[PHONE][0]) { strcpy(fields[PHONE], contact->GetPhone()); }

				if (strcmp(fields[SURNAME], contact->GetSurname()))
				{
					Contact* tmp = contact;
					contact = phoneBook.Add(fields[SURNAME], fields[NAME], fields[PHONE]);
					if (contact)
					{
						phoneBook.Delete(tmp);
					}
					else
					{
						strcpy(toolTipMessage, "Such contact already exist. Contact hasn't been changed");
						errorMessage = true;
						HideCursor(true);
						break;
					}
				}
				else
				{
					contact->SetName(fields[NAME]);
					contact->SetPhone(fields[PHONE]);
				}

				strcpy(toolTipMessage, "Contact has been changed");
				HideCursor(true);
				break;
			}
			else if ((control > 64 && control<91) || (control>96 && control < 123) || (control > 47 && control < 58) || control == 8)
			{
				if (phoneBook.IsEmpty())
				{
					strcpy(toolTipMessage, "Phone book is empty");
					errorMessage = true;
					break;
				}

				const int maskLen = strlen(mask);

				if ((control == 8) && maskLen > 0)
				{
					mask[maskLen - 1] = '\0';
				}
				else if (maskLen < 19 && control != 8)
				{
					mask[maskLen] = control;
					mask[maskLen + 1] = '\0';
				}

				GotoXY(baseX, curY);
				cout << contact;

				curY = baseY;
				contact = phoneBook.Min();
				Contact* prevContact = contact;
				while (contact && strcmp(contact->GetSurname(), mask) < 0)
				{
					prevContact = contact;
					contact = phoneBook.Next(contact);
					curY++;
				}

				if (contact != phoneBook.Min() && !contact)
				{
					contact = prevContact;
					curY--;
				}

				GotoXY(baseX, curY);
				SetColour(activeColour);
				cout << contact;
				SetColour(inactiveColour);

				strcpy(toolTipMessage, "Search mask: ");
				strcat(toolTipMessage, mask);
			}
			else if (control == KEY_ESCAPE)
			{
				contact = nullptr;
				break;
			}

			if (inputExit) break;
		}

		SetColour(systemColour);
		selectedContact = contact;
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
			phoneBook = OpenDB();
			key = 1;
			break;
		case 68:
			SaveDB(phoneBook);
			key=PressAnyKey(phoneBook);
			break;
		}
	}
	return key;
}