#ifndef __DECK_H
#define __DECK_H

#include "card.h"
#include <vector>
#include <stdexcept>

class Deck {

	friend class Dealer_Game;

	public:
	  Deck();
	  Card deal();
	  int remaining_cards();
	  bool deck_empty();

	private:
	  std::vector<Card> _deck;

};

#endif
