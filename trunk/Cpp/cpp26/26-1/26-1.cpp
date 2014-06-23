/*
Создать имитацию игры "однорукий бандит". Например, при нажатии
кнопки "Enter" происходит "вращение" трех барабанов (количество вращений
каждого из них выбирается случайно), на которых изображены разные значки;
и если выпадает  определенная комбинация, то игрок получает какой-то выигрыш.
*/

#include <iostream>
#include "Bandit.h"
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <conio.h>
using namespace std;


void GotoXY(short  x, short  y);
inline void HideCursor(bool hide);
void InitBandit(Rell* rell, const int rellCount);
void TurnRells(Rell* rell, const int rellCount, const int restCount);

void main()
{
	srand(time(NULL)); 
	HideCursor(true);

	time_t t1;
	time(&t1);
	time_t t2 = t1 + 3;

	GotoXY(30, 10);
	cout << "SLOT MACHINE";

	while (t1 < t2)
	{
		time(&t1);
	}
	GotoXY(30, 10);
	cout << "             ";
		
	const int rellCount = 3;
	Rell rell[rellCount];
	InitBandit(rell, rellCount);

	int credit = 100;
	GotoXY(28, 1);
	cout << "Credit: " << credit;

	t1 = 0;

	GotoXY(20, 3);
	cout << "Press Enter to continue the game";
	while (true)
	{
		char input = getch();
		time(&t2);
		if (input == 13 && t1+1<=t2)
		{
			GotoXY(20, 3);
			cout << "	   Game running...		";
			GotoXY(20, 18);
			cout << "								";

			TurnRells(rell, rellCount, rellCount);
			TurnRells(rell, rellCount, rellCount - 1);
			TurnRells(rell, rellCount, rellCount - 2);

			const int r1 = rell[0].Begin();
			const int r2 = rell[1].Begin();
			const int r3 = rell[2].Begin();
	
			GotoXY(20, 18); 
			if (r1 == r2 && r2 == r3)
			{
				credit += 100;				
				cout << "You have won the jackpot!";
			}
			else if (r1 == r2 || r2== r3|| r1==r3)
			{
				credit += 5;
				cout << "	  You have won 5$";
			}
			else
			{
				credit--;
				cout << "	  You have lost 1$";
			}			

			GotoXY(28, 1);
			cout << "Credit:        ";
			GotoXY(36, 1); 
			cout<< credit;

			GotoXY(20, 3);
			cout << "Press Enter to continue the game";

			time(&t1);
		}
		else if (input == 27)
		{
			GotoXY(20, 18);
			cout << "	    Game over!					";
			GotoXY(20, 19);
			exit(0);
		}
	}
}


void GotoXY(short  x, short  y)
{
	COORD coord = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

inline void HideCursor(bool hide)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO     cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = !hide; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}

void InitBandit(Rell* rell, const int rellCount)
{
	for (int i = 0; i < rellCount; ++i)
	{
		int random = rand() % 50;
		for (int j = 0; j < random; ++j)
		{
			rell[i].Pop();
		}
	}
}

void TurnRells(Rell* rell, const int rellCount, const int restCount)
{
	short y = 8;
	short x = 30;
	time_t t1;
	time(&t1);
	time_t t2 = t1 + rand() % 2 + 1;

	while (t1 < t2)
	{
		for (int i = 0; i < rellCount; ++i)
		{
			if (i == 1)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0A);
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x02);
			}
			for (int j = rellCount - restCount; j < rellCount; ++j)
			{
				GotoXY(x + j * 3, y + i * 3);
				cout << rell[j].Pop();
			}
		}
		time(&t1);
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
}