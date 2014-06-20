#pragma once

class Card
{
	int mRank;
	char mSuit;
public:
	Card() : mRank(-1), mSuit(-1){}
	Card(const int rank, const char suit) : mRank(rank), mSuit(suit){}
	void SetCard(const int rank, const char suit) {
		mRank = rank;
		mSuit = suit;
	}
	char GetSuit() const { return mSuit; }
	int GetRank() const { return mRank; }
	int GetPoint() const
	{
		if (mRank > 10) return 10;
		else return mRank;
	}
};

class Deck
{
	int mDeckSize;
	Card* mCard;
	int mPoints;
public:
	void CreateDeck(const int deckSize);
	Deck(const int deckSize = 0);
	Deck(const Deck& source);
	Deck& operator=(const Deck& source);
	~Deck(){ delete[] mCard; }

	int DeckSize() const { return mDeckSize; }
	Card& operator()(const int index) const;

	void Shuffle();
	void AddCard(const Card card);
	Card RemoveCard();
	int Points() const { return mPoints; }
};