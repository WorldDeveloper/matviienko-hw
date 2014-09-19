/*
Написать программу, которая реализует функцию с неограниченным колличеством параметров,
организовывающую форматированный вывод на экран.
*/

#include <iostream>
#include <typeinfo>
#include <cstdarg>
#include <iomanip>
using namespace std;


void PrintFormat(const char* output, ...);

void main()
{
	PrintFormat("%10.5s %c%c     %s\n\n", "Hello!!!!!!!!!!!!", 't', 'o', "all!");
	printf("%10.5s %c%c     %s\n\n", "Hello!!!!!!!!!!!!", 't', 'o',"all!");

	PrintFormat("|%-10.1f|\n\n", 123.123456);
	printf("|%-10.1f|\n\n", 123.123456);

	PrintFormat("%s %c %d%%\n\n", "rate", '=', 15);
	printf("%s %c %d%%\n\n", "rate", '=', 15);
}


void PrintFormat(const char* output, ...)
{
	va_list pArg;
	va_start(pArg, output);

	const char* curSymbol = output;
	while (*curSymbol != '\0')
	{
		if (*curSymbol == '%')
		{
			++curSymbol;
			bool leftAlign = false;
			if (*curSymbol == '-')
			{
				cout << left;
				leftAlign = true;
				++curSymbol;
			}
			else
			{
				cout << right;
			}

			char fill = ' ';
			if (*curSymbol == '0')
			{
				fill = '0';
				++curSymbol;
			}

			char fillLen[100];
			char* pLen = fillLen;
			while (*curSymbol > 47 && *curSymbol < 58)
			{
				*pLen++ = *curSymbol++;
			}
			*pLen = '\0';
			int fillLength = atoi(fillLen);

			if (fillLength)
			{
				cout << setfill(fill) << setw(fillLength);
			}

			int precision;
			char precisionChar[100];
			char* pPrecision = precisionChar;
			if (*curSymbol != '\0'&& *curSymbol == '.')
			{
				curSymbol++;
				while (*curSymbol > 47 && *curSymbol < 58)
				{
					*pPrecision++ = *curSymbol++;
				}
				*pPrecision = '\0';
				precision = atoi(precisionChar);
			}
			else
			{
				precision = -1;
			}

			switch (*curSymbol)
			{
			case 'd':
			case'i':
				cout << va_arg(pArg, int);
				break;
			case'u':
				cout << va_arg(pArg, unsigned int);
				break;
			case'f':
				if (precision >= 0)
				{
					cout << fixed << setprecision(precision);
					if (leftAlign) cout << setfill(' ');
				}
				cout << va_arg(pArg, double);
				break;
			case'c':
				cout << va_arg(pArg, char);
				break;
			case's':
				char tmp[100];
				strcpy(tmp, va_arg(pArg, char*));

				if (precision >= 0 && precision < strlen(tmp))
				{
					tmp[precision] = '\0';
				}
				cout << tmp;
				break;
			case '%':
				cout << '%';
				break;
			default:
				cout << " ";
				break;
			}
		}
		else
		{
			cout << *curSymbol;
		}

		curSymbol++;
	}

	va_end(pArg);
}
