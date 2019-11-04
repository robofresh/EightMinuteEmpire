#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>
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

//Default constructor
Cards::Cards()
{
	good = new string("");
	actions = new vector<string*>();
}

//Constructor with attributes for goods and action
Cards::Cards(string good1, vector<string*>* action1)
{
	good = new string (good1);
	actions = action1;
}

//Destructor
Cards::~Cards()
{
	delete good, actions;
	good = NULL;
	actions = NULL;
}

void shuffleAndAddCards(Deck*);

//Default constructor
Deck::Deck()
{
	drawingcards = new Hand(this);
	stackofCards = new stack <Cards*>; //in deck, there are 42 cards. they will be stacked
	shuffleAndAddCards(this); //Add Cards into the deck
	//print();
}

//destructor
Deck::~Deck()
{
	delete drawingcards;
	while (!stackofCards->empty())
	{
		delete stackofCards->top();
		stackofCards->pop();
	}
	delete stackofCards;
	drawingcards = NULL;
	stackofCards = NULL;
}

void Deck::draw()
{
	Cards* temp = stackofCards->top();
	drawingcards->faceupcards->push_back(temp);
	stackofCards->pop();
}

Hand::Hand()
{
	faceupcards = new vector <Cards*>();
	mainDeck = nullptr;
	playerCards = nullptr;
}

Hand::Hand(Deck* deck)
{
	faceupcards = new vector <Cards*>();
	mainDeck = deck;
	playerCards = new vector <Cards*>();
}

//destructor
Hand::~Hand()
{
	delete faceupcards;
	delete playerCards;
	faceupcards = NULL;
	mainDeck = NULL;
	playerCards = NULL;
}

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

void goodPoints(vector<Cards*>* playerCards)
{
	getCoalPoint(playerCards)+getAnvilPoint(playerCards)
	+getTreePoint(playerCards)+getCrystalPoint(playerCards)
	+getCarrotPoint(playerCards);
}

int getCoalPoint(vector<Cards*>* playerCards)
{
	int temp = 0;
	for (int i =0 ; i <= playerCards->size; i++)
	{
		if (*deck->drawingcards->playerCards->at(i) == "coal")
			temp++;
	}
	return coal[temp][temp];
}

int getAnvilPoint(vector<Cards*>* playerCards)
{
	int temp = 0;
	for (int i = 0; i <= playerCards->size; i++)
	{
		if (*deck->drawingcards->playerCards->at(i) == "anvil")
			temp++;
	}
	return anvil[temp][temp];
}

int getTreePoint(vector<Cards*>* playerCards)
{
	int temp = 0;
	for (int i = 0; i <= playerCards->size; i++)
	{
		if (*deck->drawingcards->playerCards->at(i) == "tree")
			temp++;
	}
	return tree[temp][temp];
}

int getCrystalPoint(vector<Cards*>* playerCards)
{
	int temp = 0;
	for (int i = 0; i <= playerCards->size; i++)
	{
		if (*deck->drawingcards->playerCards->at(i) == "crystal")
			temp++;
	}
	return crystal[temp][temp];
}

int getCarrotPoint(vector<Cards*>* playerCards)
{
	int temp = 0;
	for (int i = 0; i <= playerCards->size; i++)
	{
		if (*deck->drawingcards->playerCards->at(i) == "carrot")
			temp++;
	}
	return carrot[temp][temp];
}

int coal[5][5] = 
{
	{1, 2, 3, 4, 5}, 
	{0, 1, 2, 3, 5}
};

int anvil[7][7] =
{
	{1, 2, 3, 4, 5, 6, 7},
	{0, 1, 1, 2, 2, 3, 5}
};

int tree[6][6] =
{
	{1, 2, 3, 4, 5, 6},
	{0, 1, 1, 2, 3, 5}
};

int crystal[4][4] =
{
	{1, 2, 3, 4},
	{1, 2, 3, 5}
};

