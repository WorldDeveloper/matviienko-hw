/*
Заполнить вектор длинной 10 квадратами целых чисел и вывести его в выходной
поток.
*/
#include <iostream>
#include <vector>
using namespace std;

template <class T>
ostream& operator<<(ostream& stream, vector<T>& output);

void main()
{
	vector<int> v;
	for (int i = 1; i < 11; ++i)
	{
		v.push_back(i*i);
	}

	cout << v << endl;
}

template <class T>
ostream& operator<<(ostream& stream, vector<T>& output)
{
	stream << "[";
	for (auto& i : output)
	{
		stream << i << " ";
	}
	stream << "\b]";

	return stream;
}