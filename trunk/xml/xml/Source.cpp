#include <iostream>
#include "tinyxml2.h"
#include <vector>
#include <string>
#include <map>

using namespace std;
using namespace tinyxml2;

void TrainsAcrossStation(XMLNode* root, const string stationID);
void StationsByTrain(XMLNode* root, const string trainID);

void main()
{
	XMLDocument doc;
	doc.LoadFile("railway.xml");

	XMLNode* pRoot = doc.FirstChildElement("railway");
	if (pRoot == nullptr)
	{
		cout << "Error: file is empty/faulty." << endl;
		exit(0);
	}	


	TrainsAcrossStation(pRoot, "4");
	StationsByTrain(pRoot, "94");	

	cout << endl;
}

void TrainsAcrossStation(XMLNode* root, const string stationID)
{
	XMLElement* pTrains = root->FirstChildElement("trains");
	if (pTrains == nullptr)
	{
		cout << "Error: there are no trains." << endl;
		exit(0);
	}

	XMLElement* pTrain = pTrains->FirstChildElement("train");
	std::vector<string> trains;

	cout << "\n\nTrains:\n";
	while (pTrain != nullptr)
	{
		trains.push_back(pTrain->GetText());
		cout << trains.back() << endl;
		pTrain = pTrain->NextSiblingElement("train");
	}
	
	cout << "\nTrains crossing station with id:" << stationID << "\n";
	XMLElement* pRoutes = root->FirstChildElement("routes");
	if (pRoutes == nullptr)
	{
		cout << "Error: there are no routes." << endl;
		exit(0);
	}

	XMLElement* pRoute = pRoutes->FirstChildElement("route");

	while (pRoute != nullptr)
	{
		pTrain = pRoute->FirstChildElement("trainID");
		XMLElement* pStations = pRoute->FirstChildElement("stations");
		XMLElement* pStation = pStations->FirstChildElement("station");
		while (pStation != nullptr)
		{
			string tmp = pStation->Attribute("id");
			if (tmp == stationID)
			{
				cout << pTrain->GetText() << endl;
				break;
			}
			pStation = pStation->NextSiblingElement("station");
		}

		pRoute = pRoute->NextSiblingElement("route");
	}
}

void StationsByTrain(XMLNode* root, const string trainID)
{
	XMLElement* pStations = root->FirstChildElement("stations");
	if (pStations == nullptr)
	{
		cout << "Error: there are no stations." << endl;
		exit(0);
	}
	
	XMLElement* pStation = pStations->FirstChildElement("station");
	std::map<string, string> stations;

	while (pStation != nullptr)
	{
		stations.insert(pair<string, string>(pStation->Attribute("id"), pStation->GetText()));
		pStation = pStation->NextSiblingElement("station");
	}

	cout << "\n\nStations:\n";
	std::map<string, string>::iterator it = stations.begin();
	for (; it != stations.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';	
	
	cout << "\nList of stations which train cross:\n";
	XMLElement* pRoutes = root->FirstChildElement("routes");
	if (pRoutes == nullptr)
	{
		cout << "Error: there are no routes." << endl;
		exit(0);
	}

	XMLElement* pRoute = pRoutes->FirstChildElement("route");

	while (pRoute != nullptr)
	{
		XMLElement* pTrain = pRoute->FirstChildElement("trainID");
		string curTrainID = pTrain->GetText();
		if (curTrainID == trainID)
		{
			pStations = pRoute->FirstChildElement("stations");
			pStation = pStations->FirstChildElement("station");
			while (pStation != nullptr)
			{
				cout << stations[pStation->Attribute("id")] << endl;
				pStation = pStation->NextSiblingElement("station");
			}
		}
		pRoute = pRoute->NextSiblingElement("route");
	}
}