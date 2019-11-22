#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>
#include <random>
#include <exception>
#include "Player.h"
#include "cards.h"
#include "Cardsfactory.h"
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
Cards::Cards(const string &good1, vector<string*>* action1)
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
	goods = new int(0);

}

Hand::Hand(Deck* deck)
{
	faceupcards = new vector <Cards*>();
	mainDeck = deck;
	goods = new int(0);

}

//destructor
Hand::~Hand()
{
	delete faceupcards;
	delete goods;

	faceupcards = NULL;
	mainDeck = NULL;
	goods = nullptr;

}

Cards* Hand::exchange(int index)
{
	cout << "Selected card at position: " << index << endl;
	Cards* tmp = faceupcards->at(index);
	faceupcards->erase(faceupcards->begin() + index);
	mainDeck->draw();
	return tmp;
}

//Shift all cards to the left and draw a new card and put it on the rightmost side
void Deck::updateCardsSpace(Deck* deck, int position)
{

	for (int i = position + 1; i < 6; i++)
	{
		Cards* temp;
		temp = deck->cardsSpace->faceupcards->at(i); //temp pointer points to next card

		//Put the copy of the next card into the left position
		int previous = i - 1;
		(deck->cardsSpace->faceupcards->at(previous)) = temp;

	}
	deck->cardsSpace->faceupcards->resize(5);
	deck->draw();

}

//Print with integrated print Cards
void Hand::print() const
{
	cout << "Here are the face-up cards:" << endl;
	cout << "[card 1: cost 0] [card 2: cost 1] [card 3: cost 1] [card 4: cost 2] [card 5: cost 2] [card 6: cost 3]" << endl;
	for (int i = 0; i < 6; i++)
	{
		cout << " Card " << (i + 1) <<" : ";
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
			cout << "[Good is : " << *good ;
			cout << ", Action is : ";
			const int temp = this->actions->size();

			if (temp != 0)
			{
				for (int j = 0; j < temp; j++)
				{
					cout << *actions->at(j) << " ";
				}
				cout << "]";
			
			}
		}
		else
		{
			cout << "Empty card" << endl;
		}
		cout << endl;
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
	cout << "Initial draw" << endl;
}

//Prints the whole decks
void Deck::print() const
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

	// create 2 armies
	allCards->push_back(Cardsfactory::Create("wild", vector<string>{"waterMove"}, vector<string>{"2"}));
	allCards->push_back(Cardsfactory::Create("wild", vector<string>{"waterMove"}, vector<string>{"2"}));
	allCards->push_back(Cardsfactory::Create("coal", vector<string>{"placeArmies"}, vector<string>{"3"}));
	allCards->push_back(Cardsfactory::Create("coal", vector<string>{"waterMove"}, vector<string>{"2"}));
	allCards->push_back(Cardsfactory::Create("coal", vector<string>{"waterMove"}, vector<string>{"2"}));
	allCards->push_back(Cardsfactory::Create("coal", vector<string>{"waterMove"}, vector<string>{"3"}));
	allCards->push_back(Cardsfactory::Create("coal", vector<string>{"move"}, vector<string>{"2"}));
	allCards->push_back(Cardsfactory::Create("gem", vector<string>{"placeArmies"}, vector<string>{"2"}));
	allCards->push_back(Cardsfactory::Create("coal", vector<string>{"OR", "placeArmies", "createCity"}, vector<string>{"2", "1"}));
	allCards->push_back(Cardsfactory::Create("coal", vector<string>{"placeArmies"}, vector<string>{"3"}));
	allCards->push_back(Cardsfactory::Create("carrot", vector<string>{"move"}, vector<string>{"5"}));
	allCards->push_back(Cardsfactory::Create("carrot", vector<string>{"move"}, vector<string>{"4"}));
	allCards->push_back(Cardsfactory::Create("carrot", vector<string>{"placeArmies"}, vector<string>{"3"}));
	allCards->push_back(Cardsfactory::Create("tree", vector<string>{"move"}, vector<string>{"3"}));
	allCards->push_back(Cardsfactory::Create("wild", vector<string>{"placeArmies"}, vector<string>{"2"}));
	allCards->push_back(Cardsfactory::Create("carrot", vector<string>{"createCity"}, vector<string>{"1"}));
	allCards->push_back(Cardsfactory::Create("gem", vector<string>{"placeArmies"}, vector<string>{"2"}));
	allCards->push_back(Cardsfactory::Create("gem", vector<string>{"placeArmies"}, vector<string>{"1"}));
	allCards->push_back(Cardsfactory::Create("gem", vector<string>{"move"}, vector<string>{"2"}));
	allCards->push_back(Cardsfactory::Create("tree", vector<string>{"OR", "placeArmies", "move"}, vector<string>{"2", "3"}));
	allCards->push_back(Cardsfactory::Create("tree", vector<string>{"OR", "destroyArmies", "createCity"}, vector<string>{"1", "1"}));
	allCards->push_back(Cardsfactory::Create("tree", vector<string>{"placeArmies"}, vector<string>{"3"}));
	allCards->push_back(Cardsfactory::Create("tree", vector<string>{"move"}, vector<string>{"6"}));
	allCards->push_back(Cardsfactory::Create("tree", vector<string>{"waterMove"}, vector<string>{"4"}));
	allCards->push_back(Cardsfactory::Create("tree", vector<string>{"createCity"}, vector<string>{"1"}));
	allCards->push_back(Cardsfactory::Create("tree", vector<string>{"waterMove"}, vector<string>{"3"}));
	allCards->push_back(Cardsfactory::Create("anvil", vector<string>{"placeArmies"}, vector<string>{"3"}));
	allCards->push_back(Cardsfactory::Create("anvil", vector<string>{"placeArmies"}, vector<string>{"3"}));
	allCards->push_back(Cardsfactory::Create("anvil", vector<string>{"createCity"}, vector<string>{"1"}));
	allCards->push_back(Cardsfactory::Create("anvil", vector<string>{"OR", "placeArmies", "move"}, vector<string>{"3", "3"}));
	allCards->push_back(Cardsfactory::Create("anvil", vector<string>{"move"}, vector<string>{"4"}));
	allCards->push_back(Cardsfactory::Create("anvil", vector<string>{"OR", "placeArmies", "move"}, vector<string>{"3", "4"}));
	allCards->push_back(Cardsfactory::Create("anvil", vector<string>{"move"}, vector<string>{"5"}));
	allCards->push_back(Cardsfactory::Create("2anvil", vector<string>{"move"}, vector<string>{"4"}));
	allCards->push_back(Cardsfactory::Create("carrot", vector<string>{"createCity"}, vector<string>{"1"}));
	allCards->push_back(Cardsfactory::Create("carrot", vector<string>{"move"}, vector<string>{"4"}));
	allCards->push_back(Cardsfactory::Create("2carrot", vector<string>{"placeArmies"}, vector<string>{"3"}));
	allCards->push_back(Cardsfactory::Create("carrot", vector<string>{"waterMove"}, vector<string>{"3"}));
	allCards->push_back(Cardsfactory::Create("carrot", vector<string>{"OR", "placeArmies", "move"}, vector<string>{"4", "2"}));
	allCards->push_back(Cardsfactory::Create("anvil", vector<string>{"move"}, vector<string>{"3"}));
	allCards->push_back(Cardsfactory::Create("carrot", vector<string>{"AND", "destroyArmies", "placeArmies"}, vector<string>{"1", "1"}));
	allCards->push_back(Cardsfactory::Create("gem", vector<string>{"placeArmies"}, vector<string>{"2"}));

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
