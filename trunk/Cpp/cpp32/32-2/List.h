#pragma once
#include <new>
using namespace std;

template <class T>
struct ListNode
{
	T value;
	ListNode* next;
	ListNode() : value(T()), next(nullptr){}
	ListNode(const T& data) : value(data), next(nullptr){}
};


template <class T>
class List
{
protected:
	ListNode<T>* mpHead;
	ListNode<T>* mpTail;
	int mCount;
public:
	List() : mpHead(nullptr), mpTail(nullptr), mCount(0){}
	~List();

	List(const List& source);
	List& operator=(const List& source);

	virtual void Push(const T& value);
	virtual T Pop();
	int GetCount() const { return mCount; }
	bool InsertAt(const int index, const T& value);
	bool EraseAt(const int index);
	int Search(const T& value) const;
};



template <class T>
List<T>::~List()
{
	while (mpHead)
	{
		ListNode<T>* needlessNode = mpHead;
		mpHead = mpHead->next;
		delete needlessNode;
	}
	mCount = 0;
}

template <class T>
List<T>::List(const List<T>& source)
{
	mpHead = nullptr;
	mpTail = nullptr;
	mCount = 0;

	ListNode<T>* tmp = source.mpHead;
	for (int i = 0; i < source.mCount; ++i)
	{
		Push(tmp->value);
		tmp = tmp->next;
	}
}

template <class T>
List<T>& List<T>::operator=(const List<T>& source)
{
	if (this == &source) return *this;

	this->~List();

	ListNode<T>* tmp = source.mpHead;
	for (int i = 0; i < source.mCount; ++i)
	{
		Push(tmp->value);
		tmp = tmp->next;
	}

	return *this;
}

template <class T>
void List<T>::Push(const T& value)
{
	ListNode<T>* tmp = new ListNode<T>;
	tmp->value = value;

	if (!mpHead)
	{
		mpHead = tmp;
		mpTail = tmp;
	}
	else
	{
		mpTail->next = tmp;
		mpTail = tmp;
	}
	mCount++;
}

template <class T>
T List<T>::Pop()
{
	if (!mpHead) throw "out of range!";

	T value = mpHead->value;
	ListNode<T>* tmp = mpHead;
	mpHead = mpHead->next;
	mCount--;
	delete tmp;

	return value;
}

template <class T>
bool List<T>::InsertAt(const int index, const T& value)
{
	if (index<0 || index>mCount) { return false; }

	ListNode<T>* tmp = new ListNode<T>;
	tmp->next = mpHead;
	tmp->value = value;

	if (index == mCount)
	{
		Push(value);
		return true;
	}
	else if (index == 0)
	{
		mpHead = tmp;
	}
	else
	{
		ListNode<T>* insertIndex = mpHead;
		for (int i = 1; i < index; ++i)
		{
			insertIndex = insertIndex->next;
		}

		tmp->next = insertIndex->next;
		insertIndex->next = tmp;
	}
	mCount++;
	return true;
}

template <class T>
bool List<T>::EraseAt(const int index)
{
	if (index < 0 || index >= mCount) { return false; }

	ListNode<T>* eraseIndex = mpHead;

	if (index == 0)
	{
		mpHead = mpHead->next;
		delete eraseIndex;
	}
	else
	{
		for (int i = 1; i < index; ++i)
		{
			eraseIndex = eraseIndex->next;
		}

		ListNode<T>* beforeErase = eraseIndex;
		eraseIndex = eraseIndex->next;
		beforeErase->next = eraseIndex->next;
		delete eraseIndex;
	}
	mCount--;
	return true;
}

template <class T>
int List<T>::Search(const T& value) const
{
	ListNode<T>* index = mpHead;
	for (int i = 0; i < mCount; ++i)
	{
		if (index->value == value) { return i; }
		index = index->next;
	}

	return NULL;
}
