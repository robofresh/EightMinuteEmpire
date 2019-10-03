#include <iostream>
#include "Player.h"

int main()
{
	Player *player1 = new Player("John", 10, 10);

	cout << *player1->age << endl; 
	cout << *player1->numCoins << endl;
	cout << *player1->name << endl;


}