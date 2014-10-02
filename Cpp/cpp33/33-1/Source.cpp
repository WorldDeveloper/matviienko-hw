/*
Написать функцию вычисления значения по заданной строке символов,
являющихся записью этого числа в десятичной системе счисления. Предусмотреть
случай выхода за границы диапазона определяемого типом int. Используйте
механизм исключений.
*/

#include <iostream>
#include <string>
using namespace std;

int Input();

void main()
{
	while (true)
	{
		try
		{
			int intNumber = Input();
			cout << "\nInteger= " << intNumber << endl;
			break;
		}
		catch (char* error)
		{
			cout << "\nError: " << error << endl;
			cout << "Enter correct value.\n";
		}
	}
}

int Input()
{
	string textNumber;
	cin >> textNumber;

	string::reverse_iterator pStart = textNumber.rend();
	pStart--;
	int offset = 0;
	if (*pStart == '+' || *pStart == '-')
	{
		--pStart;
		++offset;
	}

	char* error = "out of range.";
	if (textNumber.size() - offset > 10) throw error;

	const string intMax = "2147483647";
	if (textNumber.size() - offset == 10)
	{
		for (int i = 0; i<10; ++i)
		{
			if (textNumber[i + offset]>intMax[i]) throw error;
		}
	}

	int order = 1;
	int intNumber = 0;
	for (string::reverse_iterator pEnd = textNumber.rbegin(); pEnd <= pStart; pEnd++)
	{
		if (*pEnd<'0' || *pEnd>'9') throw error;
		intNumber += order*(*pEnd - 48);
		order *= 10;
	}

	if (textNumber.substr(0, 1) == "-")  intNumber = -intNumber;

	return intNumber;
}