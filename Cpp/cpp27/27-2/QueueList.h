#pragma once

template <class T>
struct Node
{
	T value;
	Node* prev;
	Node* next;
	Node() : value(0), prev(nullptr), next(nullptr){}
	Node(const T& data) : value(data), prev(nullptr), next(nullptr){}
};

template <class T>
class QueueList
{
	Node<T>* mpHead;
	Node<T>* mpTail;
	int mCount;
public:
	QueueList() : mpHead(nullptr), mpTail(nullptr), mCount(0){}
	~QueueList();

	QueueList(const QueueList& source);
	QueueList& operator=(const QueueList& source);

	void Clear() { this->~QueueList(); }
	int GetCount() const { return mCount; }

	void PushBack(const T& value);
	T PopFront();
};

template <class T>
QueueList<T>::~QueueList()
{
	while (mpHead)
	{
		Node<T>* tmp = mpHead;
		mpHead = mpHead->next;
		delete[] tmp;
	}
	mCount = 0;
}

template <class T>
QueueList<T>::QueueList(const QueueList<T>& source)
{
	mpHead = nullptr;
	mpTail = nullptr;
	mCount = 0;

	Node<T>* tmp = source.mpHead;
	for (int i = 0; i < source.mCount; ++i)
	{
		PushBack(tmp->value);
		tmp = tmp->next;
	}
}

template <class T>
QueueList<T>& QueueList<T>::operator=(const QueueList<T>& source)
{
	if (this == &source) return *this; 
	
	this->~QueueList();

	Node<T>* tmp = source.mpHead;
	for (int i = 0; i < source.mCount; ++i)
	{
		PushBack(tmp->value);
		tmp = tmp->next;
	}

	return *this;
}

template <class T>
void QueueList<T>::PushBack(const T& value)
{
	Node<T>* tmp = new Node<T>;
	tmp->value = value;

	if (!mpHead)
	{
		mpHead = tmp;
		mpTail = tmp;
	}
	else
	{
		tmp->prev = mpTail;
		mpTail->next = tmp;
		mpTail = tmp;
	}
	mCount++;
}

template <class T>
T QueueList<T>::PopFront()
{
	if (mpHead)
	{
		T result = mpHead->value;
		Node<T>* tmp = mpHead;
		mpHead = mpHead->next;
		if (mpHead) { mpHead->prev = nullptr; }
		mCount--;
		delete[] tmp;

		return result;
	}
	else
	{
		return T();
	}
}