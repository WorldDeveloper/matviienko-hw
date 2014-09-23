/*
Написать программу, реализующую электронный органайзер. 
Реализовать возможности добавления, удаления, редактирования и хранения данных. 
Предусмотреть обработку всех возможных ошибок
*/

#include <iostream>
#include "Notes.h"

using namespace std;

void main()
{
	system("color F0");
	HideCursor(true);

	Notes note;
	Notes n1;
	Notes n2;
	Organizer* p = &note;
	p->RepaintWindow(ACTIVE, ACTIVE, true);
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
				p = &note;
				p->RepaintWindow(ACTIVE, ACTIVE, true);
				p->ShowList();
			}
			else if (secondByte == KEY_F2)
			{
				p = &n1;
				p->RepaintWindow(ACTIVE, ACTIVE, true);
				p->ShowList();
			}
			else if (secondByte == KEY_F3)
			{
				p = &n2;
				p->RepaintWindow(ACTIVE, ACTIVE, true);
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
				
			}
			else if (secondByte == KEY_DOWN)
			{
				
			}

		}
		else if ((control > 31 && control < 123) || control == 8)
		{
			//list.MaskSearch(control, activePage);
		}
		else if (control == KEY_ENTER)
		{
			/*system("cls");
			searchMenu.showMenu(activePage);
			dbMenu.showMenu();
			if (list.QuitReview())
			{
				list.ShowList(activePage);
			}
			else
			{
				list.ShowSelectedItem();
			}*/
		}
		else if (control == KEY_ESCAPE)
		{
			/*GotoXY(0, 4);
			exit(0);*/
		}
	}
	//SetColour(systemColour);
}


