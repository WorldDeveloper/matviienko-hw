#include "NotesDll.h"

void Notes::SetWindow(HWND destWindow)
{
	//remove

}

bool Notes::AddItem()
{

	//cout << " Add note: ";
	//string tmp;
	//fflush(stdin);
	//getline(cin, tmp);

	//if (tmp.empty()) return false;
	//mNotes.push_back(tmp);
	//mSelectedNote = --mNotes.end();

	//SaveDB();


	return true;
}

bool Notes::EditItem(const int id)
{
	//if (mNotes.empty()) return false;

	//cout << " Edit note:";
	//string tmp;
	//fflush(stdin);
	//getline(cin, tmp);

	//if (tmp.empty()) return false;
	//*mSelectedNote = tmp;

	//SaveDB();

	return true;
}
bool Notes::DeleteItem(const int id)
{
	//if (mNotes.empty()) return false;

	//mSelectedNote = mNotes.erase(mSelectedNote);
	//if (mSelectedNote == mNotes.end() && !mNotes.empty()) mSelectedNote--;

	//SaveDB();
	return true;
}

void Notes::ShowSingleItem(const int id) const
{
	//if (mNotes.empty() || itemIndex < 0 || itemIndex >= mNotes.size()) throw "out of range";

	//return mNotes[itemIndex];
}

void Notes::ShowAllItems() const
{
	/*if (mNotes.empty() || itemIndex < 0 || itemIndex >= mNotes.size()) throw "out of range";

	return mNotes[itemIndex];*/
}


extern "C" __declspec(dllexport) IOrganizer* CreatePlugin(HWND pluginWindow)
{
	return new Notes(pluginWindow);
}

extern "C" __declspec(dllexport) void FreePlugin(IOrganizer* pPlugin)
{
	delete pPlugin;
}



//*********************


Notes::Notes(HWND pluginWindow)
{	
	mPluginWindow = pluginWindow;
	OpenDB();
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