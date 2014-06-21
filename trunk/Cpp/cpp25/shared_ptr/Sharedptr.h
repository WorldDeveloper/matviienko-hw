template <class T>
class Sharedptr
{
	T* mPtr;
	int mCount;
public:
	Sharedptr(T* p = nullptr) :mPtr(p), mCount(0){ cout << "\n*Create mPtr"; }
	~Sharedptr()
	{
		if (mPtr != nullptr && mCount == 0)
		{
			cout << "\n*Delete mPtr wich value=\"" << *mPtr << "\"\n";
			delete mPtr;
		}
		else
		{
			cout << "\n*Delete copy of mPtr #" << mCount;
			mCount--;
		}
	}

	Sharedptr(const Sharedptr& source)
	{
		mPtr = source.mPtr;
		mCount = source.mCount + 1;
		cout << "\n\n*Copy mPtr to " << mCount << " obj";
	}

	Sharedptr& operator=(const Sharedptr& source)
	{
		if (*this == source) return *this; 
		
		mPtr = source.mPtr;
		mCount = source.mCount + 1;
		cout << "\n\n*Copy mPtr to " << mCount << " obj";

		return *this;
	}

	T* operator->()const { return mPtr; }
	T& operator*() const { return*mPtr; }

	bool operator==(const Sharedptr& operand2) const { return (*mPtr == *operand2.mPtr); }
	bool operator!=(const Sharedptr& operand2) const { return !(*this == operand2); }
	bool operator>(const Sharedptr& operand2) const  { return (*mPtr > *operand2.mPtr); }
	bool operator<(const Sharedptr& operand2) const	{ return (*mPtr < *operand2.mPtr); }
	bool operator>=(const Sharedptr& operand2) const { return !(*this < operand2); }
	bool operator<=(const Sharedptr& operand2) const { return !(*this > operand2); }

	bool Unique() const { return mCount == 0; }
	int Count() const { return mCount; }
};