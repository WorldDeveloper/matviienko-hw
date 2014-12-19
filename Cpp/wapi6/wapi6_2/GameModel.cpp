#include "GameModel.h"
#include <algorithm>
#include <ctime>
#include <sstream>
#include <iomanip>


GameModel::GameModel() :mTilesCount(16)
{
	std::srand(time(NULL));
	mTile.resize(mTilesCount);
}


std::wstring GameModel::GetTile(const int index) const
{
	if (index < 0 || index >= mTilesCount) throw "Tile is out of range";

	return std::to_wstring(mTile[index]);
}


std::wstring GameModel::GetElapsedTime() const
{
	time_t tmp;
	std::time(&tmp);
	const int time = tmp - mStartTime;

	std::wstringstream mes;
	mes << std::setw(2) << std::setfill(L'0') << time / 60 << ":";
	mes << std::setw(2) << std::setfill(L'0') << time % 60;

	return mes.str();
}

int GameModel::GetElapsedTimeInt() const
{
	time_t tmp;
	std::time(&tmp);
	return tmp - mStartTime;
}

bool GameModel::TimeIsUp()const
{
	time_t tmp;
	std::time(&tmp);
	return mFinishTime < tmp;
}


bool GameModel::NewGame(const int duration)
{
	if (duration <= 0) return false;

	for (int i = 0; i < mTilesCount; ++i)
	{
		mTile[i] = std::rand() % 100;
	}

	std::vector<int> tmp = mTile;
	std::sort(tmp.begin(), tmp.end());

	while (!mSortedTiles.empty()) mSortedTiles.pop();

	for (std::vector<int>::reverse_iterator it = tmp.rbegin(); it < tmp.rend(); ++it)
	{
		mSortedTiles.push(*it);
	}

	time(&mStartTime);
	mFinishTime = mStartTime + duration;

	return true;
}

bool GameModel::LegalMove(const int id)
{
	if (mSortedTiles.empty() || mTile.empty()) return false;

	if (mTile[id] == mSortedTiles.top())
	{
		mSortedTiles.pop();
		return true;
	}

	return false;
}