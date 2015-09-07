//game.cpp
//Game class implementation file

#include "game.hpp"
#include "SFML/Graphics.hpp"
#include "dealer.hpp"   //already includes other classes needed
#include <iostream>  //testing purposes
	using std::cout; //
	using std::endl;
#include <string>
	using std::string;
#include <fstream>
	using std::ofstream; 
	using std::ifstream;
#include <iomanip>
	using std::fixed;
	using std::setprecision;


//default constructor 
//sets up blackjack table graphics
Game::Game(BlackJackPlayer& bjp, Dealer& d)
{
	player = &bjp;
	dealer = &d;

	restartHand();

	//create window for game to be played on
	window = new sf::RenderWindow (sf::VideoMode(1600, 1000), "BlackJack"); 
	//set mouse pressed to false
	mousePressed = false;
	//set mouse starting position to (0,0)
	mousePos = new sf::Vector2i(0,0);
	//set font details
	if (!font.loadFromFile("fonts/arial.ttf")) //load font
	{
		//
		//
		std::cout << "Font Error"; //make an exception later
		//
		//
	}
	text.setFont(font); 
	text.setCharacterSize(40); 
	text.setColor(sf::Color::Black); 
	standPressed = false;
	betPlaced	 = false;
	hitPressed   = false;
	gameMenuNeeded = true;
	textEntered    = false;
	textBoxNeeded  = false;
	nameCharCount = 0;
} 

//where the game is played
void Game::run()
{	
	//if game is running
	while (window->isOpen()) 
	{
		processEvents();
		update();
		render();
	}

}

//used to handle all events that occur in the game
void Game::processEvents()
{
	mousePressed = false;
	//check for user input
	while (window->pollEvent(event)) 
	{
		//if user clicks close
		if (event.type == sf::Event::Closed) 
		{
			saveGame();
			window->close(); //close program
		}
		//if the user clicks in the program with their mouse
		if (event.type == sf::Event::MouseButtonPressed) 
		{
			*mousePos = sf::Mouse::getPosition(*window); //set mouse position to where they clicked
			mousePressed = true; 
		}
		//if the user enters text and the menu is still up
		if (event.type == sf::Event::TextEntered && textBoxNeeded)
		{
			textEntered = true;
		}
	}
}

