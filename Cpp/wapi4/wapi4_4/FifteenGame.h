#pragma once
#include <vector>
#include <string>


class FifteenGame
{
	std::vector<int> mTile;
	int mMissingTileIndex;
	const int mTilesCount;
	void Shuffle();
public:
	FifteenGame();
	std::wstring GetTile(const int index) const;
	int GetMissingTile() const { return mMissingTileIndex; }
	int GetTilesCount() const { return mTilesCount; }
	bool HasSolution() const;
	bool IsFinished() const;
	bool SwapTile(const int index);
	void Randomize();
};