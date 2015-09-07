//dealer.hpp
//Dealer class specification file
//inherited from BlackJackPlayer class
//composed of Deck class

#ifndef DEALER_H
#define DEALER_H

#include "blackjackplayer.hpp"
#include "deck.hpp"
#include <string>
	using std::string;

class Dealer: public BlackJackPlayer
{
private:
	Deck deck; //dealer will control the deck of cards used
public:	
	Dealer(string name = "Dealer"); //constructor will initialize all values needed
	void shuffle(); //will randomize cards in deck by calling the Deck class shuffle() function
	Card deal();   //will return a Card object from the "top" of the deck object
	void taunt();   //if dealer wins will pick from 5 random taunts
	bool smartHitOrStay(); //will determine whether to hit or stay returns true for hit or false for stay
	void show (sf::Sprite& sprite, sf::RenderWindow* window, sf::Texture& texture, Dealer* player, bool dealersTurn);
	//virtual ~Dealer(){};
};

#endif