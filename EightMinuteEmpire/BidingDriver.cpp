#include <iostream>
#include "Player.h"
#include "BidingFacility.h"

int main()
{
	Player* player1 = new Player("John", 10, 10);
	Player* player2 = new Player("Ray", 10, 20);

	cout << player1->name << endl;
	cout << player1->age << endl;
	cout << player1->numCoins << endl;

	BidingFacility* bidFac = new BidingFacility();

}