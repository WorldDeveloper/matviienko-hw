/*

*/

#include "MenuDlg.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int CmdShow)
{
	INITCOMMONCONTROLSEX icc = { sizeof(INITCOMMONCONTROLSEX) };
	icc.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&icc);
	MenuDlg dlg;
	MSG msg;
	HWND hDialog= CreateDialog(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, MenuDlg::DlgProc);
	HACCEL hAccel = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDR_ACCELERATOR1));
	ShowWindow(hDialog, CmdShow);
	while (GetMessage(&msg, 0, 0, 0))
	{
		if (!TranslateAccelerator(hDialog, hAccel, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return msg.wParam;
}