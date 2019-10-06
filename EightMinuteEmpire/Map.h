#pragma once

#include <vector> 
#include <list>
#include <string>
#include <iostream>
#include "Player.h"

using namespace std;

//i have pointers to vectors of pointers... assign said everything had to be a pointer

class Country;
class Map;

//not sure how continents will work because "subgraph" is unclear
class Continent
{
public:
	Continent(string, Map*);
	~Continent();

	string* name;


	vector<Country*>* containedCountries; //pointer to a vector of pointers to countries contained in continent
};


class Country
{
public:
	Country(string, Continent*, Map*);

	~Country();

	string *name;

	vector<Country*> *adjCountries; //pointer to a vector of pointers to all adjacent countries
	Continent* parentContinent;

	vector<Army*>* occupyingArmies;
	vector<Player*>* occupyingPlayers;
	Player* owner;

};


class Map
{
public:
	Map();
	~Map();

	Country* createCountry(string, Continent*);
	Continent* createContinent(string);

	vector<Country*> *mapCountries; //pointer to a vector of pointers to all Countries
	vector<Continent*>* mapContinents; //ditto for continents

	Country* getCountry(string);
	Continent* getContinent(string);

	void print();

};


