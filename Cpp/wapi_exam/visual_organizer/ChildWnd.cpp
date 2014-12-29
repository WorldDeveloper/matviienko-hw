#include "ChildWnd.h"

ChildWnd* ChildWnd::handler = nullptr;

ChildWnd::ChildWnd()
{
	handler = this;
}

LRESULT CALLBACK ChildWnd::MdiChildWinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hWnd, WM_CLOSE, handler->Cls_OnClose);
		HANDLE_MSG(hWnd, WM_COMMAND, handler->Cls_OnCommand);
		HANDLE_MSG(hWnd, WM_SIZE, handler->Cls_OnSize);
		HANDLE_MSG(hWnd, WM_SETFOCUS, handler->Cls_OnSetFocus);
		HANDLE_MSG(hWnd, WM_KILLFOCUS, handler->Cls_OnKillFocus);
	default:
		return DefMDIChildProc(hWnd, message, wParam, lParam);
	}

	return FALSE;
}

void ChildWnd::Cls_OnClose(HWND hWnd)
{
	if (mpCurrentPlugin) mpCurrentPlugin->SetPluginWindow(NULL);
	mpCurrentPlugin = NULL;

	FORWARD_WM_CLOSE(hWnd, DefMDIChildProc);
}

void ChildWnd::Cls_OnCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify)
{
	if (codeNotify == LBN_DBLCLK)
	{
		mpCurrentPlugin->ShowSingleItem();
		return;
	}
}


void ChildWnd::Cls_OnSize(HWND hWnd, UINT state, int cx, int cy)
{
	for (int i = 0; i < mPluginsCount; ++i)
	{
		if (mpPlugins[i]) mpPlugins[i]->ResizePlugin();
	}

	FORWARD_WM_SIZE(hWnd, state, cx, cy, DefMDIChildProc);
}

void ChildWnd::Cls_OnSetFocus(HWND hWnd, HWND hwndOldFocus)
{
	for (int i = 0; i < mPluginsCount; ++i)
	{
		if (!mpPlugins[i]) continue;

		HWND pluginWindow = mpPlugins[i]->GetPluginWindow();
		if (pluginWindow == hWnd)
		{
			mpCurrentPlugin = mpPlugins[i];
			break;
		}
	}
	FORWARD_WM_SETFOCUS(hWnd, hwndOldFocus, DefMDIChildProc);
}

void ChildWnd::Cls_OnKillFocus(HWND hWnd, HWND hwndNewFocus)
{
	if (!mpCurrentPlugin) return;

	HWND pluginWindow = mpCurrentPlugin->GetPluginWindow(); 
	if (hwndNewFocus == GetParent(pluginWindow))
	{
		mpCurrentPlugin = NULL;
	}

	FORWARD_WM_KILLFOCUS(hWnd, hwndNewFocus, DefMDIChildProc);
}