#include "CrackersDlg.h"
#include <iostream>
#include <sstream>


CrackersDlg* CrackersDlg::handler=nullptr;

CrackersDlg::CrackersDlg():mLeft(0), mTop(0), mWidth(0), mHeight(0), mMinSize(10), mCurrentNumber(0)
{
	handler=this;
	_tcscpy(mDialogCaption, TEXT("Static text"));
}

void CrackersDlg::Cls_OnClose(HWND hWnd)
{
	EndDialog(hWnd, 0);
}

void CrackersDlg::Cls_OnLButtonDown(HWND hWnd, BOOL fDoubleClick, int x, int y, UINT keyFlags)
{
	if (fDoubleClick)
	{
		const int curItem=ItemHasCoords(x,y);	
		if(curItem!=-1) 
		{
			DestroyWindow(mStaticsHwnd[curItem]);
		}

		SetWindowText(hWnd, mDialogCaption);
	}	

	mLeft=x;
	mTop=y;
}

void CrackersDlg::Cls_OnLButtonUp(HWND hWnd, int x, int y, UINT keyFlags)
{	
	if (x==mLeft && y==mTop) return ;

	int staticWidth=x-mLeft;
	int staticHeight=y-mTop;
	if (mLeft-x>=10 && mTop-y>=10)
	{
		mLeft=x;
		mTop=y;
		staticWidth=-staticWidth;
		staticHeight=-staticHeight;
	}


	if (staticWidth >= mMinSize && staticHeight >= mMinSize)
	{
		std::wstringstream number;
		number << ++mCurrentNumber;

		HWND staticHwnd = CreateWindowExW(0, L"STATIC", number.str().c_str(), WS_CHILD | WS_VISIBLE | WS_BORDER | WS_EX_CLIENTEDGE | SS_CENTER,
			mLeft, mTop, staticWidth, staticHeight, hWnd, 0, GetModuleHandle(NULL), 0);

		mStaticsHwnd.push_back(staticHwnd);
	}
	else
	{
		MessageBox(hWnd, TEXT("Min size of static: 10x10"), TEXT("Static hasn't been created"), MB_OK|MB_ICONEXCLAMATION);
	}

	mLeft=0;
	mTop=0;
}

void CrackersDlg::Cls_OnRButtonDown(HWND hWnd, BOOL fDoubleClick, int x, int y, UINT keyFlags)
{
	if (mStaticsHwnd.empty()) return;

	const int curItem=ItemHasCoords(x,y);	
	if(curItem!=-1) 
	{
		const HWND curStatic=mStaticsHwnd[curItem];

		int staticTextLength = GetWindowTextLength(curStatic) + 1;
		TCHAR* staticText = new TCHAR[staticTextLength];
		GetWindowText(curStatic, staticText, staticTextLength);

		std::wstringstream dialogCaption;
		dialogCaption<<"#"<<staticText
			<<"   x:"<<mLeft
			<<" y:"<<mTop
			<<"   width:"<<mWidth
			<<" height:"<<mHeight;

		SetWindowText(hWnd, dialogCaption.str().c_str());

		delete[] staticText;
	}
	else
	{
		SetWindowText(hWnd, mDialogCaption);
	}
}

int CrackersDlg::ItemHasCoords(const int x, const int y)
{
	for (int i=mStaticsHwnd.size()-1; i>=0; --i)
	{
		RECT rect;
		GetWindowRect(mStaticsHwnd[i], &rect);
		MapWindowPoints(HWND_DESKTOP, GetParent(mStaticsHwnd[i]), (LPPOINT) &rect, 2);

		if (x>=rect.left && x<=rect.right && y>=rect.top && y<=rect.bottom)
		{
			mLeft=rect.left;
			mTop=rect.top;
			mWidth=rect.right-rect.left;
			mHeight=rect.bottom-rect.top;

			return i;
		}
	}

	return -1;
}


BOOL CALLBACK CrackersDlg::DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		HANDLE_MSG(hWnd, WM_CLOSE, handler->Cls_OnClose);
		HANDLE_MSG(hWnd, WM_LBUTTONDOWN, handler->Cls_OnLButtonDown);
		HANDLE_MSG(hWnd, WM_LBUTTONUP, handler->Cls_OnLButtonUp);
		HANDLE_MSG(hWnd, WM_LBUTTONDBLCLK, handler->Cls_OnLButtonDown);
		HANDLE_MSG(hWnd, WM_RBUTTONDOWN, handler->Cls_OnRButtonDown);	
	}
	return FALSE;
}

