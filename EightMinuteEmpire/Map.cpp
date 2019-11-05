#include "Map.h"
#include "Player.h"

//with each country as a class, our map nodes will be pointers to those classes on the heap
Map::Map()
{
	mapCountries = new vector<Country*>();
	mapContinents = new vector<Continent*>();
	startingCountry = nullptr;
}

void Map::mapNotify()
{
	Notify();
}

void Map::print()
{
	//go through all continents and print their containedCountries
	for (int i = 0; i < mapContinents->size(); i++)
	{
		cout << "\'" << mapContinents->at(i)->name->c_str() << "\'" << " has the countries: " << endl;
		for (int j = 0; j < mapContinents->at(i)->containedCountries->size(); j++)
		{
			cout << "\t" << "\'" << mapContinents->at(i)->containedCountries->at(j)->name->c_str() << "\'";
			if (*mapContinents->at(i)->containedCountries->at(j)->isStartingCountry)
				cout << " (the starting country)";
				
				cout << endl;

			if (mapContinents->at(i)->containedCountries->at(j)->occupyingArmies->size() > 0)
			{
				cout << "\t\tThe occupying armies in " << mapContinents->at(i)->containedCountries->at(j)->name->c_str() << " are: " << endl;
				for (int k = 0; k < mapContinents->at(i)->containedCountries->at(j)->occupyingArmies->size(); k++)
				{
					cout << "\t\t\t#" << k+1 << " owned by " << *mapContinents->at(i)->containedCountries->at(j)->occupyingArmies->at(k)->player->name << endl;
				}
			}
			if (mapContinents->at(i)->containedCountries->at(j)->cities->size() > 0)
			{
				cout << "\t\tThe cities in " << mapContinents->at(i)->containedCountries->at(j)->name->c_str() << " are: " << endl;
				for (int k = 0; k < mapContinents->at(i)->containedCountries->at(j)->cities->size(); k++)
				{
					cout << "\t\t\t#" << k+1 << " owned by " << *mapContinents->at(i)->containedCountries->at(j)->cities->at(k)->player->name << endl;
				}
			}
		}
	}
	
	//go through all countries and print their adjCountries as well
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
	for (int i = 0; i < mapCountries->size(); i++)
	{
		delete mapCountries->at(i);
		mapCountries->at(i) = NULL;
	}
	for (int i = 0; i < mapContinents->size(); i++)
	{
		delete mapContinents->at(i);
		mapContinents->at(i) = NULL;
	}
	delete mapCountries, mapContinents;
	mapContinents = NULL;
	mapCountries = NULL;
}

//check if their is already a country in the map by the same name and return a pointer to it
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

//check if their is already a continent in the map by the same name and return a pointer to it
Continent* Map::getContinent(string str)
{
	for (int i = 0; i < mapContinents->size(); i++)
	{
		if (mapContinents->at(i)->name->compare(str) == 0)
			return mapContinents->at(i);
	}
	return nullptr;
}

//create a country and add it to the map
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

//create a continent and add it to the map
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
Country::Country()
{
	name = new string("");
	parentContinent = nullptr;
	adjCountries = new vector<Country*>();
	cities = new vector<City*>();
	occupyingArmies = new vector<Army*>;
	owningPlayer = nullptr;
}

Country::Country(string inputName, Continent* cont, Map* map)
{
	name = new string(inputName);
	parentContinent = cont;
	adjCountries = new vector<Country*>(); 
	map->mapCountries->push_back(this); //add to map
	cities = new vector<City*>();
	occupyingArmies = new vector<Army*>;
	owningPlayer = nullptr;
	isStartingCountry = new bool(false);
}

Country::~Country()
{
	delete name, parentContinent, adjCountries, occupyingArmies, cities, owningPlayer;
	name = NULL;
	parentContinent = NULL;
	adjCountries = NULL;
	occupyingArmies = NULL;
	cities = NULL;
	owningPlayer = NULL;
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

void Country::addCity(City* city)
{
	this->cities->push_back(city);
	// Check and see if the country's owner changed.
	// Get Singleton Map instance and call map->mapNotify()
}

void Country::addArmy(Army* army)
{
	this->occupyingArmies->push_back(army);
	// Check and see if the country's owner changed.
	// Get Map Singleton and call map->mapNotify();
}

void Country::moveArmy(Country* newCountry, Army* army)
{
	newCountry->occupyingArmies->push_back(army);
	// Check and see if the country's owner changed.
	this->removeArmy(army);
}

//not meant to be directly called
Continent::Continent()
{
	name = new string("");
	containedCountries = new vector<Country*>();
}

Continent::Continent(string inputName, Map* map)
{
	name = new string(inputName);
	map->mapContinents->push_back(this); //add to map
	containedCountries = new vector<Country*>();
}

Continent::~Continent()
{
	delete name, containedCountries;
	name = NULL;
	containedCountries = NULL;
}

bool Country::removeArmy(Army* army)
{
	for (int i = 0; i < occupyingArmies->size(); i++)
	{
		if (occupyingArmies->at(i) == army)
		{
			occupyingArmies->erase(occupyingArmies->begin() + i);
			// Check and see if the country's owner changed.
			// Get Map Singleton and call map->mapNotify();
			return true;
		}
	}
	return false;
}