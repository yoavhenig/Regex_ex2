#include "Player.h"


bool Player::play(Card& current_card){
  int move;
  std::cout << getName() <<", your turn - "<< '\n';
  std::cout << "Your cards: ";
  for (size_t i = 0; i <v_cards.size(); i++) {
    std::cout << "("<<i+1<<")"<<v_cards.at(i) <<" ";
  }
  std::cout << '\n';
  std::cin >> move;

    while((move>0)&&(move<=(int)v_cards.size())&&!current_card.is_leggal(v_cards.at(move-1))){
      std::cout << "You can't put "<<v_cards.at(move-1)<<" on "<<current_card << '\n';
      std::cin >> move; //waiting for another input
    }
    if(move>(int)v_cards.size()||move<=0){
      v_cards.push_back(generate_card());
      return 0;
    }
    else{
      current_card=v_cards.at(move-1);
      v_cards.erase(v_cards.begin()+(move-1));
    }
  return 1;
};

bool Player::_isWinner(){
  if(v_cards.size()==0){return true;}
  return false;
}
