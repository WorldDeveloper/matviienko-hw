
#include "TicTacToeDlg.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int CmdShow)
{
	try{
		TicTacToeDlg dlg;
		return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, TicTacToeDlg::DlgProc);
	}
	catch (char* error)
	{
		MessageBoxA(0, error, "Error", MB_OK|MB_ICONSTOP);
	}
}