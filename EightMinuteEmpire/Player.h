#pragma once

#include <vector> 
#include <list>
#include <string>
#include <iostream>
#include "Map.h"
#include "BidingFacility.h"

using namespace std;

class Army;
class City;
class Player;
class BidingFacility;

class Army
{
public:
	Army(Player*);
	~Army();

	Player* player;
	Country* occupiedCountry;

	void setOccupiedCountry(Country*);
};

class City
{
public:
	City(Player*);
	~City();

	Player* player;
	Country* occupiedCountry;

	void setOccupiedCountry(Country*);
};

class Player
{
public:
	Player(string, int, int, string);
	~Player();

	string* name;
	int* age;
	int* numCoins;
	string* color;
	vector<Army*>* armies;
	vector<City*>* cities;
	vector<Country*>* ownedCountries;
	//Hand* hand;						Part 4
	//vector<Good*>* goods				Part 4
	BidingFacility* bidFacObj;

	void createArmies();
	void createCities();
	int availableCities();
	int availableArmies();
	City* getAvailableCity();
	Army* getAvailableArmy();
	void printPlayer();
	void payCoin(int, int*);
	void placeNewArmies(Country*, int);
	void moveArmies(Country*, Country*, int);
	void moveOverLand(Country*, Country*);
	void buildCity(Country*);
	void destroyArmy(Country*, Player*);
};