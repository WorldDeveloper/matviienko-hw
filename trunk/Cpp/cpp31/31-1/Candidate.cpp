#include "Candidate.h"
#include <iostream>
using namespace std;


Candidate::Candidate(char *fName, char *lName, char *faculty, char *group, int studyYear, const char* thesisTitle, const char* supervisor)
:Student(fName, lName, faculty, group, studyYear)
{
	strcpy(mThesisTitle, thesisTitle);
	strcpy(mSupervisor, supervisor);
}

void Candidate::ShowCandidate()const
{
	this->ShowStudent();
	cout << "Title of thesis: " << mThesisTitle;
	cout << "\nSupervisor: " << mSupervisor << endl;
}