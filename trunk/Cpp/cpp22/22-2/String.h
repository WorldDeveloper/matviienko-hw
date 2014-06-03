#pragma once
#include <iostream>
#include <new>
using namespace std;

class String
{
	char *value;
	int maxLen;
public:
	void newChar();
	String();
	String(int length);
	String(char *initString);
	String(const String &string);
	~String();	
	void setString(char *initString);
	String operator*(String string);
	String operator=(String string);
	friend ostream &operator<<(ostream &stream, String string);
	friend istream &operator>>(istream &stream, String &string);
};

