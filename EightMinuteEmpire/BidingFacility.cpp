#pragma once

#include <string>
#include <iostream>
#include <vector>
#include "BidingFacility.h"
#include "Player.h"

using namespace std;

//Initialize static attributes
int* BidingFacility::supply = new int(0);
vector<Player*>* BidingFacility::players = new vector<Player*>();
vector<int>* BidingFacility::bidingAmount = new vector<int>();
Player* BidingFacility::winner = NULL;

BidingFacility::BidingFacility(string name, int age, int maxCoins)
{
	amountBid = new int(0);
	//players->push_back(himself);
	//bidingAmount->push_back(*amountBid);
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

void BidingFacility::giveToSupply(Player* winPay)
{
	supply= new int(*supply + *amountBid);
	(winPay->numCoins) = new int (*(winPay->numCoins) - *amountBid);
}

void BidingFacility::bidCoins(int amount)
{
	amountBid = new int(amount);
} 


