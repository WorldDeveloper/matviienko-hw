/*
Написать программу, которая на основе классов реализует карточную игру Блэк-Джек.
*/

#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "Deck.h"
#include "Player.h"
#include "menu.h"
#include <iomanip>
using namespace std;

inline void Gotoxy(short x, short y);
inline int CurX();
inline int CurY();
ostream& operator<<(ostream& stream, const Card& card);
ostream& operator<<(ostream& stream, const Deck& card);
void InitDeck(Deck& deck);
float Bankroll();
void NewBet(Player& player);
void ShowBankroll(const Player& player);
void ResultMessage(const float result);
void ShowPlayer(const Player& player, const char* name);
void SplashScreen();

void main()
{
	const char itemsNumber = 6;
	const char itemMaxLength = 15;
	menu mainMenu("BJ", itemsNumber, itemMaxLength);

	char* titles[itemsNumber] = { "F1 - Hit", "F2 - Stand", "F3 - Double", "F4 - Split", "F5 -Surrender", "F6 Exit" };
	mainMenu.addItems(titles);

	SplashScreen();

	Player player(Bankroll());

	while (true)
	{
		player.Reset();

		Deck deck(52);
		InitDeck(deck);
		deck.Shuffle();

		Player dealer(1);

		NewBet(player);
		float result = 0.0f;

		player.AddCard(deck);
		dealer.AddCard(deck);
		player.AddCard(deck);

		enum { HIT, STAND, DOUBLE, SPLIT, SURRENDER, EXIT };
		bool status[itemsNumber] = { true, true, true, false, true, true };
		if (player.CanSplit())
		{
			status[SPLIT] = true;
		}
		mainMenu.setStatus(status);

		if (player.HaveBJ())
		{
			result = (float)player.Bet()*2.5;
			player.WonBank(result);
		}

		enum { F1 = 59, F2, F3, F4, F5, F6 };

		while (true)
		{
			if (!player.Bet())
			{
				for (int i = 0; i < itemsNumber; ++i)
				{
					status[i] = false;
				}
				mainMenu.setStatus(status);
			}
			mainMenu.showMenu(0);
			ShowBankroll(player);
			ShowPlayer(player, "You");
			ShowPlayer(dealer, "Dealer");

			if (!player.Bet())
			{
				ResultMessage(result);
				break;
			}

			if (!getch())
			{
				unsigned char input = getch();
				switch (input)
				{
				case F1:
					player.AddCard(deck);
					break;

				case F3:
					player.Double(deck);
					input = F2;
					break;

				case F4:
					player.Split(deck);
					status[SPLIT] = false;
					mainMenu.setStatus(status);
					break;

				case F5:
					result = -(float)player.Bet() / 2;
					player.WonBank(-result);
					break;

				case F6:
					exit(0);
					break;
				}

				if (player.Points() > 21)
				{
					result = -(float)player.Bet();
					player.LostBank();
				}
				else if (player.HaveBJ())
				{
					result = (float)player.Bet()*2.5;
					player.WonBank(result);
				}
				else if (player.Points() == 21 || input == F2)
				{
					while (dealer.Points() < 17)
					{
						dealer.AddCard(deck);
					}

					if (dealer.Points()>21 ||
						dealer.Points() < player.Points())
					{
						result = (float)player.Bet() * 2;
						player.WonBank(result);
					}
					else
					{
						result = -(float)player.Bet();
						player.LostBank();
					}
				}

				if (player[0].DeckSize() > 2)
				{
					status[DOUBLE] = false;
					status[SPLIT] = false;
					mainMenu.setStatus(status);
				}
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

float Bankroll()
{
	float bankroll = 0.0f;
	cout << "\n\t\t Enter your bankroll: ";
	cin >> bankroll;

	while (bankroll <1 || bankroll > 1000000)
	{
		cout << "\n\t Enter bankroll greater than 0 and less than 1 000: ";
		cin >> bankroll;
	}
	cout << "\t\t";

	return bankroll;
}

void NewBet(Player& player)
{
	if (player.Bankroll() < 1)
	{
		cout << endl << "\t You have lost the game!\n\n\t";
		exit(0);
	}

	int bet = 0;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x2F);
	cout << " Enter your bet: ";
	cin >> bet;

	while (!player.MakeBet(bet))
	{
		cout << "\n\t Enter correct bet (greate than 0 and less than " << player.Bankroll() << "): ";
		cin >> bet;
	}
}

void ShowBankroll(const Player& player)
{
	cout << "Bankroll: " << player.Bankroll() << "\t\t";
	if (player.Bet())
	{
		cout << "bet: " << player.Bet();
	}
	cout << "\n\n";
}

void ResultMessage(const float result)
{
	cout << "\t";
	if (result > 0)	{
		cout << " You have won " << result << "$";
	}
	else if (result < 0) {
		cout << " You have lost " << -result << "$";
	}
	cout << " ";
}

void ShowPlayer(const Player& player, const char* name)
{
	cout << " " << name << ": (";

	if (player.HaveBJ()) {
		cout << "BJ";
	}
	else if (player.Points() > 21) {
		cout << "Bust";
	}
	else {
		cout << player.Points();
	}
	cout << ")\n";

	for (int i = 0; i < player.Hands(); ++i)
	{
		cout << "\t\t" << player[i] << "\n\n";
	}
}

void SplashScreen()
{
	system("color 20");

	time_t t1;
	time(&t1);
	time_t t2 = t1 + 3;

	Gotoxy(30, 10);
	cout << "BLACKJACK\n";

	while (t1 < t2)
	{
		time(&t1);
	}
}
