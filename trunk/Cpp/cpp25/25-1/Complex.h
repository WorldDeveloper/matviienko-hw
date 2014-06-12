#pragma once
#include <cmath>
using namespace std;

template <class T>
class Complex
{
	T mR;
	T mI;
	T squared(const T x) const { return x*x; }
public:
	Complex(const T r = T(), const T i = T()) : mR(r), mI(i){}
	Complex(const Complex& source) : mR(source.mR), mI(source.mI){}
	void setComplex(const T r = T(), const T i = T()) { mR = r; mI = i; }

	T real() const { return mR; }
	T imag() const { return mI; }

	Complex operator+(const Complex& z);
	Complex operator-(const Complex& z);
	Complex operator*(const Complex& z);
	Complex operator/(const Complex& z);

	bool operator==(const Complex& z) const;
	bool operator!=(const Complex& z) const { return !(*this == z); }

	template <class T2>
	friend T2 abs(const Complex<T2>& z){ return sqrt(z.mR*z.mR + z.mI*z.mI); }
	template <class T2>
	friend Complex<T2> pow(const Complex<T2>& z, const int exponent);
};

#include "Complex.cpp"

