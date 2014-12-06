#include "TicTacToeGame.h"
#include <ctime>;
#include <cmath>
#include <iostream>


TicTacToeGame::TicTacToeGame()
	:mHumansMark(1), mComputersMark(-2), mEmptySquaresNumber(mBoardSize*mBoardSize), mDifficulty(1)
{
	for (int i=0; i<mBoardSize; ++i)
	{
		for (int j=0; j<mBoardSize;++j)
		{
			mBoard[i][j]=0;
		}
	}
}

bool TicTacToeGame::HumanMove(const int row, const int col)
{
	if (!SquareIsEmpty(row, col)) throw "Illegal move!";

	--mEmptySquaresNumber;
	mBoard[row][col]=mHumansMark;

	return CheckVictory(row, col, mBoardSize);
}

bool TicTacToeGame::ComputerMove(int& row, int& col)
{
	if (BoardIsFull()) throw "Illegal move!";

	switch(mDifficulty)
	{
	case 0:
		{
			RandomMove(row, col);
			mBoard[row][col]=-1;
			mEmptySquaresNumber--;

			return CheckVictory(row, col, -mBoardSize);
		}
	}
	

	return false;
}

bool TicTacToeGame::CheckVictory(const int row, const int col, const int criteria)
{
	int vertical=0;
	int horizontal=0;
	int rightDiagonal=0;
	int leftDiagonal=0;

	int i=0;
	for (; i<mBoardSize; ++i)
	{
		vertical+=mBoard[i][col];
		horizontal+=mBoard[row][i];
		rightDiagonal+=mBoard[i][i];
		leftDiagonal+=mBoard[mBoardSize-i-1][i];
	}

	if (vertical==criteria)
	{
		mWinLine.x1=0;
		mWinLine.y1=col;
		mWinLine.x2=mBoardSize-1;
		mWinLine.y2=col;
		return true;
	}

	if (horizontal==criteria)
	{
		mWinLine.x1=row;
		mWinLine.y1=0;
		mWinLine.x2=row;
		mWinLine.y2=mBoardSize-1;
		return true;
	}

	if (rightDiagonal==criteria)
	{
		mWinLine.x1=0;
		mWinLine.y1=0;
		mWinLine.x2=mBoardSize-1;
		mWinLine.y2=mBoardSize-1;
		return true;
	}

	if (leftDiagonal==criteria)
	{
		mWinLine.x1=mBoardSize-1;
		mWinLine.y1=0;
		mWinLine.x2=0;
		mWinLine.y2=mBoardSize-1;
		return true;
	}

	return false;
}

bool TicTacToeGame::BestMove(const int mark)
{
	int vertical[mBoardSize]={0};
	int horizontal[mBoardSize]={0};
	int rightDiagonal=0;
	int leftDiagonal=0;

	
	for (int i=0; i<mBoardSize; ++i)
	{
		for (int j=0; j<mBoardSize; ++j)
		{
			vertical[i]+=mBoard[i][j];
			horizontal[i]+=mBoard[j][i];
		}
		rightDiagonal+=mBoard[i][i];
		leftDiagonal+=mBoard[mBoardSize-i-1][i];
	}

	

	return false;
}

void TicTacToeGame::SetDifficulty(const int level)
{
	if(level<0 || level>2) throw "Difficulty level is incorrect.";

	mDifficulty=level;
}



void TicTacToeGame::RandomMove(int& row, int& col)
{

	std::srand(std::time(NULL));
	int randomSquare=std::rand()%(mEmptySquaresNumber);
	
	//randomSquare=1;

	for (int i=0; i<mBoardSize; ++i)
	{
		for (int j=0; j<mBoardSize; ++j)
		{
			if (SquareIsEmpty(i,j)) 
			{
				--randomSquare;
				if (randomSquare<1)
				{
					row=i;
					col=j;
					return;
				}
			}
		}
	}
}

void TicTacToeGame::Reset()
{

	for (int i=0; i<mBoardSize; ++i)
	{
		for (int j=0; j<mBoardSize; ++j)
		{
			mBoard[i][j]=0;
		}
	}

	mEmptySquaresNumber=mBoardSize*mBoardSize;
	mDifficulty=1;
	mWinLine.Clear();
}

TicTacToeGame::~TicTacToeGame()
{
}
