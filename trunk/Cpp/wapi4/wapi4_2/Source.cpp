/*
Написать приложение, которое по введенной дате определяет день недели.
При этом день, месяц и год необходимо вводить в отдельные текстовые поля.
Результат также следует выводить в текстовое поле со стилем Read Only.
Предусмотреть поверку корректности ввода даты
*/

#include "DowDlg.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int CmdShow)
{
		DowDlg dlg;
		return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DOW), NULL, DowDlg::DlgProc);
}