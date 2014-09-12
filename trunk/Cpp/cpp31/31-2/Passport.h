#pragma once
#include <string>
using namespace std;

class Passport
{
	string mPassportNo;
	string mSurname;
	string mName;
	string mPatronymic;
	string mBirthDate;
	string mBirthPlace;
	string mSex;
	string mAuthority;
	string mIssueDate;
	string mSpecialNotes;
	string mFamilyStatus;
	string mResidencePlace;
public:
	Passport::Passport(const string passportNo,
		const string surname, 
		const string name,
		const string patronymic,
		const string birthDate,
		const string birthPlace,
		const string sex,
		const string authority,
		const string issueDate)
		:mPassportNo(passportNo), mSurname(surname), mName(name), mPatronymic(patronymic), mBirthDate(birthDate),
		mBirthPlace(birthPlace),
		mSex(sex), 
		mAuthority(authority),
		mIssueDate(issueDate)
	{}

	Passport::Passport(const string passportNo,
		const string surname,
		const string name,
		const string birthDate,
		const string birthPlace,
		const string sex,
		const string authority, 
		const string issueDate)
		: mPassportNo(passportNo), mSurname(surname), mName(name), mBirthDate(birthDate),
		mBirthPlace(birthPlace),
		mSex(sex),
		mAuthority(authority), 
		mIssueDate(issueDate)
	{}

	void AddSpecialNote(const string specialNote) 	{ mSpecialNotes += "\n\t- " + specialNote; }
	void AddFamilyStatus(const string familyStatus)	{ mFamilyStatus += "\n\t- " + familyStatus; }
	void AddResidencePlace(const string residencePlace) { mResidencePlace += "\n\t- " + residencePlace; }

	const string GetPassportNo() const { return mPassportNo; }
	const string GetSurname() const { return mSurname; }
	const string GetName() const { return mName; }
	const string GetPatronymic() const { return mPatronymic; }
	const string GetBirthDate() const { return mBirthDate; }
	const string GetBirthPlace() const { return mBirthPlace; }
	const string GetSex() const { return mSex; }
	const string GetAuthority() const { return mAuthority; }
	const string GetIssueDate() const { return mIssueDate; }
	const string GetSpecialNotes() const { return mSpecialNotes; }
	const string GetFamilyStatus() const { return mFamilyStatus; }
	const string GetResidencePlace() const { return mResidencePlace; }
};