//will update the game based on events that occured where the mechanics of the game are played
void Game::update()
{
	//if player runs out of money
	if (player->getScore() == 0 && mousePressed)
	{
		player->setScore(1000);
	}
	//if player gets blackjack 
	if ((player->getWorth() == 21 && dealer->getWorth() != 21) && mousePressed)
	{
		player->placeBet(Game::BET25 * 2); //win min bet times 2 + whatever has already been bet
		player->calcScore(true);
	}
	//if dealer gets blackjack 
	if ((dealer->getWorth() == 21 && player->getWorth() != 21) && mousePressed)
	{
		player->placeBet(Game::BET25 * 2); //lose min bet times 2 + whatever has already been bet
		player->calcScore(false);
	}
	//if round is over with no blackjack
	if ((dealer->getWorth() < 21 || player->getWorth() < 21) && mousePressed && standPressed)
	{
		restartHand(); 			//
		mousePressed = false;	//prepare for next round
		standPressed = false;	//
		betPlaced    = false;	//
		hitPressed   = false;	//
	}
	//if round is over with either a blackjack or a break
	if ((dealer->getWorth() >= 21 || player->getWorth() >= 21) && mousePressed)
	{
		restartHand(); 			//
		mousePressed = false;	//prepare for next round
		standPressed = false;	//
		betPlaced    = false;   //
		hitPressed   = false;   //
	}
	//if player pressed mouse button
	if (mousePressed) 
	{
		//if player presses new game button from start menu
		if (newGameSprite.getGlobalBounds().contains(static_cast<sf::Vector2f>(*mousePos)))
		{
			gameMenuNeeded = false;
			textBoxNeeded = true;
		}

		//if player presses resume button from start menu
		if (resumeSprite.getGlobalBounds().contains(static_cast<sf::Vector2f>(*mousePos)))
		{
			gameMenuNeeded = false; //close menu option
			if (savedGameExists())
			{
				initializePlayer();
			}
		}

		//if player pressed hit
		if (hitSprite.getGlobalBounds().contains(static_cast<sf::Vector2f>(*mousePos)) && betPlaced)
		{
			hitPressed = true;
			//only allow player to hit if their card total is less than 21
			if (player->getWorth() < 21)
			{
				player->hit(dealer->deal()); //call hit function
			}
			//if player hits 21 let dealer go
			if (player->getWorth() == 21)
			{
				//let dealer play his turn
				while (dealer->smartHitOrStay())
				{
					dealer->hit(dealer->deal());
				}
			}
			//if player hits 21 and dealer does not player won
			if (player->getWorth() == 21 && dealer->getWorth() != 21)
			{
				player->calcScore(true);
			}
			//if player goes over 21 they lose
			if (player->getWorth() > 21)
			{
				player->calcScore(false);
				//
				//add pause in
			}
		}
		//if player pressed stand
		if (standSprite.getGlobalBounds().contains(static_cast<sf::Vector2f>(*mousePos)) && betPlaced)
		{
			//let dealer play his turn if he hasnt already won
			if (dealer->getWorth() < player->getWorth() || (dealer->getWorth() == player->getWorth() && dealer->getWorth() < 17))
			{
				while (dealer->smartHitOrStay())
				{
					dealer->hit(dealer->deal());
				}
			}
			if (player->getWorth() < 21 && dealer->getWorth() < 21 && player->getWorth() > dealer->getWorth())
			{
				player->calcScore(true);
			}
			else if (player->getWorth() < 21 && dealer->getWorth() < 21 && player->getWorth() < dealer->getWorth())
			{
				player->calcScore(false);
			}
			//if dealer gets 21 and player does not player lost
			else if (dealer->getWorth() == 21 && player->getWorth() != 21)
			{
				player->calcScore(false);
			}
			else if (dealer->getWorth() == player->getWorth())
			{
				player->clearBet();
			}
			//if dealer goes over 21 player wins
			else //(dealer->getWorth() > 21)
			{
				player->calcScore(true);
			}
			standPressed = true;
		}
		//if player presses $25 chip
		if (chip25Sprite.getGlobalBounds().contains(static_cast<sf::Vector2f>(*mousePos)))
		{
			//only allow bet to be placed if they have enough money
			if (player->getBet() <= player->getScore() - Game::BET25)
			{
				player->placeBet(Game::BET25);
			}
			betPlaced = true;
		}
		//if player presses $100 chip
		if (chip100Sprite.getGlobalBounds().contains(static_cast<sf::Vector2f>(*mousePos)))
		{
			//only allow bet to be placed if they have enough money 
			if (player->getBet() <= player->getScore() - Game::BET100)
			{
				player->placeBet(Game::BET100);
			}
			betPlaced = true;
		}
		//if player presses All In Chip
		if (allInChipSprite.getGlobalBounds().contains(static_cast<sf::Vector2f>(*mousePos)))
		{
			player->clearBet(); //clear current bet
			player->placeBet(player->getScore()); //bet all money available
			betPlaced = true; 
		}
		//if player presses resetBet button and havnt called for a hit
		if (resetBetSprite.getGlobalBounds().contains(static_cast<sf::Vector2f>(*mousePos)) && !hitPressed)
		{
			player->clearBet(); //clear current bet
			betPlaced = false;
		}
		//if player presses hand
		if (cardSprite.getGlobalBounds().contains(static_cast<sf::Vector2f>(*mousePos)))
		{
			player->changeAceValue();
		}

		mousePressed = false;
	}
	//if player enters text
	else if (textBoxNeeded && textEntered)
	{
		//if text is a printable character
		if (event.text.unicode < 128 && nameCharCount < 16)
		{
			player->setName(player->getName() + static_cast<char>(event.text.unicode)); //add text to players name
			textEntered = false;
			nameCharCount += 1;
			if (static_cast<char>(event.text.unicode) == '\n')
			{
				textBoxNeeded = false;
			}	
			if (static_cast<char>(event.text.unicode) == '\b')
			{
				//doesnt work try new implementation
				//
				/*string temp = player->getName();
				temp = temp.substr(0, temp.size()-1);
				std::cout << temp << std::endl;
				player->setName(temp);*/
				/*string temp = player->getName();
				char* tempChar = new char [temp.size()]
				for (unsigned i = 0; i < temp.size(); i++)
				{
					char
				}
				delete [] tempChar;*/

				player->setName("");
				nameCharCount -= 1;
				//
				//
			}
		}
		else
		{
			textBoxNeeded = false;
			textEntered   = false;
		}
	}


}

