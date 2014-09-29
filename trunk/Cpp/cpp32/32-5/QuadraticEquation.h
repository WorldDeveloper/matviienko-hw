#pragma once
#include "Equation.h"

template <class T>
class QuadraticEquation : public Equation<T>
{
	T mA;
	T mB;
	T mC;
public:
	QuadraticEquation() :mA(T()), mB(T()), mC(T()){};

	virtual void Solve()
	{
		cout << "Quadratic equation solver" << endl;
		cout << "Enter \'a\': ";
		cin >> mA;

		cout << "Enter \'b\': ";
		cin >> mB;

		cout << "Enter \'c\': ";
		cin >> mC;

		cout << mA << "x^2";
		if ((int)mB >= 0) { cout << "+"; }
		cout << mB << "x";
		if ((int)mC >= 0) { cout << "+"; }
		cout << mC << "= 0\n\n";

		const double D = mB*mB - 4 * mA*mC;
		if (D > 0)
		{
			const double x1 = (-mB + sqrt(D)) / (2 * mA);
			const double x2 = (-mB - sqrt(D)) / (2 * mA);
			cout << "\tx1=" << x1 << "\n\tx2=" << x2;
		}
		else if (D == 0) { cout << "x1=x2=" << -(double)mB / (2 * mA); }
		else { cout << "There are no real roots"; }

		cout << "\n\n";
	}
	virtual ~QuadraticEquation(){}
};

