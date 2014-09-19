//создать аналог shared_ptr

#include <iostream>
#include "Sharedptr.h"
using namespace std;

template <typename T>
void info(const Sharedptr<T>& p, char* name);

void f1(Sharedptr<int>& p, int count);
void f2(Sharedptr<int> p, int count);

void main()
{
	cout << "Create ptr1\n";
	Sharedptr<int> ptr1(new int);

	*ptr1 = 1;
	cout << "ptr1=1\n";
	info(ptr1, "ptr1");


	cout << "\n\nCreate ptr2\n";
	Sharedptr<int> ptr2(new int);
	*ptr2 = 2;
	cout << "ptr2=2\n";
	info(ptr2, "ptr2");

	cout << "\n\n ptr1==ptr2:\t" << (ptr1 == ptr2) << endl;
	cout << " ptr1!=ptr2:\t" << (ptr1 != ptr2) << endl;
	cout << " ptr1>=ptr2:\t" << (ptr1 >= ptr2) << endl;
	cout << " ptr1<=ptr2:\t" << (ptr1 <= ptr2) << endl;
	cout << " ptr1>ptr2:\t" << (ptr1 > ptr2) << endl;
	cout << " ptr1<ptr2:\t" << (ptr1 < ptr2) << endl;

	cout << "\nptr2=ptr1\n";
	ptr2 = ptr1;
	info(ptr1, "ptr1");
	info(ptr2, "ptr2");

	cout << "\n\n***Call by reference***\n";
	f1(ptr1, 1);
	cout << "***Call by reference ended***\n";

	cout << "\n\n*****Call by value***\n";
	f2(ptr1, 1);
	cout << "***Call by value ended***\n";


	info(ptr1, "ptr1");
	info(ptr2, "ptr2");

	cout << "\nptr2=new int(2)\n";
	ptr2 = new int(2);

	cout << "\nptr1=new int(1)\n";
	ptr1 = new int(1);
	info(ptr1, "ptr1");
	info(ptr2, "ptr2");

	Sharedptr<int> p;
	info(p, "p");
	p = ptr1;
	info(p, "p");
}

template <typename T>
void info(const Sharedptr<T>& p, char* name)
{
	cout << "\t " << name << "=" << *p;
	cout << "\t # of copies: " << p.Count()<<"\n";
}

void f1(Sharedptr<int>& p, int count)
{
	if (count > 3) return;
	*p = count;
	info(p, "p");
	count++;
	f1(p, count);
}

void f2(Sharedptr<int> p, int count)
{
	if (count > 3) return;
	*p = count;
	info(p, "p");
	count++;
	f2(p, count);
}
