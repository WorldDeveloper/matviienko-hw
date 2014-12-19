#pragma once
#include <vector>
#include <string>

#include <stack>

class GameModel
{
	std::vector<int> mTile;
	std::stack<int> mSortedTiles;
	const int mTilesCount;
	time_t mStartTime;
	time_t mFinishTime;

public:
	GameModel();

	std::wstring GetTile(const int index) const;
	int GetTilesCount() const { return mTilesCount; }
	std::wstring GetElapsedTime() const;
	int GetElapsedTimeInt() const;
	bool TimeIsUp()const;
	bool NewGame(const int duration);
	bool LegalMove(const int id);
	bool IsFinished() const { return !mTile.empty() && mSortedTiles.empty(); }
};