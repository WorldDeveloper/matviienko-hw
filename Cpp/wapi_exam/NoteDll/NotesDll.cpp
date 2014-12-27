#include "NotesDll.h"

HINSTANCE hInst;

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

Notes::Notes(HWND pluginWindow)
{
	mPluginWindow = pluginWindow;

	RECT rcClient;
	GetClientRect(mPluginWindow, &rcClient);
	mhList = CreateWindowEx(WS_EX_CLIENTEDGE, L"LISTBOX", NULL,
		WS_CHILD | WS_VISIBLE | WS_VSCROLL, 0, 0, rcClient.right, rcClient.bottom, mPluginWindow, 0, GetModuleHandle(0), 0);

	OpenDB();
}

bool Notes::AddItem()
{
	DlgCracker dlg(L"Add");
	DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), mPluginWindow, DlgCracker::DlgProc);

	const std::wstring newNote = dlg.GetNote();
	if (newNote.empty()) return false;

	mNotes.push_back(newNote);
	SaveDB();

	int index = SendMessage(mhList, LB_ADDSTRING, 0, LPARAM(newNote.c_str()));
	SendMessage(mhList, LB_SETITEMDATA, index, mNotes.size() - 1);

	return true;
}

bool Notes::EditItem()
{
	if (!SendMessage(mhList, LB_GETCOUNT, 0, 0)) return false;

	const int id = SendMessage(mhList, LB_GETCURSEL, 0, 0);
	if (id == LB_ERR) return false;

	if (id < 0 || id >= mNotes.size()) return false;

	DlgCracker dlg(L"Edit");
	if (!dlg.SetNote(mNotes[id])) return false;

	DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), mPluginWindow, DlgCracker::DlgProc);

	const std::wstring newNote = dlg.GetNote();
	if (newNote.empty()) return false;

	mNotes.erase(mNotes.begin() + id);
	mNotes.push_back(newNote);
	SaveDB();

	ShowAllItems();

	return true;
}

bool Notes::DeleteItem()
{
	if (!SendMessage(mhList, LB_GETCOUNT, 0, 0)) return false;

	const int id = SendMessage(mhList, LB_GETCURSEL, 0, 0);
	if (id == LB_ERR) return false;

	if (id < 0 || id >= mNotes.size()) return false;

	mNotes.erase(mNotes.begin() + id);

	SaveDB();

	ShowAllItems();

	return true;
}

void Notes::ShowSingleItem() const
{

}

void Notes::ShowAllItems() const
{
	if (mNotes.empty()) return;

	SendMessage(mhList, LB_RESETCONTENT, 0, 0);

	for (int i = 0; i < mNotes.size(); ++i)
	{
		int index = SendMessage(mhList, LB_ADDSTRING, 0, LPARAM(mNotes[i].c_str()));
		SendMessage(mhList, LB_SETITEMDATA, index, i);
	}

}

void Notes::SaveDB()
{

	const std::locale utf8_locale = std::locale(std::locale(), new std::codecvt_utf8<wchar_t>());
	wofstream out(mDBname);
	out.imbue(utf8_locale);

	if (out.is_open())
	{
		for (vector<wstring>::iterator note = mNotes.begin(); note != mNotes.end(); ++note)
		{
			out << (*note).c_str() << L"\n";
		}
	}
	else
	{
		throw L"Error: unable to open file";
	}
	out.close();
}

void Notes::OpenDB()
{

	const std::locale utf8_locale = std::locale(std::locale(), new std::codecvt_utf8<wchar_t>());
	wifstream in(mDBname);
	in.imbue(utf8_locale);

	if (in.is_open())
	{
		while (!in.eof())
		{
			wstring note;
			if (!getline(in, note)) break;
			mNotes.push_back(note);
		}
	}
	else
	{
		throw L"Error: unable to open file.";
	}

	in.close();
}

void Notes::ResizePlugin() const
{
	RECT rcClient;
	GetClientRect(mPluginWindow, &rcClient);
	SetWindowPos(mhList, NULL, 0, 0, rcClient.right, rcClient.bottom, SWP_NOZORDER);
}


extern "C" __declspec(dllexport) IOrganizer* CreatePlugin(HWND pluginWindow)
{
	return new Notes(pluginWindow);
}

extern "C" __declspec(dllexport) void FreePlugin(IOrganizer* pPlugin)
{
	delete pPlugin;
}
