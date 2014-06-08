#include "string.h"
#include <iostream>
#include <new>
using namespace std;

void String::allocateString()
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
	curLen = 0;
	allocateString();
	strcpy(value, "\0");
}

String::String(int length)
{
	maxLen = length+1;
	curLen = 0;
	allocateString();
	strcpy(value, "\0");
}

String::String(char *initString)
{
	curLen = strlen(initString);
	maxLen = curLen+1;
	allocateString();
	strcpy(value, initString);
}

String::String(const String &string)
{
	maxLen = string.maxLen;
	curLen = string.curLen;
	allocateString();
	strcpy(value, string.value);
}

String::~String()
{
	 delete[] value;
}

void String::setString(char *initString)
{
	int initLen = strlen(initString)+ 1;
	if (maxLen < initLen)
	{
		delete[] value;
		maxLen = initLen;		
		allocateString();
	}
	curLen = initLen-1;
	strcpy(value, initString);
}


String String::operator*(const String& string)
{
	String tmp(curLen);	
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

String &String::operator=( const String& string)
{	
	if (this == &string)
	{
		return *this;
	}

	if (maxLen < string.curLen+1)
	{
		delete[] value;
		maxLen = string.curLen + 1;
		allocateString();
	}
	maxLen = string.maxLen;
	curLen = string.curLen;
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