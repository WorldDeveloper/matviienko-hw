#include "ChildWnd.h"

ChildWnd* ChildWnd::handler = nullptr;

ChildWnd::ChildWnd()
{
	handler=this;
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
		ShowWindow(hWnd, SW_HIDE);

		HWND hNextWindow = NULL;
		for (int i = 0; i < mPluginsCount; ++i)
		{
			HWND tmp = mpPlugins[i]->GetPluginWindow();
			if (tmp != hWnd && IsWindowVisible(tmp))
			{
				hNextWindow = tmp;
				break;
			}
		}

		if (hNextWindow) SetFocus(hNextWindow);
}

void ChildWnd::Cls_OnCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify)
{
	//MessageBox(hWnd, L"Button", NULL, MB_OK);
}


void ChildWnd::Cls_OnSize(HWND hWnd, UINT state, int cx, int cy)
{
	if (mpCurrentPlugin) mpCurrentPlugin->ResizePlugin();

	
	FORWARD_WM_SIZE(hWnd, state, cx, cy, DefMDIChildProc);
}

void ChildWnd::Cls_OnSetFocus(HWND hWnd, HWND hwndOldFocus)
{
	mpCurrentPlugin = NULL;
	for (int i = 0; i < mPluginsCount; ++i)
	{
		if (!mpPlugins[i]) continue;

		HWND pluginWindow = mpPlugins[i]->GetPluginWindow();
		if (pluginWindow == hWnd && IsWindowVisible(pluginWindow))
		{
			mpCurrentPlugin = mpPlugins[i];
			break;
		}
	}
	FORWARD_WM_SETFOCUS(hWnd, hwndOldFocus, DefMDIChildProc);
}

void ChildWnd::Cls_OnKillFocus(HWND hWnd, HWND hwndNewFocus)
{
	for (int i = 0; i < mPluginsCount; ++i)
	{
		if (!mpPlugins[i]) continue;

		HWND pluginWindow = mpPlugins[i]->GetPluginWindow();
		if (pluginWindow == hwndNewFocus)
		{
			mpCurrentPlugin = NULL;
			break;
		}
	}	

	FORWARD_WM_KILLFOCUS(hWnd, hwndNewFocus, DefMDIChildProc);
}


