/*
Разработать приложение «убегающий статик». Суть приложения: на форме диалогового окна расположен статический элемент управления.
Пользователь пытается подвести курсор мыши к «статику», и, если курсор находится близко со «статиком», элемент управления «убегает». 
Предусмотреть перемещение «статика» только в пределах диалогового окна.
*/

#include "RunningStaticDlg.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int CmdShow)
{
		RunningStaticDlg dlg;
		return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, RunningStaticDlg::DlgProc);
}