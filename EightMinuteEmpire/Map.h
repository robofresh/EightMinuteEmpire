#pragma once

#include <vector> 
#include <list>
#include <string>
#include <iostream>
#include "Player.h"
#include "GameObservers.h"

using namespace std;

class Country;
class Continent;
class Army;
class City;
class Player;
class Map;

class Continent
{
public:
	Continent();
	Continent(const string&, Map*);
	~Continent();
	string* name;
	void changeOwner(Player*);
	Player* owningPlayer;
	bool updateContinentOwner();
	Player* findContinentOwner() const;
	vector<Country*>* containedCountries; //pointer to a vector of pointers to countries contained in continent
};


class Country
{
public:
	Country();
	Country(const string&, Continent*, Map*);

	~Country();

	bool* isStartingCountry;
	string *name;

	vector<Country*> *adjCountries; //pointer to a vector of pointers to all adjacent countries
	Continent* parentContinent;
	vector<Army*>* occupyingArmies; //vector of all armies in the country
	vector<City*>* cities; //vector of all cities in the country
	Player* owningPlayer; //pointer to the owning player

	Army* getArmy(Player*) const;
	bool removeArmy(Army*);
	void addCity(City*);
	void addArmy(Army*);
	void moveArmy(Country*, Army*);
	void changeOwner(Player*);
	bool updateCountryOwner();
	Player* findCountryOwner() const;

};


class Map : public Subject
{
private:
	static Map* m_instance;
	Map();
public:
	static Map* getInstance();
	~Map();
	
	Country* createCountry(const string&, Continent*);
	Continent* createContinent(const string&);

	Country* startingCountry;

	vector<Country*> *mapCountries; //pointer to a vector of pointers to all Countries
	vector<Continent*>* mapContinents; //ditto for continents

	Country* getCountry(const string&) const; //explained in .cpp
	Continent* getContinent(const string&) const;

	void print() const;
	void mapNotify();
};


