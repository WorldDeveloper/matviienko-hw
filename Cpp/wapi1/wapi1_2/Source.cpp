/*
Написать приложение, которое "угадывает" задуманное пользователем число от 1 до 100.
Для запроса к пользователю использовать окна сообщений. после того, как число отгадано, 
необходимо вывести количество попыток, потребовавшихся для этого, и предоставить пользователю
возможность сыграть еще раз, не завершая программу. Окна сообщений следует оформить кнопками
и иконками в соответствии с конкретной ситуацией.
*/

#include <Windows.h>
#include <vector>
#include <algorithm>
#include <random>
#include <string>
#include <ctime>
using namespace std;


int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int nCmdShow)
{
	vector<int> numbers;
	for (int i = 1; i < 101; ++i) numbers.push_back(i);

	shuffle(numbers.begin(), numbers.end(), default_random_engine(time(NULL)));

	while (true)
	{
		int attempt = 0;
		for (; attempt < 100; ++attempt)
		{
			string number = "Is it " + to_string(numbers[attempt]) + "?";
			int button = MessageBoxA(0, number.c_str(), "Let me guess", MB_YESNOCANCEL | MB_ICONQUESTION);
			if (button == IDYES) break;
			if (button == IDCANCEL) return 0;
		}

		if (attempt == 100)
		{
			MessageBoxA(0, "You cheat me! I have won!", "I have won!", MB_OK | MB_ICONERROR);
		}
		else
		{
			string attempts = "Number of attemts: " + to_string(attempt + 1);
			MessageBoxA(0, attempts.c_str(), "I have guessed right!", MB_OK | MB_ICONINFORMATION);
		}

		int button = MessageBoxA(0, "Should I start a new game?", "New game", MB_YESNO | MB_ICONQUESTION);
		if (button == IDNO) break;
	}

	return 0;
}