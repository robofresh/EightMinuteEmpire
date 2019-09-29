#pragma once

#include <string>
#include <iostream>
#include <Player.h>

using namespace std;

class BidingFacility;

class BidingFacility
{
public:
	// Biding facility is run once
	// Everyone has a bidingFacility
	static int* numberOfPlayer;
	static int* supply;// Supply is shared among all players
	static Player* winner;
	
	int* age;
	int* maxCoins;
	int* bidCoins;

	//Not sure about those methods 
	void pickUp(maxCoins);
	void bid(bidCoins);
	string* reveal();//Shows everyone's bid
	Player* revealWinner(); //return the winner?

};