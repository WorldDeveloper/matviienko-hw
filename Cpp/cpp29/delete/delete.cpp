/*
Необходимо создать следующий набор программ:
Программа для удаления каталогов (удаляются все вложенные папки и файлы).

В том случае, если у удаляемого файла (каталога) установлен атрибут Read-Only,
необходимо вывести следующее меню: 1. Удалять? 2. Пропустить? 3.Удалять для всех? 4. Отмена?
Параметры программы передаются через командную строку. Например,
- delete.exe c:\A
*/

#include <iostream>
#include <direct.h>
#include <stdio.h>
#include <conio.h>
#include <iomanip>
#include <new>
#include <windows.h>
#include <io.h>
#include "Graphics.h"

using namespace std;

bool DeleteFile(const char* path, bool& deleteAll);
void DeleteNestedFiles(const char* path, bool& deleteAll);
int SubMenu(const char* items[], const int itemsCount, const int baseX, const int baseY);
bool IsDir(const char* path);
bool ConfirmDelete(bool& deleteAll);

void main(int argc, char* argv[])
{
	HideCursor(true);

	if (argc != 2)
	{
		cout << "Error: incorrect parametrs number.\n";
		exit(1);
	}

	char path[_MAX_PATH];
	strcpy(path, argv[1]);

	if (_access(path, 00) == -1)
	{
		cout << "Error: file doesn't exist.\n";
		exit(1);
	}

	bool deleteAll = false;
	if (!DeleteFile(path, deleteAll))
	{
		cout << "Deleting stopped.\n";
	}
	else
	{
		cout << "\nDeleting finished.\n";
	}
}


bool DeleteFile(const char* path, bool& deleteAll)
{
	const bool dir = IsDir(path);
	const char* object = dir ? "folder" : "file";

	if (dir)
	{
		cout << endl;
		DeleteNestedFiles(path, deleteAll);
		cout << endl;
	}

	if (_access(path, 00) == 0 && _access(path, 02) == -1)
	{
		if (!deleteAll)
		{
			cout << "..." << object << " is read-only. Delete anyway " << path << "?\n";
			if (!ConfirmDelete(deleteAll))
			{
				cout << "...Skipped\n";
				return false;
			}
		}

		wchar_t* dest = new wchar_t[_MAX_PATH];
		MultiByteToWideChar(0, 0, path, -1, dest, _MAX_PATH);
		SetFileAttributes(dest, FILE_ATTRIBUTE_NORMAL);
		delete[] dest;
	}

	if ((!dir && remove(path) != 0) ||
		(dir&& _rmdir(path) == -1))
	{
		cout << "    Can't delete " << path << "\n";
		cout << "Deleting stopped\n";
		exit(1);
	}

	if (!dir) { cout << "\t"; }
	cout << path << "\n";
}

void DeleteNestedFiles(const char* path, bool& deleteAll)
{
	char searchMask[_MAX_PATH];
	strcpy(searchMask, path);
	strcat(searchMask, "\\*.*");

	_finddata_t fileinfo;
	long result = _findfirst(searchMask, &fileinfo);
	long findNext = result;

	while (findNext != -1)
	{
		if (strcmp(fileinfo.name, ".") &&
			strcmp(fileinfo.name, ".."))
		{
			char nestedPath[_MAX_PATH];
			strcpy(nestedPath, path);
			strcat(nestedPath, "\\");
			strcat(nestedPath, fileinfo.name);

			DeleteFile(nestedPath, deleteAll);
		}

		findNext = _findnext(result, &fileinfo);
	}
	_findclose(result);
}


int SubMenu(const char* items[], const int itemsCount, const int baseX, const int baseY)
{
	int itemMaxLen = 0;
	for (int i = 0; i < itemsCount; ++i)
	{
		if (itemMaxLen < strlen(items[i])) { itemMaxLen = strlen(items[i]); }
	}
	itemMaxLen++;

	if (itemsCount < 2 || baseX + itemsCount*itemMaxLen>80)
	{
		cout << "\nSub menu error.\n";
		return -1;
	}
	const short systemColour = 0x07;
	const short activeColour = 0x70;
	const short inactiveColour = 0x78;

	SetColour(activeColour);
	GotoXY(baseX, baseY);
	cout << setw(itemMaxLen) << left << items[0];
	SetColour(inactiveColour);
	for (int i = 1; i < itemsCount; ++i)
	{
		GotoXY(baseX + i*itemMaxLen, baseY);
		cout << setw(itemMaxLen) << left << items[i];
	}

	const char** curItem = items;
	int curX = baseX;
	int selectedItem = -1;
	enum{ KEY_ENTER = 13, KEY_ESCAPE = 27, KEY_LEFT = 75, KEY_RIGHT = 77 };

	while (true)
	{
		unsigned char control = getch();

		if (control == 224 && kbhit())
		{
			switch (getch())
			{
			case KEY_LEFT:
				if (curItem > items)
				{
					GotoXY(curX, baseY);
					cout << setw(itemMaxLen) << left << *curItem;
					curItem--;
					curX -= itemMaxLen;
					GotoXY(curX, baseY);
					SetColour(activeColour);
					cout << setw(itemMaxLen) << left << *curItem;
					SetColour(inactiveColour);
				}
				break;
			case KEY_RIGHT:
				if (curItem < items + itemsCount - 1)
				{
					GotoXY(curX, baseY);
					cout << setw(itemMaxLen) << left << *curItem;
					curItem++;
					curX += itemMaxLen;
					GotoXY(curX, baseY);
					SetColour(activeColour);
					cout << setw(itemMaxLen) << left << *curItem;
					SetColour(inactiveColour);
				}
				break;
			}
		}
		else if (control == KEY_ENTER)
		{
			selectedItem = curItem - items;
			break;
		}
		else if (control == KEY_ESCAPE)
		{
			selectedItem = -1;
			break;
		}
	}

	SetColour(systemColour);
	GotoXY(baseX, baseY);
	cout << setw(79 - baseX) << " " << endl;
	GotoXY(baseX, baseY);

	return selectedItem;
}

bool IsDir(const char* path)
{
	struct _finddata_t find;
	long result = _findfirst(path, &find);
	_findclose(result);
	if (find.attrib & _A_SUBDIR){ return true; }

	return false;
}

bool ConfirmDelete(bool& deleteAll)
{
	const char* sub[4] = { "   Skip ", " Delete this", " Delete all", "   Cancel" };
	const short choice = SubMenu(sub, 4, 0, CurY());

	GotoXY(0, CurY() - 1);
	cout << setw(79) << " " << endl;
	GotoXY(0, CurY() - 1);

	switch (choice)
	{
	case 0:
		return false;
		break;
	case 1:
		return true;
		break;
	case 2:
		deleteAll = true;
		return true;
		break;
	default:
		cout << "\nOperation was canceled.\n";
		exit(0);
		break;
	}
}