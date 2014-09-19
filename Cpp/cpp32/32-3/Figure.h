#pragma once
#include <string>
using namespace std;


class Figure
{
	string mName;
public:
	Figure(string name) : mName(name){}
	virtual ~Figure(){}
	virtual float GetArea()const = 0;
	string GetName() const{ return mName; }
};