#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <exception>
#include "BidingFacility.h"
#include "Player.h"


using namespace std;

//Initialize static attributes
int* BidingFacility::supply = new int(0);
int* largestBid;
vector<Player*>* BidingFacility::players = new vector<Player*>();
vector<int>* BidingFacility::allBids = new vector<int>();
Player* BidingFacility::winner = NULL;

//Input Exception 
struct InputException : public exception
{
	const char* what() const throw()
	{
		return "Your input is invalid.";
	}
};

//Default constructor
BidingFacility::BidingFacility()
{	
	//amountBid = new int(0);	

	//This does not work
	int value = 0;
	*amountBid = value;

	//This does not work 
	*amountBid = 0;
}

//Destructor
BidingFacility::~BidingFacility(){}


void BidingFacility::reveal()
{
	for (int i = 0; i < players->size(); i++)
	{
		cout << "Player : " + *(players->at(i)->name) << endl;
		cout << "bids: " + std::to_string(allBids->at(i)) << endl;
	}
	
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
	giveToSupply(winner);
	cout << *(winner->name) +" is the winner!" << endl;
	return winner;
}

//Compare two players and return the youngest
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
	int amount = *(winPay->bidFacObj->amountBid);
	supply= new int(*supply + amount);
	(winPay->numCoins) = new int (*(winPay->numCoins) - amount);
}

//Player bit an amount
void BidingFacility::bidCoins(Player* playerBid)
{
	int inputBid;
	try
	{
			cout << *(playerBid->name) + ", please enter your bid :" << endl;
			cin >> inputBid;
			if (!(inputBid < *(playerBid->numCoins) && inputBid >= 0))
				throw InputException();
	}
	catch (InputException& e)
	{
		cout <<e.what()<<endl;
		cout << "Game will close down!" << endl;
		exit(0);
	}
	
	amountBid = new int(inputBid);
	players->push_back(playerBid); 
	allBids->push_back(*amountBid);

	
} 

//Prints out details about players
void BidingFacility::showDetails()
{
	cout << "Details about players" << endl;

	for (int i = 0; i < (players->size()); i++)
	{
		cout << *(players->at(i)->name) + " is " + to_string(*(players->at(i)->age))
			+ " , has " + to_string(*(players->at(i)->numCoins)) + " coins." << endl;
	}

	cout << "Content of the supply: " + to_string(*supply) << endl;

}

//Method to start the bidding process which occurs only once at the beginning of the game
//TODO: Attempting to make this a static method
 void BidingFacility::startBidProcess()
{

	//Reveal all biddings
	reveal();

	//Reveal the Winner
	revealWinner();

	showDetails();

}




