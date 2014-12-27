#pragma once
#include <string>

class IOrganizer
{
public:
	virtual std::wstring GetPluginName() const = 0; 
	virtual void SetWindow(HWND destWindow) = 0;
	virtual HWND GetPluginWindow() const = 0;
	virtual bool AddItem() = 0;
	virtual bool EditItem(const int id) = 0;
	virtual bool DeleteItem(const int id) = 0;

	virtual void ShowSingleItem(const int id) const = 0;
	virtual void ShowAllItems() const = 0;
	virtual void ResizePlugin() const = 0;
};