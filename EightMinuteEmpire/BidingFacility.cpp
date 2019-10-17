#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <exception>
#include "BidingFacility.h"
#include "Player.h"


using namespace std;

//Initialize static attributes
int* BidingFacility::largestBid = NULL;
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
BidingFacility::BidingFacility(Player* player)
{	
	amountBid = NULL;	
	this->player = player;

}

//Destructor
BidingFacility::~BidingFacility()
{


	delete amountBid;

	amountBid = NULL;
	player = NULL;

}


void BidingFacility::reveal()
{
	for (int i = 0; i < players->size(); i++)
	{
		cout << "Player : " + *(players->at(i)->name) + 
		" bids " + std::to_string(allBids->at(i)) + " coins." << endl;
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
	cout << *(winner->name) +" is the winner! \n" << endl;
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
void BidingFacility::giveToSupply(Player* winPay, int* supply)
{
	int amount = *(winPay->bidFacObj->amountBid);
	int value = *supply + amount;
	*supply = value;
	(winPay->numCoins) = new int (*(winPay->numCoins) - amount);
}

//Player bit an amount WITH AN INPUT
void BidingFacility::bidCoins()
{
	int inputBid;
	try
	{
			cout << *(this->player->name) + ", please enter your bid :" << endl;
			cin >> inputBid;
			if (!(inputBid < *(this->player->numCoins) && inputBid >= 0))
				throw InputException();
	}
	catch (InputException& e)
	{
		cout <<e.what()<<endl;
		cout << "Game will close down!" << endl;
		exit(0);
	}
	
	amountBid = new int(inputBid);
	players->push_back(this->player); 
	allBids->push_back(*amountBid);

	
} 

//Player bit an amount with an argument
void BidingFacility::bidCoins(int inputBid)
{
	try
	{
		if (!(inputBid <= *(this->player->numCoins) && inputBid >= 0))
			throw InputException();
	}
	catch (InputException & e)
	{
		cout << e.what() << endl;
		cout << "Game will close down!" << endl;
		exit(0);
	}

	amountBid = new int(inputBid);
	players->push_back(this->player);
	allBids->push_back(*amountBid);


}

//Method to start the bidding process which occurs only once at the beginning of the game
//TODO: Attempting to make this a static method
 void BidingFacility::startBidProcess(int* supply)
{

	//Reveal all biddings
	reveal();

	//Reveal the Winner
	revealWinner();

	//Add winners bid to supply
	giveToSupply(winner, supply);
}

 void BidingFacility::clearBidingFacility()
 {
	 winner = NULL;//No need to delete, will mem deallocated with delete player

	 delete largestBid;
	 largestBid = NULL;

	 players->clear();
	 allBids->clear();
 }




