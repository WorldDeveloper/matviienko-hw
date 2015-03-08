#include "ParserDlg.h"

ParserDlg* ParserDlg::ptr = nullptr;

ParserDlg::ParserDlg()
{
	ptr = this;
}

BOOL CALLBACK ParserDlg::DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hWnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hWnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hWnd, WM_COMMAND, ptr->Cls_OnCommand);
	}

	return FALSE;
}

BOOL ParserDlg::Cls_OnInitDialog(HWND hWnd, HWND hWndFocus, LPARAM lParam)
{
	mhDlg = GetDlgItem(hWnd, IDD_DLG);
	mhShowTimetable = GetDlgItem(hWnd, IDC_TIMETABLE);
	mhShowTrains = GetDlgItem(hWnd, IDC_SHOWTRAINS);
	mhShowStations = GetDlgItem(hWnd, IDC_SHOWSTATIONS);
	mhTrainsList = GetDlgItem(hWnd, IDC_TRAINSLIST);
	mhStationsList = GetDlgItem(hWnd, IDC_STATIONSLIST);

	mXmlDoc.LoadFile("railway.xml");
	mpRoot = mXmlDoc.FirstChildElement("railway");
	if (mpRoot == nullptr)
	{
		MessageBox(hWnd, "Error: the XML file is empty/faulty.", "Error", MB_OK | MB_ICONERROR);
		EndDialog(hWnd, 0);
	}

	tinyxml2::XMLElement* pNode = mpRoot->FirstChildElement("stationsNames");
	if (pNode == nullptr)
	{
		MessageBox(hWnd, "Error: there are no stations.", "Error", MB_OK | MB_ICONERROR);
		EndDialog(hWnd, 0);
	}

	tinyxml2::XMLElement* pElement = pNode->FirstChildElement("stationName");
	while (pElement != nullptr)
	{
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		std::wstring id = converter.from_bytes(pElement->Attribute("id"));
		std::wstring text = converter.from_bytes(pElement->GetText());

		mStations.insert(std::pair<std::wstring, std::wstring>(id, text));
		int index = SendMessageW(mhStationsList, CB_ADDSTRING, 0, LPARAM(text.c_str()));
		pElement = pElement->NextSiblingElement("stationName");
	}

	pNode = mpRoot->FirstChildElement("trains");
	if (pNode == nullptr)
	{
		MessageBox(mhDlg, "Error: there are no trains.", "Error", MB_OK | MB_ICONERROR);
		EndDialog(mhDlg, 0);
	}

	pElement = pNode->FirstChildElement("train");
	while (pElement != nullptr)
	{
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		std::wstring id = converter.from_bytes(pElement->Attribute("id"));
		std::wstring text = id.substr(1);
		if (pElement->GetText()) text += L" " + converter.from_bytes(pElement->GetText());


		mTrains.insert(std::pair<std::wstring, std::wstring>(id, text));
		int index = SendMessageW(mhTrainsList, CB_ADDSTRING, 0, LPARAM(text.c_str()));
		pElement = pElement->NextSiblingElement("train");
	}

	return TRUE;
}

