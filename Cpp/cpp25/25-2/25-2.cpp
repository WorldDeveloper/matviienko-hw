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

inline void gotoxy(short x, short y);
inline int curX();
inline int curY();
ostream& operator<<(ostream& stream, const Card& card);
ostream& operator<<(ostream& stream, const Deck& card);
void InitDeck(Deck& deck);
int InputBelt(float& bankroll);
void ShowBankroll(const float bankroll, const int belt);
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
	int belt = InputBelt(bankroll);
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

		/*card.SetCard(1, 4);
		player[0].AddCard(card); */
		player[0].AddCard(deck.RemoveCard());

		bool status[itemsNumber] = { true, true, true, false, true, true };
		int r1 = player[0](0).GetRank();
		int r2 = player[0](1).GetRank();
		if (r1 == r2 || (r1 > 10 && r2 > 10)) status[3] = true;
		mainMenu.setStatus(status);

		mainMenu.showMenu(0);
		ShowBankroll(bankroll, belt);

		ShowPlayer(player[0], "You");
		ShowPlayer(dealer, "Dealer");

		if (player[0].Points() == 21)
		{
			result = (float)belt*2.5;
			bankroll += result;

			for (int i = 0; i < itemsNumber; ++i)
			{
				status[i] = false;
			}
			mainMenu.setStatus(status);

			mainMenu.showMenu(0);
			ShowBankroll(bankroll, belt);
			ShowPlayer(player[0], "You");
			ShowPlayer(dealer, "Dealer");
			ResultMessage(result);
			belt = InputBelt(bankroll);
			continue;
		}

		enum{ F1 = 59, F2, F3, F4, F5, F6 };
		while (true)
		{
			if (!belt)
			{
				ResultMessage(result);
				belt = InputBelt(bankroll);
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
					if (player[0].DeckSize()>2 || bankroll < belt * 2) break;
					bankroll -= belt;
					belt *= 2;
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
					if (player[0].DeckSize() == 2 && bankroll >= belt * 2)
					{
						int r1 = player[0](0).GetRank();
						int r2 = player[0](1).GetRank();

						if (r1 == r2 || (r1 > 10 && r2 > 10))
						{
							hands = 2;
							player[1].AddCard(player[0].RemoveCard());
							player[0].AddCard(deck.RemoveCard());
							bankroll -= belt;
							belt *= 2;

							status[3] = false;
							mainMenu.setStatus(status);
						}
					}
					break;
				case F5:
					bankroll += (float)belt / 2;
					result = -(float)belt / 2;
					belt = 0;
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
							result = -(float)belt;
							belt = 0;
						}
					}
					else if (player[i].Points() == 21 && player[i].DeckSize() == 2)
					{
						result = (float)belt*2.5;
						bankroll += result;
						belt = 0;
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
							result = (float)belt * 2;
							bankroll += result;
							belt = 0;
							break;
						}
						else if (hands == 1 || (hands>1 && i > 0))
						{
							result = -(float)belt;
							belt = 0;
							break;
						}
					}
				}

				if (player[0].DeckSize() > 2)
				{
					status[2] = false;
					mainMenu.setStatus(status);
				}

				if (!belt)
				{
					for (int i = 0; i < itemsNumber; ++i)
					{
						status[i] = false;
					}
					mainMenu.setStatus(status);
				}

				mainMenu.showMenu(0);
				ShowBankroll(bankroll, belt);

				for (int i = 0; i < hands; ++i)
				{
					ShowPlayer(player[i], "You");
				}
				ShowPlayer(dealer, "Dealer");
			}
		}
	}
}

inline void gotoxy(short x, short y)
{
	COORD coord = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

inline int curX()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
		return -1;
	return csbi.dwCursorPosition.X;
}

inline int curY()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
		return -1;
	return csbi.dwCursorPosition.Y;
}

ostream& operator<<(ostream& stream, const Card& card)
{
	short x = curX();
	short y = curY();

	if (x > 70)
	{
		x = 16;
		y += 8;
		gotoxy(x, y);
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
	gotoxy(x, ++y);

	stream << " " << left << setw(2) << setfill(' ') << rank << "    " << suit << " ";
	gotoxy(x, ++y);
	stream << "         ";

	gotoxy(x, ++y);

	stream << "    " << suit << "    ";
	gotoxy(x, ++y);

	stream << "         ";

	gotoxy(x, ++y);

	stream << " " << suit << "    " << right << setw(2) << setfill(' ') << rank << " ";
	gotoxy(x, ++y);

	stream << "         ";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x20);
	gotoxy(x + 10, y - 6);
	return stream;
}
ostream& operator<<(ostream& stream, const Deck& card)
{
	for (int i = 0; i < card.DeckSize(); ++i)
	{
		cout << card(i);
	}

	short y = curY();
	gotoxy(0, y + 6);
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

int InputBelt(float& bankroll)
{
	if (bankroll<1)
	{
		cout << endl << "\t You have lost the game!\n\n\t";
		exit(0);
	}

	int belt = 0;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x2F);
	cout << "\t Enter your belt: ";
	cin >> belt;

	while (belt <= 0 || (float)belt > bankroll)
	{
		cout << "\n\t Enter correct belt (greate than 0 and less than " << bankroll << "): ";
		cin >> belt;
	}
	bankroll -= belt;

	return belt;
}

void ShowBankroll(const float bankroll, const int belt)
{
	cout << "Bankroll: " << bankroll << "\t\t";
	if (belt) cout << "Belt: " << belt << "\t\t";
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