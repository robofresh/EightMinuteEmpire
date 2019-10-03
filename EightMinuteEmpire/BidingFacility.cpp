#pragma once

#include <string>
#include <iostream>
#include <vector>
#include "BidingFacility.h"
#include "Player.h"

using namespace std;

BidingFacility::BidingFacility(Player*)
{

}

BidingFacility::~BidingFacility()
{
}

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

void BidingFacility::giveToSupply(Player*)
{
}

void BidingFacility::bidCoins(int amount)
{
} 


