#pragma once
#include "Deck.h"

class Player
{
	float mBankroll;
	int mBet;
	int mHands;
	Deck*mpDeck;
public:
	Player(const float bankroll);
	~Player();
	void NewDeck();

	Player(const Player& player);
	Player& operator=(const Player& player);
	Deck& operator[](const int index) const;


	void AddCard(Deck& deck);
	bool Split(Deck& deck);
	bool Double(Deck& deck);

	float Bankroll() const { return mBankroll; }
	void WonBank(const float bank)
	{
		mBankroll += bank;
		mBet = 0;
	}
	void LostBank() { mBet = 0; }

	int Bet() const { return mBet; }
	bool MakeBet(const int bet)
	{
		if (bet > mBankroll || bet <= 0){ return false; }
		mBet += bet;
		mBankroll -= bet;
		return true;
	}
	int Points() const;
	int Hands() const { return mHands; }
	bool HaveBJ() const;
	bool CanSplit() const;
	void Reset();
};

