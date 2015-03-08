#include "ParserDlg.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int CmdShow)
{
	ParserDlg dlg;
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DLG), NULL, ParserDlg::DlgProc);
}