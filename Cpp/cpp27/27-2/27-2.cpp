/*
Реализовать шаблонный класс "Очередь" на основе двусвязного списка.
*/

#include <iostream>
#include "QueueList.h"
using namespace std;

void main()
{
	QueueList<int> q1;
	cout << "Queue A: ";
	for (int i = 0; i < 5; ++i)
	{
		q1.PushBack(i);
	}
	int count = q1.GetCount();
	while (q1.GetCount())
	{
		cout << q1.PopFront() << " ";
	}
	cout << "\n\tTotal: " << count << " items" << endl;


	cout << "\n\nQueue A: ";
	q1.PushBack(7);
	QueueList<int> q2(q1);

	count = q1.GetCount();
	while (q1.GetCount())
	{
		cout << q1.PopFront() << " ";
	}
	cout << "\n\tTotal: " << count << " items" << endl;


	cout << "\n\nQueue B: ";
	for (int i = 0; i < 5; ++i)
	{
		q2.PushBack(i);
	}
	count = q2.GetCount();
	while (q2.GetCount())
	{
		cout << q2.PopFront() << " ";
	}
	cout << "\n\tTotal: " << count << " items" << endl;


	cout << "\n\nQueue B: ";
	for (int i = 0; i < 5; ++i)
	{
		q2.PushBack(i);
	}
	q2.Clear();
	count = q2.GetCount();
	while (q2.GetCount())
	{
		cout << q2.PopFront() << " ";
	}
	cout << "\n\tTotal: " << count << " items" << endl;

	cout << "\n\n";
}