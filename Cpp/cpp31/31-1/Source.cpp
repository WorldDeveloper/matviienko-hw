/*
�������� ����� Student, ������� ����� ��������� ���������� � ��������.
� ������� ��������� ������������, ���������� ����� Aspirant
(�������� - �������, ������� ��������� � ������ ������������ ������)
����������� �� Student.
*/

#include <iostream>
#include "Candidate.h"
using namespace std;

void main()
{
	Candidate candidate("Ivan", "Ivanov", "Economic", "A101", 1, "Macroeconomic modelling and stress testing for Ukraine", "Petrov P.P.");
	candidate.ShowCandidate();
	cout << endl;
}