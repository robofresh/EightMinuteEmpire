#include <iostream>
#include "Player.h"

int main()
{
	int* supply = new int(0);
	cout << "Supply starts out with " << *supply << " coins.\n" << endl;

	cout << "Creating player 1." << endl;
	Player *player1 = new Player("John", 26, 7, "Red");
	cout << "Player 1: " << *(player1->name) << ", ";
	cout << "age " << *(player1->age) << ", ";
	cout << "color " << *(player1->color) << endl;
	cout << "\tStarting with:" << endl;
	cout << "\t\t" << *(player1->numCoins) << " coins." << endl;

	player1->createArmies();
	player1->createCities();

	cout << "\t\t" << player1->armies->size() << " armies (wooden cubes)." << endl;
	cout << "\t\t" << player1->cities->size() << " cities (discs)." << endl;

	/*for (int i = 0; i < player1->armies->size(); i++)
	{
		cout << "Army id: " << *(player1)->armies->at(i)->id << ", ";
		cout << "Army belongs to: " << player1->armies->at(i)->player->name->c_str();
		cout << endl;
	}

	for (int i = 0; i < player1->cities->size(); i++)
	{
		cout << "City id: " << *(player1)->cities->at(i)->id << ", ";
		cout << "City belongs to: " << player1->cities->at(i)->player->name->c_str();
		cout << endl;
	}*/

	cout << "\t\t" << player1->ownedCountries->size() << " countries owned\n" << endl;

	cout << "Using method 'payCoin()' to pay 2 coins from Player 1." << endl;
	player1->payCoin(2, supply);
	cout << "Player now has " << *(player1->numCoins) << " coins." << endl;
	cout << "Supply is now at " << *supply << " coins." << endl;
}