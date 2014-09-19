/*
Создать шаблонный класс - контейнер Array, который представляет собой массив, позволяющий хранить объекты заданного типа.Класс должен реализовывать следующие функции :
--------------------------------------------------------------------------------
+ GetSize - получение размера массива(количество элементов, под которые выделена память)
+ SetSize(int size, int grow = 1) - установка размера массива(если параметр size больше предыдущего размера массива, то выделяется дополнительный блок памяти,
если нет, то "лишние" элементы теряются и память освобождается);
параметр grow определяет для какого количества элементов необходимо выделить память, если количество элементов превосходит текущий размер массива.
Например, SetSize(5, 5); означает, что при добавлении 6 - го элемента размер массива становится равным 10, при добавлении 11 - го - 15 и т.д.
+ GetUpperBound - получение последнего допустимого индекса в массиве.Например, если при размере массива 10, вы добавляете в него 4 элемента, то функция вернет 3.
+ IsEmpty - массив пуст ?
+ FreeExtra - удалить "лишнюю" память(выше последнего допустимого индекса)
+ RemoveAll - удалить все
+ GetAt - получение определенного элемента(по индексу)
+ SetAt - установка нового значения для определенного элемента(индекс элемента должен быть меньше текущего размера массива)
+ operator [] - для реализации двух предыдущих функций
+ Add - добавление элемента в массив(при необходимости массив увеличивается на значение grow функции SetSize)
+ Append - "сложение" двух массивов
+ operator =
+ GetData - получения адреса массива с данными
+ InsertAt - вставка элемента(-ов) в заданную позицию
+ RemoveAt - удаление элемента(-ов) с заданной позиции
*/

#include <iostream>
#include "Array.h"
using namespace std;

template <class T>
void GetInfo(Array<T>& obj, char* test)
{
	cout << "\n\n*" << test << endl;
	cout << "\n\t size=\t" << obj.GetSize();
	cout << "\n\t upper bound=\t" << obj.GetUpperBound();
	cout << "\n\t is empty=\t" << obj.IsEmpty();

	cout << "\n\t ";
	for (int i = 0; i <= obj.GetUpperBound(); ++i)
	{
		cout << obj.GetAt(i) << " ";
	}
	cout << endl << endl;
}
void main()
{
	cout << "\n***A***\n";

	Array<int> a;
	a.SetSize(3, 5);
	GetInfo(a, "SetSize(3,5)");

	a.Add(1);
	GetInfo(a, "Add(1)");

	a.SetSize(13, 5);
	GetInfo(a, "SetSize(13,5)");

	for (int i = 0; i < 13; ++i)
	{
		a.Add(i);
	}
	GetInfo(a, "for i=0 to 12: Add(i)");

	a.RemoveAll();
	GetInfo(a, "RemoveAll()");

	a.SetSize(10, 5);
	GetInfo(a, "SetSize(10)");


	for (int i = 0; i < 5; ++i)
	{
		a.Add(i * 3);
	}
	GetInfo(a, "for i=0 to 5: Add(i*3)");

	a.FreeExtra();
	GetInfo(a, "FreeExtra()");


	cout << "\n***B****\n";
	Array<int> b;
	b = a;
	GetInfo(b, "B=A");

	for (int i = 0; i < 5; ++i)
	{
		b.SetAt(i, i);
	}
	GetInfo(b, "for i=0 to 5: SetAt(i, i)");

	b.Append(a);
	GetInfo(b, "Append(a)");

	cout << "*InsertAt(0, 111)\n";
	b.InsertAt(0, 111);
	cout << "*InsertAt(4, 444)\n";
	b.InsertAt(4, 444);
	cout << "*InsertAt(11, 111)\n";
	b.InsertAt(11, 1222);
	GetInfo(b, "After insertion");

	cout << "*RemoveAt(11)\n";
	b.RemoveAt(11);
	cout << "*RemoveAt(4)\n";
	b.RemoveAt(4);
	cout << "*RemoveAt(0)\n";
	b.RemoveAt(0);
	GetInfo(b, "After deletion");

	cout << "\n***pA****\n";
	cout << "*pa=a.GetData()\n\t";
	int *pa = a.GetData();
	for (int i = 0; i <= a.GetUpperBound(); ++i)
	{
		cout << pa[i] << " ";
	}

	cout << "\n\n***pB***\n";
	cout << "*pb=b.GetData()\n\t";
	int *pb = b.GetData();
	for (int i = 0; i <= b.GetUpperBound(); ++i)
	{
		cout << pb[i] << " ";
	}
	cout << "\n\n";
}
