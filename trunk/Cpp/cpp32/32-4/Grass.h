#pragma once
#include "Forest.h"

class Grass :public Forest
{
public:
	Grass(const string& location) :Forest(location){}
	void Alive() const { cout << "Grass has not been eaten." << endl; }
	~Grass(){}
};

