/*
Создать абстрактный базовый класс с виртуальной функцией - площадь. 
Создать производные классы: прямоугольник, круг, прямоугольный треугольник, 
трапеция со своими функциями площади. Для проверки определить массив ссылок 
на абстрактный класс, которым присваиваются адреса различных объектов. 
Площадь трапеции:S=(a+b)h/2
*/

#include <iostream>
#include "Figure.h"
#include "Rectangle.h"
#include "Circle.h"
#include "RightTriangle.h"
#include "Trapezoid.h"
#include <vector>
#include <memory>
using namespace std;


void main()
{
	vector<Figure*> figure;
	figure.push_back(new Rectangle(2, 3));
	figure.push_back(new Circle(5));
	figure.push_back(new RightTriangle(4, 2));
	figure.push_back(new Trapezoid(2, 4, 3));


	for (auto obj : figure)
	{
		cout << obj->GetName() << ": " << obj->GetArea() << endl;
		delete obj;
	}
	cout << endl;
}
