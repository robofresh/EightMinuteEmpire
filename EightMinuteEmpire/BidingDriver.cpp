#include <iostream>
#include "Player.h"
#include "BidingFacility.h"

//int BidingFacility::supply = 0;

int main()
{

	Player* player1 = new Player("John", 5, 20);
	Player* player2 = new Player("Ray", 10, 20);
	Player* player3 = new Player("Scott", 12, 20);
	Player* player4 = new Player("Sam", 15, 20);


	player3->bidFacObj->startBidProcess();




}