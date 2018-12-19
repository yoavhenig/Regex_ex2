#include "Game.h"

inline void verify(int c_p_num){// check the players or cards positive
  if(c_p_num<=0){
    //throw invalid_argument("illeggal numbers of players or cards! must be bigger than 0");
    throw 20;
  }
}


void Game::init(){
  cout << "How many players?" << '\n';
  cin >> p_num; //private member p_num is players
  verify(p_num);
  int c_num;
  std::cout << "How many cards?" << '\n';
  std::cin >> c_num;
  verify(c_num);
  current_index=0; //first player
  dir=0;  //direction is forward
  for (auto i = 0; i < p_num; i++) {
    string name;
    cout << "player number "<<i+1<<" name?\n";
    cin >> name;
    Player p(name, c_num);
    v_players.push_back(p);
  }
  current_card=generate_card(); //init first card
  current_player=&v_players.at(current_index); //init first player - the first place at v_players
}

bool Game::turn(){
  return current_player->play(current_card);
}

void Game::specialNext(){
  if(dir==0){current_index=(current_index+1)%p_num;}
  if(dir==1){current_index=(current_index-1+p_num)%p_num;}

  current_player=&v_players.at(current_index);
}

void Game::next(){  //check who is next method
  if(current_card.get_sign()!=PLUS){
    if(current_card.get_sign()==CD){
      dir=!dir;  //the direction is backward
    }

    if(dir==0){
      if(current_card.get_sign()==STOP){
        current_index=(current_index+2)%p_num;
      }
      else{current_index=(current_index+1)%p_num;}
    }

    if(dir==1){
      if(current_card.get_sign()==STOP){
        current_index=(current_index-2+p_num)%p_num;
      }
      else{current_index=(current_index-1+p_num)%p_num;}
    }
}
  current_player=&v_players.at(current_index);

}

void Game::winPrint(){
    cout << _winner->getName()<<" wins!" << '\n';
}


void Game::start(){
  _winner=NULL; //no one is winner at that point
try{
  init(); //method to start the game and restart fields
}
catch(int e){return;}
  while(!_winner){
    std::cout << "current: " <<current_card<<'\n';
      if(turn()){
        if(current_player->_isWinner()){
            _winner=current_player;
        }
        next();
      }
      else{
        if(current_player->_isWinner()){
            _winner=current_player;
        }
        specialNext();
      }
  }
  winPrint();

};
