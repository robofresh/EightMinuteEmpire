#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>
#include <random>
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

//Copy constructor
Cards::Cards(const Cards& original)
{
	this->good = (original.good);
	this->actions = new vector<string*>();
	string* temp;

	for (int i = 0; i < original.actions->size(); i++)
	{
		temp = (original.actions->at(i));

		actions->push_back(temp);
	}
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
	cardsSpace = new Hand(this);
	stackofCards = new stack <Cards*>; //in deck, there are 42 cards. they will be stacked
	shuffleAndAddCards(this); //Add Cards into the deck
	//print();
}

//destructor
Deck::~Deck()
{
	delete cardsSpace;
	while (!stackofCards->empty())
	{
		delete stackofCards->top();
		stackofCards->pop();
	}
	delete stackofCards;
	cardsSpace = NULL;
	stackofCards = NULL;
}

//Player draw a card from the cardsremaining in the deck and place it card space.
void Deck::draw()
{
	Cards* temp = stackofCards->top();
	cardsSpace->faceupcards->push_back(temp);
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

//Prints the faceupcards
void Hand::print()
{
	cout << "Here are the face-up cards:" << endl;
	cout << "[card 1] [card 2] [card 3] [card 4] [card 5] [card 6]" << endl;
	for (int i = 0; i < 6; i++)
	{
		int* temp;
		cout << " Card " <<(i+1) << endl;
		cout << "Good is : " << *faceupcards->at(i)->good << endl;
		cout << "Action is : ";
		temp = new int (faceupcards->at(i)->actions->size());

		if (temp != 0)
		{
			for (int j = 0; j < *temp; j++)
			{
				cout << *faceupcards->at(i)->actions->at(j) << " ";
			}
			cout << endl;
		}
	}
}

void Deck::initialDraw() //one time only, when the game is started
{
	for (int i = 0; i < 6; i++) {
		draw();
	}

	this->cardsSpace->print();
}

//Prints the whole decks
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

void shuffleCards(vector<Cards*>*);


//Shuffle all the cards before making the main deck
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
				//new string("creatCity"), nullptr <== WHy is it Nullptr??
				new string("creatCity"), new string("")

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
	 //Shuffle the vector of cards
	shuffleCards(allCards);
	
	//Once shuffle is done, fill the deck
	for (int i = 0; i < allCards->size(); i++)
	{
		deck->stackofCards->push(allCards->at(i));
	}

}


void shuffleCards(vector<Cards*>* listCard)
{
	
	for (int i = 0; i < listCard->size(); i++)
	{
		swap(listCard->at(i), listCard->at(rand() % listCard->size()));
	}
}