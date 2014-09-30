#pragma once
#include "Forest.h"
#include "Grass.h"

class Rabbit :public Forest
{
	int mAge;
public:
	Rabbit(const string& location, const int age) :Forest(location), mAge(age){}
	bool SetAge(const int age)
	{
		if (age <= 0) return false;
		mAge = age;
		return true;
	}
	int GetAge() const { return mAge; }
	void Eat(Grass& grass)
	{
		cout << "Grasses have been eaten." << endl;
		grass.~Grass();
	}
	void Die()
	{
		cout << "Rabbits died." << endl;
		this->~Rabbit();
	}
	void Alive() const { cout << "Rabbits are alive." << endl; }

	~Rabbit(){}
};

