/*
Разработать приложение, имитирующее очередь печати принтера. Должны
быть клиенты, посылающие запросы на принтер, у каждого из которых есть
свой приоритет. Каждый новый клиент попадает в очередь в зависимости от
своего приоритета. Необходимо сохранять статистику печати (пользователь,
время) в отдельной очереди. Предусмотреть вывод статистики на экран.
*/

#include <iostream>
#include "PrintQueue.h"
#include <ctime>
#include <cstdlib>
#include <iomanip>
using namespace std;


void InitClients(Client* clients, const int count);
void PrintClient(const Client& client);
void Header(const char* title);

void main()
{
	srand(time(NULL));
	const int clientsCount = 5;
	Client clients[clientsCount];
	InitClients(clients, clientsCount);

	time_t rawTime;
	time(&rawTime);
	rawTime -= 60 * 60;

	Header("ADDED TASKS");
	PrintQueue server;
	for (int i = 0; i < 15; ++i)
	{
		int r = rand() % 4;
		clients[r].printTime = rawTime + i * 60;
		server.Push(clients[r]);
		PrintClient(clients[r]);
	}

	Header("PRINT QUEUE");
	for (int i = 0; i < 15; ++i)
	{
		PrintClient(server.Pop());
	}

	cout << "\n\n";
}


void InitClients(Client* clients, const int count)
{
	strcpy(clients[0].name, "Client #1");
	clients[0].priority = 0;

	strcpy(clients[1].name, "Client #2");
	clients[1].priority = 0;

	strcpy(clients[2].name, "Client #3");
	clients[2].priority = 5;

	strcpy(clients[3].name, "Client #4");
	clients[3].priority = 3;
}

void PrintClient(const Client& client)
{

	struct tm* printTime = localtime(&client.printTime);
	cout << setw(2) << setfill('0') << printTime->tm_hour << ":";
	cout << setw(2) << setfill('0') << printTime->tm_min << "\t";
	cout << client.name << "\t" << client.priority << endl;
}

void Header(const char* title)
{
	cout << "\n\n\t*** " << title << " ****\n\n";
	cout << "TIME\tCLIENT\t\tPRIORITY\n";
}