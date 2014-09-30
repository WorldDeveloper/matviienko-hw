#pragma once
#include <string>
using namespace std;


class Forest
{
	string mLocation;
public:
	Forest(const string& location) :mLocation(location){}
	virtual void Alive()const = 0;
	string GetLocation() const { return mLocation; }
	~Forest(){}
};

