#pragma once
#include <new>
#include <iostream>
using namespace std;

struct ContactBuffer
{
	char surname[20];
	char name[20];
	char phone[15];
	ContactBuffer();
	ContactBuffer(const char* iSurname, const char* iName, const char* iPhone)
	{
		strcpy(surname, iSurname);
		strcpy(name, iName);
		strcpy(phone, iPhone);
	}
};

class Contact
{
	char surname[20];
	char name[20];
	char phone[15];
	Contact* parent;
	Contact* left;
	Contact* right;
public:
	Contact() :parent(nullptr), left(nullptr), right(nullptr)
	{
		surname[0] = '\0';
		name[0] = '\0';
		phone[0] = '\0';
	}

	const char* GetSurname() const { return surname; }
	const char* GetName() const { return name; }
	const char* GetPhone() const { return phone; }
	Contact* GetParent() const { return parent; }
	Contact* GetLeft() const { return left; }
	Contact* GetRight() const { return right; }

	friend class PhoneBook;
	friend ostream& operator<<(ostream& stream, const Contact* const contact);
};

class PhoneBook
{
	Contact* mRoot;

	void CopyTree(Contact* contact);
public:
	PhoneBook() : mRoot(nullptr){}
	~PhoneBook();

	PhoneBook(const PhoneBook& source);
	PhoneBook& operator=(const PhoneBook& source);

	bool ValidInput(Contact* contact, const char* surname, const char* name, const char* phone);
	Contact* Add(const char* surname, const char* name, const char* phone);
	Contact* Add(Contact* contact);
	bool Delete(Contact* contact);

	Contact* SearchSurname(const char* surname, const Contact* const startFrom = nullptr) const;
	Contact* SearchPhone(const char* phone, Contact* const startFrom) const;

	Contact* Root() const { return mRoot; }

	Contact* Min(Contact* contact = nullptr) const;
	Contact* Max(Contact* contact = nullptr) const;

	Contact* Next(Contact* contact) const;
	Contact* Previous(Contact* contact)const;

	bool IsEmpty() const { return mRoot == nullptr; }
	friend ostream& operator<<(ostream& stream, const PhoneBook* const phoneBook);

};

