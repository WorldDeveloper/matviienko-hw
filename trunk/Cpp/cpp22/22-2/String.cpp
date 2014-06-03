#include "string.h"
#include <iostream>
#include <new>
using namespace std;

void String::newChar()
{
	try
	{
		value = new char[maxLen];
	}
	catch (bad_alloc er)
	{
		cout << "Error: out of memory!";
		exit(0);
	}
}

String::String()
{
	maxLen = 80;
	newChar();
	strcpy(value, "\0");
}

String::String(int length)
{
	maxLen = length;
	newChar();
	strcpy(value, "\0");
}

String::String(char *initString)
{
	maxLen = strlen(initString) + 1;
	newChar();
	strcpy(value, initString);
}

String::String(const String &string)
{
	maxLen = string.maxLen;
	newChar();
	strcpy(value, string.value);
}

String::~String()
{
	if (value) delete[] value;
}

void String::setString(char *initString)
{
	int initSize = strlen(initString) + 1;
	if (maxLen < initSize)
	{
		delete[] value;
		maxLen = initSize;
		newChar();
	}
	strcpy(value, initString);
}


String String::operator*(String string)
{
	int tmpLen;
	if (strlen(value) > strlen(string.value))
	{
		tmpLen = strlen(value)+1;
	}
	else
	{
		tmpLen = strlen(string.value)+1;
	}
	String tmp(tmpLen);	
	char *result = tmp.value;
	*result = '\0';

	for (char *s1 = value; *s1 !='\0'; ++s1)
	{		
		bool newChar = true;
		for (char *r = tmp.value; *r != '\0'; ++r)
		{
			if (*s1 == *r) newChar=false;
		}
		
		for (char *s2 = string.value; *s2 !='\0' && newChar;++s2)
		{
			if (*s1 == *s2)
			{
				*result = *s1;
				++result;
				*result = '\0';
				break;
			}
		}
	}
	return tmp;
}

String String::operator=(String string)
{	
	if (maxLen < strlen(string.value + 1))
	{
		delete[] value;
		maxLen = strlen(string.value) + 1;
		newChar();
	}
	maxLen = string.maxLen;
	strcpy(value, string.value);

	return *this;
}

ostream &operator<<(ostream &stream, String string)
{
	stream << string.value;
	return stream;
}
istream &operator>>(istream &stream, String &string)
{
	stream.get(string.value, string.maxLen);
	return stream;
}