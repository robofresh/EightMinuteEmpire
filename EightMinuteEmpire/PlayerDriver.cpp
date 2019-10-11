#include <iostream>
#include "Player.h"

	int main()
{
	// Creating a supply for testing purpose. 
	int* supply = new int(0);

	// Make a map object and populate map object with Countries and Continents, for testing purpose. 
	Map* map = new Map();
	Continent* cont0 = map->createContinent("North America");
	Continent* cont1 = map->createContinent("South America");
	Country* country0 = map->createCountry("Country 0", cont0);
	Country* country1 = map->createCountry("Country 1", cont0);
	Country* country2 = map->createCountry("Country 2", cont1);

	cout << "\n*****Test 1 : Creating Players*****" << endl;
	cout << "Creating player 1." << endl;
	Player* player1 = new Player("John", 26, 7, "Red");
	player1->printPlayer();
	cout << "Creating player 2." << endl;
	Player* player2 = new Player("Jane", 25, 7, "Blue");
	player2->printPlayer();

	cout << "\n*****Test 2 : Using Method payCoin() to Pay 2 Coins from Player 1*****" << endl;
	player1->payCoin(2, supply);
	cout << "Supply is now at " << *supply << " coins.\n" << endl;

	cout << "\n*****Test 3 : Using Method buildCity() to Place Cities*****" << endl;
	cout << "Placing a city of Player 1's in Country 0." << endl;
	player1->buildCity(map->mapCountries->at(0));
	cout << "Placing a city of Player 2's in Country 0." << endl;
	player2->buildCity(map->mapCountries->at(0));

	cout << "\n*****Test 4 : Using Method placeNewArmies()*****" << endl;
	cout << "Placing a single Army of Player 1's in Country 0" << endl;
	player1->placeNewArmies(map->mapCountries->at(0), 1);
	cout << "Placing two Armies of Player 2's in Country 0" << endl;
	player2->placeNewArmies(map->mapCountries->at(0), 2);

	cout << "\n*****Test 5 : Using Method destroyArmy()*****" << endl;
	cout << "Remove a single Army of Player 2's in Country 0 by Player 1." << endl;
	player1->destroyArmy(map->mapCountries->at(0), player2);

	cout << "\n*****Test 6 : Using Method moveArmies()*****" << endl;
	cout << "Move a single Army of Player 1's from Country 0 to Country 1." << endl;
	cout << "Country 0 and Country 1 are adjacent countries in North America." << endl;
	player1->moveArmies(map->mapCountries->at(0), map->mapCountries->at(1), 1);

	cout << "\n*****Test 7 : Using Method moveOverLand()*****" << endl;
	cout << "Move a single Army of Player 2's from Country 0 to Country 2." << endl;
	cout << "Country 0 is in North America, and Country 2 is in South America." << endl;
	player2->moveOverLand(map->mapCountries->at(0), map->mapCountries->at(2));

	cout << "\n*****Clean-up*****" << endl;
	delete supply;
	delete player2;
	delete player1;
	delete country2;
	delete country1;
	delete country0;
	delete cont1;
	delete cont0;
	delete map;
}
