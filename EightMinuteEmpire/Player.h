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
	//Player(string, int, string);
	Player(string, int, int);
	~Player();

	string* name;
	int* numCoins;
	int* age;

/*	string* color;
	vector<Army*>* armies;
	vector<City*>* cities;
	vector<Country*>* ownedCountries;*/	// Part 1
	// vector<Card*>* hand;				// Part 4
	// vector<Good*>* goods				// Part 4
	//BidingFacility* bidingFacility;	// Part 5

	void createArmies();
	void createCities();

	void PayCoin(int);
	void PlaceNewArmies();
	void MoveArmies();
	void MoveOverLand();
	void BuildCity(Country*);
	void DestroyArmy(Country*);

	string getName();
	int getCoins();
	int getAge();
};