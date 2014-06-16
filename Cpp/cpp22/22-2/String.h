#pragma once
#include <iostream>
#include <new>
using namespace std;

class String
{
	char *value;
	int maxLen;
	int realLen;
public:
	void allocateString();
	String();
	String(int length);
	String(char *initString);
	String(const String &string);
	~String();	
	void setString(char *initString);
	int getLength(){ return realLen; }
	String operator*(const String& string) const;
	String &operator=( const String& string);
	friend ostream &operator<<(ostream &stream, String string);
	friend istream &operator>>(istream &stream, String &string);
};

