//создать аналог shared_ptr

#include <iostream>
#include "Sharedptr.h"
using namespace std;

void f1(Sharedptr<int>& p, int count)
{
	if (count > 3) return;
	*p = count;
	cout << "\n p=" << *p << "\n # of copies: " << p.Count();
	cout << "\n Is p unique: " << p.Unique();
	count++;
	f1(p, count);
}

void f2(Sharedptr<int> p, int count)
{
	if (count > 3) return;
	*p = count;
	cout << "\n p=" << *p << "\n # of copies: " << p.Count();
	cout << "\n Is p unique: " << p.Unique();
	count++;
	f2(p, count);
}

void main()
{
	Sharedptr<int> ptr1(new int);
	*ptr1 = 1;
	cout << "\n ptr1=" << *ptr1;
	cout << "\n Is ptr1 unique: " << ptr1.Unique() << endl;

	Sharedptr<int> ptr2(new int);
	*ptr2 = 2;
	cout << "\n ptr2=" << *ptr2;

	cout << "\n\n ptr1==ptr2:\t" << (ptr1 == ptr2) << endl;
	cout << " ptr1!=ptr2:\t" << (ptr1 != ptr2) << endl;
	cout << " ptr1>=ptr2:\t" << (ptr1 >= ptr2) << endl;
	cout << " ptr1<=ptr2:\t" << (ptr1 <= ptr2) << endl;
	cout << " ptr1>ptr2:\t" << (ptr1 > ptr2) << endl;
	cout << " ptr1<ptr2:\t" << (ptr1 < ptr2) << endl;

	cout << "\n\n***Call by reference***";
	f1(ptr1, 1);
	cout << "\n\n***Call by reference ended***\n";

	cout << "\n\n*****Call by value***";
	f2(ptr1, 1);
	cout << "\n\n***Call by value ended***\n";

	cout << "\n\n ptr1=" << *ptr1;
	cout << "\n Is ptr1 unique: " << ptr1.Unique();
}