#pragma once
#include "Forest.h"
#include "Rabbit.h"

class Fox :public Forest
{
	int mAge;
public:
	Fox(const string& location, const int age) :Forest(location), mAge(age){}
	bool SetAge(const int age)
	{
		if (age <= 0) return false;
		mAge = age;
		return true;
	}
	int GetAge() const { return mAge; }
	void Eat(Rabbit& rabbit)
	{
		cout << "Rabbits have been eaten." << endl;
	}
	void Die()
	{
		cout << "Foxes died." << endl;
		this->~Fox();
	}
	void Alive() const {
		cout << "Foxes are alive." << endl;
	}
	~Fox(){}
};