//shows changes to game to screen
void Game::render()
{
	//clear screen with color of blackjack table (green)
	window->clear(sf::Color::Green); 

	if (gameMenuNeeded) //if game just started
	{
		drawMenu(); //draw first menu to screen when game starts
	}
	else if (textBoxNeeded)
	{
		renderTextBox();
	}
	else //if game menu is done
	{
		text.setColor(sf::Color::Black);
		text.setCharacterSize(40);
		drawButtons(); //draw hit button, stand button, and reset button to screen
		drawChips();   //draw $25, $100, and allinChip to screen
		drawNames();   //draw players names to screen
		drawEndResults(); //draw to screen who won round or whether player has money left
		drawValues();     //draw player values to screen
		drawCards();	  //draw players cards to screen
	}

	//show window
	window->display();
}

//private function used to clear hand and give new cards
void Game::restartHand()
{
	player->clear(); //clear players hand
	dealer->clear(); //clear dealers hand
	dealer->shuffle(); //shuffle deck
	for (int i = 0; i < 2; i++) //deal 2 cards to start with
	{
		player->drawCard(dealer->deal()); //give player 2 cards
		dealer->drawCard(dealer->deal()); //give dealer 2 cards
	}

	//if value is 11 make sure hand doesnt have ace to make it 21 for dealer
	if (dealer->getWorth() == 11)
	{
		dealer->changeAceValue();
	}

	//if value is 11 make sure hand doesnt have ace to make it 21 for player
	if (player->getWorth() == 11)
	{
		player->changeAceValue();
	}
}

//will save game information to a file called "savedinfo.txt"
//first line will hold player name and the second line will hold the amount of cash the player currently has
void Game::saveGame()
{
	ofstream writeFile("savedinfo.txt"); //create or open file if it already exist
	writeFile << player->getName() << endl;
	writeFile << setprecision(2) << fixed << player->getScore() << endl;
	writeFile.close(); //close file when done
}

//will return true if there is a "savedinfo.txt" file for the game or false otherwise
bool Game::savedGameExists()
{
	bool exists = false;
	ifstream readFile("savedinfo.txt");
	if (readFile.is_open())
	{
		exists = true;
	}
	readFile.close();
	return exists;
}

//will read data from "savedinfo.txt" if it exist into player on game
void Game::initializePlayer()
{
	ifstream readFile("savedinfo.txt");
	if (readFile.is_open())
	{
		string name;
		getline(readFile, name);
		player->setName(name);
		double score;
		readFile >> score;
		player->setScore(score);
	}
	readFile.close();
}

//draw game menu when game is opened
void Game::drawMenu()
{
	//draw border of option menu
	sf::RectangleShape border(sf::Vector2f(1100.0f, 600.0f));
	border.setFillColor(sf::Color::Black);
	border.setPosition(sf::Vector2f(250.0f, 200.0f));
	window->draw(border);
	//

	//draw text "Menu" above options
	text.setString("Menu\n");
	text.setPosition(sf::Vector2f(700.0f, 300.0f));
	text.setCharacterSize(80);
	text.setColor(sf::Color::Red);
	window->draw(text);

	//draw new game button
	if (!texture.loadFromFile("images/newgamebutton.png")) //load image
	{
		//
		//
		std::cout << "New Game Button Error."; //make exception later
		//
		//
	}
	newGameSprite.setTexture(texture); //create button sprite
	newGameSprite.setScale(sf::Vector2f(.5f, .95f));            //set size
	newGameSprite.setPosition(sf::Vector2f(400.0f, 490.0f));   //set postion
	window->draw(newGameSprite);
	//
	//

	//draw resume game button
	if (!texture.loadFromFile("images/resume.png")) //load image
	{
		//
		//
		std::cout << "Resume Game Button Error."; //make exception later
		//
		//
	}
	resumeSprite.setTexture(texture); //create button sprite
	resumeSprite.setScale(sf::Vector2f(2.3f, 2.2f));            //set size
	resumeSprite.setPosition(sf::Vector2f(900.0f, 500.0f));   //set postion
	window->draw(resumeSprite);
	//
	//
}

//draw text box to screen and any characters typed in
void Game::renderTextBox()
{
	//draw border of option menu
	sf::RectangleShape border(sf::Vector2f(1100.0f, 600.0f));
	border.setFillColor(sf::Color::Red);
	border.setPosition(sf::Vector2f(250.0f, 200.0f));
	window->draw(border);
	//
	//
	sf::RectangleShape textBorder(sf::Vector2f(900.0f, 100.0f));
	textBorder.setFillColor(sf::Color::White);
	textBorder.setPosition(sf::Vector2f(350.0f, 420.0f));
	window->draw(textBorder);
	//
	
	//draw text to screen
	text.setColor(sf::Color::Black);
	text.setCharacterSize(40);
	text.setString(player->getName());
	text.setPosition(sf::Vector2f(365.0f, 445.0f));
	window->draw(text);
	//
	}

