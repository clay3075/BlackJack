//gamepractice.cpp

#include "game.hpp" //inludes all class include files needed for game
#include <string>
	using std::string;
#include <iostream>
	using std::cin;
	using std::cout;
#include <ctime>
#include <cstdlib>

const double STARTING_CASH = 1000.00;
int main()
{
	srand(time(0)); //seed random generator

	string name = "";

	BlackJackPlayer player(name, STARTING_CASH); //create player object
	Dealer dealer; //create dealer object

	Game game(player, dealer);	//create game object
	game.run(); //play game
	return 0;
}