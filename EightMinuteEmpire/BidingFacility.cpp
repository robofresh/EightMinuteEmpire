#pragma once

#include <string>
#include <iostream>
#include <vector>
#include "BidingFacility.h"
#include "Player.h"


using namespace std;

//Initialize static attributes
int* BidingFacility::supply = new int(0);
vector<SimplePlayer*>* BidingFacility::players = new vector<SimplePlayer*>();
Player* BidingFacility::winner = NULL;

BidingFacility::BidingFacility(string name, int age, int maxCoins)
{
	
	amountBid = new int(bidCoins());
	SimplePlayer* playerTempPtr = new SimplePlayer(name, age, maxCoins, amountBid);
	players->push_back(playerTempPtr);
	
	delete playerTempPtr;
	playerTempPtr = NULL;


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

//The winner gives his coins to the supply
void BidingFacility::giveToSupply(Player* winPay)
{
	supply= new int(*supply + *amountBid);
	(winPay->numCoins) = new int (*(winPay->numCoins) - *amountBid);
}

//Player bit an amount
//TODO: Handle exception no negative number
int BidingFacility::bidCoins()
{
	cout << "Please enter your bid :" << endl;
	int inputBid;
	cin>>inputBid;
	return inputBid;
} 

SimplePlayer::SimplePlayer(string name, int age, int amountMax, int amountBid)
{
	pName = new string(name);
	pAge = new int(age);
	pAmountCoins = new int(amountMax);
	bidAmount = new int(amountBid);

}

SimplePlayer::~SimplePlayer() {}
