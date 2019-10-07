#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Card;
class Deck;
class Hand;

class Cards
{
public:
	Cards(string, string);
	~Cards();
	string* good;
	string* action; //there are actions that gives choice to the player. this needs to be discussed on how to be implemented among us. 
};

class Deck
{
public:
	Deck();
	~Deck();
	Hand* drawingcards;
	void draw();
	stack <Cards*>* stackofCards;
};

class Hand
{
public:
	Hand();
	~Hand();
	void exchange();
	int* numOnHand;
	vector<Cards*>* faceupcards;
	int const* cost[];
};

/*
1. The deck object is composed of as many cards of the Eight-minute empire cards (e.g. 42).
2. Each card gives goods and action.
3. The deck must have a draw() method that allows a player to draw a card from the cards remaining in the deck and place it in with the cards space
4. The hand object is a collection of cards that has an exchange() method that allows the player to select the card from its position in the row and 
pay the coin cost listed at the top of the board
*/