/*
Создать имитационную модель "остановка маршрутных такси". Необходимо вводить
следующую информацию: среднее время между появлениями пассажиров на остановке
в разное время суток, среднее время между появлениями маршруток на остановке
в разное время суток, тип остановки (конечная или нет). Необходимо определить:
среднее время пребывание человека на остановке, достаточный интервал времени между
приходами маршруток, чтобы на остановке находилось не более N  людей одновременно. 
Количество свободных мест в маршрутке является случайной величиной.
*/

#include <iostream>
#include <ctime>
#include "BusStop.h"
using namespace std;

void main()
{
	time_t rawTime;
	time(&rawTime);
	struct tm* calcTime;
	calcTime= localtime(&rawTime);
	
	calcTime->tm_hour = 7;
	calcTime->tm_min = 0;
	calcTime->tm_sec = 0;
	rawTime = mktime(calcTime);

	const int dayPassTime = 60; 
	const int dayBusTime = 180;
	const int nightPassTime = 120;
	const int nightBusTime = 300;
	
	BusStop busStop(dayPassTime, dayBusTime, nightPassTime, nightBusTime);
	for (int i = 0; i < 10; ++i)
	{		
		busStop.CalculateTime(rawTime+i*dayBusTime, 5);
		cout << endl;
	}
}