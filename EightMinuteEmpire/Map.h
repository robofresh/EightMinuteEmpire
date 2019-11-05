#pragma once

#include <vector> 
#include <list>
#include <string>
#include <iostream>
#include "GameObservers.h"

using namespace std;

class Country;
class Map;
class Army;
class City;
class Player;

class Continent
{
public:
	Continent();
	Continent(string, Map*);
	~Continent();

	string* name;


	vector<Country*>* containedCountries; //pointer to a vector of pointers to countries contained in continent
};


class Country
{
public:
	Country();
	Country(string, Continent*, Map*);

	~Country();

	bool* isStartingCountry;
	string *name;

	vector<Country*> *adjCountries; //pointer to a vector of pointers to all adjacent countries
	Continent* parentContinent;
	vector<Army*>* occupyingArmies; //vector of all armies in the country
	vector<City*>* cities; //vector of all cities in the country
	Player* owningPlayer; //pointer to the owning player

	Army* getArmy(Player*);
	bool removeArmy(Army*);
	void addCity(City*);
	void addArmy(Army*);
	void moveArmy(Country*, Army*);

};


class Map : public Subject
{
public:
	Map();
	~Map();

	Country* createCountry(string, Continent*);
	Continent* createContinent(string);

	Country* startingCountry;

	vector<Country*> *mapCountries; //pointer to a vector of pointers to all Countries
	vector<Continent*>* mapContinents; //ditto for continents

	Country* getCountry(string); //explained in .cpp
	Continent* getContinent(string);

	void print();
	void mapNotify();
};


