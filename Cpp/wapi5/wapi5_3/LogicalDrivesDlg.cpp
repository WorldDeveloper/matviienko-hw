#include "LogicalDrivesDlg.h"


LogicalDrivesDlg* LogicalDrivesDlg::ptr = nullptr;

LogicalDrivesDlg::LogicalDrivesDlg() 
{
	ptr = this;

}

BOOL CALLBACK LogicalDrivesDlg::DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hWnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hWnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
	}

	return FALSE;
}

BOOL LogicalDrivesDlg::Cls_OnInitDialog(HWND hWnd, HWND hwndFocus, LPARAM lParam)
{

	HWND mhDrives = GetDlgItem(hWnd, IDC_COMBO);

	const wchar_t* driveType[] = { L"Unknown type", L"Root dir doesn't exist", L"Removable disk", L"Local disk", L"Remote disk", L"CD-ROM", L"Ram disk" };

	wchar_t buffer[MAX_PATH] = { 0 };
	DWORD dwResult= GetLogicalDriveStrings(MAX_PATH, (LPWSTR)buffer);

	if (dwResult > 0 && dwResult <= MAX_PATH)
	{
		wchar_t* symbol = buffer;
		wchar_t* drive = buffer;
		for (int i = 0; i < MAX_PATH-1; ++i)
		{			
			if (*symbol == L'\0')
			{
				if (drive != symbol)
				{
					int driveCode=GetDriveType(drive);
					std::wstringstream driveStr; 
					driveStr << drive << " (" << driveType[driveCode] << ")";
					SendMessage(mhDrives, CB_ADDSTRING, 0, (LPARAM)driveStr.str().c_str());
				}
				drive = symbol + 1;
			}
			symbol++;
		}
	}

	return TRUE;
}
