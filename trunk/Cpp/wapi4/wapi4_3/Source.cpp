/*
Написать приложение, определяющее, сколько осталось времени до указанной даты 
(день, месяц и год вводятся в отдельные текстовые поля). 
Предусмотреть выдачу результата в годах, месяцах, днях.
*/

#include "TimeToDateDlg.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int CmdShow)
{
	TimeToDateDlg dlg;
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_TIMETODATE), NULL, TimeToDateDlg::DlgProc);
}