/*
� ������� ����� "������������� � ����������" �������� ������ �� ������
������ "�����" � ������ "������". ���� ������ �������� � ��������� �����,
������� ����� ��������� � ���� ��������� �������� ������ ������,
�������� ��� ����� ����������.
*/

#include <iostream>
#include <vector>
#include <new>
#include "FiguresCollection.h"
using namespace std;

void main()
{
	int fNumber = 0;
	while (fNumber < 2)	{
		cout << "Enter a number of figures in collection: ";
		cin >> fNumber;
	}

	try{
		FiguresCollection collection(fNumber);
		collection.ShowCollection();
	}
	catch (char* err){
		cout << "\nError: " << err << "\n\n";
		exit(1);
	}
}