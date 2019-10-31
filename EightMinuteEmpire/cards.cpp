#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <exception>
#include "Player.h"
#include "Cards.h"

using namespace std;


/* 

format of actions:

string = "action" + # + ("AND" or "OR") + "action2" + #
- # and "AND/OR" are optional, but if there is "AND/OR" there must be an "action2"
- at least one action is required

*/


Cards::Cards(string good1, vector<string*>* action1)
{
	good = new string (good1);
	actions = action1;
}

//destructor
Cards::~Cards(){}

void addCards(Deck*);

Deck::Deck()
{
	drawingcards = new Hand(this);
	stackofCards = new stack <Cards*>; //in deck, there are 42 cards. they will be stacked
	addCards(this);
	//print();
}

void Deck::draw()
{
	Cards* temp = stackofCards->top(); 
	drawingcards->faceupcards->push_back(temp);
	stackofCards->pop();
}

//destructor
Deck::~Deck(){}

Hand::Hand(Deck* deck)
{
	faceupcards = new vector <Cards*>();
	mainDeck = deck;
}

//destructor
Hand::~Hand(){}

Cards* Hand::exchange(int index)
{
	cout << "selected " << index << endl;
	Cards* tmp = faceupcards->at(index);
	faceupcards->erase(faceupcards->begin() + index);
	mainDeck->draw();
	return tmp;
}

void Hand::print()
{
	for (int i = 0; i < 6; i++)
	{
		cout << *faceupcards->at(i)->good << endl;
	}
}

void Deck::initialDraw() //one time only, when the game is started
{
	for (int i = 0; i < 6; i++) {
		draw();
	}
}

void Deck::print()
{
	stack<Cards*> tmp;
	tmp = *stackofCards;
	while(!tmp.empty()) // this is messed up
	{
		cout << *tmp.top()->good << endl;
		tmp.pop();
	}
}


