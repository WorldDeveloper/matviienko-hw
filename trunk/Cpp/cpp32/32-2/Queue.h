#include "List.h"

template <class T>
class Queue : public List<T>
{
public:
	Queue() :List<T>(){}
	virtual ~Queue(){}
	//virtual void Push(const T& value);
	//virtual T Pop();
};

//template <class T>
//void Queue<T>::Push(const T& value)
//{
//	ListNode<T>* tmp = new ListNode<T>;
//	tmp->value = value;
//
//	if (!mpHead)
//	{
//		mpHead = tmp;
//		mpTail = tmp;
//	}
//	else
//	{
//		mpTail->next = tmp;
//		mpTail = tmp;
//	}
//	mCount++;
//}
//
//template <class T>
//T Queue<T>::Pop()
//{
//	if (!mpHead) throw "out of range!";
//
//	T value = mpHead->value;
//	ListNode<T>* tmp = mpHead;
//	mpHead = mpHead->next;
//	mCount--;
//	delete tmp;
//
//	return value;
//
//}