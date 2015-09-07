//test.cpp

#include "card.hpp"
#include "deck.hpp"
#include "player.hpp"
#include "hand.hpp"
#include <iostream>
	using std::cout;
	using std::endl;
#include <string>
	using std::string;
#include <cstdlib>
#include <ctime>
#include <vector>
	using std::vector;

int main()
{
	/*
	Deck deck;
	Card temp;
	srand(time(0));

	for(int i = 0; i < 104; i++)
	{
		temp = deck.deal();
		cout << i << " " << temp.getFace() << " " << temp.getSuit() << " " << temp.getValue() << std::endl;
	}

	deck.shuffle();

	for(int i = 0; i < 52; i++)
	{
		temp = deck.deal();
		cout << temp.getFace() << " " << temp.getSuit() << " " << temp.getValue() << std::endl;
	}
	*/
	/*
	try
	{
		Player p("Clay");
		cout << p.getName() << " " << p.getScore() << std::endl;
		p.setScore();
		cout << p.getScore() << std::endl;
		p.setScore(-4);
		cout << p.getScore();
	}
	catch (string exception)
	{
		if (exception == "Negative Value")
		{
			cout << "Error. Could not initialize score with negative value." << std::endl;
		}
	}
	*/

	Hand hand;
	Card ace("Ace", "Hearts", 1);
	Card king("King", "Hearts", 10);
	cout << hand.getWorth() << endl;
	hand.drawCard(ace);
	cout << hand.getWorth() << endl;
	hand.drawCard(king);
	cout << hand.getWorth() << endl;
	vector<Card> temp;
	temp = hand.getCards();
	for (unsigned int i = 0; i < temp.size(); i++)
	{
		cout << temp.at(i).getFace() << endl;
	}
	hand.clear();
	cout << hand.getWorth() << endl;
	temp = hand.getCards();
	if (temp.empty())
	{
		cout << "true" << endl;
	}

	return 0;
}
