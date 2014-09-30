/*
������� ����� ������� � ���������������. ���������� ����������� ������ - ����, ������ � �����.
���� ��� �������. ������ ��� �����. ���� ����� ������� - ��������� �������.
������ ���� ����� �������. ����� ����� ��������� ����� - ���������� �����.
���� � ����������� ������� ������ �����, ��� ��������, �� ����� ��������, ����� ����� �������.
���� ��� ������� ������ �� ����� �������. ���� ��� ������� ����� (������ 5 � �����������),
���� ������ �� ����������. ���� �������� ������ ���, �� ��� ��� �������.
*/


#include <iostream>
#include "Fox.h"
#include "Rabbit.h"
#include "Grass.h"
#include "Emptiness.h"
#include <vector>
using namespace std;

void main()
{

	int grassesNumber = 0;
	while (grassesNumber <= 0)
	{
		cout << "Grasses number: ";
		cin >> grassesNumber;
	}
	Grass grass("forest");

	int rabbitsNumber = 0;
	while (rabbitsNumber <= 0)
	{
		cout << "Rabbits number: ";
		cin >> rabbitsNumber;
	}

	int rabbitsAge = 0;
	while (rabbitsAge <= 0)
	{
		cout << "Rabbits age: ";
		cin >> rabbitsAge;
	}
	Rabbit rabbit("forest", rabbitsAge);

	int foxesNumber = 0;
	while (foxesNumber <= 0)
	{
		cout << "Foxes number: ";
		cin >> foxesNumber;
	}

	int foxesAge = 0;
	while (foxesAge <= 0)
	{
		cout << "Foxes age: ";
		cin >> foxesAge;
	}
	Fox fox("forest", foxesAge);
	cout << "\n\n";

	if (grassesNumber > rabbitsNumber) grass.Alive();
	else rabbit.Eat(grass);
	if (rabbitsAge > 5) rabbit.Die();

	if (foxesNumber > rabbitsNumber && rabbit.GetLocation() != "") fox.Eat(rabbit);
	else if (rabbit.GetLocation() != "") rabbit.Alive();

	if (foxesAge > 5) fox.Die();
	else if (foxesNumber <= 5) fox.Alive();

	cout << endl;
}