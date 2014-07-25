#include "PhoneBook.h"



PhoneBook::~PhoneBook()
{
	while (mRoot)
	{
		Delete(mRoot);
	}
}

bool PhoneBook::ValidInput(Contact* contact, const char* surname, const char* name, const char* phone)
{
	if (
		((!surname[0] || !name[0]) && !phone[0]) ||
		(!strcmp(surname, contact->surname) && !strcmp(name, contact->name) && !strcmp(phone, contact->phone))
		)
	{
		return false;
	}
	else
	{
		const char*phoneEnd = phone + strlen(phone);
		const char* i = phone;
		if (*i != 43 && (*i<48 || *i>57)) return false;

		for (++i; i < phoneEnd; i++)
		{
			if (*i<48 || *i>57) return false;
		}

		return true;
	}
}

void PhoneBook::CopyTree(Contact* contact)
{
	if (contact)
	{
		Add(contact);
		CopyTree(contact->left);
		CopyTree(contact->right);
	}
}

PhoneBook::PhoneBook(const PhoneBook& source)
{
	mRoot = nullptr;
	CopyTree(source.mRoot);
}
PhoneBook& PhoneBook::operator = (const PhoneBook& source)
{
	if (this == &source) return *this;

	this->~PhoneBook();

	CopyTree(source.mRoot);

	return *this;
}


Contact*  PhoneBook::Add(const char* surname, const char* name, const char* phone)
{
	if ((!surname[0] || !name[0]) && !phone[0]) { return nullptr; }

	Contact* newContact = new Contact;
	strcpy(newContact->surname, surname);
	strcpy(newContact->name, name);
	strcpy(newContact->phone, phone);

	Contact* iContact = mRoot;
	while (iContact)
	{
		if (!ValidInput(iContact, surname, name, phone)) return nullptr;

		int nameCompare = strcmp(surname, iContact->surname);
		newContact->parent = iContact;

		if (nameCompare < 0)
		{
			iContact = iContact->left;
		}
		else
		{
			iContact = iContact->right;
		}
	}

	if (!mRoot)
	{
		mRoot = newContact;
	}
	else if (strcmp(surname, newContact->parent->surname) < 0)
	{
		newContact->parent->left = newContact;
	}
	else
	{
		newContact->parent->right = newContact;
	}
	return newContact;
}

Contact*  PhoneBook::Add(Contact* contact)
{
	return Add(contact->surname, contact->name, contact->phone);
}

Contact* PhoneBook::SearchSurname(const char* surname, const Contact* const startFrom /*=nullptr*/) const
{
	Contact* contact = new Contact;
	if (startFrom)
	{
		*contact = *startFrom;
	}
	else
	{
		contact = mRoot;
	}

	while (contact)
	{
		int nameCompare = strcmp(surname, contact->surname);
		if (nameCompare < 0)
		{
			contact = contact->left;
		}
		else if (nameCompare>0)
		{
			contact = contact->right;
		}
		else
		{
			return contact;
		}
	}
	return nullptr;
}


Contact* PhoneBook::SearchPhone(const char* phone, Contact*  const startFrom) const
{
	Contact* contact = new Contact;
	if (startFrom)
	{
		contact = startFrom;
	}
	else
	{
		contact = Min();
	}

	while (contact)
	{
		if (strcmp(phone, contact->phone))
		{
			contact = Next(contact);
		}
		else
		{
			return contact;
		}
	}
	return nullptr;
}


Contact* PhoneBook::Min(Contact* contact /*=nullptr*/) const
{
	if (!contact)
	{
		contact = mRoot;
	}

	if (contact)
	{
		while (contact->left)
		{
			contact = contact->left;
		}
	}
	return contact;
}

Contact* PhoneBook::Max(Contact* contact/*=nullptr*/) const
{
	if (!contact)
	{
		contact = mRoot;
	}

	if (contact)
	{
		while (contact->right)
		{
			contact = contact->right;
		}
	}
	return contact;
}

Contact* PhoneBook::Next(Contact* contact) const
{

	if (contact)
	{
		if (contact->right)
		{
			return Min(contact->right);
		}

		Contact* contactParent = contact->parent;
		while (contactParent&& contact == contactParent->right)
		{
			contact = contactParent;
			contactParent = contactParent->parent;
		}
		return contactParent;
	}

	return nullptr;
}

Contact* PhoneBook::Previous(Contact* contact) const
{

	if (contact)
	{
		if (contact->left)
		{
			return Max(contact->left);
		}

		Contact* contactParent = contact->parent;
		while (contactParent &&
			contact == contactParent->left)
		{
			contact = contactParent;
			contactParent = contactParent->parent;
		}
		return contactParent;
	}

	return nullptr;
}

bool PhoneBook::Delete(Contact* contact)
{
	if (!mRoot)
	{
		return false;
	}

	if (contact)
	{
		Contact* contactChild = nullptr;
		if (contact->left && !contact->right)
		{
			contactChild = contact->left;
		}
		else if (contact->right && !contact->left)
		{
			contactChild = contact->right;
		}
		else if (contact->left && contact->right)
		{
			contactChild = contact->right;
			Contact* tmp = Next(contact);
			tmp->left = contact->left;
			contact->left->parent = tmp;
		}

		if (contactChild)
		{
			contactChild->parent = contact->parent;
		}

		if (!contact->parent)
		{
			mRoot = contactChild;
		}
		else if (contact == contact->parent->left)
		{
			contact->parent->left = contactChild;
		}
		else if (contact == contact->parent->right)
		{
			contact->parent->right = contactChild;
		}

		delete contact;
		return true;
	}

	return false;
}
