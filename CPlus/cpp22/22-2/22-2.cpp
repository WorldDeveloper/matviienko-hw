/*
�������� � ��������� ����� �������, ������� ������� ������,
���������� ����������� ���� �����, �� ���� ����� ������� ��� ���� �����.
��������, ����������� ����������� ����� "sdqcg" "rgfas34" ����� ������ "sg".
��� ���������� ������� ����������� �������� * (�������� ���������).
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
	cout << a;

	cout << "\n\nTest B:\n";
	String b("...test B is passed ");
	cout << b;
	
	cout << "\n\nTest C:\n"; 
	String c;
	c= a*b;
	cout << "a*b= \"" << a*b<<"\"";

	cout << "\n\nTest D:\n";
	String d(10);
	cout << "Enter a string:";
	cin >> d;
	cout << d;

	cout << endl << endl;
}