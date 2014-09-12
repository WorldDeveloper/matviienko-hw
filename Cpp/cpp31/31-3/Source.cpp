/*
Используя понятие множественного наследования, разработайте класс
"Окружность, вписанная в квадрат".
*/

#include <iostream>
using namespace std;

class Square
{
	float mWidth;
public:
	Square(const float width) : mWidth(width){}
	float GetSquareArea() const { return mWidth*mWidth; }
	float GetSquarePerimeter() const { return 4 * mWidth; }
	float GetSquareWidth() const { return mWidth; }
};

class Circle
{
	float mRadius;
	const float mPi;
public:
	Circle(const float radius) : mRadius(radius), mPi(3.141592){}
	float GetCircleArea() const { return mPi*mRadius*mRadius; }
	float GetCirclePerimetr() const { return 2 * mPi*mRadius; }
	float GetCircleRadius() const { return mRadius; }
};

class CircleInSquare :public Square, public Circle
{
public:
	CircleInSquare(const float width) : Square(width), Circle(width / 2){}
};

void main()
{
	CircleInSquare f(10.0);
	cout << "SQUARE\n";
	cout << "Width: " << f.GetSquareWidth() << endl;
	cout << "Perimeter: " << f.GetSquarePerimeter() << endl;
	cout << "Area: " << f.GetSquareArea() << endl;

	cout << "\nCIRCLE\n";
	cout << "Radius: " << f.GetCircleRadius() << endl;
	cout << "Perimeter: " << f.GetCirclePerimetr() << endl;
	cout << "Area: " << f.GetCircleArea() << endl;

}