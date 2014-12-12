#include "FifteenGame.h"
#include <algorithm>
#include <ctime>



FifteenGame::FifteenGame():mTilesCount(16)
{
	std::srand(time(NULL));
	for (int i = 0; i < mTilesCount; ++i) mTile.push_back(i);
	Randomize();
}


std::wstring FifteenGame::GetTile(const int index) const
{
	if (index < 0 || index >= mTilesCount) throw "Tile is out of range";
	
	return std::to_wstring(mTile[index]);
}

bool FifteenGame::IsFinished() const
{
	const int end = mTilesCount - 1;
	for (int i = 0; i < end; ++i)
	{
		if (mTile[i] != i+1) return false;
	}

	return true;
}

bool FifteenGame::HasSolution() const
{
	const int end = mTilesCount - 1;
	int n = 0;
	for (int i = 0; i < end; ++i)
	{
		int k = 0;
		for (int j = i+1; j < mTilesCount; ++j)
		{
			if (!mTile[j]) break;
			if (mTile[j] <mTile[i]) k++;
		}
		n += k;
	}

	int sa = (int)std::sqrt(mTilesCount);
	if (((n + mMissingTileIndex / (int)std::sqrt(mTilesCount) + 1) % 2)==1) return false;

	return true;
}

void FifteenGame::Shuffle()
{
	std::random_shuffle(mTile.begin(), mTile.end());
	for (int i = 0; i < mTilesCount; ++i)
	{
		if (!mTile[i])
		{
			mMissingTileIndex = i;
			break;
		}
	}
}


bool FifteenGame::SwapTile(const int index)
{
	if (index<0 || index >= mTilesCount)   throw "Tile is out of range";
	if (index==mMissingTileIndex) return false;

	const int frameSize = (int)std::sqrt(mTilesCount);

	int rowDifference = abs((mMissingTileIndex - index) / frameSize);
	int colDifference = abs((mMissingTileIndex - index) % frameSize);

	if ((colDifference == 1 && !rowDifference) ||
		(!colDifference && rowDifference == 1))
	{
		std::swap(mTile[index], mTile[mMissingTileIndex]);
		mMissingTileIndex = index;
		return true;
	}

	return false;	
}

void FifteenGame::Randomize()
{
	do 
	{
		Shuffle();
	} while (!(HasSolution() && !IsFinished()));

}