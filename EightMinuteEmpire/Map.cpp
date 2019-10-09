#include "Map.h"
#include "Player.h"

//with each country as a class, our map nodes will be pointers to those classes on the heap


Map::Map()
{
	mapCountries = new vector<Country*>();
	mapContinents = new vector<Continent*>();
}


Map::~Map()
{
}

Country* Map::createCountry(string inputName, Continent* cont)
{
	//check if country already exists in map
	for (int j = 0; j < mapCountries->size(); j++)
	{
		if ((inputName.compare(mapCountries->at(j)->name->c_str())) == 0)
		{
			cout << '\"' << inputName << '\"' << " already exists in the map; it will not be added again." << endl;			
			return nullptr;
		}
	}
	return new Country(inputName, cont, this);
}


Continent* Map::createContinent(string inputName)
{
	//check if continent already exists in map
	for (int j = 0; j < mapContinents->size(); j++)
	{
		if ((inputName.compare(mapContinents->at(j)->name->c_str())) == 0)
		{
			cout << '\"' << inputName << '\"' << " already exists in the map; it will not be added again." << endl;
			return nullptr;
		}
	}

	return new Continent(inputName, this);
}

//not meant to be directly called
Country::Country(string inputName, Continent* cont, Map* map)
{
	name = new string(inputName);
	parentContinent = cont;
	adjCountries = new vector<Country*>(); 
	map->mapCountries->push_back(this); //add to map
	occupyingArmies = new vector<Army*>();
	cities = new vector<City*>();
	owningPlayer = nullptr;
}

Country::~Country()
{
}

Army* Country::getArmy(Player* ofPlayer)
{
	for (int i = 0; i < occupyingArmies->size(); i++)
	{
		if (occupyingArmies->at(i)->player == ofPlayer)
		{
			return occupyingArmies->at(i);
		}
	}
	return nullptr;
}

//not meant to be directly called
Continent::Continent(string inputName, Map* map)
{
	name = new string(inputName);
	map->mapContinents->push_back(this); //add to map
	containedCountries = new vector<Country*>();
}

Continent::~Continent()
{
}
