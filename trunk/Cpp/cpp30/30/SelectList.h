#pragma once
#include "BTree.h"
#include <Windows.h>
#include "Graphics.h"

class SelectList
{
	BTree* mBTree;
	Leaf* mSelectedLeaf;
	Leaf* mFirstLeaf;
	Leaf* mLastLeaf;
	int mCurY;
	int mBaseX;
	int mBaseY;
	char* mMessage;
	bool mErrorMessage;
	const short mActiveColour = 0x70;
	const short mInactiveColour = 0xF0;
	char mMask[20];
	bool mSelectedLeafReview;
public:
	SelectList(BTree* bTree, const int baseX, const int baseY);
	~SelectList() { delete[] mMessage; }

	bool ListIsEmpty();
	void SelectActiveItem();
	void DeselectActiveItem();
	void ShowItem(const Leaf* const leaf) const;
	void ShowSelectedItem();
	void ShowList();
	void NextNode();
	void PreviousNode();
	bool DeleteNode();
	bool EditNode();
	bool AddNode();
	bool Search(const int field, const bool findNext = false);
	void MaskSearch(const unsigned char symbol, const int field);
	bool QuitReview();
	bool ReviewStatus() const { return mSelectedLeafReview; }

	void ShowStatus();
	void ResetMessage();
	void ResetList();

};