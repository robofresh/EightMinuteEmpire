#include <iostream>
#include "Player.h"
#include "BidingFacility.h"

//int BidingFacility::supply = 0;

int main()
{

	Player* player1 = new Player("John", 10, 10);
	Player* player2 = new Player("Ray", 10, 20);

	//cout << *(player1->name) << endl;
	//cout << *(player1->age) << endl;
	//cout << *(player1->numCoins) << endl;

	//BidingFacility* bidFac = new BidingFacility(*player1->name, *player1->age, *player1->numCoins);

	//cout << *(bidFac->supply) << endl; //Print supply
	//cout << bidFac->players->size() << endl;
	//std::vector<Player*>::iterator iterate = bidFac->players->begin();

	//cout << *(iterate) << endl;

	// Testing of bidCoins and giveToSupply
	(player1->bidFacObj->bidCoins(10));

	cout << *player1->bidFacObj->amountBid << endl;//print the amount bid by player 1

	(player1->bidFacObj->giveToSupply(player1));

	cout << "coin left by player 1 is : " << endl;
	cout << *player1->numCoins << endl; //print amount of coins left
	cout << *(BidingFacility::supply) << endl;// print supply

	//END testing of bidCoins and giveToSupply

}