#include "Deck.h"
#include <new>
#include <ctime>
#include <cstdlib>
using namespace std;

void Deck::CreateDeck(const int deckSize)
{
	mDeckSize = deckSize;
	try
	{
		mCard = new Card[mDeckSize];
	}
	catch (bad_alloc)
	{
		exit(1);
	}
	mPoints = 0;
}
Deck::Deck(const int deckSize)
{
	CreateDeck(deckSize);
}

Deck::Deck(const Deck& source)
: mDeckSize(source.mDeckSize), mCard(new Card[mDeckSize]), mPoints(source.mPoints)
{
	for (int i = 0; i < mDeckSize; ++i)
	{
		mCard[i] = source.mCard[i];
	}
}

Deck& Deck::operator=(const Deck& source)
{
	if (this == &source) return *this;

	delete[] mCard;
	CreateDeck(source.mDeckSize);
	for (int i = 0; i < mDeckSize; ++i)
	{
		mCard[i] = source.mCard[i];
	}
	mPoints = source.mPoints;
	return *this;
}

Card& Deck::operator()(const int index) const
{
	if (index >= 0 || index < mDeckSize) return mCard[index];
}


void Deck::Shuffle()
{
	srand(time(NULL));
	int i = mDeckSize * 5;
	while (i--)
	{
		Card tmp;
		const int leftI = i%mDeckSize;
		const int rightI = rand() % mDeckSize;
		tmp = mCard[leftI];
		mCard[leftI] = mCard[rightI];
		mCard[rightI] = tmp;
	}
}

void Deck::AddCard(const Card card)
{
	Deck tmp(*this);
	delete[] mCard;
	++mDeckSize;
	CreateDeck(mDeckSize);

	for (int i = 0; i < tmp.mDeckSize; ++i)
	{
		mCard[i] = tmp.mCard[i];
	}

	mCard[mDeckSize - 1] = card;
	int rank = card.GetRank();

	if (rank == 1 && tmp.mPoints + 11 <= 21)
	{
		mPoints = tmp.mPoints + 11;
	}
	else if (tmp.mPoints + card.GetPoint() > 21)
	{
		mPoints = 0;
		for (int i = 0; i < mDeckSize; ++i)
		{
			mPoints += mCard[i].GetPoint();
		}
	}
	else
	{
		mPoints = tmp.mPoints + card.GetPoint();
	}
}

Card Deck::RemoveCard()
{
	if (mDeckSize > 0)
	{
		mDeckSize--;
		if (mPoints > 0) mPoints -= mCard[mDeckSize].GetPoint();
		return mCard[mDeckSize];
	}
	else
	{
		exit(1);
	}

}