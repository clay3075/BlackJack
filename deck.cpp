//deck.cpp
//deck class implementation file
//uses Card class (composition)

#include "deck.hpp"
#include "card.hpp"
#include <vector>
	using std::vector;
#include <cstdlib>
#include <string>
	using std::string;

//constants for initializing deck
const int DECKSIZE = 13;
const int SUITSIZE = 4;
const string FACES[DECKSIZE]{"Ace","Two","Three","Four","Five","Six","Seven","Eight","Nine","Ten","Jack","Queen","King"};
const int    VALUES[DECKSIZE]{ 1  ,  2 ,    3  ,  4   ,  5   , 6   ,  7    ,  8    , 9    , 10  , 10   , 10    , 10   };
const string SUIT[SUITSIZE]{"Heart","Diamond","Spade","Club"};

//a private function used to clear used cards so that they can be used in the game again
void Deck::clear()
{
	usedCards.clear();
}

//will initialize the Decks vector of cards to those of a regular deck of cards
Deck::Deck()
{
	Card *temp = nullptr; 
	for(int j = 0; j < SUITSIZE; j++) //for each suit
	{
		for(int i = 0; i < DECKSIZE; i++) //for each type of card Face
		{
			temp = new Card(FACES[i], SUIT[j], VALUES[i]); //make temporary card
			cards.push_back(*temp); //add card to deck
		}
	}
	delete temp; //free allocated memory
	temp = nullptr;
}	

//requires main function to seed srand
//will randomize the order of the cards in the vector cards to mirror the shuffling of a deck of cards 
void Deck::shuffle()
{	
	Card temp;
	int  tempIndex;
	//go through the deck 5 times making swaps along the way to mirror shuffling of a deck
	for(int j = 0; j < 5; j++)
	{
		for(int i = 0; i < 52 - 1; i++) //for each card in deck
		{
			tempIndex = rand() % 52; //get random card to swap
			temp = cards.at(tempIndex);         //
			cards.at(tempIndex) = cards.at(i);	//make swap
			cards.at(i) = temp;					//
		}
	}
}

//will return a card from the top of the deck (return Card from cards vector)
Card Deck::deal()
{
	static unsigned int timesdealt = 0; 
	static Card temp;
	if(timesdealt < cards.size()) //if cards are still in deck
	{
		temp = cards.at(timesdealt); //get card from top of deck
		usedCards.push_back(temp);   //put card taken in used pile
	}
	else //if no cards are left in deck
	{
		clear(); //clear used card pile
		shuffle();
		timesdealt = 0; //reset dealt counter
		deal(); //run function again to deal card
	}
	timesdealt++;
	return temp;
}











