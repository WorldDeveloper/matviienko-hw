/*
Заполнить двухмерный вектор таблицей умножения и выввести его в выходной
поток.
*/

#include <iostream>
#include <vector>
using namespace std;

template <class T>
ostream& operator<<(ostream& stream, const vector<T>& output);

template <class T>
ostream& operator<<(ostream& stream, const vector<vector<T>>& output);

void main()
{
	vector<vector<int>> multiplicationTable;
	const int m = 9;
	const int n = 9;
	multiplicationTable.resize(m);

	for (int i = 0; i <m; ++i)
	{
		multiplicationTable[i].resize(n);

		for (int j = 0; j <n; ++j)
		{
			multiplicationTable[i][j] = (i+1)*(j+1);
		}
	}

	cout << multiplicationTable << endl;
}

template <class T>
ostream& operator<<(ostream& stream, const vector<T>& output)
{
	for (auto& i : output)
	{
		stream << i << "\t";
	}

	return stream;
}

template <class T>
ostream& operator<<(ostream& stream, const vector<vector<T>>& output)
{	
	for (int i = 0; i < output.size();++i)
	{
		stream << output[i] << endl;
	}

	return stream;
}
