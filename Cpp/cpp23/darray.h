#include <new>
#include <iostream>
using namespace std;

template <typename T>
class darray
{
	T *array;
	int capacity;
	int size;
public:
	void newArray();
	darray(T iCapacity);
	~darray();
	darray(const darray &source);

	T &operator[](int index);
	darray& operator=(const darray& result);	
	darray operator+(const darray& operator2);
	darray operator-(const darray& operator2);
	darray &operator++(); //использовать ссылку, чтобы вернуть "самого себя"?
	darray operator++(int);
	darray &operator--();//использовать ссылку, чтобы вернуть "самого себя"?
	darray operator--(int);

	int end(){ return size; }
	void pushBack(const T value);
};

template <typename T>
void darray<T>::newArray()
{
	try
	{
		array = new T[capacity];
	}
	catch (bad_alloc error)
	{
		cout << endl << "Error: out of memory!" << endl;
		exit(1);
	}
	size = 0;
}


template <typename T>
darray<T>::darray(T iCapacity)
{
	capacity = iCapacity;
	newArray();
}

template <typename T>
darray<T>::~darray()
{
	 delete[] array; 
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
	capacity = source.capacity;
	newArray();
	for (int i = 0; i < source.size; ++i)
	{
		pushBack(source.array[i]);
	}
}

template <typename T>
darray<T> &darray<T>::operator=(const darray<T>& result)
{
	if (this == &result)
	{
		return *this;		
	}

	if (capacity != result.capacity)
	{
		capacity = result.capacity;
		delete[] array;
		newArray();
	}

	size = 0;
	for (int i = 0; i < result.size; ++i)
	{
		pushBack(result.array[i]);
	}
	return *this;
}

template <typename T>
darray<T> darray<T>::operator+(const darray<T>& operator2)
{
	int tmpCapacity;
	if (size > operator2.size)
	{
		tmpCapacity = size;
	}
	else
	{
		tmpCapacity = operator2.size;
	}
	darray<T> tmp(tmpCapacity);

	for (int i = 0; i < tmpCapacity; ++i)
	{
		int o1 = 0;
		if (i < size) o1 = array[i];
		int o2 = 0;
		if (i < operator2.size) o2 = operator2.array[i];
		tmp.pushBack(o1 + o2);	
	}

	return tmp;
}

template <typename T>
darray<T> darray<T>::operator-(const darray<T>& operator2)
{
	int tmpCapacity;
	if (size > operator2.size)
	{
		tmpCapacity = size;
	}
	else
	{
		tmpCapacity = operator2.size;
	}
	darray<T> tmp(tmpCapacity);

	for (int i = 0; i < tmpCapacity; ++i)
	{
		int o1 = 0;
		if (i < size) o1 = array[i];
		int o2 = 0;
		if (i < operator2.size) o2 = operator2.array[i];
		tmp.pushBack(o1 - o2);
	}

	return tmp;
}

template <typename T>
darray<T>& darray<T>::operator++()
{
	capacity++;
	darray<T> tmp(capacity);
	tmp = *this;

	delete[] array;
	newArray();

	*this = tmp;

	return *this;
}

template <typename T>
darray<T> darray<T>::operator++(int)
{	
	darray<T> tmp(capacity);
	tmp = *this;
	++(*this);
	return tmp;
}

template <typename T>
darray<T>& darray<T>::operator--()
{
	capacity--;
	size--;
	darray<T> tmp(capacity);
	tmp = *this;
	
	delete[] array;	
	newArray();

	*this = tmp;

	return *this;
}

template <typename T>
darray<T> darray<T>::operator--(int)
{
	darray<T> tmp(capacity);
	tmp = *this;
	--(*this);
	return tmp;
}

template <typename T>
void darray<T>::pushBack(const T value)
{
	if (size >= capacity)
	{
		array++;
	}
	array[size] = value;
	size++;
}