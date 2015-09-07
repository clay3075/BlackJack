blackjack.app : card.o deck.o hand.o player.o blackjackplayer.o dealer.o game.o
	g++ -o blackjack.app -lsfml-graphics -lsfml-window -lsfml-system gamepractice.cpp game.o dealer.o blackjackplayer.o player.o hand.o deck.o card.o
card.o : card.cpp
	g++ -Wall -Wextra -std=c++11 -pedantic -c card.cpp
deck.o : deck.cpp
	g++ -Wall -Wextra -std=c++11 -pedantic -c deck.cpp
hand.o : hand.cpp
	g++ -Wall -Wextra -std=c++11 -pedantic -c hand.cpp
player.o : player.cpp
	g++ -Wall -Wextra -std=c++11 -pedantic -c player.cpp
blackjackplayer.o : blackjackplayer.cpp
	g++ -Wall -Wextra -std=c++11 -pedantic -c blackjackplayer.cpp
dealer.o : dealer.cpp
	g++ -Wall -Wextra -std=c++11 -pedantic -c dealer.cpp
game.o : game.cpp
	g++ -Wall -Wextra -std=c++11 -pedantic -c game.cpp