/*
Написать приложение, позволяющее вывести на экран краткое резюме
с помощью поседовательности окон сообщений (количество окон сообщений -
не менее трёх). На заголовке последнего окна сообщения должно 
отобразиться среднее число символов на странице
(общее число символов в резюме поделить на количество окон сообщений).
*/

#include <windows.h>
#include <vector>
#include <string>
using namespace std;

void MsgBox(const char* message, const char* title);

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int nCmdShow)
{
	const int messagesNumber = 3;
	const char* messages[messagesNumber] = {
		"My name is Oleksandr.", 
		"I was born on the 20th of January 1983.",
		"I'm Ukrainian." };

	int symbolsNumber = 0;
	for (auto message : messages)
	{
		MsgBox(message, "Resume");
		symbolsNumber += strlen(message);
	}

	string averageNumber = to_string(symbolsNumber/messagesNumber);
	MsgBox(averageNumber.c_str(),"Average number of symbols");

	return 0;
}

void MsgBox(const char* message, const char* title)
{
	MessageBoxA(
		0,
		message,
		title,
		MB_OK | MB_ICONINFORMATION);
}