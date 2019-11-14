#include "PlayerStrategies.h"
#include "global.h"

void Strategy::computer_action(const Cards&)
{
	
}


void Human::execute(const Player& p)
{
	

}


void Greedy::execute(const Player& p)
{
	//go through all face-up cards
	for(auto i : *global::main_deck->cardsSpace->faceupcards)
	{
		//go through all actions of face-up cards
		for(auto j : *i->actions)
		{
			//do action if any card has them
			if (*j == "destroyArmies")
			{
				computer_action(*i);
				return;
			}
			if (*j == "createCity")
			{
				computer_action(*i);
				return;
			}
		}
	}
	//if no face-up card has destroyArmies or createCity, choose the first one (cheapest) and do it's action
	computer_action(*global::main_deck->cardsSpace->faceupcards->at(0));
	
}

void Moderate::execute(const Player& p)
{
	
}
