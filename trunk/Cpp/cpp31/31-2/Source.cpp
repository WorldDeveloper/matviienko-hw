/*
Создайте класс Passport (паспорт), который будет содержать паспортную информацию о гражданине Украниы. 
С помощью механизма наследования, реализуйте класс ForeignPassport (загран.паспорт) производный от Passport. 
Напомним, что загран.паспорт содержит помимо паспортных данных, также данные о визах, номер загран.паспорта.
*/

#include <iostream>
#include <string>
#include "ForeignPassport.h"
using namespace std;


ostream& operator<<(ostream& stream, const Passport& passport);
ostream& operator<<(ostream& stream, const ForeignPassport& passport);

void main()
{
	Passport passport("AA 111111", "Ivanov", "Ivan", "Ivanovych", "01.01.1990", "Ukraine", "male", "Ministry of Internal Affairs of Ukraine", "01.01.2006");
	passport.AddFamilyStatus("single");
	passport.AddResidencePlace("01.01.2006 Odesa");
	passport.AddResidencePlace("01.01.2010 Lviv");
	passport.AddSpecialNote("foreing passport BB 111111 was issued on 01.01.2009");
	passport.AddSpecialNote("blood group A");
	cout << "PASSPORT"<<passport;

	ForeignPassport foreignPassport("p", "UKR", "BB 111111", "Ivanov", "Ivan", "Ukraine", "1111111111", "01.01.1990", "Ukraine", "M", "1111", "01.01.2009", "01.01.2019");
	foreignPassport.AddVisa("01.01.2012 Canada");
	foreignPassport.AddVisa("01.01.2013 Australia");
	cout << endl<<"FOREIGN PASSPORT" << foreignPassport << endl;

}

ostream& operator<<(ostream& stream, const Passport& passport)
{

	stream << "\nPassport No: " << passport.GetPassportNo();
	stream << "\nSurname: " << passport.GetSurname();
	stream << "\nName: " << passport.GetName();
	stream << "\nPatronymic: " << passport.GetPatronymic();
	stream << "\nDate of birth: " << passport.GetBirthDate();
	stream << "\nPlace of birth: " << passport.GetBirthPlace();
	stream << "\nSex: " << passport.GetSex();
	stream << "\nAuthority: " << passport.GetAuthority();
	stream << "\nDate of issue: " << passport.GetIssueDate();
	stream << "\nSpecial notes: " << passport.GetSpecialNotes();
	stream << "\nFamily status: " << passport.GetFamilyStatus();
	stream << "\nPermanent residence:" << passport.GetResidencePlace() << endl;

	return stream;
}

ostream& operator<<(ostream& stream, const ForeignPassport& passport)
{
	stream << "\nType: " << passport.GetType();
	stream << "\nCountry code: " << passport.GetCountryCode();
	stream << "\nPassport No: " << passport.GetPassportNo();
	stream << "\nSurname: " << passport.GetSurname();
	stream << "\nName: " << passport.GetName();
	stream << "\nNationality: " << passport.GetNationality();
	stream << "\nDate of birth: " << passport.GetBirthDate();
	stream << "\nPersonal No: " << passport.GetPersonalNo();
	stream << "\nSex: " << passport.GetSex();
	stream << "\nPlace of birth: " << passport.GetBirthPlace();
	stream << "\nAuthority: " << passport.GetAuthority();
	stream << "\nDate of issue: " << passport.GetIssueDate();
	stream << "\nDate of expiry: " << passport.GetExpiryDate();
	stream << "\nSpecial notes: " << passport.GetSpecialNotes();
	stream << "\nVisas:" << passport.GetVisas() << endl;

	return stream;
}