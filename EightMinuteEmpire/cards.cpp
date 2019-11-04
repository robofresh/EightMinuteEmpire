#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>
#include <random>
#include <exception>
#include "Player.h"
#include "Cards.h"
#include <ctime>

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

//Copy constructor TESTED OK
Cards::Cards(const Cards& original)
{
	good = new string (*original.good); //deep copy of string
	actions = new vector<string*>();
	
	string* temp;

	for (int i = 0; i < original.actions->size(); i++)
	{
		temp = new string(*(original.actions->at(i)));

		this->actions->push_back(temp);

	}
}

//Operator = TESTED OK
Cards& Cards::operator= (const Cards& original)
{
	if (this == &original)
		return *this;

	//do copy
	good = new string(*original.good); //deep copy of string
	actions = new vector<string*>();

	string* temp;

	for (int i = 0; i < original.actions->size(); i++)
	{
		temp = new string(*(original.actions->at(i)));
		actions->push_back(temp);
	}

	return *this;

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

}

Hand::Hand(Deck* deck)
{
	faceupcards = new vector <Cards*>();
	mainDeck = deck;

}

//destructor
Hand::~Hand()
{
	delete faceupcards;

	faceupcards = NULL;
	mainDeck = NULL;

}

Cards* Hand::exchange(int index)
{
	cout << "selected " << index << endl;
	Cards* tmp = faceupcards->at(index);
	faceupcards->erase(faceupcards->begin() + index);
	mainDeck->draw();
	return tmp;
}

//Shift all cards to the left and draw a new card and put it on the rightmost side
void Deck::updateCardsSpace(Deck* deck, int position)
{
	delete deck->cardsSpace->faceupcards->at(position);

	for (int i = position + 1; i < 6; i++)
	{
		Cards* temp;
		temp = new Cards(*deck->cardsSpace->faceupcards->at(i)); //Copy the next card

		//Erase from memory that next card
		delete	deck->cardsSpace->faceupcards->at(i);
		deck->cardsSpace->faceupcards->at(i) = nullptr;

		//Put the copy of the next card into the left position
		int previous = i - 1;
		(deck->cardsSpace->faceupcards->at(previous)) = temp;

		temp = nullptr;
	}
	deck->cardsSpace->faceupcards->resize(5);
	deck->draw();


}

//Print with integrated print Cards
void Hand::print()
{
	cout << "Here are the face-up cards:" << endl;
	cout << "[card 1] [card 2] [card 3] [card 4] [card 5] [card 6]" << endl;
	for (int i = 0; i < 6; i++)
	{
		cout << " Card " << (i + 1) << endl;
		try
		{
			if (faceupcards->at(i)==nullptr)
			{
				cout<<"Empty space"<<endl;
			}
			else
			{
				faceupcards->at(i)->print();
			}
		}
		catch (const std::exception& msg)
		{
			cout << msg.what() << endl;
		}
	}
}

//Print Card's info
void Cards::print()
{
	try
	{
		if (this != nullptr)
		{
			int* temp;
			cout << "Good is : " << *good << endl;
			cout << "Action is : ";
			temp = new int(this->actions->size());

			if (temp != 0)
			{
				for (int j = 0; j < *temp; j++)
				{
					cout << *actions->at(j) << " ";
				}
				cout << endl;
			}
		}
		else
		{
			cout << "Empty card" << endl;
		}
	}
	catch (const std::exception& e)
	{
		cout << "catch error inside of cards print" << endl;
		cout << e.what() << endl;

	}
}

void Deck::initialDraw() //one time only, when the game is started
{
	for (int i = 0; i < 6; i++) {
		draw();
	}
	//this->cardsSpace->print();
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


//Shuffle method of all cards in a vector
void shuffleCards(vector<Cards*>* listCard)
{
	srand((unsigned)time(0));
	
	for (int i = 0; i < listCard->size(); i++)
	{
		swap(listCard->at(i), listCard->at(rand() % listCard->size()));
	}
}