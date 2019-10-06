//#include <iostream>
//#include "Player.h"
//
//int main()
//{
//	int* supply = new int(0);
//	cout << "Supply starts out with " << *supply << " coins.\n" << endl;
//
//	Map* map = new Map(); // make a map object
//	for (int i = 0; i < 10; i++) // populate map object with Countries and Continents. Eventual change for map loader
//	{
//		Continent* cont = map->createContinent("Continent " + to_string(i / 2));
//		Country* country = map->createCountry("Country " + to_string(i) , cont);
//
//		if (country != nullptr)
//		{
//			for (int j = 0; j < i; j += 2)
//			{
//				country->adjCountries->push_back(map->mapCountries->at(j));
//			}
//		}
//	}
//	cout << endl;
//
//	cout << "Creating player 1." << endl;
//	Player *player1 = new Player("John", 26, 7, "Red");
//	player1->createArmies();
//	player1->createCities();
//
//	cout << "Player 1: " << *(player1->name) << ", age " << *(player1->age) << ", color " << *(player1->color) << endl;
//	cout << "\tStarting with:" << endl;
//	cout << "\t\t" << *(player1->numCoins) << " coins." << endl;
//	cout << "\t\t" << player1->armies->size() << " armies (wooden cubes)." << endl;
//	cout << "\t\t" << player1->cities->size() << " cities (discs)." << endl;
//	cout << "\t\t" << player1->ownedCountries->size() << " countries owned\n" << endl;
//
//	cout << "Creating player 2." << endl;
//	Player* player2 = new Player("Jane", 25, 7, "Blue");
//	player2->createArmies();
//	player2->createCities();
//
//	cout << "Player 2: " << *(player2->name) << ", age " << *(player2->age) << ", color " << *(player2->color) << endl;
//	cout << "\tStarting with:" << endl;
//	cout << "\t\t" << *(player2->numCoins) << " coins." << endl;
//	cout << "\t\t" << player2->armies->size() << " armies (wooden cubes)." << endl;
//	cout << "\t\t" << player2->cities->size() << " cities (discs)." << endl;
//	cout << "\t\t" << player2->ownedCountries->size() << " countries owned\n" << endl;
//
//	cout << "Using method 'payCoin()' to pay 2 coins from Player 1." << endl;
//	player1->payCoin(2, supply);
//	cout << "Player 1 now has " << *(player1->numCoins) << " coins." << endl;
//	cout << "Supply is now at " << *supply << " coins.\n" << endl;
//
//	cout << "Using method 'buildCity()' to place a city of Player 1's in Country 0." << endl;
//	player1->buildCity(map->mapCountries->at(0));
//	for (int k = 0; k < player1->cities->size(); k++)
//	{
//		if (player1->cities->at(k)->occupiedCountry != nullptr)
//		{
//			cout << "This player has a city occupied in: " << *(player1->cities->at(k)->occupiedCountry->name) << endl;
//		}
//	}
//
//	cout << endl;
//	cout << "Using method 'placeNewArmies()' to place a single Army of Player 1's in Country 2 and in Country 4" << endl;
//	player1->placeNewArmies(map->mapCountries->at(2), 1);
//	player1->placeNewArmies(map->mapCountries->at(4), 1);
//	for (int l = 0; l < player1->armies->size(); l++)
//	{
//		if (player1->armies->at(l)->occupiedCountry != nullptr)
//		{
//			cout << "This player has an army occupied in: " << *(player1->armies->at(l)->occupiedCountry->name) << endl;
//		}
//	}
//
//}