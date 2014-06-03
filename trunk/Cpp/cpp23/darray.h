#include <new>
#include <iostream>
using namespace std;

template <typename T>
class darray
{
	T *array;
	int size;
public:
	void newArray();
	darray(T iSize);
	~darray();
	darray(const darray &source);

	T &operator[](int index);
	darray operator=(darray result);
	darray operator+(darray operator2);
	darray operator-(darray operator2);
	darray operator++();
	darray operator++(int);
	darray operator--();
	darray operator--(int);

	int end(){ return size; }
};

template <typename T>
void darray<T>::newArray()
{
	try
	{
		array = new T[size];
	}
	catch (bad_alloc error)
	{
		cout << endl << "Error: out of memory!" << endl;
		exit(1);
	}
}

template <typename T>
darray<T>::darray(T iSize)
{
	size = iSize;
	newArray();
	for (int i = 0; i < size; ++i)
	{
		array[i] = 0;
	}
}

template <typename T>
darray<T>::~darray()
{
	if (array) { delete[] array; }
}

template <typename T>
T &darray<T>::operator[](int index)
{
	if (index>=0 && index < size) 
	{
		return array[index];
	}
	else
	{
		cout << endl<<"Error: out of range!" << endl;
		exit(1);
	}
}

template <typename T>
darray<T>::darray(const darray &source)
{
	size = source.size;
	newArray();
	for (int i = 0; i < size; ++i)
	{
		array[i] = source.array[i];
	}
}

template <typename T>
darray<T> darray<T>::operator=(darray<T> result)
{
	if (size != result.size)
	{
		size = result.size;
		delete[] array;
		newArray();
	}
	for (int i = 0; i < size; ++i)
	{
		array[i] = result[i];
	}
	return *this;
}

template <typename T>
darray<T> darray<T>::operator+(darray<T> operator2)
{
	int tmpSize;
	if (size > operator2.size)
	{
		tmpSize = size;
	}
	else
	{
		tmpSize = operator2.size;
	}
	darray<T> tmp(tmpSize);

	for (int i = 0; i < size; ++i)
	{
		tmp[i] = array[i];
	}

	for (int i = 0; i < operator2.size; ++i)
	{
		tmp[i] += operator2[i];
	}

	return tmp;
}

template <typename T>
darray<T> darray<T>::operator-(darray<T> operator2)
{
	int tmpSize;
	if (size > operator2.size)
	{
		tmpSize = size;
	}
	else
	{
		tmpSize = operator2.size;
	}
	darray<T> tmp(tmpSize);
	for (int i = 0; i < size; ++i)
	{
		tmp[i] = array[i];
	}

	for (int i = 0; i < operator2.size; ++i)
	{
		tmp[i] -= operator2[i];
	}

	return tmp;
}

template <typename T>
darray<T> darray<T>::operator++()
{
	size++;
	darray<T> tmp(size);
	tmp = *this;

	delete[] array;
	newArray();

	*this = tmp;
	array[size - 1] = 0;

	return *this;
}

template <typename T>
darray<T> darray<T>::operator++(int)
{	
	darray<T> tmp(size);
	tmp = *this;
	++(*this);
	return tmp;
}

template <typename T>
darray<T> darray<T>::operator--()
{
	size--;
	darray<T> tmp(size);
	tmp = *this;
	
	delete[] array;	
	newArray();

	*this = tmp;

	return *this;
}

template <typename T>
darray<T> darray<T>::operator--(int)
{
	darray<T> tmp(size);
	tmp = *this;
	--(*this);
	return tmp;
}