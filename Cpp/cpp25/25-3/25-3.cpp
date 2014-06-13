/*
Написать программу, которая реализует функцию с неограниченным колличеством параметров,
организовывающую форматированный вывод на экран.
*/

#include <iostream>
#include <typeinfo>
#include <cstdarg>
using namespace std;

template <typename T>
void AnyNumParam(const int count, T arg ...)
{
	va_list pArg;
	va_start(pArg, count);

	cout << "\n\nThere are " << count << " \"";
	cout << typeid(va_arg(pArg, T)).name() << "\" parametrs in the function:\n";

	for (int i = 0; i < count; ++i)
	{
		cout << va_arg(pArg, T) << " ";
	}
	va_end(pArg);
}

void main()
{
	AnyNumParam(3, "aaa", "bbb", "ccc");
	AnyNumParam(4, 'a', 'b', 'c', 'd');
	AnyNumParam(5, 1, 2, 3, 4, 5);
	AnyNumParam(3, 1.1, 'a', 1);//don't work properly
}