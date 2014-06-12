/*
Написать класс, реализующий работу с комплексными числами.
*/

#include <iostream>
#include "Complex.h"
#include <complex>
#include <cmath>
using namespace std;

template <class T>
ostream &operator<<(ostream &stream, const Complex<T> &output);
template <class T>
istream& operator>>(istream& stream, Complex<T>& input);

void main()
{
	Complex<double> a(2, 3);
	complex<double>cA(2, 3);
	cout << "a:\t" << a << "\t:stl: " << cA << endl;

	Complex<double> b(a);
	complex<double>cB(cA);
	cout << "b:\t" << b << "\t:stl: " << cB << endl;

	Complex<double> c;
	complex<double> cC;
	cout << "c:\t" << c << "\t:stl: " << cC << endl << endl;

	cin >> c;
	cC = complex < double>(c.real(), c.imag());
	cout << endl << "c:\t" << c << "\t:stl: " << cC << endl << endl;

	cout << "a+c:\t" << a + c << "\t:stl: " << cA + cC << endl << endl;
	cout << "a-c:\t" << a - c << "\t:stl: " << cA - cC << endl << endl;
	cout << "a*c:\t" << a * c << "\t:stl: " << cA * cC << endl << endl;
	cout << "a==b:\t" << (a == b) << "\t:stl: " << (cA == cB) << endl;
	cout << "a!=b:\t" << (a != b) << "\t:stl: " << (cA != cB) << endl << endl;
	cout << "a==c:\t" << (a == c) << "\t:stl: " << (cA == cC) << endl;
	cout << "a!=c:\t" << (a != c) << "\t:stl: " << (cA != cC) << endl << endl;
	cout << "abs(c):\t" << abs(c) << "\t:stl: " << abs(cC) << endl << endl;
	cout << "pow(c,0):\t" << pow(c, 0) << "\t:stl: " << pow(cC, 0) << endl;
	cout << "pow(c,1):\t" << pow(c, 1) << "\t:stl: " << pow(cC, 1) << endl;
	cout << "pow(c,3):\t" << pow(c, 3) << "\t:stl: " << pow(cC, 3) << endl << endl;

	if (c.real() || c.imag()){
		cout << "a/c:\t" << a / c << "\t:stl: " << cA / cC << endl << endl;
	}
	else{
		cout << "Error:division by zero!" << endl << endl;
		exit(1);
	}
}

template <class T>
ostream &operator<<(ostream &stream, const Complex<T> &output)
{
	const T real = output.real();
	const T imaginary = output.imag();

	if (real != 0) {
		stream << real;
	}

	if (imaginary != 0)
	{
		if (imaginary > 0) stream << "+";
		stream << imaginary << "i";
	}

	if (real == 0 && imaginary == 0){
		stream << "0";
	}

	return stream;
}

template <class T>
istream& operator>>(istream& stream, Complex<T>& input)
{
	cout << "Enter components of complex number\n";
	cout << "\t real: ";
	T real;
	stream >> real;

	T imaginary;
	cout << "\t imaginary: ";
	stream >> imaginary;

	input.setComplex(real, imaginary);
	return stream;
}