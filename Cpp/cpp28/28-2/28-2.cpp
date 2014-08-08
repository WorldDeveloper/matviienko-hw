/*
Реализовать базу данных ГАИ по штрафным квитанциям с помощью бинарного дерева.
Ключом будет служить номер автомашины, значением узла - список правонарушений.
Если квитанция добавляется в первый раз, то в дереве появляется новый узел,
а в списке данные по правонарушению; если нет, то данные заносятся в существующий список.
Необходимо также реализовать следующие операции:

Полная распечатка базы данных (по номерам машин и списку правонарушений, числящихся за ними)
Распечатка данных по заданному номеру
Распечатка данных по диапазону номеров
*/
#include <iostream>
#include <conio.h>
#include "menu.h"
#include "ForwardList.h"
#include "BTree.h"
using namespace std;

bool DBEmpty(const BTree& db);
void PrintDB(const Leaf* const root);
bool CheckDate(const char* const date);
void AddOffence(BTree& db);
void FindCarNumber(const BTree& db);
void FindCarNumbers(const BTree& db);

void main()
{
	system("color F0");
	const char menuItemsNumber = 5;
	const char menuItemMaxLength = 15;
	const char* menuItems[menuItemsNumber] = { "F1 Add offence", "F2 Print", "F3 Find number", "F4 Find range", "F5 Exit" };
	const int menuX = 0;
	const int menuY = 0;
	Menu menu("Menu", menuItemsNumber, menuItemMaxLength, menuItems, menuX, menuY);

	BTree db;
	db.Add("110", "01.01.2014", "Speeding");
	db.Add("101", "01.02.2014", "Smoking and driving");
	db.Add("111", "01.03.2014", "Drink driving");
	db.Add("112", "01.01.2014", "Careless driving");
	db.Add("103", "01.02.2014", "Failure to wear a seatbelt");
	db.Add("110", "01.03.2014", "Speeding");
	db.Add("101", "01.04.2014", "Drink driving");
	db.Add("100", "01.05.2014", "Failure to wear a seatbelt");
	PrintDB(db.Root());

	while (true)
	{
		system("cls");
		menu.showMenu();
		HideCursor(true);

		while (true)
		{
			enum{ KEY_F1 = 59, KEY_F2, KEY_F3, KEY_F4, KEY_F5 };
			unsigned char control = getch();

			if (control == 0 && kbhit())
			{
				system("cls");
				menu.showMenu();

				switch (getch())
				{
				case KEY_F1:
					HideCursor(false);
					AddOffence(db);
					break;

				case KEY_F2:
					if (!DBEmpty(db)) { PrintDB(db.Root()); }
					break;

				case KEY_F3:
					if (!DBEmpty(db)) { FindCarNumber(db); }
					break;

				case KEY_F4:
					if (!DBEmpty(db)) { FindCarNumbers(db); }
					break;

				case KEY_F5:
					exit(0);
					break;
				}
			}
		}
	}
}

bool DBEmpty(const BTree& db)
{
	if (db.IsEmpty()) cout << "\n Database is empty\n";
	return db.IsEmpty();
}


void PrintDB(const Leaf* const root)
{
	if (root)
	{
		PrintDB(root->GetLeft());
		cout << root << endl;
		PrintDB(root->GetRight());
	}
}


bool CheckDate(const char* const date)
{
	if (strlen(date) != 10) return false;

	char tmpDate[11];
	strcpy(tmpDate, date);
	tmpDate[2] = '\0';
	int day = atoi(tmpDate);

	strcpy(tmpDate, &date[3]);
	tmpDate[2] = '\0';
	int month = atoi(tmpDate);
	if (month<1 || month>12) return false;

	strcpy(tmpDate, &date[6]);
	tmpDate[4] = '\0';
	int year = atoi(tmpDate);
	if (!year) return false;

	char delimiter[3];
	delimiter[0] = date[2];
	delimiter[1] = date[5];
	delimiter[2] = '\0';
	if (strcmp("..", delimiter)) return false;

	unsigned short monthlen[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	if (month == 2 && (!(year % 4) && (year % 100) || !(year % 400)))
		monthlen[1]++;

	if (day<1 || day>monthlen[month - 1])
		return false;

	return true;
}


void AddOffence(BTree& db)
{
	cout << "Enter a registration number: ";
	char carNumber[10];
	cin.getline(carNumber, 10);
	cin.clear();
	fflush(stdin);

	cout << "Enter a date: ";
	char date[11];
	cin.getline(date, 11);
	cin.clear();

	cout << "Enter an offence: ";
	char offence[500];
	cin.getline(offence, 500);
	cin.clear();

	if (!CheckDate(date))
	{
		cout << "\n Record hasn't been added. Incorrect date.\n";
		return;
	}

	Leaf* result = db.Add(carNumber, date, offence);
	if (result)
	{
		cout << "\nRecord has been successfully added.\n\n";
		cout << result;
	}
	else
	{
		cout << "\n Record hasn't been added.\n";
	}
}


void FindCarNumber(const BTree& db)
{
	cout << "Enter a registration number: ";
	char carNumber[10];
	cin.getline(carNumber, 10);

	Leaf* leaf = db.FindCarNumber(carNumber);

	cout << endl;
	if (leaf)
	{
		cout << leaf;
	}
	else
	{
		cout << "Such registration number hasn't been finded.";
	}
}

void FindCarNumbers(const BTree& db)
{
	cout << "Enter the first registration number: ";
	char carNumberBegin[10];
	cin.getline(carNumberBegin, 10);

	cout << "Enter the last registration number: ";
	char carNumberEnd[10];
	cin.getline(carNumberEnd, 10);

	if (strcmp(carNumberBegin, carNumberEnd) > 0)
	{
		cout << "\nError: incorrect range.";
		return;
	}

	Leaf* leaf = db.Min();
	while (leaf && strcmp(leaf->CarNumber(), carNumberBegin) < 0)
	{
		leaf = db.Next(leaf);
	}

	cout << endl;
	if (leaf)
	{
		while (leaf && strcmp(leaf->CarNumber(), carNumberEnd) <= 0)
		{
			cout << leaf;
			leaf = db.Next(leaf);
		}
	}
	else
	{
		cout << "\nSuch registration numbers hasn't been finded.";
	}
}
