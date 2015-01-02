#include "CalendarDlg.h"

CalendarDlg* CalendarDlg::ptr = nullptr;

CalendarDlg::CalendarDlg(std::wstring action, CalendarEvent newEvent)
{
	ptr = this;
	mAction = action;
	mEvent = newEvent;
}


BOOL CALLBACK CalendarDlg::DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hWnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hWnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hWnd, WM_COMMAND, ptr->Cls_OnCommand);
	}

	return FALSE;
}


BOOL CalendarDlg::Cls_OnInitDialog(HWND hWnd, HWND hwndFocus, LPARAM lParam)
{
	mhDlg = hWnd;
	mhTitle = GetDlgItem(hWnd, IDC_TITLE);
	mhDescription = GetDlgItem(hWnd, IDC_DESCRIPTION);
	mhWhere = GetDlgItem(hWnd, IDC_WHERE);
	
	time_t fromTime = 0;
	time_t toTime = 0;

	if (mAction == L"Add")
	{
		time_t today;
		time(&today); 
		toTime = today + 60 * 60;
	}
	else if (mAction == L"Edit" || mAction==L"View")
	{
		SetWindowText(mhDlg, L"Edit event");
		SetWindowText(mhTitle, mEvent.mName.c_str());
		SetWindowText(mhDescription, mEvent.mDescription.c_str());
		SetWindowText(mhWhere, mEvent.mWhere.c_str());
		fromTime = mEvent.mFromDate;
		toTime = mEvent.mToDate;
	}
	
	if (mAction == L"View")
	{
		for (int i = 0; i < 13; ++i)
		{
			SetWindowText(mhDlg, L"View event"); 
			EnableWindow(GetDlgItem(mhDlg, IDC_TITLE + i), FALSE);
		}		
	}

	HWND hTmp[5];
	for(int i = 0; i < 5; ++i)
	{
		hTmp[i] = GetDlgItem(hWnd, IDC_FROM_YEAR+i);
	}
	mFromTime = new DateTime(hTmp[0], hTmp[1], hTmp[2], hTmp[3], hTmp[4], fromTime);


	for (int i = 0; i < 5; ++i)
	{
		hTmp[i] = GetDlgItem(hWnd, IDC_TO_YEAR + i);
	}
	mToTime = new DateTime(hTmp[0], hTmp[1], hTmp[2], hTmp[3], hTmp[4], toTime);	

	return TRUE;
}

void CalendarDlg::Cls_OnCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify)
{
	if (codeNotify == CBN_SELCHANGE || codeNotify == EN_KILLFOCUS) 
	{
		mFromTime->CheckLastDay(); // split check
		mToTime->CheckLastDay();
	}

	if (id == IDC_OK)
	{
		if (mAction == L"View") EndDialog(hWnd, 0);

		try
		{
			mEvent.mName = GetStringFromEdit(mhTitle);
			mEvent.mDescription = GetStringFromEdit(mhDescription);
			mEvent.mWhere = GetStringFromEdit(mhWhere);
			mEvent.mFromDate = mFromTime->GetDateTime();
			mEvent.mToDate = mToTime->GetDateTime();

			if (mEvent.mName.empty())
			{
				MessageBox(hWnd, L"Title is empty!", L"Correct record", MB_OK | MB_ICONEXCLAMATION);
				return;
			}

			if(mEvent.mFromDate >mEvent.mToDate)
			{
				MessageBox(hWnd, L"Incorrect time duration!", L"Correct record", MB_OK | MB_ICONEXCLAMATION);
				return;
			}

		}
		catch (wchar_t* err)
		{
			MessageBox(hWnd, L"Incorrect event!", L"Error", MB_OK | MB_ICONEXCLAMATION);
			mEvent.Clear();
			return;
		}

		EndDialog(hWnd, 0);
	}
	else if (id == IDC_CANCEL)
	{
		mEvent.Clear();
		EndDialog(hWnd, 0);
	}

}

void CalendarDlg::Cls_OnClose(HWND hWnd)
{
	mEvent.Clear();
	EndDialog(mhDlg, 0);
}


std::wstring  CalendarDlg::GetStringFromEdit(HWND hEdit) const
{
	std::wstring ret;
	int length = SendMessage(hEdit, WM_GETTEXTLENGTH, 0, 0);
	if (length > 0)
	{
		wchar_t* buf = new wchar_t[length + 1];
		SendMessage(hEdit, WM_GETTEXT, (length + 1), (LPARAM)buf);
		ret = buf;
		delete[] buf;
	}

	return ret;
}