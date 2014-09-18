/*
Создать абстрактный базовый класс Employer (служащий) с чисто виртуальной функцией Print().
Создайте три производных класса: President, Manager, Worker. Переопределите функцию Print()
для вывода информации, соответствующей каждому типу служащего.
*/

#include <iostream>
#include <string>
#include <memory>
#include <vector>
using namespace std;

class Employer
{
	string mName;
	string mSurname;
public:
	Employer(const string name, const string surname) : mName(name), mSurname(surname){}
	virtual ~Employer()
	{
		mName = "";
		mSurname = "";
	}
	virtual void Print() = 0;
	string GetName() const { return mName; }
	string GetSurname() const { return mSurname; }
};

class President : public Employer
{
public:
	President(const string name, const string surname) :Employer(name, surname){}
	virtual ~President(){ }
	virtual void Print()
	{
		cout << "\nName: " << GetName();
		cout << "\nSurname: " << GetSurname();
		cout << "\nPost: President";
	}
};

class Manager : public Employer
{
public:
	Manager(const string name, const string surname) :Employer(name, surname){}
	virtual ~Manager(){ }
	virtual void Print()
	{
		cout << "\nName: " << GetName();
		cout << "\nSurname: " << GetSurname();
		cout << "\nPost: Manager";
	}
};

class Worker : public Employer
{
public:
	Worker(const string name, const string surname) :Employer(name, surname){}
	virtual ~Worker(){ }
	virtual void Print()
	{
		cout << "\nName: " << GetName();
		cout << "\nSurname: " << GetSurname();
		cout << "\nPost: Worker";
	}
};

void main()
{
	Employer* employer[3] = { new President("Pname", "Psurname"), new Manager("Mname", "Msurname"), new Worker("Wname", "Wsurname") };

	for (int i = 0; i < 3; ++i)
	{
		employer[i]->Print();
		cout << "\n\n";
		delete employer[i];
	}

	//why delete[] employer doesn't work?
}