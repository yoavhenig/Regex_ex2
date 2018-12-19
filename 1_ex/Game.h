#ifndef GAME_H
#define GAME_H
#include<vector>
#include "Player.h"
#include "Card.h"
using namespace std;

class Game {
private:
	//private members and functions
	Player* current_player;
	Player* _winner;
	Card current_card;
	int current_index;
	int p_num;
	vector<Player> v_players;

	void init();
	bool turn();
	void next();
	void specialNext();
	bool dir;
	void winPrint();

	Game(const Game& game){};
	Game operator=(const Game& game){return *this;} //prevent default copy

public:
	//public members and functions
	Game(){};
	void start();

	Card& getCurrentCard(){return current_card;}
};
#endif
