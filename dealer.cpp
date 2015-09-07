//dealer.cpp
//Dealer class implementation file
//inherited from BlackJackPlayer class
//composed of Deck class

#include "dealer.hpp"
#include "blackjackplayer.hpp"
#include "deck.hpp"
#include <string>
	using std::string;
#include <cstdlib>
#include <iostream>



//constructor will initialize all values needed
Dealer::Dealer(string name): BlackJackPlayer(name)
{
	shuffle(); //shuffle deck
}

//will randomize cards in deck by calling the Deck class shuffle() function
void Dealer::shuffle()
{
	deck.shuffle();
}

//will return a Card object from the "top" of the deck object
Card Dealer::deal()
{
	return deck.deal();
}

//if dealer wins will pick from 5 random taunts to display to the screen
void Dealer::taunt()
{
	int temp = rand() % 5; //get random number
	//
	//
	//needs sfml
	//
	//
}

//will determine whether to hit or stay returns true for hit or false for stay
bool Dealer::smartHitOrStay()
{
	//if value is 11 make sure hand doesnt have ace to make it 21
	if (getWorth() == 11)
	{
		changeAceValue();
	}

	bool hitOrNot = true;
	//hit while hand is below 17
	if (getWorth() >= 17)
	{
		hitOrNot = false;
	}

	//if hand breaks make sure hand doesnt have ace
	if (getWorth() > 21)
	{
		changeAceValue();
	}
	return hitOrNot;
}

//shows hand to screen
void Dealer::show(sf::Sprite& sprite, sf::RenderWindow* window, sf::Texture& texture, Dealer* player, bool dealersTurn)
{
	vector<Card> tempCards;
	tempCards = player->getCards();
	if (dealersTurn)
	{
		//draw cards to screen
		for (unsigned int i = 0; i < player->getNumberOfCardsInDeck(); i++) //for each card in hand
		{
			if (!texture.loadFromFile("images/" + tempCards.at(i).getFace() + tempCards.at(i).getSuit() + ".jpg"))
			{
				std::cout << "Sprite Error";
			}
			//postion of first card for each player
			//
			sprite.setTexture(texture); //set image to sprite
			sprite.setScale(sf::Vector2f(2.5f, 2.5f)); //make card bigger //this is scale needed
		
			sprite.setPosition(sf::Vector2f(70.0f * (i+2), 100.0f)); //this is position needed for top player
			window->draw(sprite); //show sprite to screen
		}
		//
		//
	}
	else
	{
		if (!texture.loadFromFile("images/card.jpg"))
		{
			std::cout << "Card Sprite Error";
		}
		sprite.setTexture(texture); //set image to sprite
		sprite.setScale(sf::Vector2f(2.5f, 2.5f)); //make card bigger //this is scale needed
		
		sprite.setPosition(sf::Vector2f(70.0f * 2, 100.0f)); //this is position needed for top player
		window->draw(sprite); //show sprite to screen

		if (!texture.loadFromFile("images/" + tempCards.at(1).getFace() + tempCards.at(1).getSuit() + ".jpg"))
		{
			std::cout << "Card Sprite Error";
		}
		sprite.setTexture(texture); //set image to sprite
		sprite.setScale(sf::Vector2f(2.5f, 2.5f)); //make card bigger //this is scale needed
		
		sprite.setPosition(sf::Vector2f(70.0f * 3, 100.0f)); //this is position needed for top player
		window->draw(sprite); //show sprite to screen

	}
	
}
