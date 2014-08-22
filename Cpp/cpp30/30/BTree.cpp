#include "BTree.h"



BTree::~BTree()
{
	while (mRoot)
	{
		Delete(mRoot);
	}
}

bool BTree::ValidInput(const Data& data)
{
	if (
		((!data.firm[0] || !data.owner[0]) && !data.branch[0]) &&
		(!data.phone[0] || !data.address[0]))
	{
		return false;
	}
	else
	{
		const char*phoneEnd = data.phone + strlen(data.phone);
		const char* i = data.phone;
		if (*i != 43 && (*i<48 || *i>57)) return false;

		for (++i; i < phoneEnd; i++)
		{
			if (*i<48 || *i>57) return false;
		}

		return true;
	}
}

void BTree::CopyTree(Leaf* leaf)
{
	if (leaf)
	{
		Add(leaf->mData);
		CopyTree(leaf->left);
		CopyTree(leaf->right);
	}
}

BTree::BTree(const BTree& source)
{
	mRoot = nullptr;
	CopyTree(source.mRoot);
}

BTree& BTree::operator = (const BTree& source)
{
	if (this == &source) return *this;

	this->~BTree();

	CopyTree(source.mRoot);

	return *this;
}

void BTree::CalcID(Leaf* leaf)
{
	const Leaf* prevLeaf = Previous(leaf);
	int id = -1;
	if (prevLeaf)
	{
		id = prevLeaf->mID;
	}

	while (leaf)
	{
		leaf->mID = ++id;
		leaf = Next(leaf);
	}
}

Leaf*  BTree::Add(const Data& data)
{
	if ((!data.firm[0] || !data.owner[0])) { return nullptr; }

	Leaf* newLeaf = new Leaf(data);

	Leaf* iLeaf = mRoot;
	while (iLeaf)
	{
		if (!ValidInput(data)) return nullptr;

		int firmCompare = strcmp(data.firm, iLeaf->mData.firm);
		newLeaf->parent = iLeaf;

		if (firmCompare < 0)
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
	else if (strcmp(data.firm, newLeaf->parent->mData.firm) < 0)
	{
		newLeaf->parent->left = newLeaf;
	}
	else
	{
		newLeaf->parent->right = newLeaf;
	}

	CalcID(newLeaf);
	return newLeaf;
}


Leaf* BTree::FindFirm(const char* firm, const Leaf* const startFrom /*=nullptr*/) const
{
	Leaf* leaf = new Leaf;
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
		int nameCompare = strcmp(firm, leaf->mData.firm);
		if (nameCompare < 0)
		{
			leaf = leaf->left;
		}
		else if (nameCompare>0)
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

		Leaf* nextLeaf = Next(leaf);
		delete leaf;
		CalcID(nextLeaf);

		return true;
	}

	return false;
}
