//game.hpp
//Game class specification file

#ifndef GAME_H
#define GAME_H

#include "SFML/Graphics.hpp"
#include "dealer.hpp" 

class Game
{
private:
	int  nameCharCount;
	bool betPlaced;
	bool standPressed;
	bool hitPressed;
	bool gameMenuNeeded; 
	bool textEntered;
	bool textBoxNeeded;
	BlackJackPlayer*  player;
	Dealer*  		  dealer;
	sf::RenderWindow* window;
	sf::Event event;
	bool mousePressed; 
	sf::Vector2i* mousePos;
	sf::Texture texture;
	sf::Sprite cardSprite;
	sf::Sprite hitSprite;
	sf::Sprite standSprite;
	sf::Sprite chip25Sprite;
	sf::Sprite chip100Sprite;
	sf::Sprite allInChipSprite;
	sf::Sprite resetBetSprite;
	sf::Sprite newGameSprite;
	sf::Sprite resumeSprite;
	sf::Font font;
	sf::Text text;
	void processEvents(); //used to handle all events that occur in the game
	void update(); 		  //will update the game based on events that occured
	void render();		  //shows changes to game to screen
	void restartHand(); 	 //resets hand
	void initializePlayer(); //will read data from "savedinfo.txt" if it exist into player on game
	void drawMenu();   		 //draw game menu when game is opened
	void drawButtons();      //draw buttons to screen
	void drawChips();        //draw chips to screen
	void drawNames();        //draw names to screen
	void drawEndResults();   //draw to screen whether player or dealer one hand 
	void drawValues();	     //draw the players values to screen
	void drawCards();        //draw cards to the screen
	void renderTextBox();    //draw text box to screen and any characters typed in
public:	
	static const int BET25 = 25;
	static const int BET100 = 100;
	Game(BlackJackPlayer& bjp, Dealer& d); //default constructor //sets up blackjack table graphics
	void run(); //will be used to play the game
	void saveGame(); //will save game information to a file called "savedinfo.txt"
	bool savedGameExists(); //will return true if there is a "savedinfo.txt" file for the game or false otherwise
	~Game(); //free allocated memory
};


#endif