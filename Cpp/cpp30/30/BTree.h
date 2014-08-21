#pragma once
#include <new>
#include <iostream>
using namespace std;

const int FIRM_LEN = 35;
const int OWNER_LEN = 35;
const int PHONE_LEN = 15;
const int ADDRESS_LEN = 250;
const int BRANCH_LEN = 100;

struct Data
{
	char firm[FIRM_LEN];
	char owner[OWNER_LEN];
	char phone[PHONE_LEN];
	char address[ADDRESS_LEN];
	char branch[BRANCH_LEN];
	Data()
	{
		firm[0] = '\0';
		owner[0] = '\0';
		phone[0] = '\0';
		address[0] = '\0';
		branch[0] = '\0';
	}
};

class Leaf
{
	Data mData;
	Leaf* parent;
	Leaf* left;
	Leaf* right;
public:
	Leaf() :parent(nullptr), left(nullptr), right(nullptr)	{}

	Leaf(const Data& data) : parent(nullptr), left(nullptr), right(nullptr)
	{
		mData = data;
	}

	Leaf(const Leaf& leaf) : parent(leaf.parent), left(leaf.left), right(leaf.right)
	{
		mData = leaf.mData;
	}

	const Data  GetData() const { return mData; }
	const char* GetFirm() const { return mData.firm; }
	const char* GetOwner() const { return mData.owner; }
	const char* GetPhone() const { return mData.phone; }
	const char* GetAddress() const { return mData.address; }
	const char* GetBranch() const { return mData.branch; }
	const char* GetField(const int index) const
	{
		switch (index)
		{
		case 0:
			return mData.firm;
		case 1:
			return mData.owner;
		case 2:
			return mData.phone;
		case 3:
			return mData.branch;
		default:
			return "\0";
		}
	}

	Leaf* GetParent() const { return parent; }
	Leaf* GetLeft() const { return left; }
	Leaf* GetRight() const { return right; }

	friend class BTree;
	friend ostream& operator<<(ostream& stream, const Leaf* const leaf);
};

class BTree
{
	Leaf* mRoot;

	void CopyTree(Leaf* leaf);
public:
	BTree() : mRoot(nullptr){}
	~BTree();

	BTree(const BTree& source);
	BTree& operator=(const BTree& source);

	bool ValidInput(const Data& data);
	Leaf* Add(const Data& data);
	bool Delete(Leaf* leaf);

	Leaf* FindFirm(const char* firm, const Leaf* const startFrom = nullptr) const;
	Leaf* Root() const { return mRoot; }

	Leaf* Min(Leaf* leaf = nullptr) const;
	Leaf* Max(Leaf* leaf = nullptr) const;

	Leaf* Next(Leaf* leaf) const;
	Leaf* Previous(Leaf* leaf)const;

	bool IsEmpty() const { return mRoot == nullptr; }
	friend ostream& operator<<(ostream& stream, const BTree* const bTree);

};

