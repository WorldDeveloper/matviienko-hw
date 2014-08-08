#include "ForwardList.h"
#include "Graphics.h"

ForwardList::~ForwardList()
{
	while (mpHead)
	{
		ListNode* needlessNode = mpHead;
		mpHead = mpHead->next;
		delete needlessNode;
	}
	mpTail = nullptr;
	mCount = 0;
}


ForwardList::ForwardList(const ForwardList& source)
{
	mpHead = nullptr;
	mpTail = nullptr;
	mCount = 0;

	ListNode* tmp = source.mpHead;
	while (tmp)
	{
		PushBack(tmp->offenceNumber, tmp->date, tmp->offence);
		tmp = tmp->next;
	}
}


ForwardList& ForwardList::operator=(const ForwardList& source)
{
	if (this == &source) return *this;

	this->~ForwardList();

	ListNode* tmp = source.mpHead;
	while (tmp)
	{
		PushBack(tmp->offenceNumber, tmp->date, tmp->offence);
		tmp = tmp->next;
	}

	return *this;
}


bool ForwardList::PushBack(const int number, const char* const date, const char* const offence)
{
	if (strlen(date) > 10) return false;

	ListNode* tmp = new ListNode(number, date, offence);


	if (!mpHead)
	{
		mpHead = tmp;
		mpTail = tmp;
	}
	else
	{
		mpTail->next = tmp;
		mpTail = tmp;
	}
	mCount++;

	return true;
}


ostream& operator<<(ostream& stream, const ForwardList& fList)
{
	ListNode* output = fList.mpHead;
	while (output)
	{
		SetColour(0x70);
		stream << "#" << output->offenceNumber << "\t";
		stream << output->date << endl;
		SetColour(0xF0);
		stream << output->offence << "\n\n";
		output = output->next;
	}
	return stream;
}