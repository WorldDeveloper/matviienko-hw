#include "BTree.h"

BTree::~BTree()
{
	while (mRoot)
	{
		Delete(mRoot);
	}
}

void  BTree::CopyLeaf(Leaf* leaf)
{
	Leaf* newLeaf = new Leaf(*leaf);

	Leaf* iLeaf = mRoot;
	while (iLeaf)
	{
		int leafCompare = strcmp(leaf->carNumber, iLeaf->carNumber);
		newLeaf->parent = iLeaf;

		if (leafCompare < 0)
		{
			iLeaf = iLeaf->left;
		}
		else
		{
			iLeaf = iLeaf->right;
		}
	}

	if (!mRoot)
	{
		mRoot = newLeaf;
	}
	else if (strcmp(leaf->carNumber, newLeaf->parent->carNumber) < 0)
	{
		newLeaf->parent->left = newLeaf;
	}
	else
	{
		newLeaf->parent->right = newLeaf;
	}
}

void BTree::CopyTree(Leaf* leaf)
{
	if (leaf)
	{
		CopyLeaf(leaf);
		CopyTree(leaf->left);
		CopyTree(leaf->right);
	}
}

BTree::BTree(const BTree& source)
{
	mRoot = nullptr;
	CopyTree(source.mRoot);
	mCurPenaltyNumber = source.mCurPenaltyNumber;
}


BTree& BTree::operator = (const BTree& source)
{
	if (this == &source) return *this;

	this->~BTree();
	CopyTree(source.mRoot);
	mCurPenaltyNumber = source.mCurPenaltyNumber;

	return *this;
}


Leaf* BTree::Add(const char* const carNumber, const char* const date, const char* const penalty)
{
	if (!carNumber[0] && !date[0] && !penalty[0] ||
		strlen(carNumber) > 9 || strlen(date) > 10) {
		return nullptr;
	}

	mCurPenaltyNumber++;
	Leaf* newLeaf = FindCarNumber(carNumber);
	if (newLeaf)
	{
		newLeaf->penalty->PushBack(mCurPenaltyNumber, date, penalty);
		return newLeaf;
	}

	newLeaf = new Leaf(carNumber);
	newLeaf->penalty->PushBack(mCurPenaltyNumber, date, penalty);

	Leaf* iLeaf = mRoot;
	while (iLeaf)
	{
		int leafCompare = strcmp(carNumber, iLeaf->carNumber);
		newLeaf->parent = iLeaf;

		if (leafCompare < 0)
		{
			iLeaf = iLeaf->left;
		}
		else
		{
			iLeaf = iLeaf->right;
		}
	}

	if (!mRoot)
	{
		mRoot = newLeaf;
	}
	else if (strcmp(carNumber, newLeaf->parent->carNumber) < 0)
	{
		newLeaf->parent->left = newLeaf;
	}
	else
	{
		newLeaf->parent->right = newLeaf;
	}

	return newLeaf;
}


Leaf* BTree::FindCarNumber(const char* const carNumber, const Leaf* const startFrom /*= nullptr*/) const
{
	Leaf* leaf = new Leaf(carNumber);
	if (startFrom)
	{
		*leaf = *startFrom;
	}
	else
	{
		leaf = mRoot;
	}

	while (leaf)
	{
		int leafCompare = strcmp(carNumber, leaf->carNumber);
		if (leafCompare < 0)
		{
			leaf = leaf->left;
		}
		else if (leafCompare>0)
		{
			leaf = leaf->right;
		}
		else
		{
			return leaf;
		}
	}
	return nullptr;
}



Leaf* BTree::Min(Leaf* leaf /*=nullptr*/) const
{
	if (!leaf)
	{
		leaf = mRoot;
	}

	if (leaf)
	{
		while (leaf->left)
		{
			leaf = leaf->left;
		}
	}
	return leaf;
}


Leaf* BTree::Max(Leaf* leaf/*=nullptr*/) const
{
	if (!leaf)
	{
		leaf = mRoot;
	}

	if (leaf)
	{
		while (leaf->right)
		{
			leaf = leaf->right;
		}
	}
	return leaf;
}


Leaf* BTree::Next(Leaf* leaf) const
{

	if (leaf)
	{
		if (leaf->right)
		{
			return Min(leaf->right);
		}

		Leaf* leafParent = leaf->parent;
		while (leafParent&& leaf == leafParent->right)
		{
			leaf = leafParent;
			leafParent = leafParent->parent;
		}
		return leafParent;
	}

	return nullptr;
}


Leaf* BTree::Previous(Leaf* leaf) const
{

	if (leaf)
	{
		if (leaf->left)
		{
			return Max(leaf->left);
		}

		Leaf* leafParent = leaf->parent;
		while (leafParent &&
			leaf == leafParent->left)
		{
			leaf = leafParent;
			leafParent = leafParent->parent;
		}
		return leafParent;
	}

	return nullptr;
}


bool BTree::Delete(Leaf* leaf)
{
	if (!mRoot)
	{
		return false;
	}

	if (leaf)
	{
		Leaf* leafChild = nullptr;
		if (leaf->left && !leaf->right)
		{
			leafChild = leaf->left;
		}
		else if (leaf->right && !leaf->left)
		{
			leafChild = leaf->right;
		}
		else if (leaf->left && leaf->right)
		{
			leafChild = leaf->right;
			Leaf* tmp = Next(leaf);
			tmp->left = leaf->left;
			leaf->left->parent = tmp;
		}

		if (leafChild)
		{
			leafChild->parent = leaf->parent;
		}

		if (!leaf->parent)
		{
			mRoot = leafChild;
		}
		else if (leaf == leaf->parent->left)
		{
			leaf->parent->left = leafChild;
		}
		else if (leaf == leaf->parent->right)
		{
			leaf->parent->right = leafChild;
		}

		delete leaf;
		return true;
	}

	return false;
}