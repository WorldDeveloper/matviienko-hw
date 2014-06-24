#include "BusStop.h"
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <iomanip>
using namespace std;


BusStop::BusStop():mLastStop(false)
{
	mStopParametrs[0].passAppearTime = 0; 
	mStopParametrs[0].busAppearTime = 0;
	mStopParametrs[1].passAppearTime = 0;
	mStopParametrs[1].busAppearTime = 0;
	srand(time(NULL));
}

BusStop::BusStop(const int dayPassAppearTime, const int dayBusAppearTime,
	const int nightPassAppearTime, const int nightBusAppearTime, const bool lastStop/*=false*/):mLastStop(lastStop)
{
	mStopParametrs[0].passAppearTime = dayPassAppearTime;
	mStopParametrs[0].busAppearTime = dayBusAppearTime;
	mStopParametrs[1].passAppearTime = nightPassAppearTime;
	mStopParametrs[1].busAppearTime = nightBusAppearTime;
	srand(time(NULL));
}

void BusStop::CalculateTime(const time_t calcTime, const int maxQueue)
{
	struct tm* logTime = localtime(&calcTime); 
	bool night;
	if (logTime->tm_hour>20 || logTime->tm_hour<6) night = true;
	else night = false;

	int carryingCapacity = rand() % 10;
	int sufficientTime = 0;
	for (int i = passengers.Count(); i < maxQueue; ++i)
	{
		sufficientTime += mStopParametrs[night].passAppearTime;
	}

	time_t busTime = calcTime + mStopParametrs[night].busAppearTime;
	for (time_t i = calcTime; i < busTime; i += mStopParametrs[night].passAppearTime)
	{
		passengers.Push(i);
	}

	int gonePass = 0;
	time_t totalWaitingTime=0;
	for (; gonePass < carryingCapacity; ++gonePass)
	{
		if (passengers.IsEmpty()) break;
		totalWaitingTime += busTime - passengers.Pop();
	}

	logTime = localtime(&busTime);
	cout << setw(2) << setfill('0') << logTime->tm_hour << ":";
	cout << setw(2) << setfill('0') << logTime->tm_min << endl;

	cout << "Average waiting time: ";
	if (gonePass>0)
	{
		PrintTime(totalWaitingTime / gonePass);
		cout  << " (m:s)";
	}
	else
	{
		cout << "0";
	}

	cout << "\n\t Free bus seats: " << carryingCapacity << endl;
	cout << "\t Gone passengers: " << gonePass << endl;
	cout << "\t Waiting passengers: " << passengers.Count() << endl;
	cout << "Sufficient time between buses arrival: ";
	PrintTime(sufficientTime);
	cout << " (m:s) \n\n";
}

void BusStop::PrintTime(const int time) const
{
	cout << setw(2) << setfill('0') << time/60 << ":";
	cout << setw(2) << setfill('0') << time%60 ;
}