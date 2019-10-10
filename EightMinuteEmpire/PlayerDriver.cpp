//#include <iostream>
//#include "Player.h"
//
//int main()
//{
//	int* supply = new int(0);
//	cout << "Supply starts out with " << *supply << " coins.\n" << endl;
//
//	// Make a map object and populate map object with Countries and Continents. Will replace with loader. 
//	Map* map = new Map(); 
//	for (int i = 0; i < 10; i++) // 
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
//	// Creating Players
//	cout << "Creating player 1." << endl;
//	Player *player1 = new Player("John", 26, 7, "Red");
//	player1->createArmies();
//	player1->createCities();
//	player1->printPlayer();
//
//	cout << "Creating player 2." << endl;
//	Player* player2 = new Player("Jane", 25, 7, "Blue");
//	player2->createArmies();
//	player2->createCities();
//	player2->printPlayer();
//
//	cout << "Using method 'payCoin()' to pay 2 coins from Player 1." << endl;
//	player1->payCoin(2, supply);
//	cout << "Player 1 now has " << *(player1->numCoins) << " coins." << endl;
//	cout << "Supply is now at " << *supply << " coins.\n" << endl;
//
//	cout << "Using method 'buildCity()' to place a city of Player 1's in Country 0." << endl;
//	player1->buildCity(map->mapCountries->at(0));
//	cout << "Using method 'buildCity()' to place a city of Player 2's in Country 0." << endl;
//	player2->buildCity(map->mapCountries->at(0));
//	cout << "Reviewing cities in Country 0:" << endl;
//	for (int k = 0; k < map->mapCountries->at(0)->cities->size(); k++)
//	{
//		cout << "\tA city owned by " << *(map->mapCountries->at(0)->cities->at(k)->player->name) << " was found in Country 0." << endl;
//	}
//
//	cout << endl;
//	cout << "Using method 'placeNewArmies()' to place a single Army of Player 1's in Country 0 and two Armies in Country 1" << endl;
//	player1->placeNewArmies(map->mapCountries->at(0), 1);
//	player1->placeNewArmies(map->mapCountries->at(1), 2);
//	cout << "Using method 'placeNewArmies()' to place three Armies of Player 2's in Country 0" << endl;
//	player2->placeNewArmies(map->mapCountries->at(0), 3);
//	cout << "Reviewing armies in Country 0:" << endl;
//	for (int k = 0; k < map->mapCountries->at(0)->occupyingArmies->size(); k++)
//	{
//		cout << "\tAn army owned by " << *(map->mapCountries->at(0)->occupyingArmies->at(k)->player->name) << " was found in Country 0." << endl;
//	}
//	cout << "Reviewing armies in Country 1:" << endl;
//	for (int k = 0; k < map->mapCountries->at(1)->occupyingArmies->size(); k++)
//	{
//		cout << "\tAn army owned by " << *(map->mapCountries->at(1)->occupyingArmies->at(k)->player->name) << " was found in Country 1." << endl;
//	}
//
//	cout << endl;
//	cout << "Using method 'destroyArmy()' to remove a single Army of Player 2's in Country 0 by Player 1." << endl;
//	player1->destroyArmy(map->mapCountries->at(0), player2);
//	cout << "Reviewing armies in Country 0:" << endl;
//	for (int k = 0; k < map->mapCountries->at(0)->occupyingArmies->size(); k++)
//	{
//		cout << "\tAn army owned by " << *(map->mapCountries->at(0)->occupyingArmies->at(k)->player->name) << " was found in Country 0." << endl;
//	}
//
//	cout << endl;
//	cout << "Using method 'moveArmies()' to move a single Army of Player 1's from Country 1 to Country 2." << endl;
//	player1->moveArmies(map->mapCountries->at(1), map->mapCountries->at(2), 1);
//	cout << "Reviewing armies in Country 1:" << endl;
//	for (int k = 0; k < map->mapCountries->at(1)->occupyingArmies->size(); k++)
//	{
//		cout << "\tAn army owned by " << *(map->mapCountries->at(1)->occupyingArmies->at(k)->player->name) << " was found in Country 1." << endl;
//	}
//	cout << "Reviewing armies in Country 2:" << endl;
//	for (int k = 0; k < map->mapCountries->at(2)->occupyingArmies->size(); k++)
//	{
//		cout << "\tAn army owned by " << *(map->mapCountries->at(2)->occupyingArmies->at(k)->player->name) << " was found in Country 2." << endl;
//	}
//
//	//cout << endl;
//	//cout << "Using method 'moveOverLand()' to move a single Army of Player 1's to a country in another continent..." << endl;
//	//player1->moveOverLand(...);
//}
