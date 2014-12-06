#pragma once

struct Line{
int x1;
int y1;
int x2;
int y2;
Line():x1(0), y1(0), x2(0), y2(0){}
void Clear()
	{
		x1=0;
		y1=0;
		x2=0;
		y2=0;
	}
};

	struct Move{
		int value;
		int row;
		int col;
		Move():value(0), row(0), col(0){}
	};



class TicTacToeGame
{
	static const int mBoardSize=3;
	int mBoard[mBoardSize][mBoardSize];
	int mEmptySquaresNumber;
	int mHumansMark;
	int mComputersMark;
	int mDifficulty;
	Line mWinLine;



public:
	TicTacToeGame();
	bool HumanMove(const int row, const int col);
	bool ComputerMove(int& row, int& col);
	void RandomMove(Move& ramdnomMove);
	bool CanWin(const int mark);
	bool SquareIsEmpty(const int row, const int col) const {return !mBoard[row][col];}
	bool BoardIsFull() const {return !mEmptySquaresNumber;}
	void SetDifficulty(const int level);
	Line GetResult() const {return mWinLine;}
	void Reset();
	bool CheckVictory(const int row, const int col, const int criteria);
	bool BestMove(Move& bestMove, const int playersMark);
	void FirstMove(Move& firstMove);

	~TicTacToeGame();
};

