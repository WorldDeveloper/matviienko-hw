#include "Student.h"
#include <iostream>
using namespace std;

Student::Student(char *fName, char *lName, char *faculty, char *group, int studyYear)
:mStudyYear(studyYear)
{
	strcpy(mFirstName, fName);
	strcpy(mLastName, lName);
	strcpy(mFaculty, faculty);
	strcpy(mGroup, group);
}

void Student::EditStudent(char *fName, char *lName, char *faculty, char *group, int studyYear)
{
	strcpy(mFirstName, fName);
	strcpy(mLastName, lName);
	strcpy(mFaculty, faculty);
	strcpy(mGroup, group);
	mStudyYear = studyYear;
}

void Student::ShowStudent()const
{
	cout << "\nFirst name: " << mFirstName;
	cout << "\nLast name: " << mLastName;
	cout << "\nFaculty: " << mFaculty;
	cout << "\nGroup: " << mGroup;
	cout << "\nYear of study: " << mStudyYear << endl;
}