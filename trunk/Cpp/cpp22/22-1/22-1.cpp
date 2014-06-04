/*
Cоздайте класс Date, который будет содержать информацию о дате
(день, месяц, год). С помощью механизма перегрузки операторов,
определите операцию разности двух дат (результат в виде количества дней между датами),
а также операцию увеличения даты на определенное количество дней.
*/

#include <iostream>
#include "Date.h";
using namespace std;

void main()
{
	Date firstDate(2, 1, 2013);
	cout << "First Date (d,m,y):" << firstDate;

	Date secondDate(1, 1, 2014);
	cout << "Second Date (d,m,y):" << secondDate;

	cout << endl << "Second date - First date= " << secondDate-firstDate<<" days";

	while (true)
	{
		int days;
		cout << "\n\nDays to be added:";
		cin >> days;
		cout << "First date + " << days << " days= " << firstDate + days;
	}
}