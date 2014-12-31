#include "AlarmsDll.h"

HINSTANCE hInst = NULL;

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
	)
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


Alarms::Alarms(HWND pluginWindow)
{
	mPluginWindow = pluginWindow;

	RECT rcClient;
	GetClientRect(mPluginWindow, &rcClient);
	mhList = CreateWindowEx(WS_EX_CLIENTEDGE, L"LISTBOX", NULL,
		WS_CHILD | WS_VISIBLE | WS_VSCROLL | LBS_NOTIFY, 0, 0, rcClient.right, rcClient.bottom, mPluginWindow, 0, GetModuleHandle(0), 0);

	OpenDB();
}

void Alarms::SetPluginWindow(HWND hWnd)
{
	mPluginWindow = hWnd;

	RECT rcClient;
	GetClientRect(mPluginWindow, &rcClient);
	mhList = CreateWindowEx(WS_EX_CLIENTEDGE, L"LISTBOX", NULL,
		WS_CHILD | WS_VISIBLE | WS_VSCROLL, 0, 0, rcClient.right, rcClient.bottom, mPluginWindow, 0, GetModuleHandle(0), 0);
}


bool Alarms::AddItem()
{
	AlarmDlg dlg(L"Add", 0);
	DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), mPluginWindow, AlarmDlg::DlgProc);

	const  time_t result = dlg.GetAlarm();
	if (!result) return false;

	mAlarms.push_back(result);
	std::sort(mAlarms.begin(), mAlarms.end());
	SaveDB();

	ShowAllItems();

	return true;
}

bool Alarms::EditItem()
{
	if (!SendMessage(mhList, LB_GETCOUNT, 0, 0)) return false;

	const int id = SendMessage(mhList, LB_GETCURSEL, 0, 0);
	if (id == LB_ERR) return false;

	if (id < 0 || id >= mAlarms.size()) return false;

	AlarmDlg dlg(L"Edit", mAlarms[id]);

	DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), mPluginWindow, AlarmDlg::DlgProc);

	const  time_t result = dlg.GetAlarm();
	if (!result) return false;

	mAlarms.erase(mAlarms.begin() + id);
	mAlarms.push_back(result);
	std::sort(mAlarms.begin(), mAlarms.end());
	SaveDB();

	ShowAllItems();
	
	return true;
}
bool Alarms::DeleteItem()
{
	if (!SendMessage(mhList, LB_GETCOUNT, 0, 0)) return false;

	const int id = SendMessage(mhList, LB_GETCURSEL, 0, 0);
	if (id == LB_ERR) return false;

	if (id < 0 || id >= mAlarms.size()) return false;

	mAlarms.erase(mAlarms.begin() + id);
	std::sort(mAlarms.begin(), mAlarms.end());
	SaveDB();

	ShowAllItems(); 
	
	return true;
}

void Alarms::ShowSingleItem() const
{
	if (!SendMessage(mhList, LB_GETCOUNT, 0, 0)) return;

	const int id = SendMessage(mhList, LB_GETCURSEL, 0, 0);
	if (id == LB_ERR) return;

	if (id < 0 || id >= mAlarms.size()) return;

	AlarmDlg dlg(L"View", mAlarms[id]);

	DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), mPluginWindow, AlarmDlg::DlgProc);
}

void Alarms::ShowAllItems() const
{
	if (mAlarms.empty()) return;

	SendMessage(mhList, LB_RESETCONTENT, 0, 0);

	for (int i = 0; i < mAlarms.size(); ++i)
	{
		int index = SendMessage(mhList, LB_ADDSTRING, 0, LPARAM(GetTimeString(mAlarms[i]).c_str()));
		SendMessage(mhList, LB_SETITEMDATA, index, i);
	}
}

std::wstring Alarms::GetTimeString(const time_t alarm) const
{
	if (!alarm) throw L"Incorrect time";

	struct tm * moment;
	moment = localtime(&alarm);

	std::wstringstream buf;
	buf << Format2Digit(moment->tm_hour) << L":";
	buf << Format2Digit(moment->tm_min)<<L"   "; 
	buf << moment->tm_year + 1900 << L".";
	buf << Format2Digit(moment->tm_mon + 1) << L".";
	buf << Format2Digit(moment->tm_mday);
	

	return buf.str().c_str();
}

std::wstring Alarms::Format2Digit(const int number) const
{
	if (number < 10) return L"0" + std::to_wstring(number);
	else return std::to_wstring(number);
}

void Alarms::ResizePlugin() const
{
	RECT rcClient;
	GetClientRect(mPluginWindow, &rcClient);
	SetWindowPos(mhList, NULL, 0, 0, rcClient.right, rcClient.bottom, SWP_NOZORDER);
}


void Alarms::SaveDB()
{
	const std::locale utf8_locale = std::locale(std::locale(), new std::codecvt_utf8<wchar_t>());

	std::wofstream out(mDBname);
	out.imbue(utf8_locale);

	if (out.is_open())
	{
		for (std::vector<time_t>::iterator alarm = mAlarms.begin(); alarm != mAlarms.end(); ++alarm)
		{
			out << to_wstring(*alarm) << L"\n";
		}
	}
	else
	{
		throw L"unable to open file";
	}
	out.close();
}

void Alarms::OpenDB()
{
	const std::locale utf8_locale = std::locale(std::locale(), new std::codecvt_utf8<wchar_t>());

	std::wifstream in(mDBname);
	in.imbue(utf8_locale);

	if (!in) return;

	if (in.is_open())
	{
		while (!in.eof())
		{
			wstring alarm;
			if (!getline(in, alarm)) break;
			mAlarms.push_back(stoi(alarm));
		}
	}
	else
	{
		throw L"unable to open file.";
	}

	in.close();
}

extern "C" __declspec(dllexport) IOrganizer* CreatePlugin(HWND pluginWindow)
{
	return new Alarms(pluginWindow);
}

extern "C" __declspec(dllexport) void FreePlugin(IOrganizer* pPlugin)
{
	delete pPlugin;
}