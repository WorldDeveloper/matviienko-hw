/*
Модифицировать интерфейс приложения «Пятнашки» следующим образом:
дополнить главное окно приложения строкой состояния, разделённой на две секции.
В первую секцию необходимо выводить время продолжительности игры, 
а во вторую секцию следует поместить индикатор процесса,
который будет отображать процесс собирания «пятнашек» (процент попадания кнопок на свои места).
*/

#include "FifteenDlg.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int CmdShow)
{
	FifteenDlg dlg;
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_FIFTEEN), NULL, FifteenDlg::DlgProc);
}