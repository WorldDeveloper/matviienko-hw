#include "List.h"

template <class T>
class Stack : public List<T>
{
public:
	Stack() :List<T>(){}
	virtual ~Stack(){}
	virtual void Push(const T& value);
	/*virtual T Pop();*/
};

template <class T>
void Stack<T>::Push(const T& value)
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
		tmp->next = mpHead;
		mpHead = tmp;
	}
	mCount++;
}

//template <class T>
//T Stack<T>::Pop()
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
//}