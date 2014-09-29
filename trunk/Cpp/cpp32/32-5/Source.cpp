/*
Создать абстрактный базовый класс с виртуальной функцией - корни уравнения. 
Создать производные классы: класс линейных уравнений и класс квадратных уравнений.
Определить функцию вычисления корней уравнений.
*/
#include <iostream>
#include "LinearEquation.h"
#include "QuadraticEquation.h"
using namespace std;

void main()
{
	Equation<int>* equation = new LinearEquation<int>;
	equation->Solve();
	delete equation;

	equation = new QuadraticEquation<int>;
	equation->Solve();
	delete equation;
}