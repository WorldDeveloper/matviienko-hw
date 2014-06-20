/*
Написать программу, которая на основе классов реализует карточную игру Блэк-Джек.
*/

#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "Deck.h"
#include "menu.h"
#include <iomanip>
using namespace std;

inline void Gotoxy(short x, short y);
inline int CurX();
inline int CurY();
ostream& operator<<(ostream& stream, const Card& card);
ostream& operator<<(ostream& stream, const Deck& card);
void InitDeck(Deck& deck);
int InputBet(float& bankroll);
void ShowBankroll(const float bankroll, const int bet);
void ResultMessage(const float result);
void ShowPlayer(const Deck& deck, const char* player);


void main()
{
	const char itemsNumber = 6;
	const char itemMaxLength = 15;
	menu mainMenu("BJ", itemsNumber, itemMaxLength);

	char* titles[itemsNumber] = { "F1 - Hit", "F2 - Stand", "F3 - Double", "F4 - Split", "F5 -Surrender", "F6 Exit" };
	mainMenu.addItems(titles);

	system("color 20");
	cout << "\n\t You are playing Blackjack \n\n";
	float bankroll;
	cout << "\t Enter your bankroll: ";
	cin >> bankroll;
	while (bankroll <1 || bankroll > 1000000)
	{
		cout << "\n\t Enter bankroll greater than 0 and less than 1 000: ";
		cin >> bankroll;
	}
	int bet = InputBet(bankroll);
	float result = 0;

	while (true)
	{
		Deck deck(52);
		InitDeck(deck);
		int hands = 1;
		Deck player[2];
		Deck dealer;
		deck.Shuffle();

		/*Card card;
		card.SetCard(1, 3);
		player[0].AddCard(card);*/
	
		player[0].AddCard(deck.RemoveCard());
		dealer.AddCard(deck.RemoveCard());

		/*card.SetCard(10, 4);
		player[0].AddCard(card); */
		player[0].AddCard(deck.RemoveCard());

		bool status[itemsNumber] = { true, true, true, false, true, true };
		int r1 = player[0](0).GetRank();
		int r2 = player[0](1).GetRank();
		if (r1 == r2 || (r1 > 10 && r2 > 10)) status[3] = true;
		mainMenu.setStatus(status);

		mainMenu.showMenu(0);
		ShowBankroll(bankroll, bet);

		ShowPlayer(player[0], "You");
		ShowPlayer(dealer, "Dealer");

		if (player[0].Points() == 21)
		{
			result = (float)bet*2.5;
			bankroll += result;

			for (int i = 0; i < itemsNumber; ++i)
			{
				status[i] = false;
			}
			mainMenu.setStatus(status);

			mainMenu.showMenu(0);
			ShowBankroll(bankroll, bet);
			ShowPlayer(player[0], "You");
			ShowPlayer(dealer, "Dealer");
			ResultMessage(result);
			bet = InputBet(bankroll);
			continue;
		}

		enum{ F1 = 59, F2, F3, F4, F5, F6 };
		while (true)
		{
			if (!bet)
			{
				ResultMessage(result);
				bet = InputBet(bankroll);
				break;
			}

			if (!getch())
			{
				unsigned char input = getch();
				switch (input)
				{
				case F1:
					for (int i = 0; i < hands; ++i)
					{
						if (player[i].Points()<21)
						{
							player[i].AddCard(deck.RemoveCard());
						}
					}
					break;

				case F3:
					if (player[0].DeckSize()>2 || bankroll < bet * 2) break;
					bankroll -= bet;
					bet *= 2;
					for (int i = 0; i < hands; ++i)
					{
						if (player[i].Points() < 21)
						{
							player[i].AddCard(deck.RemoveCard()); 
						}
					}
					input = 60;
					break;

				case F4:
					if (hands == 2) break;
					if (player[0].DeckSize() == 2 && bankroll >= bet * 2)
					{
						int r1 = player[0](0).GetRank();
						int r2 = player[0](1).GetRank();

						if (r1 == r2 || (r1 > 10 && r2 > 10))
						{
							hands = 2;
							player[1].AddCard(player[0].RemoveCard());
							player[0].AddCard(deck.RemoveCard());
							bankroll -= bet;
							bet *= 2;

							status[3] = false;
							mainMenu.setStatus(status);
						}
					}
					break;
				case F5:
					bankroll += (float)bet / 2;
					result = -(float)bet / 2;
					bet = 0;
					break;
				case F6:
					exit(0);
					break;
				}

				for (int i = 0; i<hands; ++i)
				{
					if (player[i].Points() > 21)
					{
						if (hands == 1 || (i > 0 && player[0].Points() > 21))
						{
							result = -(float)bet;
							bet = 0;
						}
					}
					else if (player[i].Points() == 21 && player[i].DeckSize() == 2)
					{
						result = (float)bet*2.5;
						bankroll += result;
						bet = 0;
						break;
					}
					else if (player[i].Points() == 21 || input == F2)
					{
						while (dealer.Points() < 17)
						{
							Card tmp = deck.RemoveCard();
							dealer.AddCard(tmp);
						}

						if (dealer.Points() > 21 || dealer.Points() < player[i].Points())
						{
							result = (float)bet * 2;
							bankroll += result;
							bet = 0;
							break;
						}
						else if (hands == 1 || (hands>1 && i > 0))
						{
							result = -(float)bet;
							bet = 0;
							break;
						}
					}
				}

				if (player[0].DeckSize() > 2)
				{
					status[2] = false;
					mainMenu.setStatus(status);
				}

				if (!bet)
				{
					for (int i = 0; i < itemsNumber; ++i)
					{
						status[i] = false;
					}
					mainMenu.setStatus(status);
				}

				mainMenu.showMenu(0);
				ShowBankroll(bankroll, bet);

				for (int i = 0; i < hands; ++i)
				{
					ShowPlayer(player[i], "You");
				}
				ShowPlayer(dealer, "Dealer");
			}
		}
	}
}

