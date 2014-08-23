/*
Создать класс СПРАВОЧНИК со следующими полями:

Название фирмы
Владелец
Телефон
Адрес
Род деятельности

Реализовать следующие возможности:
Поиск по названию
Поиск по владельцу
Поиск по номеру телефона
Поиск по роду деятельности
Показ всех записей и добавление
Вся информация, естественно, хранится в файле с возможностью дозаписи.
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <conio.h>
#include <io.h>

#include "BTree.h"
#include "SelectList.h"
#include "Menu.h"

using namespace std;

const int systemColour = 0xF0;

ostream& operator<<(ostream& stream, const Leaf* const leaf);
int SubMenu(const char* items[], const int itemsCount, const int baseX, const int baseY);
bool WriteLeafToFile(Leaf* leaf, ofstream& out);
void SaveDB(BTree& bTree, const char* name);
BTree* OpenDB(const char* name);

void main()
{
	system("color F0");
	const char searchItemsNumber = 4;
	const char* searchItems[searchItemsNumber] = { "F1 Firm", "F2 Owner", "F3 Phone", "F4 Branch" };
	const int searchX = 0;
	const int searchY = 0;
	Menu searchMenu(" Search by ", searchItemsNumber, searchItems, searchX, searchY);

	const char dbItemsNumber = 3;
	const char* dbItems[dbItemsNumber] = { "F9 Add", "F10 Edit", "F11 Del" };
	const int dbX = 47;
	const int dbY = 0;
	Menu dbMenu("DB management", dbItemsNumber, dbItems, dbX, dbY);

	HideCursor(false);
	cout << "DB opening...\n\nEnter file name ( db, for example): ";
	char dbPath[250];
	cin.getline(dbPath, 250);
	HideCursor(true);

	BTree db = *OpenDB(dbPath);

	enum { INACTIVE = -1, FIND_FIRM, FIND_OWNER, FIND_PHONE, FIND_BRANCH, ADD = 0, EDIT, DEL };
	int activePage = FIND_FIRM;

	SelectList list(&db, 0, 5);
	while (true)
	{
		system("cls");
		searchMenu.showMenu(activePage);
		dbMenu.showMenu();

		list.ShowStatus();
		list.ResetMessage();
		list.ShowList(activePage);

		while (true)
		{
			enum{ KEY_ENTER = 13, KEY_ESCAPE = 27, KEY_F1 = 59, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F9 = 67, KEY_F10, KEY_F11 = 133, KEY_UP = 72, KEY_DOWN = 80, KEY_DELETE = 83 };
			unsigned char control = getch();

			if (control == 0 || control == 224 && kbhit())
			{
				unsigned char secondByte = getch();
				if (secondByte == KEY_F1)
				{
					activePage = FIND_FIRM;
					list.ResetMessage();
					break;
				}
				else if (secondByte == KEY_F2)
				{
					activePage = FIND_OWNER;
					list.ResetMessage();
					break;
				}
				else if (secondByte == KEY_F3)
				{
					activePage = FIND_PHONE;
					list.ResetMessage();
					break;
				}
				else if (secondByte == KEY_F4)
				{
					activePage = FIND_BRANCH;
					list.ResetMessage();
					break;
				}
				else if (secondByte == KEY_F5)
				{
					if (list.ReviewStatus())
					{
						system("cls");
						searchMenu.showMenu(activePage);
						dbMenu.showMenu();
					}
					list.Search(activePage, true);
				}
				else if (secondByte == KEY_F9)
				{
					system("cls");
					searchMenu.showMenu(INACTIVE);
					dbMenu.showMenu(ADD);
					if (list.AddNode())
					{
						SaveDB(db, dbPath);
					}
					break;
				}
				else if (secondByte == KEY_F10)
				{
					system("cls");
					searchMenu.showMenu(INACTIVE);
					dbMenu.showMenu(EDIT);
					if (list.EditNode())
					{
						SaveDB(db, dbPath);
					}
					break;
				}
				else if (secondByte == KEY_F11 || secondByte == KEY_DELETE)
				{
					if (list.DeleteNode())
					{
						SaveDB(db, dbPath);
					}
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
			else if ((control > 31 && control < 123) || control == 8)
			{
				list.MaskSearch(control, activePage);
			}
			else if (control == KEY_ENTER)
			{
				system("cls");
				searchMenu.showMenu(activePage);
				dbMenu.showMenu();
				if (list.QuitReview())
				{
					list.ShowList(activePage);
				}
				else
				{
					list.ShowSelectedItem();
				}
			}
			else if (control == KEY_ESCAPE)
			{
				GotoXY(0, 4);
				exit(0);
			}
		}
		SetColour(systemColour);
	}
}

ostream& operator<<(ostream& stream, const Leaf* const leaf)
{
	stream << "Trade name: " << leaf->mData.firm << "\n\n";
	stream << "Owner: " << leaf->mData.owner << "\n\n";
	stream << "Phone number: " << leaf->mData.phone << "\n\n";
	stream << "Address: " << leaf->mData.address << "\n\n";
	stream << "Branch: " << leaf->mData.branch << "\n\n";
	return stream;
}

bool WriteLeafToFile(Leaf* leaf, ofstream& out)
{
	if (leaf)
	{
		Data buffer = leaf->GetData();
		if (out.write((char*)&buffer, sizeof(buffer)))
		{
			WriteLeafToFile(leaf->GetLeft(), out);
			WriteLeafToFile(leaf->GetRight(), out);
		}
		else
		{
			return false;
		}
	}
	return true;
}


void SaveDB(BTree& bTree, const char* name)
{
	ofstream out(name, ios::out | ios::binary);
	if (!out || !WriteLeafToFile(bTree.Root(), out))
	{
		cout << "Error: write failure\n";
		exit(1);
	}

	out.close();
}

BTree* OpenDB(const char* name)
{
	BTree* openedDB = new BTree;

	ifstream in(name, ios::in | ios::binary);
	if (!in)
	{
		cout << "\nError: read failure.\n\n";
		exit(1);
	}

	while (!in.eof())
	{
		Data buffer;
		in.read((char*)&buffer, sizeof(buffer));
		openedDB->Add(buffer);
	}

	in.close();
	return openedDB;
}
