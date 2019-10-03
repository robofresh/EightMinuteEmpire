#pragma once

#include <string>
#include <iostream>
#include <vector>
#include "Player.h"

using namespace std;

class BidingFacility;
class Player;


class BidingFacility
{
public:
	// Biding facility is run once
	// Everyone has a bidingFacility

	static int* supply;// Supply is shared among all players
	static Player* winner;// Winner pays the amount to the supply
	static vector<Player*>* players;
	static vector<int>* allBids;
	
	int* amountBid;

	//Not sure about those methods 
	BidingFacility();
	~BidingFacility();

	string* reveal();//Shows everyone's bid
	Player* revealWinner(); //return the winner?
	Player* determineYoungest(Player*,Player*);//Called only if multiple highest bid
	
	void giveToSupply(Player*);
	void bidCoins(Player*);
	
};