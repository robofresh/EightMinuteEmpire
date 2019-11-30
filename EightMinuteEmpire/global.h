#pragma once

#include "Player.h"
#include "Actions.h"

namespace global
{
	extern Map* map;
	extern Deck* main_deck;
	extern vector<Player*>* players;
	extern Actions* action;
	extern Player* currentPlayer;
	extern int* currentPlayerIndex;
	extern int* supply;
	extern Player* random_player();
	extern int random_range_int(int, int);
	extern const string COLORS[5] ;
}