void ParserDlg::Cls_OnCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify)
{
	switch (id)
	{
	case IDC_TIMETABLE:
	{
		tinyxml2::XMLElement* pNode = mpRoot->FirstChildElement("routes");
		if (pNode == nullptr)
		{
			MessageBox(hWnd, "Error: there are no routes.", "Error", MB_OK | MB_ICONERROR);
			EndDialog(hWnd, 0);
		}

		tinyxml2::XMLElement* pElement = pNode->FirstChildElement("route");
		std::wstringstream output;
		output << L"Route id\t" << L"Train id\t" << L"Station\t" << L"Dep. tm\t" << L"Station\t" << L"Arr. tm\n";
		while (pElement != nullptr)
		{
			std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
			output << converter.from_bytes(pElement->Attribute("id")).substr(1);
			output << L".\t" << converter.from_bytes(pElement->Attribute("trainID")).substr(1);


			tinyxml2::XMLElement* pStations = pElement->FirstChildElement("stations");
			if (pStations == nullptr) return;

			tinyxml2::XMLElement* pStation = pStations->FirstChildElement("station");
			if (pStation == nullptr) return;
			std::wstring stationID = converter.from_bytes(pStation->Attribute("id"));

			output << L"\t" << mStations[stationID];
			output << L"\t" << converter.from_bytes(pStation->FirstChildElement("departureTime")->GetText());

			pStation = pStations->LastChildElement("station");
			if (pStation == nullptr) return;
			stationID = converter.from_bytes(pStation->Attribute("id"));
			output << L"\t" << mStations[stationID];
			output << L"\t" << converter.from_bytes(pStation->FirstChildElement("arrivalTime")->GetText());
			output << std::endl;

			pElement = pElement->NextSiblingElement("route");
		}
		MessageBoxW(hWnd, output.str().c_str(), L"Railway timetable", MB_OK | MB_ICONINFORMATION);

		break;
	}
	case IDC_SHOWTRAINS:
	{
		int index = SendMessage(mhStationsList, CB_GETCURSEL, 0, 0);
		if (index == CB_ERR) return;

		int len = SendMessage(mhStationsList, CB_GETLBTEXTLEN, index, 0);
		wchar_t* buffer = new wchar_t[len + 1];
		SendMessageW(mhStationsList, CB_GETLBTEXT, index, LPARAM(buffer));

		std::wstring stationName = buffer;
		delete[] buffer;

		tinyxml2::XMLElement* pNode = mpRoot->FirstChildElement("routes");
		if (pNode == nullptr)
		{
			MessageBox(hWnd, "Error: there are no routes.", "Error", MB_OK | MB_ICONERROR);
			EndDialog(hWnd, 0);
		}

		tinyxml2::XMLElement* pElement = pNode->FirstChildElement("route");
		std::wstringstream output;
		output << L"Route id\t" << L"Train id\t" << L"Arr. tm\t" << L"Dep. tm\n";
		while (pElement != nullptr)
		{
			std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

			tinyxml2::XMLElement* pStations = pElement->FirstChildElement("stations");
			if (pStations == nullptr) return;

			tinyxml2::XMLElement* pStation = pStations->FirstChildElement("station");
			while (pStation != nullptr)
			{
				std::wstring stationID = converter.from_bytes(pStation->Attribute("id"));
				if (mStations[stationID] == stationName)
				{
					output << converter.from_bytes(pElement->Attribute("id")).substr(1);
					output << L".\t" << converter.from_bytes(pElement->Attribute("trainID")).substr(1);
					if (pStation->FirstChildElement("arrivalTime")->GetText())
						output << L"\t" << converter.from_bytes(pStation->FirstChildElement("arrivalTime")->GetText());
					else output << L"\t";

					if (pStation->FirstChildElement("departureTime")->GetText())
						output << L"\t" << converter.from_bytes(pStation->FirstChildElement("departureTime")->GetText());
					else output << L"\t";

					output << std::endl;
				}
				pStation = pStation->NextSiblingElement("station");
			}

			pElement = pElement->NextSiblingElement("route");
		}
		std::wstring caption = L"List of trains passing throught the station \"" + stationName + L"\"";
		MessageBoxW(hWnd, output.str().c_str(), caption.c_str(), MB_OK | MB_ICONINFORMATION);

		break;
	}
	case IDC_SHOWSTATIONS:
	{
		int index = SendMessage(mhTrainsList, CB_GETCURSEL, 0, 0);
		if (index == CB_ERR) return;

		int len = SendMessage(mhTrainsList, CB_GETLBTEXTLEN, index, 0);
		wchar_t* buffer = new wchar_t[len + 1];
		SendMessageW(mhTrainsList, CB_GETLBTEXT, index, LPARAM(buffer));

		std::wstring trainName = buffer;
		delete[] buffer;

		tinyxml2::XMLElement* pNode = mpRoot->FirstChildElement("routes");
		if (pNode == nullptr)
		{
			MessageBox(hWnd, "Error: there are no routes.", "Error", MB_OK | MB_ICONERROR);
			EndDialog(hWnd, 0);
		}

		tinyxml2::XMLElement* pElement = pNode->FirstChildElement("route");
		std::wstringstream output;
		output << L"Station\t" << L"Arr. tm\t" << L"Dep. tm\n";
		while (pElement != nullptr)
		{
			std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
			std::wstring trainID = converter.from_bytes(pElement->Attribute("trainID"));
			if (mTrains[trainID] == trainName)
			{
				tinyxml2::XMLElement* pStations = pElement->FirstChildElement("stations");
				if (pStations == nullptr) return;

				tinyxml2::XMLElement* pStation = pStations->FirstChildElement("station");
				while (pStation != nullptr)
				{
					std::wstring stationID = converter.from_bytes(pStation->Attribute("id"));
					output << mStations[stationID];
					if (pStation->FirstChildElement("arrivalTime")->GetText())
						output << L"\t" << converter.from_bytes(pStation->FirstChildElement("arrivalTime")->GetText());
					else output << L"\t";

					if (pStation->FirstChildElement("departureTime")->GetText())
						output << L"\t" << converter.from_bytes(pStation->FirstChildElement("departureTime")->GetText());
					else output << L"\t";
					output << std::endl;

					pStation = pStation->NextSiblingElement("station");
				}
			}
			pElement = pElement->NextSiblingElement("route");
		}
		std::wstring caption = L"List of stations being passed by the train \"" + trainName + L"\"";
		MessageBoxW(hWnd, output.str().c_str(), caption.c_str(), MB_OK | MB_ICONINFORMATION);

		break;
	}

	}
}