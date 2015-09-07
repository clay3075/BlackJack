//card.hpp
//Card class specification file

#ifndef CARD_H
#define CARD_H

#include <string>
	using std::string;

//a standalone class used to represent a playing card
class Card
{
private:
	string face;  //holds the string equivelent of the face value
	string suit;  //holds the suit of the card
	int    value; //holds the actual value of the card for mathmatical purposes
public:
	Card() //default constructor makes a blank card //definded inline
		{face = "";
		 suit = "";
		 value = 0;};
	Card(string fce, string s, int val); //contructor used to initialize values
	string getFace();  //returns the string face value of the card
	string getSuit();  //returns the suit of the card as a string
	int    getValue(); //returns the actual value of the card as an int
	void   changeValue(int val = 0); //changes value of card
};

#endif