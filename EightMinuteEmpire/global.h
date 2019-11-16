#pragma once

#include "Player.h"
#include "Actions.h"

namespace global
{
	extern Map* main_map;
	extern Deck* main_deck;
	extern vector<Player*>* players;
	extern Actions* action;
	extern Player* random_player();
	extern int random_range_int(int, int);
}