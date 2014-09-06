/*
Создайте класс Student, который будет содержать информацию о студенте.
С помощью механизма наследования, реализуйте класс Aspirant
(аспирант - студент, который готовится к защите кандидатской работы)
производный от Student.
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