//blackjackplayer.cpp
//BlackJackPlayer implementation file
//inherits Player class and Hand Class

#include "blackjackplayer.hpp"
#include "player.hpp" //for inheritance of Player class
#include "hand.hpp"   //for inheritance of Hand class
#include <string>
	using std::string;
#include <vector>
	using std::vector;
#include "SFML/Graphics.hpp"
#include <iostream>


//constructor that uses default amount of starting money takes a name as arguement
BlackJackPlayer::BlackJackPlayer(string name): Player(name), Hand()
{
	//scr = 1500 default 
	moneyBet = 0;
}

//constructor that takes a name and a custom amount of starting money
BlackJackPlayer::BlackJackPlayer(string name, double startingCash): Player(name), Hand()
{
	setScore(startingCash); //change starting cash to user defined starting cash
	moneyBet = 0;
}

//if arguement is true player one won and gets money added to account if false the opposite is applied
void BlackJackPlayer::calcScore(bool wonOrLost)
{
	if (wonOrLost == true) //if player won hand
	{
		setScore(getScore() + moneyBet); //add money won to current total
	}
	else //if player lost hand
	{
		setScore(getScore() - moneyBet); //subract money lost from current total
	}
	clearBet();
}

//used to get from user how much they want to bet and sets it to the moneyBet member variable
void BlackJackPlayer::placeBet(const int bet)
{
	moneyBet += bet;
}

//returns value currently placed in moneyBet member variable
double BlackJackPlayer::getBet()
{
	return moneyBet;
}

//if player hits return true, else return false to indicate end of hand for player
bool BlackJackPlayer::hitOrStay()
{
	//
	//
	//needs sfml
	//
	//
	return true;
}

//recieves another card from the deck and adds it to hand
int BlackJackPlayer::hit(Card card)
{
	drawCard(card); //add card to players hand

	//if worth is over 21 try checking for ace in hand
	if (getWorth() > 21)
	{
		changeAceValue();
	}

	//if worth is 11 make sure they dont have blackjack
	if (getWorth() == 11)
	{
		changeAceValue();
	}
	
	return getWorth(); //return worth of the players hand
}

//shows hand to screen
void BlackJackPlayer::show(sf::Sprite& sprite, sf::RenderWindow* window, sf::Texture& texture, BlackJackPlayer* player)
{
	vector<Card> tempCards;
	tempCards = player->getCards();
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
		sprite.setPosition(sf::Vector2f(70.0f * (i+2), 600.0f)); //this is position needed for bottom player
		window->draw(sprite); //show sprite to screen
	}
	//
	//
	
}
