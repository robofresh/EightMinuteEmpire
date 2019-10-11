#include "Map.h"
#include "Player.h"

//with each country as a class, our map nodes will be pointers to those classes on the heap


Map::Map()
{
	mapCountries = new vector<Country*>();
	mapContinents = new vector<Continent*>();
}

void Map::print()
{
	for (int i = 0; i < mapContinents->size(); i++)
	{
		cout << "\'" << mapContinents->at(i)->name->c_str() << "\'" << " has the countries: " << endl;
		for (int j = 0; j < mapContinents->at(i)->containedCountries->size(); j++)
		{
			cout << "\t" << "\'" << mapContinents->at(i)->containedCountries->at(j)->name->c_str() << "\'" << endl;
		}
	}

	for (int i = 0; i < mapCountries->size(); i++)
	{
		if (mapCountries->at(i)->adjCountries->size() > 0)
		{
			cout << "\'" << mapCountries->at(i)->name->c_str() << "\'" << " is connected to the countries: " << endl;
			for (int j = 0; j < mapCountries->at(i)->adjCountries->size(); j++)
			{
				cout << "\t" <<  "\'"<< mapCountries->at(i)->adjCountries->at(j)->name->c_str() << "\'" << endl;
			}
		}
	}
}

Map::~Map()
{
	delete mapCountries, mapContinents;
}

Country* Map::getCountry(string str)
{
	for (int i = 0; i < mapCountries->size(); i++)
	{
		if (mapCountries->at(i)->name->compare(str) == 0)
		{
			return mapCountries->at(i);
		}
	}
	return nullptr;
}

Continent* Map::getContinent(string str)
{
	for (int i = 0; i < mapContinents->size(); i++)
	{
		if (mapContinents->at(i)->name->compare(str) == 0)
			return mapContinents->at(i);
	}
	return nullptr;
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
	cities = new vector<City*>();
	occupyingArmies = new vector<Army*>;
	owningPlayer = nullptr;

}

Country::~Country()
{
	delete name, parentContinent, adjCountries, occupyingArmies, cities, owningPlayer;
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
	delete name, containedCountries;
}
