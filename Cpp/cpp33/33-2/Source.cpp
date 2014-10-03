/*
Перепишите класс stack одного из предыдущих домашних заданий таким образом,
чтобы генерировать исключения для такого количества условий, какое Вы
считаете приемлемым. (Например, невозможность выделить нужное количество
памяти, переполнение стека и т.д.)
*/
#include <iostream>
#include "Stack.h"
using namespace std;


void Fill(Stack<int>& stack, const int size);
void Show(Stack<int>& stack, const int size);

void main()
{
	try
	{
		Stack<int> stack;

		cout << "Stack is filling...\n";
		Fill(stack, 3);

		cout << "\nStack is clearing...\n";
		stack.Clear();

		cout << "\nStack is popping...\n";
		if (!stack.Empty()) Show(stack, 10);
		else cout << "\t stack is empty\n";

		cout << "\nStack is filling...\n";
		Fill(stack, 3);

		cout << "\nStack is popping...\n";
		Show(stack, 4);

	}
	catch (bad_alloc)
	{
		cout << "\nError: out of memory.\n";
	}
	catch (char* e)
	{
		cout << "\nError: " << e << ".\n";
	}
}

void Fill(Stack<int>& stack, const int size)
{
	for (int i = 0; i < size; ++i)
	{
		stack.PushBack(i);
		cout << "\tpush " << i << endl;
	}
	cout << endl;
}

void Show(Stack<int>& stack, const int size)
{
	for (int i = 0; i < size; ++i)
	{
		cout << "\tpop " << stack.PopBack() << endl;
	}
	cout << endl;
}