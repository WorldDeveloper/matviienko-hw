#pragma once
#include "Header.h"

typedef IOrganizer*(*PluginMaker)(HWND);
typedef void(*PluginReleaser)(IOrganizer*);


class FrameWnd
{
	static const int mPluginsCount = 3;
	HINSTANCE mhInst;
	HWND mhWnd;
	wchar_t szChildWindow[12];

	std::wstring mModuleName[mPluginsCount];
	HMODULE mModules[mPluginsCount];
	IOrganizer* mpPlugins[mPluginsCount];
	IOrganizer* mpCurrentPlugin;
	HWND CreateChildWindow(const wchar_t* title);
public:
	FrameWnd();

	static FrameWnd* handler;
	static 	HWND mhMdiClient;
	static HWND mhCalendar;
	static HWND mhNote;
	static HWND mhAlarm;

	static LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void Cls_OnClose(HWND hWnd);
	BOOL Cls_OnCreate(HWND hWnd, LPCREATESTRUCT lpCreateStruct);
	void Cls_OnCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify);
	void Cls_OnSize(HWND hWnd, UINT state, int cx, int cy);


	void CreateMainMenu(HWND hWnd);
	void CreateToolbar(HWND hWnd);
	void CreateStatusbar(HWND hWnd);

	void ReSize(HWND hWnd, HWND hClient); //remove parameters?

	HWND GetClient() const { return mhMdiClient; }
	const wchar_t* GetChildClassName()const { return szChildWindow; }


	friend class ChildWnd; ///????
};

