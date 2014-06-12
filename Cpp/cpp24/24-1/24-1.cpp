/*
Создайте класс Время, в котором реализованы операции
сложения, вычитания, сравнения, ввода и вывода на экран. 
Возможность конвертации времени из американского формата
am(pm):10:00pm=22:00, 12:00pm=00:00
*/

#include <iostream>
#include "Time.h"
#include <iomanip>
#include <ctime>
#include <stdio.h>
using namespace std;


ostream &TwoDigitFormat(ostream &stream);
ostream &operator<<(ostream &stream, const Time &output);
void Print(const bool state, const char *condition);
bool InputTime(Time &timeObject);

void main()
{
	time_t rawTime;
	time(&rawTime);
	struct tm* curTime = localtime(&rawTime);

	Time a(curTime->tm_hour,
		curTime->tm_min,
		curTime->tm_sec,
		false);
	
	Time b;	
	while (true)
	{		
		if (InputTime(b))
		{
			system("cls"); 
			cout << "\nCurrent time (a):" << a << endl;
			a.ChangeFormat();
			cout << "\t\t " << a << endl; 
			
			cout << "\nInputed time (b):" << b << endl;
			b.ChangeFormat();
			cout <<"\t\t "<< b << endl;

			Time c = a;
			cout << "\nc=a\t" << c << endl;
			cout <<"a+b\t"<< a + b << endl;
			cout <<"a-b\t"<< a - b << endl;
			cout << "b-c\t"<<b - c << endl;

			Print(a == c, "a==c\t");
			Print(a != c, "a!=c\t");

			Print(a<b, "a<b\t");
			Print(a <= b, "a<=b\t");

			Print(a>b, "a>b\t");
			Print(a >= b, "a>=b\t");

			Print(a <= c, "a<=c\t");
			Print(a>=c, "a>=c\t");
			Print(b >= a, "b>=a\t");
		}
		else
		{
			system("cls");
			cout << "\nError: inputed time is incorrect!" << endl;
		}
	}
}


bool InputTime(Time &timeObject)
{
	fflush(stdin);
	cout << endl << "Enter a new time \"hh:mm:ss:am*\" (*:am/pm - optional)" << endl;
	int hour = -1;
	int min = -1;
	int sec = -1;
	char format[3];
	strcpy(format, "\0");

	if (!scanf("%d:%d:%d:%2s", &hour, &min, &sec, &format))
	{
		return false;
	}

	bool american; 
	if (hour >= 0 && min >= 0 && sec >= 0)
	{
		strcpy(format, strlwr(format));
		
		if ((!strcmp(format, "am") || !strcmp(format, "pm")) && hour<13)
		{
			american = true;
			if (!strcmp(format, "pm"))
			{
				hour == 12 ? 0 : hour += 12;
			}
		}
		else if (strlen(format)==0)
		{
			american = false;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}

	if (timeObject(hour, min, sec, american))
	{
		return true;
	}
	
	return false;
}


ostream &TwoDigitFormat(ostream &stream)
{
	stream << setw(2) << setfill('0');
	return stream;
}


ostream &operator<<(ostream &stream, const Time &output)
{
	stream << TwoDigitFormat;
	if (output.mAmerican)
	{
		if (output.mHour == 0)	{ stream << "12"; }
		else if (output.mHour>12) { stream << output.mHour - 12; }
		else { stream << output.mHour; }
	}
	else
	{
		stream << output.mHour;
	}

	stream << ":";
	stream << TwoDigitFormat << output.mMin << ":";
	stream << TwoDigitFormat << output.mSec;

	if (output.mAmerican)
	{
		if (output.mHour < 12) { stream << " am"; }
		else { stream << " pm"; }
	}

	return stream;
}


void Print(const bool state, const char* condition)
{
	cout << condition;
	if (state) 
	{
		cout <<": True";
	}
	else
	{
		cout << ": False";
	}
	cout << endl;
}
