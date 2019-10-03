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
	
	amountBid = new int(0);
	
}

BidingFacility::~BidingFacility(){}


string* BidingFacility::reveal()
{

	for (int i = 0; i < players->size(); i++)
	{
		cout << "Player : " + *(players->at(i)->name) << endl;
		cout << "bids: " + std::to_string(allBids->at(i)) << endl;
	}
	return NULL;
}

Player* BidingFacility::revealWinner()
{
	for (int i = 0; i < players->size(); i++) {
		if (largestBid == NULL) 
		{
			largestBid = new int (*players->at(i)->bidFacObj->amountBid);
			winner = players->at(i);
		}
		else if (*largestBid < (*players->at(i)->bidFacObj->amountBid))
		{
			largestBid = (players->at(i)->bidFacObj->amountBid);
			winner = players->at(i);
		}
		else if (*largestBid == (*players->at(i)->bidFacObj->amountBid))
		{
			winner= determineYoungest(players->at(i), winner);
		}
	}
	return winner;
}

Player* BidingFacility::determineYoungest(Player* player1, Player* player2)
{
	if (*(player1->age) < *(player2->age))
		return player1;
	else
		return player2;

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

