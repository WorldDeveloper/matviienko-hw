#pragma once

#include "student.h"
#include <iostream>
using namespace std;

class Candidate : public Student
{
	char mThesisTitle[200];
	char mSupervisor[100];
public:
	Candidate(char *fName, char *lName, char *faculty, char *group, int studyYear, const char* thesisTitle, const char* supervisor);
	void SetThesisTitle(const char* title) { strcpy(mThesisTitle, title); }
	void SetSupervisor(const char* supervisor) { strcpy(mSupervisor, supervisor); }
	const char* GetThesisTitle() const { return mThesisTitle; }
	const char* GetSupervisor() const { return mSupervisor; }
	void ShowCandidate() const;

};
