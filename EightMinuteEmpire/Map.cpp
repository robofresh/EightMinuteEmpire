#include "Map.h"
#include <string>
//with each country as a class, our map nodes will be pointers to those classes on the heap


Map::Map()
{
	mapCountries = new vector<Country*>();
	mapContinents = new vector<Continent*>();
}


Map::~Map()
{
}



Country::Country(string inputName, Continent* cont, Map* map)
{
	//check if country already exists in map
	for (int j = 0; j < map->mapCountries->size(); j++)
	{
		if ((inputName.compare(map->mapCountries->at(j)->name->c_str())) == 0)
			return;
	}

	name = new string(inputName);
	parentContinent = cont;
	adjCountries = new vector<Country*>(); //add to map
	map->mapCountries->push_back(this);

}


Country::~Country()
{
}

Continent::Continent(string inputName, Map* map)
{
	//check if continent already exists in map
	for (int j = 0; j < map->mapContinents->size(); j++)
	{
		if ((inputName.compare(map->mapContinents->at(j)->name->c_str())) == 0)
			return;
	}

	name = new string(inputName);
	map->mapContinents->push_back(this); //add to map
	containedCountries = new vector<Country*>();
}


Continent::~Continent()
{
}
