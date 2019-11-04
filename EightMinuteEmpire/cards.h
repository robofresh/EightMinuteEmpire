#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <stack>

using namespace std;

class Cards;
class Deck;
class Hand;

class Cards
{
public:
	Cards(string, vector<string*>*); //1st string for good(resources), 2nd string for action
	Cards();
	Cards(const Cards&);
	Cards& operator= (const Cards&);
	~Cards();
	string* good; //there are different good(resources) including crystal, lumber,	carrot,	anvil, coal, joker.
	vector<string*>* actions; //there are actions that gives choice to the player. this needs to be discussed on how to be implemented among us. 
	void print();
};

class Deck
{
public:
	Deck();
	~Deck();
	void initialDraw();
	Hand* cardsSpace;
	void draw();
	stack<Cards*>* stackofCards;
	void print();
	void updateCardsSpace(Deck*, int);
};

class Hand
{
public:
	Hand();
	Hand(Deck*);
	~Hand();
	Deck* mainDeck;
	Cards* exchange(int index);
	vector<Cards*>* faceupcards; //6 cards are poped from stack and revealed (faced-up)
	vector<Cards*>* playerCards; //Cards own by the player
	//int const* cost[]; //cost of card is fixed depending on the index, 0 1 1 2 2 3 respectively
	void print();
};