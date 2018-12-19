#ifndef PLAYER_H
#define PLAYER_H
#include<vector>
#include "Card.h"
using namespace std;

class Player {
private:
	string name;
	int num_of_cards;
	//vector of cards
	vector<Card> v_cards;
	//private members

public:
	//public members
	Player(string name, const int num_of_cards):name(name),num_of_cards(num_of_cards){
		for (auto i = 0; i < num_of_cards; i++) {
			Card temp=generate_card();
			this->v_cards.push_back(temp);
		}
	};

	Player(const Player& player){
		this->name=player.name; this->num_of_cards=player.num_of_cards;
		for (int i = 0; i < num_of_cards; i++) {
			this->v_cards.push_back(player.v_cards.at(i));
		}
	};

	Player(){
		num_of_cards=0;

	};

	Player operator=(const Player& player) {
		this->name=player.name; this->num_of_cards=player.num_of_cards;
		for (int i = 0; i < num_of_cards; i++) {
			this->v_cards.push_back(player.v_cards.at(i));
		}
		return *this;
	};

	string getName()const {return this->name;}
	bool play(Card&);
	bool _isWinner();
};
#endif
