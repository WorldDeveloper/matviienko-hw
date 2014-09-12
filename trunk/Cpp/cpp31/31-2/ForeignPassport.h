#pragma once
#include "Passport.h"

class ForeignPassport :public Passport
{
	string mType;
	string mCountryCode;
	string mNationality;
	string mPersonalNo;
	string mExpiryDate;
	string mVisas;
public:
	ForeignPassport(const string type,
		const string countryCode, 
		const string passportNo, 
		const string surname, 
		const string name,
		const string nationality,
		const string personalNo, 
		const string birthDate,
		const string birthPlace,
		const string sex,
		const string authority,
		const string issueDate,
		const string expiryDate)
		: Passport(passportNo, surname, name, birthDate, birthPlace, sex, authority, issueDate),
		mType(type),
		mCountryCode(countryCode),
		mNationality(nationality),
		mPersonalNo(personalNo),
		mExpiryDate(expiryDate)
	{}

	void AddVisa(const string visa) { mVisas += "\n\t- " + visa; }

	const string GetType() const { return mType; }
	const string GetCountryCode() const { return mCountryCode; }
	const string GetNationality() const { return mNationality; }
	const string GetPersonalNo() const { return mPersonalNo; }
	const string GetExpiryDate() const { return mExpiryDate; }
	const string GetVisas() const { return mVisas; }
};

