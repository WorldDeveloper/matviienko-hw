/*
Создайте класс динамического массива, в котором реализована проверка
выхода за границы массива. Перегрузите операторы: [], =, +, -, ++
(добавление элемента в конец массива), -- (удаление элемента из конца массива).
*/

#include <iostream>
#include "darray.h"
using namespace std;


ostream &operator<<(ostream &stream, darray<char> out)
{
	for (int i = 0; i < out.end(); ++i)
	{
		stream << out[i];
	}
	return stream;
}

template <typename T>
ostream &operator<<(ostream &stream, darray<T> out)
{
	for (int i = 0; i < out.end(); ++i)
	{
		stream << out[i] << " ";
	}
	return stream;
}

void main()
{
	int sizeA = 5;
	darray<int> a(sizeA);
	cout << "A:\t";
	for (int i = 0; i < sizeA; ++i)
	{
		a.pushBack(i);
		cout << a[i]<<" ";
	}
	cout << "\n\n";

	a = a;
	cout << "A=A:\t" << a;
	cout << "\n\n";


	int sizeB = 3;
	darray<int> b(sizeB);
	b = a;
	cout << "B=A:\t" << b;
	cout << "\n\n";

	int sizeC = 10;
	darray<int> c(sizeC);
	c=b+ a;
	cout << "C=A+B:\t" << c;
	cout << "\n\n";

	int sizeD = 10;
	darray<int> d(sizeD);
	for (int i = 0; i < sizeD; ++i)
	{
		d.pushBack(i);
	}
	cout << "D:\t" << d;
	cout << "\n\n";

	int sizeE = 1;
	darray<int> e(sizeE);
	e = d + c;
	cout << "E=D+C:\t" << e;
	cout << "\n\n";

	e = d-c;
	cout << "E=D-C:\t" << e;
	cout << "\n\n";

	cout << "A++:\t" << a++ << endl;
	a.pushBack(0);
	cout << "A: \t" << a << endl;
	++a;
	a.pushBack(0);
	cout << "++A:\t" <<a;
	cout << "\n\n";

	cout << "B--:\t" << b-- << endl;
	cout << "B: \t" << b << endl;
	cout << "--B:\t" << --b;
	cout << "\n\n";

	const int stringSize = 5;
	darray<char> string(stringSize);
	for (int i = 0; i < stringSize+5; ++i)
	{
		string.pushBack('a'+i);
	}
	cout <<"String:\t"<< string<<endl << endl;

	cout << "String[9]:\t";
	cout << string[9] << "\n\n"; 
	
	cout << "String[10]:\t";
	cout << string[10] << "\n\n";
}