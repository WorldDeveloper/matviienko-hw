/*
Написать приложение, формирующее список логических дисков, которые доступны в данный момент
*/

#include "LogicalDrivesDlg.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int CmdShow)
{
	LogicalDrivesDlg dlg;
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, LogicalDrivesDlg::DlgProc);
}