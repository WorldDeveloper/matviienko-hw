#pragma once
#include <memory>
using namespace std;

template <class T>
class Array
{
	T* mArray;
	int mUpperBound;
	int mSize;
	int mGrow;

	void CreateArray(const int size);
	void ReSize(const int size, const int grow=0);
public:
	Array(const int size=1, const int grow=1) 
		: mSize(size), mUpperBound(-1), mGrow(grow)
	{
		if (size < 1 || grow < 1)
		{
			cout << "\nError: incorrect parametrs!";
			exit(1);
		}
		CreateArray(size);
	}
	~Array();
	int GetSize() const { return mSize; }
	void SetSize(const int size, const int grow = 1);
	int GetUpperBound() const { return mUpperBound; }
	bool IsEmpty() const { return mUpperBound == -1; }
	void FreeExtra();
	void RemoveAll();
	T & operator[](const int index);
	T GetAt(int index);
	void SetAt(const int index, const T& value);
	void Add(const T& value);
	void Append(const Array& appendedObj);
	Array(const Array& source);
	Array& operator=(const Array& source);
	T* GetData() const { return mArray; }
	void InsertAt(const int index, const T& value);
	void RemoveAt(const int index);
};

template <class T>
Array<T>::~Array()
{
	delete[] mArray;
	mArray = nullptr;
	mSize = 0;
	mUpperBound = -1;
	mGrow = 1;
}


template<class T>
void Array<T>::CreateArray(const int size)
{
	try{
		mArray = new T[size];
	}
	catch (bad_alloc)
	{
		cout << "\nError: out of memory!\n\n";
		exit(1);
	}
}

template <class T>
void Array<T>::ReSize(const int size, const int grow/*=0*/)
{
	if (size < 0 || grow < 0)
	{
		cout << "Error: incorrect parametrs!";
		exit(1);
	}
	if (grow) mGrow = grow;

	if ( mSize==size)	return;
	else mSize = size;

	if (mUpperBound + 1 > mSize)
	{
		mUpperBound = mSize - 1;
	}

	T* tmp = mArray;
	CreateArray(mSize);
	for (int i = 0; i <= mUpperBound; ++i)
	{
		mArray[i] = tmp[i];
	}
	delete[] tmp;
}

template <class T>
void Array<T>::SetSize(const int size, const int grow/*=1*/)
{
	if (size < 0 || grow < 0)
	{
		cout << "Error: incorrect parametrs!";
		exit(1);
	}
	
	if (mArray)
	{
		ReSize(size, grow);
	}
	else
	{
		mSize = size;
		mUpperBound = -1;
		mGrow = grow;
		CreateArray(size);
	}
}

template <class T>
void Array<T>::FreeExtra()
{
	ReSize(mUpperBound + 1);
}

template <class T>
void Array<T>::RemoveAll()
{
	this->~Array();
}

template <class T>
T& Array<T>::operator[](const int index)
{
	if (index >= 0 && index <= mUpperBound)
	{
		return mArray[index];
	}
	else
	{
		cout << endl << "Error: out of range!" << endl;
		exit(1);
	}
}

template <class T>
T Array<T>::GetAt(int index)
{
	return this->operator[](index);
}


template <class T>
void Array<T>::SetAt(const int index, const T& value)
{
	this->operator[](index) = value;
}

template <class T>
void Array<T>::Add(const T& value)
{
	if (mUpperBound + 1 >= mSize)
	{
		ReSize(mSize + mGrow);		
	}
	mUpperBound++;
	mArray[mUpperBound] = value;
}

template<class T>
void Array<T>::Append(const Array& appendedObj)
{
	if (appendedObj.IsEmpty()) return;

	int newSize = mUpperBound + appendedObj.mUpperBound+2;
	newSize += newSize%mGrow;
	ReSize(newSize);

	for (int i = 0; i <= appendedObj.GetUpperBound(); ++i)
	{
		Add(appendedObj.mArray[i]);
	}
}

template <class T>
Array<T>::Array(const Array<T>& source)
{
	mSize = source.mSize;
	mUpperBound = source.mUpperBound;
	mGrow = source.mGrow;
	CreateArray(mSize);

	for (int i = 0; i <= mUpperBound; ++i)
	{
		mArray[i] = source.mArray[i];
	}
}

template <class T>
Array<T>& Array<T>::operator=(const Array<T>& source)
{
	if (this == &source) return *this; 

	if (mSize != source.mSize)
	{
		delete[] mArray;
		CreateArray(source.mSize);
	}

	mSize = source.mSize;
	mUpperBound = source.mUpperBound;
	mGrow = source.mGrow;

	for (int i = 0; i <= mUpperBound; ++i)
	{
		mArray[i] = source.mArray[i];
	}

	return *this;
}

template <class T>
void Array<T>::InsertAt(const int index, const T& value)
{
	if (index<0 || index>mUpperBound)
	{
		cout << endl << "Error: out of range!" << endl;
		exit(1);
	}

	if (mUpperBound + 1 == mSize) ReSize(mSize + mGrow);

	for (int i = ++mUpperBound; i > index; --i)
	{
		mArray[i] = mArray[i - 1];
	}
	mArray[index] = value;
}

template <class T>
void Array<T>::RemoveAt(const int index)
{
	if (index<0 || index>mUpperBound)
	{
		cout << endl << "Error: out of range!" << endl;
		exit(1);
	}

	for (int i = index; i <mUpperBound; ++i)
	{
		mArray[i] = mArray[i + 1];
	}
	mUpperBound--;
}
