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
class ForwardList
{
	ListNode<T>* mpHead;
	ListNode<T>* mpTail;
	int mCount;
public:
	ForwardList() : mpHead(nullptr), mpTail(nullptr), mCount(0){}
	~ForwardList();

	ForwardList(const ForwardList& source);
	ForwardList& operator=(const ForwardList& source);

	void PushBack(const T& value);
	T PopFront();
	int GetCount() const { return mCount; }
	bool InsertAt(const int index, const T& value);
	bool EraseAt(const int index);
	int Search(const T& value) const;
};



template <class T>
ForwardList<T>::~ForwardList()
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
ForwardList<T>::ForwardList(const ForwardList<T>& source)
{
	mpHead = nullptr;
	mpTail = nullptr;
	mCount =0;
	
	ListNode<T>* tmp = source.mpHead;
	for (int i = 0; i < source.mCount; ++i)
	{
		PushBack(tmp->value);
		tmp = tmp->next;
	}
}

template <class T>
ForwardList<T>& ForwardList<T>::operator=(const ForwardList<T>& source)
{
	if (this == &source) return *this; 
	
	this->~ForwardList();

	ListNode<T>* tmp = source.mpHead;
	for (int i = 0; i < source.mCount; ++i)
	{
		PushBack(tmp->value);
		tmp = tmp->next;
	}

	return *this;
}

template <class T>
void ForwardList<T>::PushBack(const T& value)
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
T ForwardList<T>::PopFront()
{
	if (mpHead)
	{
		T value = mpHead->value;
		ListNode<T>* tmp = mpHead;
		mpHead = mpHead->next;
		mCount--;
		delete tmp;

		return value;
	}
	else
	{
		return T();
	}
}

template <class T>
bool ForwardList<T>::InsertAt(const int index, const T& value)
{
	if (index<0 || index>mCount) { return false; }

	ListNode<T>* tmp = new ListNode<T>;
	tmp->next = mpHead;
	tmp->value = value;
	
	if (index == mCount)
	{
		PushBack(value);
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
bool ForwardList<T>::EraseAt(const int index)
{
	if (index<0 || index>=mCount) { return false; }

	ListNode<T>* eraseIndex = mpHead;

	if (index == 0)
	{
		mpHead = mpHead->next;
		delete eraseIndex;
	}//if (index==mCount)*******************************************add
	else
	{		
		for (int i = 1; i < index; ++i)
		{
			eraseIndex = eraseIndex->next;
		}

		ListNode<T>* beforeErase=eraseIndex;
		eraseIndex = eraseIndex->next;
		beforeErase->next = eraseIndex->next;
		delete eraseIndex;
	}
	mCount--;
	return true;
}

template <class T>
int ForwardList<T>::Search(const T& value) const
{
	ListNode<T>* index = mpHead;
	for (int i = 0; i < mCount; ++i)
	{
		if (index->value == value) { return i; }
		index = index->next;
	}

	return NULL;
}
