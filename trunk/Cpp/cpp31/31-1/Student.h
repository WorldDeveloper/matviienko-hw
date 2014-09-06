#pragma once

class Student
{
	char mFirstName[20];
	char mLastName[30];
	char mFaculty[50];
	char mGroup[6];
	int mStudyYear;
public:
	Student(char *fName, char *lName, char *faculty, char *group, int studyYear);
	void EditStudent(char *fName, char *lName, char *faculty, char *group, int studyYear);
	void ShowStudent() const;
	const char* GetFirstName()const { return mFirstName; }
	const char* GetLastName()const { return mLastName; }
	const char* GetFaculty() const { return mFaculty; }
	const char* GetGroup()const { return mGroup; }
	const int GetStudyYear()const { return mStudyYear; }


};

