/*
Разработать приложение, работа которого состоит в следующем. 
По щелчку правой кнопкой мыши на форме диалога выпадает контекстное меню со следующими пунктами:
«Надпись 3», «Текст 3», «Кнопка 3». Когда пользователь выбирает пункт меню, то на форме в точке щелчка появляется
соответствующий элемент управления (Static, Edit or Button). При этом счетчик для созданного элемента управления уменьшается на единицу. 
Если на форме диалога выставлены все элементы одного типа, то данный пункт исчезает из меню.
*/

#include "MenuDlg.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int CmdShow)
{
	INITCOMMONCONTROLSEX icc = { sizeof(INITCOMMONCONTROLSEX) };
	icc.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&icc);
	MenuDlg dlg;
	return  DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, MenuDlg::DlgProc);
	
}