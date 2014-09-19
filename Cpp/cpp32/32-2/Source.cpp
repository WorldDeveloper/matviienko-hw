/*
Создать базовый класс список. Реализовать на базе списка стек и очередь с виртуальными функциями вставки и вытаскивания.
*/

#include <iostream>
#include "List.h"
#include "Queue.h"
#include "Stack.h"
using namespace std;

void main()
{
	List<int> list;
	Queue<int> queue;
	Stack<int> stack;

	List<int>* pList = &list;
	List<int>* pQueue = &queue;
	List<int>* pStack = &stack;
	
	for (int i = 0; i < 5; ++i)
	{
		list.Push(i);
		queue.Push(i);
		stack.Push(i);
	}

	cout << "List \tQueue \tStack\n";
	for(int i = 0; i < 5; ++i)
	{
		cout << list.Pop() << "\t";
		cout << queue.Pop() << "\t";
		cout << stack.Pop() << "\n";
	}

	cout << "\n*******Pointers**********\n\n";
	for (int i = 0; i < 5; ++i)
	{
		pList->Push(i);
		pQueue->Push(i);
		pStack->Push(i);
	}

	cout << "List \tQueue \tStack\n";
	for (int i = 0; i < 5; ++i)
	{
		cout << pList->Pop() << "\t";
		cout << pQueue->Pop() << "\t";
		cout << pStack->Pop() << "\n";
	}
	cout << endl;
}