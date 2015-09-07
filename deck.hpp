//deck.hpp
//deck class specification file
//uses Card class (composition)

#ifndef DECK_H
#define DECK_H

#include "card.hpp"
#include <vector>
	using std::vector;
#include <cstdlib>

class Deck
{
private:
	vector<Card> cards; 	//a vector to hold the cards needed for a deck
	vector<Card> usedCards; //a vector to hold cards from the deck that have been used in play
	void clear(); //a private function used to clear used cards so that they can be used in the game again
public:	
	Deck(); 		//will initialize the Decks vector of cards to those of a regular deck of cards
	//requires main function to seed rand
	void shuffle(); //will randomize the order of the cards in the vector cards to mirror the shuffling of a deck of cards 
	Card deal();    //will return a card from the top of the deck (return Card from cards vector

};

#endif
