#pragma once
#include <new>
#include <iostream>
#include "ForwardList.h";
#include "Graphics.h"
#include <iomanip>
using namespace std;

class Leaf
{
	char carNumber[10];
	ForwardList* penalty;
	Leaf* parent;
	Leaf* left;
	Leaf* right;
public:
	Leaf(const char* const iCarNumber) :penalty(new ForwardList), parent(nullptr), left(nullptr), right(nullptr)
	{
		strcpy(carNumber, iCarNumber);
	}

	Leaf(const Leaf& leaf) :penalty(leaf.penalty), parent(nullptr), left(nullptr), right(nullptr)
	{
		strcpy(carNumber, leaf.carNumber);

	}

	~Leaf() { delete penalty; }

	const char* CarNumber() const { return carNumber; }

	Leaf* GetLeft() const { return left; }
	Leaf* GetRight() const { return right; }

	friend class BTree;
	friend ostream& operator<<(ostream& stream, const Leaf* const leaf)
	{
		SetColour(0x8F);
		stream << setw(79) << leaf->carNumber << " \n";

		if (leaf->penalty->GetCount())
		{
			cout << *leaf->penalty;
		}
		else
		{
			stream << "\n\n";
		}
		SetColour(0xF0);
		return stream;
	}
};


class BTree
{
	Leaf* mRoot;
	int mCurPenaltyNumber;

	void CopyTree(Leaf* leaf);
	void CopyLeaf(Leaf* leaf);
public:
	BTree() : mRoot(nullptr), mCurPenaltyNumber(0){}
	~BTree();

	BTree(const BTree& source);
	BTree& operator=(const BTree& source);

	Leaf* Add(const char* const carNumber, const char* const date, const char* const penalty);
	bool Delete(Leaf* leaf);

	Leaf* FindCarNumber(const char* const carNumber, const Leaf* const startFrom = nullptr) const;

	Leaf* Root() const { return mRoot; }
	Leaf* Min(Leaf* leaf = nullptr) const;
	Leaf* Max(Leaf* leaf = nullptr) const;
	Leaf* Next(Leaf* leaf) const;
	Leaf* Previous(Leaf* leaf)const;

	bool IsEmpty() const { return mRoot == nullptr; }
	friend ostream& operator<<(ostream& stream, const BTree* const bTree);
};


