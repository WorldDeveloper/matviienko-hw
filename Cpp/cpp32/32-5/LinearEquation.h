#pragma once
#include "Equation.h"

template <class T>
class LinearEquation : public Equation<T>
{
	T mA;
	T mB;
public:
	LinearEquation() :mA(T()), mB(T()){};

	virtual void Solve()
	{
		cout << "Linear equation solver" << endl;
		cout << "Enter \'a\': ";
		cin >> mA;

		cout << "Enter \'b\': ";
		cin >> mB;

		cout << mA << "x";
		if ((int)mB >= 0) { cout << "+"; }
		cout << mB << "= 0\n";
		cout << "\n\tx = ";

		if ((int)mA == 0 && (int)mB == 0) { cout << "Every number"; }
		else if ((int)mA == 0) { cout << "No solution"; }
		else { cout << -(double)mB / mA; }

		cout << "\n\n";
	}
	virtual ~LinearEquation(){}
};

