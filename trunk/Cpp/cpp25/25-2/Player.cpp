#include "Player.h"
#include <new>
using namespace std;

void Player::NewDeck()
{
	try
	{
		mpDeck = new Deck[2];
	}
	catch (bad_alloc)
	{
		exit(1);
	}
}
Player::Player(const float bankroll) : mBankroll(bankroll), mBet(0), mHands(1)
{
	NewDeck();
}

Player::~Player()
{
	delete[] mpDeck;
	mBankroll = 0;
	mBet = 0;
	mHands = 1;
}

void Player::Reset()
{
	delete[] mpDeck;
	NewDeck();
	mBet = 0;
	mHands = 1;
}

Player::Player(const Player& player)
{
	NewDeck();
	mBankroll = player.mBankroll;
	mBet = player.mBet;
	mHands = player.mHands;

	for (int i = 0; i < mHands; ++i)
	{
		mpDeck[i] = player.mpDeck[i];
	}
}

Player& Player::operator = (const Player& player)
{
	if (this == &player)
	{
		return *this;
	}

	mBankroll = player.mBankroll;
	mBet = player.mBet;
	mHands = player.mHands;

	for (int i = 0; i < mHands; ++i)
	{
		mpDeck[i] = player.mpDeck[i];
	}

	return *this;
}

Deck& Player::operator[](const int index)const
{
	if (index >= 0 && index < mHands)
	{
		return mpDeck[index];
	}
	else
	{
		exit(1);
	}
}

void Player::AddCard(Deck& deck)
{
	for (int i = 0; i < mHands; ++i)
	{
		mpDeck[i].AddCard(deck.RemoveCard());
	}
}

bool Player::CanSplit() const
{
	if (mHands == 1 &&
		mpDeck[0].DeckSize() == 2 &&
		mBankroll >= mBet)
	{
		if (mpDeck[0](0).GetRank() == mpDeck[0](1).GetRank() ||
			(mpDeck[0](0).GetRank() > 10 && mpDeck[0](1).GetRank() > 10))
		{
			return true;
		}
	}
	return false;
}

bool Player::Split(Deck& deck)
{
	if (!CanSplit()) { return false; }
	mHands = 2;
	mpDeck[1].AddCard(mpDeck[0].RemoveCard());
	mpDeck[0].AddCard(deck.RemoveCard());
	MakeBet(mBet);
	return true;
}

bool Player::Double(Deck& deck)
{
	if (mpDeck[0].DeckSize() != 2 || mBankroll < mBet) { return false; }
	AddCard(deck);
	MakeBet(mBet);
	return true;
}

int Player::Points() const
{
	int maxPoints = 0;
	for (int i = 0; i < mHands; ++i)
	{
		if (mpDeck[i].Points()>maxPoints)
		{
			maxPoints = mpDeck[i].Points();
		}
	}
	return maxPoints;
}

bool Player::HaveBJ() const
{
	bool bj = false;
	for (int i = 0; i < mHands; ++i)
	{
		if (mpDeck[i].Points() == 21 && mpDeck[i].DeckSize() == 2)
		{
			bj = true;
		}
		else if (mpDeck[i].Points()>21)
		{
			return false;
		}
	}
	return bj;
}