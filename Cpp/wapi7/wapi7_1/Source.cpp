/*
Создать в ресурсах приложения два идентичных многоуровневых меню, одно из которых содержит английские названия, а другое – русские. 
При старте программы необходимо загрузить англоязычное меню и присоединить его к главному окну приложения. 
Предусмотреть на форме диалога две кнопки. При нажатии на первую кнопку англоязычное меню должно русифицироваться,
т.е. все английские названия должны быть переведены на русский язык. При повторном нажатии на эту же кнопку меню вновь должно стать англоязычным. 
При нажатии на вторую кнопку должны происходить аналогичные действия. Отличие состоит в том, что в первом случае одно меню должно подменяться другим, 
а во втором случае меню должно создаваться программным способом, а перевод меню осуществляться путем модификации каждого пункта меню.
Кроме того, необходимо предусмотреть в программе возможность выбора пунктов меню с помощью акселераторов.
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