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

void Hand::exchange(int index)
{
	cout << "selected " << index << endl;
	faceupcards->erase(faceupcards->begin() + index);
	mainDeck->draw();
}

void Deck::initialDraw() //one time only, when the game is started
{
	for (int i = 0; i < 6; i++) {
		draw();
	}
}



void addCards(Deck* deck)
{
	//gem, create 2 armies
	deck->stackofCards->push
	(
		new Cards(
			"gem", 
			new vector<string*>  
			{
				new string("createArmies"), new string("2")
			}
		)
	);

	//gem, create 2 armies
	deck->stackofCards->push
	(
		new Cards(
			"coal",
			new vector<string*>
			{
				new string("createArmies"), new string("2")
			}
		)
	);

	//gem, create 2 armies
	deck->stackofCards->push
	(
		new Cards(
			"coal",
			new vector<string*>
			{
				new string("createArmies"), new string("2")
			}
		)
	);

	//gem, create 2 armies
	deck->stackofCards->push
	(
		new Cards(
			"coal",
			new vector<string*>
			{
				new string("createArmies"), new string("2")
			}
		)
	);
	//gem, create 2 armies
	deck->stackofCards->push
	(
		new Cards(
			"coal",
			new vector<string*>
			{
				new string("createArmies"), new string("2")
			}
		)
	);
	//gem, create 2 armies
	deck->stackofCards->push
	(
		new Cards(
			"coal",
			new vector<string*>
			{
				new string("createArmies"), new string("2")
			}
		)
	);
	//gem, create 2 armies
	deck->stackofCards->push
	(
		new Cards(
			"coal",
			new vector<string*>
			{
				new string("createArmies"), new string("2")
			}
		)
	);

}