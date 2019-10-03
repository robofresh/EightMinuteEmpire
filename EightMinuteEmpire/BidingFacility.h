#pragma once

#include <string>
#include <iostream>
#include <vector>
#include "Player.h"

using namespace std;

class BidingFacility;
class Player;

class SimplePlayer
{
public:
	string* pName;
	int* pAge;
	int* pAmountCoins;
	int* bidAmount;

	SimplePlayer(string, int, int,int);
	~SimplePlayer();
};

class BidingFacility
{
public:
	// Biding facility is run once
	// Everyone has a bidingFacility

	static int* supply;// Supply is shared among all players
	static Player* winner;// Winner pays the amount to the supply
	static vector<SimplePlayer*>* players;
	static vector<int>* bidingAmount;
	
	int* amountBid;

	//Not sure about those methods 
	BidingFacility(string, int, int);
	~BidingFacility();

	string* reveal();//Shows everyone's bid
	Player* revealWinner(); //return the winner?
	Player* determineYoungest();//Called only if multiple highest bid
	
	void giveToSupply(Player*);
	int bidCoins();
	
};