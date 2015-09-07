//hand.cpp
//Hand class implementation file
//Composed of Card class

#include "card.hpp" //include Card class
#include "hand.hpp"
#include <vector>
	using std::vector;
#include "SFML/Graphics.hpp"
#include <iostream>

//protected

//function to calculate the worth of the cards in hand
void Hand::calcWorth()
{
	if (cards.empty()) //if no cards are in hand
	{
		worth = 0;
	}
	else
	{
		int points = 0; //accumulator
		for (unsigned int i = 0; i < cards.size(); i++) //for each card
		{
			points += cards.at(i).getValue(); //add up card values
		}
		worth = points;
	}
	return;
} 

//public

//default constructor used to initialize hand to blank values 
//does so by calling clear() function
Hand::Hand()
{
	clear();
}

//mirrors the drawing of a card from a deck and adds it to the cards in hand and then calculates the hands worth
//@param card Is a Card value used to mirror the existence of a card being drawn
void Hand::drawCard(Card card)
{
	cards.push_back(card);
	calcWorth();
	return;
}
//returns a vector holding the cards in hand
vector<Card>& Hand::getCards()
{
	return cards;
}

//removes all cards from hand
void Hand::clear()
{
	cards.clear();
	calcWorth();
	return;
}

//returns the worth of the cards in hand
int Hand::getWorth()
{
	return worth;
}

//if ace is in hand changes ace value
void Hand::changeAceValue()
{
	for (unsigned int i = 0; i < cards.size(); i++)
	{
		if (cards.at(i).getValue() == 1)
		{
			cards.at(i).changeValue(11);
		}
		else if (cards.at(i).getValue() == 11)
		{
			cards.at(i).changeValue(1);
		}
	}
	calcWorth();
}

