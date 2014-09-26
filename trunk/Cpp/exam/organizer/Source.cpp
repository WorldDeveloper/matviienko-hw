/*
Написать программу, реализующую электронный органайзер.
Реализовать возможности добавления, удаления, редактирования и хранения данных.
Предусмотреть обработку всех возможных ошибок
*/

#include <iostream>
#include "Notes.h"
#include "Contacts.h"
#include "Events.h"

using namespace std;

void main()
{
	system("color F0");
	HideCursor(true);

	Events events;
	Contacts contacts;
	Notes notes;
	Organizer* p = &events;
	p->RepaintWindow();
	p->ShowList();
	while (true)
	{
		enum{ KEY_ENTER = 13, KEY_ESCAPE = 27, KEY_F1 = 59, KEY_F2, KEY_F3, KEY_F5 = 63, KEY_F6, KEY_F7, KEY_UP = 72, KEY_DOWN = 80, KEY_DELETE = 83 };
		unsigned char control = getch();

		if (control == 0 || control == 224 && kbhit())
		{
			unsigned char secondByte = getch();
			if (secondByte == KEY_F1)
			{
				p = &events;
				p->SetActivePage(0);
				p->Today();
				p->RepaintWindow();
				p->ShowList();
			}
			else if (secondByte == KEY_F2)
			{
				p = &contacts;
				p->SetActivePage(1);
				p->RepaintWindow();
				p->ShowList();
			}
			else if (secondByte == KEY_F3)
			{
				p = &notes;
				p->SetActivePage(2);
				p->RepaintWindow();
				p->ShowList();
			}
			else if (secondByte == KEY_F5)
			{
				p->Add();
			}
			else if (secondByte == KEY_F6)
			{
				p->Edit();
			}
			else if (secondByte == KEY_F7 || secondByte == KEY_DELETE)
			{
				p->Delete();
			}
			else if (secondByte == KEY_UP)
			{
				p->PreviousItem();
			}
			else if (secondByte == KEY_DOWN)
			{
				p->NextItem();
			}

		}
		else if (control == KEY_ENTER)
		{
			p->ReviewSelectedItem();
		}
		else if (control == KEY_ESCAPE)
		{
			GotoXY(0, 4);
			exit(0);
		}
	}
}