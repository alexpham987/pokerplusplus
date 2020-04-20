#include "player_game.h"


Player_Game::Player_Game(player_comm* pc) : _pc{pc} 
{
  
   boost::uuids::random_generator generator;
   boost::uuids::uuid id = generator();
   _id = id;

}

void Player_Game::setName(std::string name) { _name = name; }
	

//Changed this function a little to make it easier to use in mainwin
nlohmann::json Player_Game::move_j(std::string play, int cards_requested, int current_bet) const
{
  nlohmann::json to_dealer;
  chat_message uuid;
  std::string json_str;


  to_dealer["uuid"] = this->_id;
  to_dealer["name"] = this->_name;
  to_dealer["event"] = play;        // "stand","hit","fold","raise","join","request_cards"
  to_dealer["cards_requested"] = cards_requested;    // optional, number of cards requested, 1 to 5
  to_dealer["current_bet"] = current_bet;
  //to_dealer["total_bet"] = this->total_bet;
  //to_dealer["chat"] = std::string(chat);

  json_str = to_dealer.dump();

  uuid.body_length(std::strlen(json_str.c_str()));
  std::memcpy(uuid.body(), json_str.c_str(), uuid.body_length());
  uuid.encode_header();

  std::cout << json_str << std::endl;
  _pc->write(uuid);

  return to_dealer;

}

void Player_Game::exchange_j(std::string play, int cards_requested, std::vector<int> cards) 
{
  _hand.modify_hand(cards);

  nlohmann::json to_dealer;
  chat_message uuid;
  std::string json_str;


  to_dealer["uuid"] = this->_id;
  to_dealer["name"] = this->_name;
  to_dealer["event"] = "request_cards";        // "stand","hit","fold","raise","join","request_cards"
  to_dealer["cards_requested"] = cards_requested;    // optional, number of cards requested, 1 to 5
  to_dealer["current_bet"] = 0;
  //to_dealer["total_bet"] = this->total_bet;
  //to_dealer["chat"] = std::string(chat);

  json_str = to_dealer.dump();

  uuid.body_length(std::strlen(json_str.c_str()));
  std::memcpy(uuid.body(), json_str.c_str(), uuid.body_length());
  uuid.encode_header();

  std::cout << json_str << std::endl;
  _pc->write(uuid);
}





