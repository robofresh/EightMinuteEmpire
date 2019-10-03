#include <iostream>
#include "Player.h"

int main()
{
<<<<<<< HEAD
	Player *player1 = new Player("John", 10, 10);

	cout << *player1->age << endl; 
	cout << *player1->numCoins << endl;
	cout << *player1->name << endl;


=======
	Player *player1 = new Player("John", 26, 7, "Red");
	cout << "Player name: " << player1->name->c_str() << endl; //print player name
	cout << "Player age: " << *(player1)->age << endl; //print player age
	cout << "Player color: " << player1->color->c_str() << endl; //print player color
	cout << "Number of coins player has: " << *(player1)->numCoins << endl; //print player coin value

	player1->createArmies();
	player1->createCities();

	cout << "Player has " << player1->armies->size() << " armies (wooden cubes)." << endl;
	cout << "Player has " << player1->cities->size() << " cities (discs)." << endl;

	for (int i = 0; i < player1->armies->size(); i++)
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
	}

	cout << "Player currently owns " << player1->ownedCountries->size() << " countries." << endl;
>>>>>>> 379b933a3b3a6b3b7551054a089ecb937adb8f68
}