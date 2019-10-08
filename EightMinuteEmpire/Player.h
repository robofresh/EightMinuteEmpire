#pragma once

#include <vector> 
#include <list>
#include <string>
#include <iostream>
#include "Map.h"

using namespace std;

class Army;
class City;
class Player;

class Army
{
public:
	Army(Player*, int);
	~Army();

	int* id;
	Player* player;
	Country* occupiedCountry;

	void setOccupiedCountry(Country*);
};

class City
{
public:
	City(Player*, int);
	~City();

	int* id;
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
	vector<Country*>* ownedCountries;	// Part 1
	// Hand* hand;				// Part 4
	// vector<Good*>* goods				// Part 4
	//BidingFacility* bidingFacility;	// Part 5

	void createArmies();
	void createCities();
	int availableCities();
	int availableArmies();
	City* getAvailableCity();
	Army* getAvailableArmy();

	void payCoin(int, int*);
	void placeNewArmies(Country*, int);
	void moveArmies(Country*, Country*, int);
	void moveOverLand(Country*, Country*);
	void buildCity(Country*);
	void destroyArmy(Country*, Player*);
};