template <class T>
class Sharedptr
{
	T* mPtr;
	int* mCount;
public:
	Sharedptr(T* p = nullptr) :mPtr(p), mCount(new int)
	{
		if (mPtr) 
		{ 
			*mCount = 1;
			cout << "\*Create mPtr\n";
		}
		else { *mCount = 0; }

		
	}
	~Sharedptr()
	{
		if (mPtr != nullptr && *mCount ==1)
		{
			cout << "*Delete mPtr wich value=\"" << *mPtr << "\"\n";
			delete mPtr;
			delete mCount;
		}
		else
		{
			cout << "*Delete copy of mPtr #" << *mCount << endl;
			--(*mCount);
		}
	}

	Sharedptr(const Sharedptr& source)
	{
		mPtr = source.mPtr;
		mCount = source.mCount;
		++(*mCount);
		cout << "*Copy mPtr to " << *mCount << " obj\n";
	}

	Sharedptr& operator=(const Sharedptr& source)
	{
		if (this == &source) return *this;

		this->~Sharedptr();
		mPtr = source.mPtr;
		mCount = source.mCount;
		++(*mCount);
		cout << "*Copy mPtr to " << *mCount << " obj\n";

		return *this;
	}

	T* operator->()const
	{
		if (mPtr != nullptr || *mCount != 0)
		{
			return mPtr;
		}
		else
		{
			cout << "\nError\n";
			exit(1);
		}
	}
	T& operator*() const
	{
		if (mPtr != nullptr || *mCount != 0)
		{
			return *mPtr;
		}
		else
		{
			cout << "\nError\n";
			exit(1);
		}
	}

	bool operator==(const Sharedptr& operand2) const { return (*mPtr == *operand2.mPtr); }
	bool operator!=(const Sharedptr& operand2) const { return !(*this == operand2); }
	bool operator>(const Sharedptr& operand2) const  { return (*mPtr > *operand2.mPtr); }
	bool operator<(const Sharedptr& operand2) const	{ return (*mPtr < *operand2.mPtr); }
	bool operator>=(const Sharedptr& operand2) const { return !(*this < operand2); }
	bool operator<=(const Sharedptr& operand2) const { return !(*this > operand2); }

	bool Unique() const { return *mCount == 0; }
	int Count() const { return *mCount; }
};