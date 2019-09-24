#pragma once

#include <vector> 
#include <list>
#include <string>

using namespace std;

//i have pointers to vectors of pointers... assign said everything had to be a pointer

//not sure how continents will work because "subgraph" is unclear
class Continent
{
public:
	Continent();
	~Continent();

//	vector<Country*>* containedCountries; //pointer to a vector of pointers to countries contained in continent
};


class Country
{
public:
	Country(string);

	~Country();

	string *name;

	vector<Country*> *adjCountries; //pointer to a vector of pointers to all adjacent countries
	Continent* parentContinent;
};


class Map
{
public:
	Map();
	~Map();

	vector<Country*> *mapCountries; //pointer to a vector of pointers to all Countries
	vector<Continent*>* mapContinents; //ditto for continents

};


