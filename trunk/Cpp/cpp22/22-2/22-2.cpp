﻿/*
Добавить в строковый класс функцию, которая создает строку,
содержащую пересечение двух строк, то есть общие символы для двух строк.
Например, результатом пересечения строк "sdqcg" "rgfas34" будет строка "sg".
Для реализации функции перегрузить оператор * (бинарное умножение).
*/

#include <iostream>
#include "string.h"
using namespace std;

void main()
{
	cout << "Test A:\n";
	String a;
	cout << a;
	a.setString("...test A is passed");
	cout << a<<" (" << a.getLength()<<"s)";

	cout << "\n\nTest A=A:" << endl;
	a = a;
	cout << a;

	cout << "\n\nTest B:\n";
	String b("...test B is passed");
	cout << b<<" ("<<b.getLength()<<"s)";
	

	cout << "\n\nTest C:\n"; 
	String c;
	c= a*b;
	cout << "a*b= \"" << a*b<<"\" ("<<c.getLength()<<"s)";

	cout << "\n\nTest D:\n";
	String d(10);
	cout << "Enter a string:";
	cin >> d;
	cout << d <<" ("<<d.getLength()<<"s)"<< endl << endl;
}