#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <exception>
#include "Player.h"
#include "Cards.h"

using namespace std;

Cards::Cards(string good1, string action1)
{
	good = new string (good1);
	action = new string(action1);
}

//destructor
Cards::~Cards(){}

Deck::Deck()
{
	drawingcards = new Hand(this);
	stackofCards = new stack <Cards*>; //in deck, there are 42 cards. they will be stacked
}

void Deck::draw()
{
	Cards* temp = stackofCards->top(); 
	drawingcards->faceupcards->push_back(temp);
	stackofCards->pop(); //it should head to the last index of Hand object
}

//destructor
Deck::~Deck(){}

Hand::Hand(Deck* deck)
{
	//int numOnHand = 0;
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