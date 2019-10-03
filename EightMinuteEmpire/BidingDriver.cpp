#include <iostream>
#include "Player.h"
#include "BidingFacility.h"

//int BidingFacility::supply = 0;

int main()
{

	Player* player1 = new Player("John", 10, 10);
	Player* player2 = new Player("Ray", 10, 20);

	player1->bidFacObj->bidCoins(player1);
	player2->bidFacObj->bidCoins(player2);

	player1->bidFacObj->reveal();

	//// Testing of bidCoins and giveToSupply
	//(player1->bidFacObj->bidCoins(10));

	//cout << *player1->bidFacObj->amountBid << endl;//print the amount bid by player 1

	//(player1->bidFacObj->giveToSupply(player1));

	//cout << "coin left by player 1 is : " << endl;
	//cout << *player1->numCoins << endl; //print amount of coins left
	//cout << *(BidingFacility::supply) << endl;// print supply

	////END testing of bidCoins and giveToSupply

}