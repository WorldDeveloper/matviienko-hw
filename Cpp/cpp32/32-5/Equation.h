#pragma once
#include <iostream>


template <class T>
class Equation
{
public:
	Equation(){}
	virtual void Solve() = 0;
	virtual ~Equation(){}
};