void addCards(Deck* deck)
{
	//wild, create 2 armies
	deck->stackofCards->push
	(
		new Cards(
			"wild",
			new vector<string*>
			{
				new string("waterMove"), new string("2")
			}
		)
	);

	//gem, create 2 armies
	deck->stackofCards->push
	(
		new Cards(
			"gem", 
			new vector<string*>  
			{
				new string("placeArmies"), new string("2")
			}
		)
	);

	deck->stackofCards->push
	(
		new Cards(
			"coal",
			new vector<string*>
			{
				new string("placeArmies"), new string("3")
			}
		)
	);

	deck->stackofCards->push
	(
		new Cards(
			"coal",
			new vector<string*>
			{
				new string("waterMove"), new string("2")
			}
		)
	);

	deck->stackofCards->push
	(
		new Cards(
			"coal",
			new vector<string*>
			{
				new string("waterMove"), new string("2")
			}
		)
	);

	deck->stackofCards->push
	(
		new Cards(
			"coal",
			new vector<string*>
			{
				new string("waterMove"), new string("3")
			}
		)
	);

	deck->stackofCards->push
	(
		new Cards(
			"coal",
			new vector<string*>
			{
				new string("move"), new string("2")
			}
		)
	);

	deck->stackofCards->push
	(
		new Cards(
			"gem",
			new vector<string*>
			{
				new string("placeArmies"), new string("2")
			}
		)
	);

	deck->stackofCards->push
	(
		new Cards(
			"coal",
			new vector<string*>
			{
				new string("placeArmies"), new string("2"), new string("OR"), new string("createCity"),  new string("1")
			}
		)
	);

	deck->stackofCards->push
	(
		new Cards(
			"coal",
			new vector<string*>
			{
				new string("placeArmies"), new string("3")
			}
		)
	);

	deck->stackofCards->push
	(
		new Cards(
			"carrot",
			new vector<string*>
			{
				new string("move"), new string("5")
			}
		)
	);

	deck->stackofCards->push
	(
		new Cards(
			"carrot",
			new vector<string*>
			{
				new string("move"), new string("4")
			}
		)
	);

	deck->stackofCards->push
	(
		new Cards(
			"carrot",
			new vector<string*>
			{
				new string("placeArmies"), new string("3")
			}
		)
	);

	deck->stackofCards->push
	(
		new Cards(
			"tree",
			new vector<string*>
			{
				new string("move"), new string("3")
			}
		)
	);

	deck->stackofCards->push
	(
		new Cards(
			"wild",
			new vector<string*>
			{
				new string("placeArmies"), new string("2")
			}
		)
	);

	deck->stackofCards->push
	(
		new Cards(
			"carrot",
			new vector<string*>
			{
				new string("creatCity"), nullptr
			}
		)
	);

	deck->stackofCards->push
	(
		new Cards(
			"carrot",
			new vector<string*>
			{
				new string("destroyArmies"), new string("1"), new string("AND"), new string("placeArmies"), new string("1")
			}
		)
	);

	deck->stackofCards->push
	(
		new Cards(
			"gem",
			new vector<string*>
			{
				new string("placeArmies"), new string("2")
			}
		)
	);

	deck->stackofCards->push
	(
		new Cards(
			"gem",
			new vector<string*>
			{
				new string("placeArmies"), new string("1")
			}
		)
	);

	deck->stackofCards->push
	(
		new Cards(
			"gem",
			new vector<string*>
			{
				new string("move"), new string("2")
			}
		)
	);

	deck->stackofCards->push
	(
		new Cards(
			"tree",
			new vector<string*>
			{
				new string("placeArmies"), new string("2"), new string("OR"), new string("move"), new string("3")
			}
		)
	);

	deck->stackofCards->push
	(
		new Cards(
			"tree",
			new vector<string*>
			{
				new string("destroyArmies"), new string("1"), new string("OR"), new string("createCity"), new string("1")
			}
		)
	);

	deck->stackofCards->push
	(
		new Cards(
			"tree",
			new vector<string*>
			{
				new string("placeArmies"), new string("3")
			}
		)
	);

	deck->stackofCards->push
	(
		new Cards(
			"tree",
			new vector<string*>
			{
				new string("move"), new string("6")
			}
		)
	);

	deck->stackofCards->push
	(
		new Cards(
			"tree",
			new vector<string*>
			{
				new string("waterMove"), new string("4")
			}
		)
	);

	deck->stackofCards->push
	(
		new Cards(
			"tree",
			new vector<string*>
			{
				new string("createCity"), new string("1")
			}
		)
	);

	deck->stackofCards->push
	(
		new Cards(
			"tree",
			new vector<string*>
			{
				new string("waterMove"), new string("3")
			}
		)
	);

	deck->stackofCards->push
	(
		new Cards(
			"anvil",
			new vector<string*>
			{
				new string("placeArmies"), new string("3")
			}
		)
	);

	deck->stackofCards->push
	(
		new Cards(
			"anvil",
			new vector<string*>
			{
				new string("placeArmies"), new string("3")
			}
		)
	);

	deck->stackofCards->push
	(
		new Cards(
			"anvil",
			new vector<string*>
			{
				new string("move"), new string("3")
			}
		)
	);

	deck->stackofCards->push
	(
		new Cards(
			"anvil",
			new vector<string*>
			{
				new string("createCity"), new string("1")
			}
		)
	);

	deck->stackofCards->push
	(
		new Cards(
			"anvil",
			new vector<string*>
			{
				new string("placeArmies"), new string("3"), new string("OR"), new string("move"), new string("3")
			}
		)
	);

	deck->stackofCards->push
	(
		new Cards(
			"anvil",
			new vector<string*>
			{
				new string("move"), new string("4")
			}
		)
	);

	deck->stackofCards->push
	(
		new Cards(
			"anvil",
			new vector<string*>
			{
				new string("placeArmies"), new string("3"), new string("OR"), new string("move"), new string("4")
			}
		)
	);

	deck->stackofCards->push
	(
		new Cards(
			"anvil",
			new vector<string*>
			{
				new string("move"), new string("5")
			}
		)
	);

	deck->stackofCards->push
	(
		new Cards(
			"anvil2",
			new vector<string*>
			{
				new string("move"), new string("4")
			}
		)
	);

	deck->stackofCards->push
	(
		new Cards(
			"carrot",
			new vector<string*>
			{
				new string("createCity"), new string("1")
			}
		)
	);

	deck->stackofCards->push
	(
		new Cards(
			"carrot",
			new vector<string*>
			{
				new string("move"), new string("4")
			}
		)
	);



	deck->stackofCards->push
	(
		new Cards(
			"carrot",
			new vector<string*>
			{
				new string("moveWater"), new string("3")
			}
		)
	);

	deck->stackofCards->push
	(
		new Cards(
			"carrot2",
			new vector<string*>
			{
				new string("placeArmies"), new string("3")
			}
		)
	);

	deck->stackofCards->push
	(
		new Cards(
			"carrot",
			new vector<string*>
			{
				new string("move"), new string("4")
			}
		)
	);

	deck->stackofCards->push
	(
		new Cards(
			"carrot",
			new vector<string*>
			{
				new string("createCity"), new string("1")
			}
		)
	);

	deck->stackofCards->push
	(
		new Cards(
			"carrot",
			new vector<string*>
			{
				new string("placeArmies"), new string("4"), new string("OR"), new string("move"), new string("2")
			}
		)
	);
}