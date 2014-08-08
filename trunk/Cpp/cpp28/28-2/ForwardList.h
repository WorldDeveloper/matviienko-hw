#pragma once
#include <new>
#include <ostream>
using namespace std;

struct ListNode
{
	int offenceNumber;
	char date[11];
	char* offence;
	ListNode* next;
	ListNode(int iNumber, const char* const iDate, const char* const iOffence) 
		:offenceNumber(iNumber), offence(new char[strlen(iOffence) + 1]), next(nullptr) 
	{
		strcpy(date, iDate);
		strcpy(offence, iOffence);
	}
	~ListNode()
	{
		delete[] offence;
	}
};

class ForwardList
{
	ListNode* mpHead;
	ListNode* mpTail;
	int mCount;
public:
	ForwardList() : mpHead(nullptr), mpTail(nullptr), mCount(0){}
	~ForwardList();

	ForwardList(const ForwardList& source);
	ForwardList& operator=(const ForwardList& source);

	bool PushBack(const int number, const char* const date, const char* const offence);
	int GetCount() const { return mCount; }

	friend ostream& operator<<(ostream& stream, const ForwardList& fList);
};