inline void Gotoxy(short x, short y)
{
	COORD coord = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

inline int CurX()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
		return -1;
	return csbi.dwCursorPosition.X;
}

inline int CurY()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
		return -1;
	return csbi.dwCursorPosition.Y;
}

ostream& operator<<(ostream& stream, const Card& card)
{
	short x = CurX();
	short y = CurY();

	if (x > 70)
	{
		x = 16;
		y += 8;
		Gotoxy(x, y);
	}

	char ranks[][13] = { "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };

	int itemColor;
	if (card.GetSuit() > 4) itemColor = 0xF0;
	else itemColor = 0xF4;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), itemColor);

	if (card.GetRank() == -1 || card.GetSuit() == -1)
	{
		stream << endl << "Error: card  wasn't initialized" << endl;
		return stream;
	}
	char rank[3];
	strcpy(rank, ranks[card.GetRank() - 1]);
	char suit = card.GetSuit();

	stream << "         ";
	Gotoxy(x, ++y);

	stream << " " << left << setw(2) << setfill(' ') << rank << "    " << suit << " ";
	Gotoxy(x, ++y);
	stream << "         ";

	Gotoxy(x, ++y);

	stream << "    " << suit << "    ";
	Gotoxy(x, ++y);

	stream << "         ";

	Gotoxy(x, ++y);

	stream << " " << suit << "    " << right << setw(2) << setfill(' ') << rank << " ";
	Gotoxy(x, ++y);

	stream << "         ";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x20);
	Gotoxy(x + 10, y - 6);
	return stream;
}
ostream& operator<<(ostream& stream, const Deck& card)
{
	for (int i = 0; i < card.DeckSize(); ++i)
	{
		cout << card(i);
	}

	short y = CurY();
	Gotoxy(0, y + 6);
	return stream;
}

void InitDeck(Deck& deck)
{
	for (int i = 0; i < deck.DeckSize() / 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			deck(i * 4 + j).SetCard(i + 1, j + 3);
		}
	}
}

int InputBet(float& bankroll)
{
	if (bankroll<1)
	{
		cout << endl << "\t You have lost the game!\n\n\t";
		exit(0);
	}

	int bet = 0;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x2F);
	cout << "\t Enter your bet: ";
	cin >> bet;

	while (bet <= 0 || (float)bet > bankroll)
	{
		cout << "\n\t Enter correct bet (greate than 0 and less than " << bankroll << "): ";
		cin >> bet;
	}
	bankroll -= bet;

	return bet;
}

void ShowBankroll(const float bankroll, const int bet)
{
	cout << "Bankroll: " << bankroll << "\t\t";
	if (bet) cout << "bet: " << bet << "\t\t";
	cout << "\n\n";
}

void ResultMessage(const float result)
{
	cout << "\t";
	if (result > 0) cout << " You have won " << result << "$";
	else if (result < 0) cout << " You have lost " << -result << "$";
	cout << endl;
}

void ShowPlayer(const Deck& deck, const char* player)
{
	cout << " " << player << ": (";

	if (deck.Points() == 21 && deck.DeckSize() == 2){
		cout << "BJ";
	}
	else if (deck.Points() > 21){
		cout << "Bust";
	}
	else{
		cout << deck.Points();
	}
	cout << ")\t" << deck << "\n\n";
}