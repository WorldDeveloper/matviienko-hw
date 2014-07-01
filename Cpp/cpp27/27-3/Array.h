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
class Array
{
	Node<T>* mpHead;
	Node<T>* mpTail;
	int mCount;
	int mCurIndex;
	int mGrow;

	T& operator[](const int index) const;
	Node<T>* Item(const int index) const;
	void PushBack(const T& value);
	void RemoveLast();
public:
	Array() : mpHead(nullptr), mpTail(nullptr), mCount(0), mCurIndex(0), mGrow(0){}
	~Array();

	Array(const Array& source);
	Array& operator=(const Array& source);

	int GetSize() const { return mCount; }
	void SetSize(const int size, const int grow = 1);
	int GetUpperBound() const { return mCurIndex - 1; }
	bool IsEmpty() const { return mCurIndex == 0; }
	void FreeExtra();
	void RemoveAll();

	T GetAt(const int index) const;
	void SetAt(const int index, const T& value);

	void Add();
	void Append(Array obj);
	T* GetData() const;

	bool InsertAt(const int index, const T& value);
	bool RemoveAt(const int index);
};

template <class T>
void Array<T>::SetSize(const int size, const int grow)
{
	mGrow = grow;

	while (mCount < size)
	{
		PushBack(T());
	}

	while (mCount>size)
	{
		RemoveLast();
	}
}

template <class T>
void Array<T>::RemoveAll()
{
	while (mpTail)
	{
		Node<T>* tmp = mpTail;

		if (mpTail->prev)
		{
			mpTail = mpTail->prev;
		}
		else
		{
			mpTail = mpHead = nullptr;
		}
		delete tmp;
	}
	mCount = 0;
	mCurIndex = 0;
}

template <class T>
Array<T>::~Array()
{
	while (mpTail)
	{
		RemoveLast();
	}

	mCount = 0;
	mCurIndex = 0;
	mGrow = 0;
}

template <class T>
Array<T>::Array(const Array<T>& source)
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

	mCurIndex = source.mCurIndex;
	mGrow = source.mGrow;
}

template <class T>
Array<T>& Array<T>::operator=(const Array<T>& source)
{
	RemoveAll();

	Node<T>* tmp = source.mpHead;
	for (int i = 0; i < source.mCount; ++i)
	{
		PushBack(tmp->value);
		tmp = tmp->next;
	}

	mCurIndex = source.mCurIndex;
	mGrow = source.mGrow;

	return *this;
}

template <class T>
void Array<T>::PushBack(const T& value)
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
void Array<T>::RemoveLast()
{
	if (mpTail)
	{
		Node<T>* tmp = mpTail;
		mCount--;
		if (mpTail->prev)
		{
			mpTail = mpTail->prev;
			mpTail->next = nullptr;
		}
		else
		{
			mpTail = mpHead = nullptr;
		}

		if (mCurIndex > mCount) { mCurIndex = mCount; }

		delete tmp;
	}
}

template <class T>
void Array<T>::FreeExtra()
{
	while (mCount > mCurIndex)
	{
		RemoveLast();
	}
}

template <class T>
Node<T>* Array<T>::Item(const int index) const
{
	if (index < 0 || index >= mCount) { exit(1); }

	Node<T>* tmp = mpHead;
	for (int i = 0; i < index; ++i)
	{
		tmp = tmp->next;
	}

	if (tmp) { return tmp; }
	else { exit(1); }
}

template <class T>
T& Array<T>::operator[](const int index) const
{
	if (index < 0 || index >= mCount) { exit(1); }

	Node<T>* tmp = mpHead;
	for (int i = 0; i < index; ++i)
	{
		tmp = tmp->next;
	}

	if (tmp) { return tmp->value; }
	else { exit(1); }
}

template <class T>
T Array<T>::GetAt(const int index) const
{
	if (index < mCurIndex)
	{
		return this->operator[](index);  //return Item(index)->value;
	}
	else
	{
		exit(1);
	}
}

template <class T>
void Array<T>::SetAt(const int index, const T& value)
{
	if (index <= mCurIndex)
	{
		this->operator[](index) = value;  // Item(index)->value = value;
		if (index == mCurIndex && mCurIndex < mCount) { mCurIndex++; }
	}
	else
	{
		exit(1);
	}
}

template <class T>
void Array<T>::Add()
{
	do
	{
		PushBack(T());
	} while (mCount%mGrow);
}

template <class T>
void Array<T>::Append(Array<T> obj)
{
	this->FreeExtra();
	Node<T>* tmp = obj.mpHead;
	while (tmp)
	{
		PushBack(tmp->value);
		tmp = tmp->next;
	}

	mCurIndex += obj.mCurIndex;
}

template <class T>
T* Array<T>::GetData() const
{
	T* pData = new T[mCurIndex];
	for (int i = 0; i < mCurIndex; ++i)
	{
		pData[i] = Item(i)->value;
	}

	return pData;
}

template <class T>
bool Array<T>::InsertAt(const int index, const T& value)
{
	if (index<0 || index>mCurIndex) { return false; }

	Node<T>* insertedItem = new Node<T>;
	insertedItem->value = value;
	if (index <= mCount) { mCurIndex++; }

	if (index == mCount)
	{
		PushBack(value);
		return true;
	}
	else if (index == 0)
	{
		insertedItem->next = mpHead;
		mpHead->prev = insertedItem;
		mpHead = insertedItem;
	}
	else
	{
		Node<T>* oldItem = Item(index);
		insertedItem->prev = oldItem->prev;
		(oldItem->prev)->next = insertedItem;
		insertedItem->next = oldItem;
		oldItem->prev = insertedItem;

		if (!insertedItem->next) { mpTail = insertedItem; }
	}

	mCount++;
	return true;
}

template <class T>
bool Array<T>::RemoveAt(const int index)
{
	if (index < 0 || index >= mCurIndex) { return false; }
	mCurIndex--;
	if (index == mCount - 1)
	{
		RemoveLast();
		return true;
	}
	else if (index == 0)
	{
		Node<T>* tmp = mpHead;
		mpHead = mpHead->next;
		mpHead->prev = nullptr;
		delete tmp;
	}
	else
	{
		Node<T>* oldNode = Item(index);
		(oldNode->prev)->next = oldNode->next;
		(oldNode->next)->prev = oldNode->prev;
		delete oldNode;
	}

	mCount--;
}