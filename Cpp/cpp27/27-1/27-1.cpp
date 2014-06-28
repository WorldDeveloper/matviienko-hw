/*
Добавить в класс "Односвязный список" следующие функции:
вставка элемента в заданную позицию, удаление элемента по заданной позиции, поиск заданного элемента
(функция возвращает позицию найденного элемента в случае успеха или NULL в случае неудачи).
*/

#include <iostream>
#include "ForwardList.h"
using namespace std;

void main()
{
	ForwardList<int> listA;
	
	listA.InsertAt(0, -1);

	for (int i = 0; i < 5; ++i)
	{
		listA.PushBack(i);
	}
	
	listA.InsertAt(6, 5);	
	int search=listA.Search(4);

	ForwardList<int> listB = listA;

	cout << "***List A***\n";
	while (listA.GetCount())
	{
		cout << listA.PopFront() << " ";
	}
	cout << "\n\nIndex of item \"4\" is :" << search;

	listB.EraseAt(0);
	listB.EraseAt(5);
	listB.EraseAt(3);
	search=listB.Search(4);

	cout << "\n\n\n***List B***\n";
	while (listB.GetCount())
	{
		cout << listB.PopFront() << " ";
	}
	cout << "\n\nIndex of item \"4\" is : " << search;
	cout << "\n\n";
}