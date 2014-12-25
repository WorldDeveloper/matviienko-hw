#pragma once
#include <Windows.h>

class iOrganizer
{
	virtual void SetWindow(HWND destWindow) = 0;
	virtual bool AddItem() = 0;
	virtual bool EditItem(const int id) = 0;
	virtual bool DeleteItem(const int id) = 0;

	void ShowSingleItem(const int id) const;
	void ShowAllItems() const;
};