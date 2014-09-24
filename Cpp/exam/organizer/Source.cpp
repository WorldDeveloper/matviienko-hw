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


	Contacts contact;
	Notes note;
	Notes n1;
	Notes n2;
	Organizer* p = &note;
	p->RepaintWindow();
	p->ShowList();
	while (true)
	{
		enum{ KEY_ENTER = 13, KEY_ESCAPE = 27, KEY_F1 = 59, KEY_F2, KEY_F3, KEY_F5=63, KEY_F6, KEY_F7, KEY_UP = 72, KEY_DOWN = 80, KEY_DELETE = 83 };
		unsigned char control = getch();

		if (control == 0 || control == 224 && kbhit())
		{
			unsigned char secondByte = getch();
			if (secondByte == KEY_F1)
			{
				p = &n1;
				p->SetActivePage(0);
				p->RepaintWindow();
				p->ShowList();
			}
			else if (secondByte == KEY_F2)
			{
				p = &contact;
				p->SetActivePage(1);
				p->RepaintWindow();
				p->ShowList();
			}
			else if (secondByte == KEY_F3)
			{
				p = &note;
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
		else if ((control > 31 && control < 123) || control == 8)
		{
			//list.MaskSearch(control, activePage);
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


