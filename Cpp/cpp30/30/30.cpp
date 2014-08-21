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
bool WriteLeafToFile(Leaf* leaf, FILE* pFile);
bool SaveDB(BTree& bTree, const char* name);
BTree OpenDB(const char* name);


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

	BTree db = OpenDB(dbPath);

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
		list.ShowList();

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
					break;
				}
				else if (secondByte == KEY_F2)
				{
					activePage = FIND_OWNER;
					break;
				}
				else if (secondByte == KEY_F3)
				{
					activePage = FIND_PHONE;
					break;
				}
				else if (secondByte == KEY_F4)
				{
					activePage = FIND_BRANCH;
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
			else if ((control > 64 && control<91) || (control>96 && control < 123) || (control > 47 && control < 58) || control == 8 || control == 32)
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
					list.ShowList();
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


int SubMenu(const char* items[], const int itemsCount, const int baseX, const int baseY)
{
	int itemMaxLen = 0;
	for (int i = 0; i < itemsCount; ++i)
	{
		if (itemMaxLen < strlen(items[i])) { itemMaxLen = strlen(items[i]); }
	}
	itemMaxLen++;

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


bool WriteLeafToFile(Leaf* leaf, FILE* pFile)
{
	if (leaf)
	{
		Data buffer = leaf->GetData();
		if (fwrite(&buffer, sizeof(buffer), 1, pFile))
		{
			WriteLeafToFile(leaf->GetLeft(), pFile);
			WriteLeafToFile(leaf->GetRight(), pFile);
		}
		else
		{
			return false;
		}
	}
	return true;
}


bool SaveDB(BTree& bTree, const char* name)
{
	FILE* pFile = fopen(name, "w+");
	if (!pFile)
	{
		cout << "Error: write failure\n";
		exit(1);
	}
	WriteLeafToFile(bTree.Root(), pFile);
	fclose(pFile);

	return true;
}

BTree OpenDB(const char* name)
{
	BTree openedDB; //pointer???

	FILE* pFile = fopen(name, "r+");
	if (!pFile)
	{
		cout << "\nError: read failure.\n\n";
		exit(1);
	}

	while (!feof(pFile))
	{
		Data buffer;
		fread(&buffer, sizeof(buffer), 1, pFile);
		openedDB.Add(buffer);
	}
	return openedDB;
}
