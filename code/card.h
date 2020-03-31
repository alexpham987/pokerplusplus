#ifndef __CARD_H
#define __CARD_H

#include <string>
#include <vector>
#include <stdexcept>
#include <sstream>
#include <map>
#include <iostream>
#include <gtkmm.h>

enum Suit {C,D,H,S};

const int MAX_SUIT = 4;
const int MIN_NUM = 2;
const int MAX_NUM = 13;

class Card {

  public:
	Card(int num, Suit suit);
	int num () const;
	Suit suit() const;
	int compareCard(Card C);
	std::string card_to_string();
	std::string card_to_filename();
	
  private:
	int _num;
	Suit _suit;
	Gtk::Image *cardimage;
};

#endif
