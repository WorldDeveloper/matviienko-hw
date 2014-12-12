/*
Написать игру «Пятнашки», учитывая следующие требования:
- предусмотреть автоматическую перестановку «пятнашек» в начале новой игры;
- выводить время, за которое пользователь окончил игру;
- предусмотреть возможность начать новую игру.

*/

#include "FifteenDlg.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int CmdShow)
{
	//try****	
	FifteenDlg dlg;
		return DialogBox(hInstance, MAKEINTRESOURCE(IDD_FIFTEEN), NULL, FifteenDlg::DlgProc);
}