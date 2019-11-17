#pragma once

#include "global.h"
#include <random>

namespace global
{
	Map* main_map = nullptr;
	Deck* main_deck = nullptr;
	vector<Player*>* players = nullptr;
	Actions* action = nullptr;
	int* supply;
	Player* random_player()
	{
		if(players != nullptr)
		{
			std::random_device rd;  //Will be used to obtain a seed for the random number engine
			std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
			std::uniform_int_distribution<int> dis(0, players->size());
			return players->at(dis(gen));
		}
		cout << "Error: random_player() was called but players are not set in global." << endl;
		return nullptr;
	}
	int random_range_int(int a, int b)
	{
		std::random_device rd;  //Will be used to obtain a seed for the random number engine
		std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
		std::uniform_int_distribution<int> dis(a, b);
		return dis(gen);
	}
	

}
