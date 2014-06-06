/*
—оздать класс дл€ работы с матрицами. ѕредусмотреть, как минимум,
функции дл€ сложени€ матриц, умножени€ матриц, транспонировани€ и 
присваивани€ матриц друг другу, установку и получение произвольного 
элемента матрицы. Ќеобходимо перегрузить соответствующие операторы.
*/

#include <iostream>
#include "Matrix.h"
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;

ostream &operator<<(ostream &stream, Matrix &output);
void RandomInit(Matrix &source);

void main()
{
	srand(time(NULL));
	Matrix a;
	cout << a;

	Matrix b(3, 5);
	RandomInit(b);
	a = b;

	cout <<"a:\n"<< a;
	cout << endl <<"b:\n"<< b << endl;

	Matrix c= a + b;
	cout <<"c=a+b:\n"<< c << endl;

	a++;
	cout << "transposed a:\n"<<a << endl;

	Matrix d;
	d= a*b;
	cout <<"d=transposed a * b:\n"<< d << endl;
}

ostream &operator<<(ostream &stream, Matrix &output)
{
	for (int i = 0; i < output.GetVSize(); ++i)
	{
		cout << "\t";
		for (int j = 0; j < output.GetHSize(); ++j)
		{
			stream <<setw(4)<<setfill(' ')<< output(i,j);
		}
		cout << endl;
	}
	return stream;
}

void RandomInit(Matrix &source)
{
	for (int i = 0; i < source.GetVSize(); ++i)
	{
		for (int j = 0; j < source.GetHSize(); ++j)
		{
			source(i,j) = rand() % 10;
		}
	}
}