/*
Написать программу, которая использует класс string для анализа строки,
содержащей математическое выражение, например, вида - (2+3)*4+1. Строка
вводится с клавиатуры. Программа выдает результат вычисления выражения.
*/
#include <iostream>
#include <string>
using namespace std;

int Input(string& text, string::iterator& pStart);
int AnalyseString(string& text);

void main()
{
	cout << "Expression: ";
	string expression;
	cin >> expression;

	try
	{
		cout <<"Result: "<< AnalyseString(expression) << endl;
	}
	catch (char* e)
	{
		cout << "Error: " << e << endl;
	}
}


int Input(string& text, string::iterator& pStart)
{
	if (pStart == text.end()) throw "syntax error";

	if (*pStart == '(')
	{
		++pStart;
		size_t found = text.find(")", pStart - text.begin());
		if (found == string::npos) throw "syntax error";
		
		const int cur = pStart - text.begin();
		pStart = text.begin() + found + 1;

		return AnalyseString(text.substr(cur, found - cur));
	}

	string::iterator pEnd = pStart + 1;
	while (pEnd != text.end() &&
		(*pEnd != '+' &&
		*pEnd != '-' &&
		*pEnd != '*' &&
		*pEnd != '/')) pEnd++;

	char* error = "out of range.";
	if (pEnd - pStart > 10) throw error;

	const string intMax = "2147483647";
	if (pEnd - pStart == 10)
	{
		for (int i = 0; i<10; ++i)
		{
			if (text[i]>intMax[i]) throw error;
		}
	}

	int intNumber = 0;
	for (; pStart < pEnd; pStart++)
	{
		if (*pStart<'0' || *pStart>'9') throw error;
		intNumber *= 10;
		intNumber += *pStart - 48;
	}

	pStart = pEnd;
	return intNumber;
}

int AnalyseString(string& text)
{
	if (text.empty()) throw "syntax error";

	string::iterator symb = text.begin();

	if (*symb == '*' || *symb == '/') throw "syntax error";
	if (*symb != '+' && *symb != '-')
	{
		text.insert(0, "+");
	}

	int result = 0;
	int buffer = 0;

	while (symb != text.end())
	{
		if (*symb == '+')
		{
			result += buffer;
			buffer = Input(text, ++symb);
		}
		else if (*symb == '-')
		{
			result += buffer;
			buffer = -Input(text, ++symb);
		}
		else if (*symb == '*')
		{
			buffer *= Input(text, ++symb);
		}
		else if (*symb == '/')
		{
			int tmp= Input(text, ++symb);
			if (tmp) buffer /= tmp;
			else throw "division by zero";
		}
		else
		{
			throw "syntax error";
		}
	}
	result += buffer;

	return result;
}