int carrot[7][7] =
{
	{1, 2, 3, 4, 5, 6, 7},
	{0, 0, 1, 1, 2, 3, 5}
};

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


void shuffleAndAddCards(Deck* deck)
{
	vector<Cards*>* allCards = new vector<Cards*>();//Vectors of all hardcoded cards

	//wild, create 2 armies
	allCards->push_back
	(
		new Cards(
			"wild",
			new vector<string*>
			{
				new string("waterMove"), new string("2")
			}
		)
	);

	allCards->push_back
	(
		new Cards(
			"coal",
			new vector<string*>
			{
				new string("placeArmies"), new string("3")
			}
		)
	);

	allCards->push_back
	(
		new Cards(
			"coal",
			new vector<string*>
			{
				new string("waterMove"), new string("2")
			}
		)
	);

	allCards->push_back
	(
		new Cards(
			"coal",
			new vector<string*>
			{
				new string("waterMove"), new string("2")
			}
		)
	);

	allCards->push_back
	(
		new Cards(
			"coal",
			new vector<string*>
			{
				new string("waterMove"), new string("3")
			}
		)
	);

	allCards->push_back
	(
		new Cards(
			"coal",
			new vector<string*>
			{
				new string("move"), new string("2")
			}
		)
	);

	allCards->push_back
	(
		new Cards(
			"gem",
			new vector<string*>
			{
				new string("placeArmies"), new string("2")
			}
		)
	);

	allCards->push_back
	(
		new Cards(
			"coal",
			new vector<string*>
			{
				new string("placeArmies"), new string("2"), new string("OR"), new string("createCity"),  new string("1")
			}
		)
	);

	allCards->push_back
	(
		new Cards(
			"coal",
			new vector<string*>
			{
				new string("placeArmies"), new string("3")
			}
		)
	);

	allCards->push_back
	(
		new Cards(
			"carrot",
			new vector<string*>
			{
				new string("move"), new string("5")
			}
		)
	);

	allCards->push_back
	(
		new Cards(
			"carrot",
			new vector<string*>
			{
				new string("move"), new string("4")
			}
		)
	);

	allCards->push_back
	(
		new Cards(
			"carrot",
			new vector<string*>
			{
				new string("placeArmies"), new string("3")
			}
		)
	);

	allCards->push_back
	(
		new Cards(
			"tree",
			new vector<string*>
			{
				new string("move"), new string("3")
			}
		)
	);

	allCards->push_back
	(
		new Cards(
			"wild",
			new vector<string*>
			{
				new string("placeArmies"), new string("2")
			}
		)
	);

	allCards->push_back
	(
		new Cards(
			"carrot",
			new vector<string*>
			{
				new string("creatCity"), nullptr
			}
		)
	);



	allCards->push_back
	(
		new Cards(
			"gem",
			new vector<string*>
			{
				new string("placeArmies"), new string("2")
			}
		)
	);

	allCards->push_back
	(
		new Cards(
			"gem",
			new vector<string*>
			{
				new string("placeArmies"), new string("1")
			}
		)
	);

	allCards->push_back
	(
		new Cards(
			"gem",
			new vector<string*>
			{
				new string("move"), new string("2")
			}
		)
	);

	allCards->push_back
	(
		new Cards(
			"tree",
			new vector<string*>
			{
				new string("placeArmies"), new string("2"), new string("OR"), new string("move"), new string("3")
			}
		)
	);

	allCards->push_back
	(
		new Cards(
			"tree",
			new vector<string*>
			{
				new string("destroyArmies"), new string("1"), new string("OR"), new string("createCity"), new string("1")
			}
		)
	);

	allCards->push_back
	(
		new Cards(
			"tree",
			new vector<string*>
			{
				new string("placeArmies"), new string("3")
			}
		)
	);

	allCards->push_back
	(
		new Cards(
			"tree",
			new vector<string*>
			{
				new string("move"), new string("6")
			}
		)
	);

	allCards->push_back
	(
		new Cards(
			"tree",
			new vector<string*>
			{
				new string("waterMove"), new string("4")
			}
		)
	);

	allCards->push_back
	(
		new Cards(
			"tree",
			new vector<string*>
			{
				new string("createCity"), new string("1")
			}
		)
	);

	allCards->push_back
	(
		new Cards(
			"tree",
			new vector<string*>
			{
				new string("waterMove"), new string("3")
			}
		)
	);

	allCards->push_back
	(
		new Cards(
			"anvil",
			new vector<string*>
			{
				new string("placeArmies"), new string("3")
			}
		)
	);

	allCards->push_back
	(
		new Cards(
			"anvil",
			new vector<string*>
			{
				new string("placeArmies"), new string("3")
			}
		)
	);



	allCards->push_back
	(
		new Cards(
			"anvil",
			new vector<string*>
			{
				new string("createCity"), new string("1")
			}
		)
	);

	allCards->push_back
	(
		new Cards(
			"anvil",
			new vector<string*>
			{
				new string("placeArmies"), new string("3"), new string("OR"), new string("move"), new string("3")
			}
		)
	);

	allCards->push_back
	(
		new Cards(
			"anvil",
			new vector<string*>
			{
				new string("move"), new string("4")
			}
		)
	);

	allCards->push_back
	(
		new Cards(
			"anvil",
			new vector<string*>
			{
				new string("placeArmies"), new string("3"), new string("OR"), new string("move"), new string("4")
			}
		)
	);

	allCards->push_back
	(
		new Cards(
			"anvil",
			new vector<string*>
			{
				new string("move"), new string("5")
			}
		)
	);

	allCards->push_back
	(
		new Cards(
			"anvil2",
			new vector<string*>
			{
				new string("move"), new string("4")
			}
		)
	);

	allCards->push_back
	(
		new Cards(
			"carrot",
			new vector<string*>
			{
				new string("createCity"), new string("1")
			}
		)
	);

	allCards->push_back
	(
		new Cards(
			"carrot",
			new vector<string*>
			{
				new string("move"), new string("4")
			}
		)
	);

	allCards->push_back
	(
		new Cards(
			"carrot2",
			new vector<string*>
			{
				new string("placeArmies"), new string("3")
			}
		)
	);

	allCards->push_back
	(
		new Cards(
			"carrot",
			new vector<string*>
			{
				new string("moveWater"), new string("3")
			}
		)
	);

	allCards->push_back
	(
		new Cards(
			"carrot",
			new vector<string*>
			{
				new string("move"), new string("4")
			}
		)
	);

	allCards->push_back
	(
		new Cards(
			"carrot",
			new vector<string*>
			{
				new string("createCity"), new string("1")
			}
		)
	);

	allCards->push_back
	(
		new Cards(
			"carrot",
			new vector<string*>
			{
				new string("placeArmies"), new string("4"), new string("OR"), new string("move"), new string("2")
			}
		)
	);

	allCards->push_back
	(
		new Cards(
			"anvil",
			new vector<string*>
			{
				new string("move"), new string("3")
			}
		)
	);

	allCards->push_back
	(
		new Cards(
			"carrot",
			new vector<string*>
			{
				new string("destroyArmies"), new string("1"), new string("AND"), new string("placeArmies"), new string("1")
			}
		)
	);

	//gem, create 2 armies
	allCards->push_back
	(
		new Cards(
			"gem",
			new vector<string*>
			{
				new string("placeArmies"), new string("2")
			}
		)
	);

	std::random_shuffle(allCards->begin(), allCards->end()); //Shuffle the vector of cards
	
	//Once shuffle is done, fill the deck

	for (int i = 0; i < allCards->size(); i++)
	{
		deck->stackofCards->push(allCards->at(i));
	}

}