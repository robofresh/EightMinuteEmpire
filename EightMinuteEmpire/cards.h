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
	Cards(string, string); //1st string for good(resources), 2nd string for action
	~Cards();
	string* good; //there are different good(resources) including crystal, lumber,	carrot,	anvil, coal, joker.
	string* action; //there are actions that gives choice to the player. this needs to be discussed on how to be implemented among us. 
};

class Deck
{
public:
	Deck();
	~Deck();
	Hand* drawingcards;
	Cards* draw();
	stack<Cards*>* stackofCards;
};

class Hand
{
public:
	Hand();
	~Hand();
	void exchange(int index);
	void initialDraw();
	//int* numOnHand; //numOnHand has to be six all the time
	vector<Cards*>* faceupcards; //6 cards are poped from stack and revealed (faced-up)
	int const* cost[]; //cost of card is fixed depending on the index, 0 1 1 2 2 3 respectively
};
