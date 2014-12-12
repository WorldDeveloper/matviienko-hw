#pragma once
#include <vector>
#include <string>


class FifteenGame
{
	std::vector<int> mTile;
	int mMissingTileIndex;
	const int mTilesCount;
	time_t mStartTime;
	time_t mElapsedTime;
	void Shuffle();
public:
	FifteenGame();
	std::wstring GetTile(const int index) const;
	int GetMissingTile() const { return mMissingTileIndex; }
	int GetTilesCount() const { return mTilesCount; }
	int GetElapsedTime() const { return mElapsedTime; }
	bool HasSolution() const;
	bool IsFinished();
	bool SwapTile(const int index);
	void NewGame();
};