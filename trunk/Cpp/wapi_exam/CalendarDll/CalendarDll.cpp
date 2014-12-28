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
		WS_CHILD | WS_VISIBLE | WS_VSCROLL, 0, 0, rcClient.right, rcClient.bottom, mPluginWindow, 0, GetModuleHandle(0), 0);
}

bool Calendar::AddItem()
{
	DlgCracker dlg(L"Add");
	DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), mPluginWindow, DlgCracker::DlgProc);

	/*const std::wstring newNote = dlg.GetNote();
	if (newNote.empty()) return false;

	mNotes.push_back(newNote);
	SaveDB();

	int index = SendMessage(mhList, LB_ADDSTRING, 0, LPARAM(newNote.c_str()));
	SendMessage(mhList, LB_SETITEMDATA, index, mNotes.size() - 1);*/

	return true;
}

bool Calendar::EditItem()
{
	return true;
}
bool Calendar::DeleteItem()
{
	return true;
}

void Calendar::ShowSingleItem() const
{

}

void Calendar::ShowAllItems() const
{

}

void Calendar::ResizePlugin() const
{
	RECT rcClient;
	GetClientRect(mPluginWindow, &rcClient);
	SetWindowPos(mhList, NULL, 0, 0, rcClient.right, rcClient.bottom, SWP_NOZORDER);
}

//*******************
void Calendar::SaveDB(const char* name)
{
	const std::locale utf8_locale = std::locale(std::locale(), new std::codecvt_utf8<wchar_t>());

	std::wofstream out(name);
	out.imbue(utf8_locale);

	if (out.is_open())
	{
		for (std::vector<Event>::iterator event = mEvents.begin(); event != mEvents.end(); ++event)
		{
			out << event->mName << L"\n";
			out << event->mDescription << L"\n";
			out << event->mWhere << L"\n";
			out << std::to_wstring(event->mFromDate) << L"\n";
			out << std::to_wstring(event->mToDate) << L"\n";
		}
	}
	else
	{
		throw "unable to open file";
	}
	out.close();
}

void Calendar::OpenDB(const char* name)
{
	const std::locale utf8_locale = std::locale(std::locale(), new std::codecvt_utf8<wchar_t>());

	std::wifstream in(name);
	in.imbue(utf8_locale);

	if (!in) return;

	if (in.is_open())
	{
		while (!in.eof())
		{
			std::vector<std::wstring> field;
			std::wstring tmp;
			if (!getline(in, tmp)) break;
			
			for (int i = 0; i < 5; ++i)
			{
				getline(in, tmp);
				field.push_back(tmp);
			}

			if (field.size() != 5) break;

			Event newEvent(field[0], field[1], field[2], std::stoi(field[3]), std::stoi(field[4]));
			mEvents.push_back(newEvent);
		}
	}
	else
	{
		throw "unable to open file.";
	}

	in.close();
}

//****************

//BOOL CALLBACK Calendar::CalendarDlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
//{
//	switch (message)
//	{
//		
//	}
//
//	return FALSE;
//}


extern "C" __declspec(dllexport) IOrganizer* CreatePlugin(HWND pluginWindow)
{
	return new Calendar(pluginWindow);
}

extern "C" __declspec(dllexport) void FreePlugin(IOrganizer* pPlugin)
{
	delete pPlugin;
}