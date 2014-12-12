/*
Создать диалоговое приложение, у  которого на форме находится список, кнопка, 
текстовое поле и три переключателя. По кнопку «Старт» в список заносится от 10 до 20 случайных чисел
в диапазоне от -10 до 10 (0 не включается). Переключатели обеспечивают отображение пользователю суммы чисел,
произведения чисел либо среднего арифметического чисел.
*/

#include "ArithmeticDlg.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int CmdShow)
{
	ArithmeticDlg dlg;
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, ArithmeticDlg::DlgProc);
}