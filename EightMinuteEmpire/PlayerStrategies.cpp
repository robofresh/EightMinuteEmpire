#include "PlayerStrategies.h"
#include "global.h"

using namespace std;




void Human::execute(Player& p)
{
	

}


void Greedy::execute(Player& p)
{

	cout << "\tThe greedy computer will try to destroy armies or create cities." << endl;

	//go through all face-up cards
	for(auto i : *global::main_deck->cardsSpace->faceupcards)
	{
		//go through all actions of face-up cards
		for(auto j : *i->actions)
		{
			//do action if any card has them
			if (*j == "destroyArmies")
			{
				cout << "\tSelected card: " << endl;
				i->print();
				global::action->computer_action(p, *i);
				return;
			}
			if (*j == "createCity")
			{
				cout << "\tSelected card: " << endl;
				i->print();
				global::action->computer_action(p, *i);
				return;
			}
		}
	}
	//if no face-up card has destroyArmies or createCity, choose the first one (cheapest) and do it's action
	cout << "\tThe greedy computer did not find any destroy armies or create city cards." << endl;
	cout << "\tIt will take the cheapest one." << endl;
	global::action->computer_action(p, *global::main_deck->cardsSpace->faceupcards->at(0));
	
}

void Moderate::execute(Player& p)
{
	cout << "\tThe moderate computer will try to place armies to control regions." << endl;

	//go through all face-up cards
	for (auto i : *global::main_deck->cardsSpace->faceupcards)
	{
		//go through all actions of face-up cards
		for (auto j : *i->actions)
		{
			//do action if any card has them
			if (*j == "placeArmies")
			{
				cout << "\tSelected card: " << endl;
				i->print();
				global::action->computer_action(p, *i);
				return;
			}
		}
	}
	//if no face-up card has destroyArmies or createCity, choose the first one (cheapest) and do it's action
	cout << "\tThe moderate computer did not find any place army cards." << endl;
	cout << "\tIt will take the cheapest one." << endl;
	global::action->computer_action(p, *global::main_deck->cardsSpace->faceupcards->at(0));
}






Human::Human()
{
	type = new string("human");
}

Greedy::Greedy()
{
	type = new string("greedy");
}

Moderate::Moderate()
{
	type = new string("moderate");
}

Human::~Human()
{
	delete type;
}

Greedy::~Greedy()
{
	delete type;
}

Moderate::~Moderate()
{
	delete type;
}