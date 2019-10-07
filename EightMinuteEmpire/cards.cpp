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
Cards::~Cards()
{
}

Deck::Deck()
{
	stackofCards = new stack <Cards*>;
	stackofCards->push(new Cards("crystal", "attack"));
	stackofCards->push(new Cards("lumber", "attack"));
	stackofCards->push(new Cards("carrot", "buildcity"));
	stackofCards->push(new Cards("coal","oversea"));
	stackofCards->push(new Cards("joker", "buildcity"));
}

Cards* Deck::draw()
{
	Cards* temp = stackofCards->top();
	stackofCards->pop();
	return temp; 
}

//destructor
Deck::~Deck()
{
}

Hand::Hand()
{
}

//destructor
Hand::~Hand()
{
}

void Hand::exchange()
{

}

/*
1. The deck object is composed of as many cards of the Eight-minute empire cards (e.g. 42).
2. Each card gives goods and action.
3. The deck must have a draw() method that allows a player to draw a card from the cards remaining in the deck
and place it in with the cards space
4. The hand object is a collection of cards that has an exchange
() method that allows the player to select the card from its position in the row and pay the coin
cost listed at the top of the board
*/