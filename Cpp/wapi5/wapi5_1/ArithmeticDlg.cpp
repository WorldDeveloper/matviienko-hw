#include "ArithmeticDlg.h"
#include <ctime>

ArithmeticDlg* ArithmeticDlg::ptr = nullptr;

ArithmeticDlg::ArithmeticDlg()
{
	ptr = this;
}

BOOL CALLBACK ArithmeticDlg::DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hWnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hWnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hWnd, WM_COMMAND, ptr->Cls_OnCommand);
	}

	return FALSE;
}

void ArithmeticDlg::Cls_OnCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify)
{
	switch (id)
	{
	case IDC_START:
	{
		SendMessage(mhList, LB_RESETCONTENT, 0, 0);
		std::srand(time(NULL));
		int end = std::rand() % 10 + 10;

		for (int i = 0; i < end; ++i)
		{
			int rNumber;
			do{
				rNumber = std::rand() % 20 - 10;
			} while (!rNumber);

			std::wstring number = std::to_wstring(rNumber);
			int index = SendMessage(mhList, LB_ADDSTRING, 0, LPARAM(number.c_str()));
			SendMessage(mhList, LB_SETITEMDATA, index, rNumber);
		}

		CheckRadioButton(hWnd, IDC_SUM, IDC_AVG, IDC_SUM);
		Sum();

		break;
	}

	case IDC_SUM:
		Sum();
		break;

	case IDC_PRODUCT:
		Product();
		break;

	case IDC_AVG:
		Average();
		break;
	}
}

BOOL ArithmeticDlg::Cls_OnInitDialog(HWND hWnd, HWND hwndFocus, LPARAM lParam)
{
	mhList = GetDlgItem(hWnd, IDC_NUMBERS);
	mhResult = GetDlgItem(hWnd, IDC_RESULT);
	SendDlgItemMessage(hWnd, IDC_SUM, BM_SETCHECK, WPARAM(BST_CHECKED), 0);


	return TRUE;
}

void ArithmeticDlg::Sum()
{
	int count = SendMessage(mhList, LB_GETCOUNT, 0, 0);
	if (!count) return;

	int sum = 0;
	for (int i = 0; i < count; ++i)
	{
		sum += SendMessage(mhList, LB_GETITEMDATA, WPARAM(i), 0);
	}

	std::wstring sumString = std::to_wstring(sum);
	SetWindowText(mhResult, sumString.c_str());
}

void ArithmeticDlg::Product()
{
	int count = SendMessage(mhList, LB_GETCOUNT, 0, 0);
	if (!count) return;

	int prod = 1;
	for (int i = 0; i < count; ++i)
	{
		prod *= SendMessage(mhList, LB_GETITEMDATA, WPARAM(i), 0);
	}

	std::wstring sumString = std::to_wstring(prod);
	SetWindowText(mhResult, sumString.c_str());
}

void ArithmeticDlg::Average()
{
	int count = SendMessage(mhList, LB_GETCOUNT, 0, 0);
	if (!count) return;

	int sum = 0;
	for (int i = 0; i < count; ++i)
	{
		sum += SendMessage(mhList, LB_GETITEMDATA, WPARAM(i), 0);
	}

	std::wstring sumString = std::to_wstring((float)sum / count);
	SetWindowText(mhResult, sumString.c_str());
}
