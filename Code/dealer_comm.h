#ifndef DEALER_COMM_H
#define DEALER_COMM_H

#include <cstdlib>
#include <deque>
#include <iostream>
#include <list>
#include <memory>
#include <set>
#include <utility>
#include <chrono>
#include "asio.hpp"
#include "chat_message.hpp"
#include "dealer_game.h"

using asio::ip::tcp;

//----------------------------------------------------------------------

typedef std::deque<chat_message> chat_message_queue;

//----------------------------------------------------------------------

class chat_participant
{
public:
	virtual ~chat_participant() {}
	virtual void deliver(const chat_message& msg) = 0;
};

typedef std::shared_ptr<chat_participant> chat_participant_ptr;

class chat_room
{
  public:
	void join(chat_participant_ptr participant);
	void leave(chat_participant_ptr participant);
	void deliver(const chat_message& msg);
	std::set<chat_participant_ptr> participants();
	void setDeck(Deck deck);

  private:	
	std::set<chat_participant_ptr> participants_;
	enum { max_recent_msgs = 100 };
	chat_message_queue recent_msgs_;
	Deck _deck;
	Dealer_Game _dg{_deck};
};


class chat_session 
	: public chat_participant, 
	  public std::enable_shared_from_this<chat_session>
{
  public:
	chat_session(tcp::socket socket, chat_room& room);
	void start();
	void deliver(const chat_message& msg);

  private:
	void do_read_header();
	void do_read_body();
	void do_write();
	tcp::socket socket_;
	chat_room& room_;
	chat_message read_msg_;
	chat_message_queue write_msgs_;
	Deck _deck;
	Dealer_Game _dg{_deck};

};

class Dealer_comm
{
  public:
	Dealer_comm(asio::io_context& io_context,
	    const tcp::endpoint& endpoint);
	void startGame();

  private:
	void do_accept();
	tcp::acceptor acceptor_;
	chat_room room_;

};

	

	
#endif
