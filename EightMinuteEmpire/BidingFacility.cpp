#pragma once

#include <string>
#include <iostream>
#include <vector>
#include "BidingFacility.h"
#include "Player.h"


using namespace std;

//Initialize static attributes
int* BidingFacility::supply = new int(0);
int* largestBid;
vector<Player*>* BidingFacility::players = new vector<Player*>();
vector<int>* BidingFacility::allBids = new vector<int>();
Player* BidingFacility::winner = NULL;

BidingFacility::BidingFacility()
{
	
	amountBid = NULL;
	
}

BidingFacility::~BidingFacility(){}


string* BidingFacility::reveal()
{
	return NULL;
}

Player* BidingFacility::revealWinner()
{
	return NULL;
}

Player* BidingFacility::determineYoungest()
{

	return NULL;
}

//The winner gives his coins to the supply
void BidingFacility::giveToSupply(Player* winPay)
{
	supply= new int(*supply + *amountBid);
	(winPay->numCoins) = new int (*(winPay->numCoins) - *amountBid);
}

//Player bit an amount
//TODO: Handle exception no negative number
void BidingFacility::bidCoins(Player* playerBid)
{
	cout << "Please enter your bid :" << endl;
	int inputBid;
	cin>>inputBid;
	amountBid = new int(inputBid);
	players->push_back(playerBid);
	allBids->push_back(*amountBid);
	
} 

