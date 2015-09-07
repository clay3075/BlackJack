//player.cpp
//Player class implementation file

#include "player.hpp"
#include <string>
	using std::string;

//constructor will initialize name and set score to 0
Player::Player(string nme)
{
	name = nme;
	score = 0;
}

//accepts a floating point number to set to score value
//default score is 1500
//throws a string exception of negative value
void Player::setScore(double scr)
{	
	if (scr >= 0)					
	{								
		score = scr;				
	}								
	else
	{
		string exception = "Negative Value";
		throw exception;
	}
}

//returns players current score
double Player::getScore()
{
	return score;
}

//returns players name
string Player::getName()
{
	return name;
}