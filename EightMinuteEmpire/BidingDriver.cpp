#include <iostream>
#include "Player.h"
#include "BidingFacility.h"

int main()
{

	// Test 1: Highest bid wins
	cout << "*****Test 1 : Player who bid the most coins wins!*****"<<endl;
	cout << "Creating player 1." << endl;
	Player* player1 = new Player("John", 26, 7, "Red");
	player1->printPlayer();

	cout << "Creating player 2." << endl;
	Player* player2 = new Player("Jane", 28, 7, "Blue");
	player2->printPlayer();

	cout << "Creating player 3." << endl;
	Player* player3 = new Player("Luke", 25, 7, "Pink");
	player3->printPlayer();

	player1->bidFacObj->bidCoins(7);
	player2->bidFacObj->bidCoins(4);
	player3->bidFacObj->bidCoins(5);

	player1->bidFacObj->startBidProcess();

	player1->bidFacObj->clearBidingFacility();
	delete player1, player2, player3;
	player1 = NULL;
	player2 = NULL;
	player3 = NULL;

	// Test 2: Bids tied, Youngest wins
	cout << "\n***** Test 2 :Bids are tied, the Youngest wins!*****" << endl;
	cout << "Creating player 1." << endl;
	player1 = new Player("John", 26, 7, "Red");
	player1->printPlayer();

	cout << "Creating player 2." << endl;
	player2 = new Player("Jane", 28, 7, "Blue");
	player2->printPlayer();

	cout << "Creating player 3." << endl;
	player3 = new Player("Luke", 25, 7, "Pink");
	player3->printPlayer();

	player1->bidFacObj->bidCoins(5);
	player2->bidFacObj->bidCoins(5);
	player3->bidFacObj->bidCoins(5);

	player1->bidFacObj->startBidProcess();

	player1->bidFacObj->clearBidingFacility();
	delete player1, player2, player3;
	player1 = NULL;
	player2 = NULL;
	player3 = NULL;

	//Test 3: All bids are 0, Youngest wins

	cout << "\n***** Test 3 : All bids are 0, Youngest wins*****" << endl;
	cout << "Creating player 1." << endl;
	player1 = new Player("John", 26, 7, "Red");
	player1->printPlayer();

	cout << "Creating player 2." << endl;
	player2 = new Player("Jane", 28, 7, "Blue");
	player2->printPlayer();

	cout << "Creating player 3." << endl;
	player3 = new Player("Luke", 25, 7, "Pink");
	player3->printPlayer();

	player1->bidFacObj->bidCoins(0);
	player2->bidFacObj->bidCoins(0);
	player3->bidFacObj->bidCoins(0);

	player1->bidFacObj->startBidProcess();

	player1->bidFacObj->clearBidingFacility();
	delete player1, player2, player3;
	player1 = NULL;
	player2 = NULL;
	player3 = NULL;
}
