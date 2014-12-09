/*
Написать приложение «Простейший калькулятор» на четыре действия (сложение, вычитание, умножение и деление).
На форме диалога расположены три текстовых поля для ввода операндов и знака  операции, 
кнопка, при нажатии на которую, подсчитывается результат, а также статик для вывода результата вычисления.
*/

#include "CalcDlg.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int CmdShow)
{
		CalcDlg dlg;
		return DialogBox(hInstance, MAKEINTRESOURCE(IDD_CALC), NULL, CalcDlg::DlgProc);
}