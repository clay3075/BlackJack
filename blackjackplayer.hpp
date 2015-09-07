//blackjackplayer.hpp
//BlackJackPlayer class specification
//inherits Player class and Hand Class

#ifndef BLACKJACKPLAYER_H
#define BLACKJACKPLAYER_H

#include "player.hpp" //for inheritance of Player class
#include "hand.hpp"   //for inheritance of Hand class
#include <string>
	using std::string;

class BlackJackPlayer: public Player, public Hand
{
private:
	double moneyBet; //will hold the amount of money currently being bet by player
public:	
	BlackJackPlayer(): Player(), Hand(){};
	BlackJackPlayer(string name); //constructor that uses default amount of starting money takes a name as arguement
	BlackJackPlayer(string name, double startingCash); //constructor that takes a name and a custom amount of starting money
	void calcScore(bool wonOrLost); //if arguement is true player one and gets money added to account if false the opposite is applied
	void placeBet(const int bet = 0); //used to get from user how much they want to bet and sets it to the moneyBet member variable
	double getBet(); //returns value currently placed in moneyBet member variable
	bool hitOrStay(); //if player hits return true, else return false to indicate end of hand for player
	int hit(Card card); //recieves another card from the deck and adds it to hand
	void clearBet()
		{moneyBet = 0;}
	void show (sf::Sprite& sprite, sf::RenderWindow* window, sf::Texture& texture, BlackJackPlayer* player); //shows hand to screen
	//virtual ~BlackJackPlayer(){};
};


#endif