//draw buttons to screen
void Game::drawButtons()
{
	//
	//draw hit button
	if (!texture.loadFromFile("images/hit.png")) //load image
	{
		//
		//
		std::cout << "Hit Error."; //make exception later
		//
		//
	}
	hitSprite.setTexture(texture); //create button sprite
	hitSprite.setScale(sf::Vector2f(2.0f,2.0f));            //set size
	hitSprite.setPosition(sf::Vector2f(1300.0f, 600.0f));   //set postion
	window->draw(hitSprite);
	//
	//

	//
	//draw stand button
	if (!texture.loadFromFile("images/stand.png")) //load image
	{
		//
		//
		std::cout << "Stand Error"; //make exception later
		//
		//
	}
	standSprite.setTexture(texture); //create button sprite
	standSprite.setScale(sf::Vector2f(2.0f,2.0f));  
	standSprite.setPosition(sf::Vector2f(1300.0f, 725.0f));  //set postion
	window->draw(standSprite);
	//
	//

	//
	//draw resetBet button
	if (!texture.loadFromFile("images/reset.png")) //load image
	{
		//
		//
		std::cout << "Reset Error"; //make exception later
		//
		//
	}
	resetBetSprite.setTexture(texture); //create all in chip sprite
	resetBetSprite.setScale(sf::Vector2f(.47f,.47f));  
	resetBetSprite.setPosition(sf::Vector2f(840.0f, 800.0f));  //set postion
	window->draw(resetBetSprite);
	//
	//
}

//draw chips to screen
void Game::drawChips()
{
	//
	//draw $25 chip button
	if (!texture.loadFromFile("images/PokerChip25.png")) //load image
	{
		//
		//
		std::cout << "Chip Error"; //make exception later
		//
		//
	}
	chip25Sprite.setTexture(texture); //create $25 chip sprite
	chip25Sprite.setScale(sf::Vector2f(.3f,.3f));  
	chip25Sprite.setPosition(sf::Vector2f(700.0f, 625.0f));  //set postion
	window->draw(chip25Sprite);
	//
	//

	//
	//draw $100 chip button
	if (!texture.loadFromFile("images/PokerChip100.gif")) //load image
	{
		//
		//
		std::cout << "Chip Error"; //make exception later
		//
		//
	}
	chip100Sprite.setTexture(texture); //create $100 chip sprite
	chip100Sprite.setScale(sf::Vector2f(1.3f,1.3f));  
	chip100Sprite.setPosition(sf::Vector2f(900.0f, 620.0f));  //set postion
	window->draw(chip100Sprite);
	//
	//

	//
	//draw all in chip button
	if (!texture.loadFromFile("images/AllInChip.png")) //load image
	{
		//
		//
		std::cout << "Chip Error"; //make exception later
		//
		//
	}
	allInChipSprite.setTexture(texture); //create all in chip sprite
	allInChipSprite.setScale(sf::Vector2f(.47f,.47f));  
	allInChipSprite.setPosition(sf::Vector2f(1100.0f, 625.0f));  //set postion
	window->draw(allInChipSprite);
	//
	//
}

//draw names to screen
void Game::drawNames()
{
	//draw names to screen
	text.setString(dealer->getName()); //holds dealer name
	text.setPosition(sf::Vector2f(85.0f, 40.0f)); //i think is good for bottom player
	window->draw(text);
	text.setString(player->getName()); //will hold name of user
	text.setPosition(sf::Vector2f(85.0f, 870.0f)); //i think is good for top user
	window->draw(text);
	//
}

