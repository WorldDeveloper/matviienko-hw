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
void GetInfo(const Array<T>& obj)
{
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
	cout << "\n***A************************************\n";
	Array<int> a;
	cout << "*SetSize(3,5)\n";
	a.SetSize(3, 5);
	GetInfo(a);

	cout << "*SetSize(13,5)\n";
	a.SetSize(13, 5);

	cout << "*Add()\n";
	a.Add();

	cout << "*for i=0 to 14: Set(i,i)\n";
	for (int i = 0; i < 15; ++i)
	{
		a.SetAt(i, i);
	}
	GetInfo(a);

	cout << "*RemoveAll()\n";
	a.RemoveAll();
	GetInfo(a);

	cout << "*SetSize(14)\n";
	a.SetSize(14);

	cout << "*for i=0 to 9: Set(i,i*2)\n";
	for (int i = 0; i < 10; ++i)
	{
		a.SetAt(i, i * 2);
	}

	cout << "*FreeExtra()\n";
	a.FreeExtra();
	GetInfo(a);


	cout << "\n***B************************************\n";
	Array<int> b;
	cout << "*B=A\n";
	b = a;
	GetInfo(b);

	cout << "*Append(a)\n";
	b.Append(a);
	GetInfo(b);

	cout << "*InsertAt(0, 111)\n";
	b.InsertAt(0, 111);
	cout << "*InsertAt(5, 555)\n";
	b.InsertAt(5, 555);
	cout << "*InsertAt(21, 21)\n";
	b.InsertAt(21, 21);
	cout << "*InsertAt(23,23)\n";
	b.InsertAt(23, 23);
	GetInfo(b);

	cout << "*RemoveAt(23)\n";
	b.RemoveAt(23);
	cout << "*RemoveAt(21)\n";
	b.RemoveAt(21);
	cout << "*RemoveAt(5)\n";
	b.RemoveAt(5);
	cout << "*RemoveAt(0)\n";
	b.RemoveAt(0);
	GetInfo(b);

	cout << "\n***pA************************************\n";
	cout << "*pa=a.GetData()\n\t";
	int *pa = a.GetData();
	for (int i = 0; i <= a.GetUpperBound(); ++i)
	{
		cout << pa[i] << " ";
	}

	cout << "\n\n***pB************************************\n";
	cout << "*pb=b.GetData()\n\t";
	int *pb = b.GetData();
	for (int i = 0; i <= b.GetUpperBound(); ++i)
	{
		cout << pb[i] << " ";
	}
	cout << "\n\n";
}
