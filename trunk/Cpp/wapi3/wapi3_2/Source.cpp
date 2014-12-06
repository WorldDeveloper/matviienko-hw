/*
Написать игру «Крестики-нолики», учитывая следующие требования:
- игровое поле размером 3х3 должно состоять из кнопок;
- при нажатии на кнопку, на ней должна отобразиться картинка (крестик или нолик);
- необходимо предотвращать попытку поставить крестик или нолик на занятую клетку;
- предоставить пользователю право выбора первого хода, используя флажок;
- предусмотреть возможность выбора уровня сложности, используя переключатели;
- предусмотреть кнопку «Начать игру».

*/
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