//draw to screen whether player or dealer one hand 
void Game::drawEndResults()
{
	//if dealer gets blackjack draw blackjack to dealer screen
	if (dealer->getWorth() == 21 && player->getWorth() != 21)
	{
		text.setString("BlackJack");
		text.setPosition(sf::Vector2f(485.0f, 40.0f)); //i think is good for top player
		window->draw(text);
		//inform user they lost
		text.setString("You Lost."); 
		text.setPosition(sf::Vector2f(485.0f, 470.0f)); //i think is 
		window->draw(text);
	}
	//

	//if player gets blackjack draw blackjack to player screen
	if (player->getWorth() == 21 && dealer->getWorth() != 21)
	{
		text.setString("BlackJack");
		text.setPosition(sf::Vector2f(485.0f, 870.0f)); //i think is good bottom player
		window->draw(text);
		//inform user they won
		text.setString("You Won!"); 
		text.setPosition(sf::Vector2f(485.0f, 470.0f)); //i think is good 
		window->draw(text);
	}
	//

	//if player breaks they lose and print to screen player lost
	if (player->getWorth() > 21)
	{
		text.setString("You Lost."); 
		text.setPosition(sf::Vector2f(485.0f, 470.0f)); //i think is good 
		window->draw(text);
	}

	//if dealer breaks player wins and print to screen player won
	if (dealer->getWorth() > 21)
	{
		text.setString("You Won!"); 
		text.setPosition(sf::Vector2f(485.0f, 470.0f)); //i think is good 
		window->draw(text);
	}

	//if dealer is done playing compare value to see who wins
	if (dealer->getWorth() < 21 && standPressed)
	{
		//if dealer beats player print to screen telling player they lost
		if (dealer->getWorth() > player->getWorth())
		{
			text.setString("You Lost."); 
			text.setPosition(sf::Vector2f(485.0f, 470.0f)); //i think is good 
			window->draw(text);
		}
		//if dealer ties player print to screen a tie has occured
		else if (dealer->getWorth() == player->getWorth() && standPressed)
		{
			text.setString("Tie."); 
			text.setPosition(sf::Vector2f(485.0f, 470.0f)); //i think is good 
			window->draw(text);
		}
		//if player beats dealer let player know they won
		else
		{
			text.setString("You Won!"); 
			text.setPosition(sf::Vector2f(485.0f, 470.0f)); //i think is good 
			window->draw(text);
		}
	}

	//tell player if they are out of money
	if (player->getScore() == 0)
	{
		text.setString("Game Over!\nClick anywhere to play again."); 
		text.setPosition(sf::Vector2f(485.0f, 515.0f)); //i think is good 
		window->draw(text);
	}
}

//draw the players values to screen
//value of players hands
//players total money amount and money bet amount
void Game::drawValues()
{
	//draw value of the players hands to screen
	if (standPressed || player->getWorth() >= 21 || dealer->getWorth() == 21) //if player is done playing show dealers score
	{
		text.setString(std::to_string(dealer->getWorth()));		////
		text.setPosition(sf::Vector2f(85.0f, 40.0f + 160.0f));  //draw dealers 
		window->draw(text);										////
	}
	//////////////////////////////////////////////////////////////////////
	text.setString(std::to_string(player->getWorth()));		////
	text.setPosition(sf::Vector2f(85.0f, 870.0f - 160.0f)); //draw players
	window->draw(text);										////
	//

	//draw players total money amount to screen
	text.setString("Money:");					//
	text.setPosition(sf::Vector2f(1300.0f, 40.0f));	//draw the text "Score:"
	window->draw(text);								//
	/////////////////////////////////////////////////////////////////////////////////////
	text.setString("$ " + std::to_string(player->getScore())); //
	text.setPosition(sf::Vector2f(1300.0f, 80.0f));	   	   	   //draw the players score to screen
	window->draw(text);								           //	
	//

	//draw players money bet to screen
	text.setString("Pot:");					//
	text.setPosition(sf::Vector2f(1300.0f, 120.0f));	//draw the text "Pot:"
	window->draw(text);	
	/////////////////////////////////////////////////////////////////////////////////////
	text.setString("$ " + std::to_string(player->getBet())); //
	text.setPosition(sf::Vector2f(1300.0f, 160.0f));	       //draw the players pot to screen
	window->draw(text);								           //	
	//
}

//draw cards to the screen
void Game::drawCards()
{
	//draw cards to screen
	if (standPressed || player->getWorth() >= 21 || dealer->getWorth() == 21) //if player is done playing
	{
		dealer->show(cardSprite, window, texture, dealer, true);
	}
	else //player is still playing
	{
		dealer->show(cardSprite, window, texture, dealer, false);
	}
	player->show(cardSprite, window, texture, player);
	//
}

//free allocated memory
Game::~Game()
{
	delete window;
	window = nullptr;
	delete mousePos;
	mousePos = nullptr;
	/*delete player;
	player = nullptr;
	delete dealer;
	dealer = nullptr;*/
}
