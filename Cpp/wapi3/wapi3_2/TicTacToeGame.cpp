#include "TicTacToeGame.h"
#include <ctime>;
#include <cmath>
#include <iostream>


TicTacToeGame::TicTacToeGame()
	:mHumansMark(1), mComputersMark(-1), mEmptySquaresNumber(mBoardSize*mBoardSize), mDifficulty(1)
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

	Move bestMove;
	switch(mDifficulty)
	{
	case 0:
		{
			RandomMove(bestMove);
			break;
		}
	case 1:
		{			
			bool win=false;
			if (mEmptySquaresNumber>mBoardSize*mBoardSize-2) RandomMove(bestMove);
			else win=BestMove(bestMove, mComputersMark);

			if (!win)
				{
					Move blockMove;
					if (BestMove(blockMove, mHumansMark))
					{
						bestMove=blockMove;
					}
			}

			break;
		}
	case 2:
		{
			bool win=false;
			if (mEmptySquaresNumber>mBoardSize*mBoardSize-2) FirstMove(bestMove);
			else win=BestMove(bestMove, mComputersMark);

			if (!win)
				{
					Move blockMove;
					if (BestMove(blockMove, mHumansMark))
					{
						bestMove=blockMove;
					}
			}
			
			break;
		}
	default:
		throw "Incorrect dfficulty level!";
	}

	row=bestMove.row;
	col=bestMove.col;
	mBoard[row][col]=-1;
	mEmptySquaresNumber--;

	return CheckVictory(row, col, -mBoardSize);
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

void TicTacToeGame::FirstMove(Move& firstMove)
{
	Move move[5];
	move[1].row=2;
	move[2].col=2;
	move[3].row=2;
	move[3].col=2;
	move[4].row=1;
	move[4].col=1;

	std::srand(std::time(NULL));
	int randomMove=std::rand()%5;
	while(!SquareIsEmpty(move[randomMove].row, move[randomMove].col))
	{
		randomMove=std::rand()%5;
	}

	firstMove=move[randomMove];
}


bool TicTacToeGame::BestMove(Move& bestMove, const int playersMark)
{
	int sign=-playersMark;
	bestMove.value=mBoardSize*sign;

	for (int row=0; row<mBoardSize; ++row)
	{
		for (int col=0; col<mBoardSize; ++col)
		{
			if(SquareIsEmpty(row,col))
			{
				int strategies[4]={0};
				for (int i=0; i<mBoardSize; ++i)
				{
					if (row==col) strategies[0]+=mBoard[i][i];
					if (mBoardSize-row-1==col) strategies[1]+=mBoard[mBoardSize-i-1][i];
					strategies[2]+=mBoard[i][col];
					strategies[3]+=mBoard[row][i];
					
				}

				for (int i=0; i<4; ++i)
				{
					if (strategies[i]*sign<bestMove.value*sign)
					{
						bestMove.value=strategies[i];	
						bestMove.row=row;
						bestMove.col=col;

						if (bestMove.value==(mBoardSize-1)*playersMark) 
						{	
							return true;
						}
					}
				}
			}
		}
	}

	return false;

}

void TicTacToeGame::SetDifficulty(const int level)
{
	if(level<0 || level>2) throw "Difficulty level is incorrect.";

	mDifficulty=level;
}



void TicTacToeGame::RandomMove(Move& randomMove)
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
					randomMove.row=i;
					randomMove.col=j;
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
