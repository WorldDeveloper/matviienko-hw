#include "CalcDlg.h"

CalcDlg* CalcDlg::ptr = nullptr;

CalcDlg::CalcDlg()
{
	ptr = this;
}

BOOL CALLBACK CalcDlg::DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hWnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hWnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hWnd, WM_COMMAND, ptr->Cls_OnCommand);
	}

	return FALSE;
}

void CalcDlg::Cls_OnCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify)
{
	if (id == IDC_CALCULATE)
	{
		SetWindowText(mhResult, L"result");

		if (!IsValidNumber(mh1stOperand))
		{
			MessageBox(hWnd, L"First number is incorrect", L"Error", MB_OK | MB_ICONERROR);
			return;
		}

		if (!IsValidNumber(mh2ndOperand))
		{
			MessageBox(hWnd, L"Second number is incorrect", L"Error", MB_OK | MB_ICONERROR);
			return;
		}

		double op1 = _wtof(GetString(mh1stOperand).c_str());
		double op2 = _wtof(GetString(mh2ndOperand).c_str());
		std::wstring sign = GetString(mhOperator);
		if (sign.length() != 1)
		{
			MessageBox(hWnd, L"Openator is incorrect", L"Error", MB_OK | MB_ICONERROR);
			return;
		}

		std::wstringstream result;
		switch (*sign.begin())
		{
		case '+':
			result << op1 + op2;
			break;
		case '-':
			result << op1 - op2;
			break;
		case '*':
			result << op1*op2;
			break;
		case '/':
		{
			if (op2 != 0)
			{
				result << op1 / op2;
				break;
			}
			else
			{
				result << "Error: division by zero";
				break;
			}
		}
		default:
			MessageBox(hWnd, L"Openator is incorrect", L"Error", MB_OK | MB_ICONERROR);
			return;
		}

		SetWindowText(mhResult, result.str().c_str());
		SetFocus(mhClear);
	}
	else if (id == IDC_CLEAR)
	{
		SetWindowText(mh1stOperand, NULL);
		SetWindowText(mhOperator, NULL);
		SetWindowText(mh2ndOperand, NULL);
		SetWindowText(mhResult, L"result");
		SetFocus(mh1stOperand);
	}
}

BOOL CalcDlg::Cls_OnInitDialog(HWND hWnd, HWND hwndFocus, LPARAM lParam)
{
	mhCalc = GetDlgItem(hWnd, IDC_CALCULATE);
	mhClear = GetDlgItem(hWnd, IDC_CLEAR);
	mh1stOperand = GetDlgItem(hWnd, IDC_1STOPERAND);
	mh2ndOperand = GetDlgItem(hWnd, IDC_2NDOPERAND);
	mhOperator = GetDlgItem(hWnd, IDC_OPERATOR);
	mhResult = GetDlgItem(hWnd, IDC_RESULT);
	SetFocus(mh1stOperand);

	return TRUE;
}

std::wstring CalcDlg::GetString(HWND hWnd)
{
	int len = GetWindowTextLength(hWnd) + 1;
	wchar_t* string = new wchar_t[len];
	GetWindowText(hWnd, string, len);

	return string;
}

bool CalcDlg::IsValidNumber(HWND hWnd)
{
	std::wstring stringNumber = GetString(hWnd);
	if (stringNumber.empty()) return false;
	std::wstring::iterator it = stringNumber.begin();

	if (*it == '-') ++it;

	bool point = false;
	while (it != stringNumber.end())
	{
		if (*it == '.' && point == false) point = true;
		else if (!isdigit(*it))	return false;
		++it;
	}

	return true;
}