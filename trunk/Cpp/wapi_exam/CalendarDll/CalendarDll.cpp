#include "CalendarDll.h"


	HINSTANCE hInst = NULL;
BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
	{
		hInst = (HINSTANCE)hModule;
		
		switch (ul_reason_for_call)
		{
			
			case DLL_PROCESS_ATTACH:
			case DLL_THREAD_ATTACH:
			case DLL_THREAD_DETACH:
			case DLL_PROCESS_DETACH:
			break;
		}
		return TRUE;
	}


Calendar::Calendar(HWND pluginWindow)
{
	mPluginWindow = pluginWindow;

	RECT rcClient;
	GetClientRect(mPluginWindow, &rcClient);
	mhList = CreateWindowEx(WS_EX_CLIENTEDGE, L"LISTBOX", NULL,
		WS_CHILD | WS_VISIBLE | WS_VSCROLL | LBS_NOTIFY, 0, 0, rcClient.right, rcClient.bottom, mPluginWindow, 0, GetModuleHandle(0), 0);

	OpenDB();
}

void Calendar::SetPluginWindow(HWND hWnd)
{
	mPluginWindow = hWnd;

	RECT rcClient;
	GetClientRect(mPluginWindow, &rcClient);
	mhList = CreateWindowEx(WS_EX_CLIENTEDGE, L"LISTBOX", NULL,
		WS_CHILD | WS_VISIBLE | WS_VSCROLL, 0, 0, rcClient.right, rcClient.bottom, mPluginWindow, 0, GetModuleHandle(0), 0);
}


bool Calendar::AddItem()
{
	CalendarEvent newEvent;
	CalendarDlg dlg(L"Add", newEvent);
	DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), mPluginWindow, CalendarDlg::DlgProc);

	CalendarEvent result = dlg.GetEvent();
	if (result.Empty()) return false;

	mEvents.push_back(result);
	std::sort(mEvents.begin(), mEvents.end());
	SaveDB();

	ShowAllItems();

	return true;
}

bool Calendar::EditItem()
{
	if (!SendMessage(mhList, LB_GETCOUNT, 0, 0)) return false;

	const int id = SendMessage(mhList, LB_GETCURSEL, 0, 0);
	if (id == LB_ERR) return false;

	if (id < 0 || id >= mEvents.size()) return false;

	CalendarDlg dlg(L"Edit", mEvents[id]);

	DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), mPluginWindow, CalendarDlg::DlgProc);

	CalendarEvent result = dlg.GetEvent();
	if (result.Empty()) return false;

	mEvents.erase(mEvents.begin() + id);
	mEvents.push_back(result);
	std::sort(mEvents.begin(), mEvents.end());
	SaveDB();

	ShowAllItems();

	return true;
}
bool Calendar::DeleteItem()
{
	if (!SendMessage(mhList, LB_GETCOUNT, 0, 0)) return false;

	const int id = SendMessage(mhList, LB_GETCURSEL, 0, 0);
	if (id == LB_ERR) return false;

	if (id < 0 || id >= mEvents.size()) return false;

	mEvents.erase(mEvents.begin() + id);
	std::sort(mEvents.begin(), mEvents.end());
	SaveDB();
	ShowAllItems(); 

	return true;
}

void Calendar::ShowSingleItem() const
{
	if (!SendMessage(mhList, LB_GETCOUNT, 0, 0)) return;

	const int id = SendMessage(mhList, LB_GETCURSEL, 0, 0);
	if (id == LB_ERR) return;

	if (id < 0 || id >= mEvents.size()) return;

	CalendarDlg dlg(L"View", mEvents[id]);

	DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), mPluginWindow, CalendarDlg::DlgProc);
}

void Calendar::ShowAllItems() const
{
	SendMessage(mhList, LB_RESETCONTENT, 0, 0); 
	
	if (mEvents.empty()) return;	

	for (int i = 0; i < mEvents.size(); ++i)
	{
		int index = 0;
		if (i==0 || mEvents[i].GetFromDate()!=mEvents[i-1].GetFromDate())
			int index = SendMessage(mhList, LB_ADDSTRING, 0, LPARAM(mEvents[i].GetEventString().c_str()));
		else
			int index = SendMessage(mhList, LB_ADDSTRING, 0, LPARAM(mEvents[i].GetEventShortString().c_str()));

		SendMessage(mhList, LB_SETITEMDATA, index, i);
	}

	const int todayIndex = Today();
	if (todayIndex >= 0)
	{
		SendMessage(mhList, LB_SETCURSEL, todayIndex, 0);
	}
	else SendMessage(mhList, LB_SETCURSEL, mEvents.size()-1, 0);
}


void Calendar::ResizePlugin() const
{
	RECT rcClient;
	GetClientRect(mPluginWindow, &rcClient);
	SetWindowPos(mhList, NULL, 0, 0, rcClient.right, rcClient.bottom, SWP_NOZORDER);
}

void Calendar::SaveDB()
{
	const std::locale utf8_locale = std::locale(std::locale(), new std::codecvt_utf8<wchar_t>());

	std::wofstream out(mDBname);
	out.imbue(utf8_locale);

	if (out.is_open())
	{
		for (std::vector<CalendarEvent>::iterator calendarEvent = mEvents.begin(); calendarEvent != mEvents.end(); ++calendarEvent)
		{
			out << calendarEvent->mName << L"\n";
			out << calendarEvent->mDescription << L"\n";
			out << calendarEvent->mWhere << L"\n";
			out << std::to_wstring(calendarEvent->mFromDate) << L"\n";
			out << std::to_wstring(calendarEvent->mToDate) << L"\n";
		}
	}
	else
	{
		throw L"unable to open file";
	}
	out.close();
}

void Calendar::OpenDB()
{
	const std::locale utf8_locale = std::locale(std::locale(), new std::codecvt_utf8<wchar_t>());

	std::wifstream in(mDBname);
	in.imbue(utf8_locale);

	if (!in) return;

	if (in.is_open())
	{
		while (!in.eof())
		{
			std::vector<std::wstring> field;
			std::wstring tmp;
			if (!getline(in, tmp)) break;
			field.push_back(tmp);

			for (int i = 0; i < 4; ++i)
			{
				getline(in, tmp);
				field.push_back(tmp);
			}

			if (field.size() != 5) break;

			CalendarEvent newEvent(field[0], field[1], field[2], std::stoi(field[3]), std::stoi(field[4]));
			mEvents.push_back(newEvent);
		}
	}
	else
	{
		throw L"unable to open file.";
	}

	in.close();
}

int Calendar::Today() const
{
	time_t now;
	time(&now);
	CalendarEvent today(L"today", L"", L"", now, now);
	int curItem = -1;

	for (int i = 0; i < mEvents.size(); ++i)
	{
		if (mEvents[i] >= today)
		{
			curItem = i;
			break;
		}
	}

	return curItem;
}

extern "C" __declspec(dllexport) IOrganizer* CreatePlugin(HWND pluginWindow)
{
	return new Calendar(pluginWindow);
}

extern "C" __declspec(dllexport) void FreePlugin(IOrganizer* pPlugin)
{
	delete pPlugin;
}