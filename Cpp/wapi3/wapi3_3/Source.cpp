/*
����������� ���������� ���������� ������. ���� ����������: �� ����� ����������� ���� ���������� ����������� ������� ����������.
������������ �������� �������� ������ ���� � ��������, �, ���� ������ ��������� ������ �� ���������, ������� ���������� ��������. 
������������� ����������� �������� ������ � �������� ����������� ����.
*/

#include "RunningStaticDlg.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int CmdShow)
{
		RunningStaticDlg dlg;
		return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, RunningStaticDlg::DlgProc);
}