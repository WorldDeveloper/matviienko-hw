#pragma once
#include <new>
using namespace std;

template <class T>
struct Node
{
	T value;
	Node* previous;
	Node() : value(T()), previous(nullptr){}
	Node(const T& data) : value(data), previous(nullptr){}
};


template <class T>
class Stack
{
	Node<T>* mpTop;
	Node<T>* mpBase;
public:
	Stack() : mpTop(nullptr), mpBase(nullptr){}
	~Stack();

	Stack(const Stack& source);
	Stack& operator=(const Stack& source);

	void PushBack(const T& value);
	T PopBack();
	bool Empty() const { return !mpBase; }
	void Clear() { this->~Stack(); }
};


template <class T>
Stack<T>::~Stack()
{
	while (mpTop)
	{
		Node<T>* needlessNode = mpTop;
		mpTop = mpTop->previous;
		delete needlessNode;
	}
	mpBase = nullptr;
}

template <class T>
Stack<T>::Stack(const Stack<T>& source)
{
	mpTop = nullptr;
	mpBase = nullptr;

	Node<T>* tmp = source.mpTop;
	while (tmp)
	{
		Push(tmp->value);
		tmp = tmp->previous;
	}
}

template <class T>
Stack<T>& Stack<T>::operator=(const Stack<T>& source)
{
	if (this == &source) return *this;

	this->~Stack();

	Node<T>* tmp = source.mpTop;
	while (tmp)
	{
		Push(tmp->value);
		tmp = tmp->previous;
	}

	return *this;
}

template <class T>
void Stack<T>::PushBack(const T& value)
{
	Node<T>* tmp = new Node<T>(value);

	if (!mpBase)
	{
		mpBase = tmp;
		mpTop = tmp;
	}
	else
	{
		tmp->previous = mpTop;
		mpTop = tmp;
	}
}

template <class T>
T Stack<T>::PopBack()
{
	if (mpTop)
	{
		T value = mpTop->value;
		Node<T>* tmp = mpTop;

		if (mpTop == mpBase)
		{
			mpTop = nullptr;
			mpBase = nullptr;
		}
		else
		{
			mpTop = mpTop->previous;
		}
		delete tmp;

		return value;
	}
	else
	{
		throw "nothing to pop, stack is empty";
	}
}
