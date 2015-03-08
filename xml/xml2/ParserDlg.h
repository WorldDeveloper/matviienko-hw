#pragma once
#include <windowsx.h>
#include <Windows.h>
#include <tchar.h>
#include "resource.h"
#include "tinyxml2.h"
#include <vector>
#include <sstream>
#include <map>

#include <locale>
#include <codecvt>

#include <atlconv.h>

class ParserDlg
{
	HWND mhDlg;
	HWND mhShowTimetable;
	HWND mhTrainsList;
	HWND mhShowStations;
	HWND mhStationsList;
	HWND mhShowTrains;
	std::map<std::wstring, std::wstring> mTrains;
	std::map<std::wstring, std::wstring> mStations;
	tinyxml2::XMLDocument mXmlDoc;
	tinyxml2::XMLNode* mpRoot;
public:
	ParserDlg();

	static ParserDlg* ptr;
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void Cls_OnClose(HWND hWnd) { EndDialog(hWnd, 0); }
	void Cls_OnCommand(HWND hWnd, int id, HWND hWndCtl, UINT codeNotify);
	BOOL Cls_OnInitDialog(HWND hWnd, HWND hWndFocus, LPARAM lParam);
};

