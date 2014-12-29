#pragma once
#include <string>

class IOrganizer
{
public:
	virtual std::wstring GetPluginName() const = 0;
	virtual HWND GetPluginWindow()const = 0;
	virtual void SetPluginWindow(HWND hWnd) = 0;
	virtual bool AddItem() = 0;
	virtual bool EditItem() = 0;
	virtual bool DeleteItem() = 0;

	virtual void ShowSingleItem() const = 0;
	virtual void ShowAllItems() const = 0;
	virtual void ResizePlugin() const = 0;
};