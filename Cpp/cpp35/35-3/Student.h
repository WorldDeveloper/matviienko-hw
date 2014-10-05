#pragma once
#include <string>
#include <iostream>
using namespace std;

class Student
{
	string mSurname;
	string mName;
	string mCourse;
public:
	Student(const string surname, const string name, const string course)
		: mSurname(surname), mName(name), mCourse(course){}
	string GetSurname()const { return mSurname; }
	string GetName() const { return mName; }
	string GetCourse() const { return mCourse; }
	bool operator==(const Student& student){ return mName == student.mName; }
	bool operator<(const Student& student){ return mName < student.mName; }
};

