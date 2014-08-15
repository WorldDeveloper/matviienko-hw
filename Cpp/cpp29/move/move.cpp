/*
Необходимо создать следующий набор программ:
Программа для перемещения каталогов (перемещаются все вложенные папки и файлы).


Для функций копирования и перемещения выполнить те же действия: 1.
Перезаписать? 2. Пропустить? 3. Перезаписывать для всех? 4. Отмена?
Параметры программы передаются через командную строку. Например,
- move.exe c:\A d:\B
*/

#include <iostream>
#include <direct.h>
#include <stdio.h>
#include <conio.h>
#include <iomanip>
#include <windows.h>
#include <io.h>
#include "Graphics.h"

using namespace std;

bool MoveObject(const char* source, const char* destination, bool& overwriteAll);
void MoveNestedObject(const char* source, const char* destination, bool& overwriteAll);
int SubMenu(const char* items[], const int itemsCount, const int baseX, const int baseY);
bool IsDir(const char* path);
bool ConfirmOverwrite(bool& overwriteAll);

void main(int argc, char* argv[])
{
	HideCursor(true);

	if (argc != 3)
	{
		cout << "Error: incorrect parametrs number.\n";
		exit(1);
	}

	char source[_MAX_PATH];
	strcpy(source, argv[1]);

	char destination[_MAX_PATH];
	strcpy(destination, argv[2]);

	if (_access(source, 00) == -1)
	{
		cout << "Error: source object doesn't exist.\n";
		exit(1);
	}

	bool overwriteAll = false;
	MoveObject(source, destination, overwriteAll);
	cout << "\nMoving finished.\n";
}


bool MoveObject(const char* source, const char* destination, bool& overwriteAll)
{
	const bool dir = IsDir(source);
	const char* object = dir ? "folder" : "file";

	if (dir) { cout << source << " ->\n    " << destination << "\n"; }
	else { cout << "\t" << source << " ->\n" << "\t\t" << destination << "\n"; }

	if (_access(destination, 00) == 0)
	{
		if (!overwriteAll)
		{
			cout << "...Overwrite an existing " << object << "?\n";
			if (!ConfirmOverwrite(overwriteAll))
			{
				cout << "...Skipped\n";
				return false;
			}
		}

		if (_access(destination, 02) == -1)
		{
			if (!overwriteAll)
			{
				cout << "..." << object << " is read-only. Overwrite anyway?\n";
				if (!ConfirmOverwrite(overwriteAll))
				{
					cout << "...Skipped\n";
					return false;
				}
			}

			wchar_t* dest = new wchar_t[_MAX_PATH];
			MultiByteToWideChar(0, 0, destination, -1, dest, _MAX_PATH);
			SetFileAttributes(dest, FILE_ATTRIBUTE_NORMAL);
			delete[] dest;
		}

		if (dir)
		{
			MoveNestedObject(source, destination, overwriteAll);
			_rmdir(source);
			return true;
		}
		else
		{
			remove(destination);
		}
	}

	if (rename(source, destination) != 0)
	{
		cout << "Error: can't move " << source << "\n";
		cout << "Moving stopped\n";
		exit(1);
	}

	return true;
}

void MoveNestedObject(const char* source, const char* destination, bool& overwriteAll)
{
	char searchMask[_MAX_PATH];
	strcpy(searchMask, source);
	strcat(searchMask, "\\*.*");

	_finddata_t fileinfo;
	long result = _findfirst(searchMask, &fileinfo);
	long findNext = result;

	while (findNext != -1)
	{
		if (strcmp(fileinfo.name, ".") &&
			strcmp(fileinfo.name, ".."))
		{
			char nestedSource[_MAX_PATH];
			strcpy(nestedSource, source);
			strcat(nestedSource, "\\");
			strcat(nestedSource, fileinfo.name);

			char nestedDestination[_MAX_PATH];
			strcpy(nestedDestination, destination);
			strcat(nestedDestination, "\\");
			strcat(nestedDestination, fileinfo.name);

			MoveObject(nestedSource, nestedDestination, overwriteAll);
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

bool ConfirmOverwrite(bool& overwriteAll)
{
	const char* sub[4] = { "     Skip ", " Overwrite this", " Overwrite all", "   Cancel" };
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
		overwriteAll = true;
		return true;
		break;
	default:
		cout << "\nOperation was canceled.\n";
		exit(0);
		break;
	}
}