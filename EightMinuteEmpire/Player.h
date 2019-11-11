#pragma once

#include <vector> 
#include <list>
#include <string>
#include <iostream>
#include "Map.h"
#include "BidingFacility.h"
#include "cards.h"
#include "GameObservers.h"

using namespace std;

class Army;
class City;
class Player;
class BidingFacility;

class Army
{
public:
	Army();
	Army(Player*);
	~Army();

	Player* player;
	Country* occupiedCountry;

	void setOccupiedCountry(Country*);
};

class City
{
public:
	City();
	City(Player*);
	~City();

	Player* player;
	Country* occupiedCountry;

	void setOccupiedCountry(Country*);
};

class Player: public Subject
{
public:
	Player();
	Player(string, int, int, string, Deck*);
	~Player();

	string* name;
	int* age;
	int* numCoins;
	string* color;
	vector<Army*>* armies;
	vector<City*>* cities;
	vector<Country*>* ownedCountries;
	vector<Continent*>* ownedContinents;
	Hand* hand;
	BidingFacility* bidFacObj;
	int* victoryPoint;
	vector<Player*>* scores; 
	
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
	void computeScore(Map*);
	void ignore(Cards*);
	void payCard(Cards*, int, int*);
};