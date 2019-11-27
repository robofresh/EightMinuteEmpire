#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <stack>

#include "GameObservers.h"
//#include "Player.h"

using namespace std;

class Cards;
class Deck;
class Hand;

class Cards: public Subject
{
public:
	Cards(const string&, vector<string*>*); //1st string for good(resources), 2nd string for action
	Cards();
	Cards(const Cards&);
	Cards& operator= (const Cards&);
	virtual ~Cards();
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
	void print() const;
	void updateCardsSpace(Deck*, int);
};

class Hand
{
public:
	Hand();
	Hand(Deck*);
	~Hand();
	Deck* mainDeck;
	int* goods;
	Cards* exchange(int index);
	vector<Cards*>* faceupcards; //faceupcards from deck => faceupcards
								//faceupcards from each players => cards they keep
	void print() const;
	//void goodPoints();
};