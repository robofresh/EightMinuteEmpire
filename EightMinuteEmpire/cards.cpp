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
	stackofCards = new stack <Cards*>; //in deck, there are 42 cards. they will be stacked
}

Cards* Deck::draw()
{
	Cards* temp = stackofCards->top(); 
	stackofCards->pop(); //it should head to the last index of Hand object
	return temp; 
}

//destructor
Deck::~Deck(){}

Hand::Hand()
{
	//int numOnHand = 0;
	faceupcards = new vector <Cards*>();
}

//destructor
Hand::~Hand(){}

void Hand::exchange(int index)
{
	cout << "selected" << index << endl;
	Cards* draw(); //need to check this
}

void Hand::initialDraw() //when the game is started
{
	for (int i = 0; i < 6; i++) {
		Cards* draw();  //need to check this
		i++;
		//numOnHand++;
	}
}