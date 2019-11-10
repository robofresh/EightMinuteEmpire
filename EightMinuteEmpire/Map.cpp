#include "Map.h"
#include "Player.h"

//with each country as a class, our map nodes will be pointers to those classes on the heap
Map::Map()
{
	mapCountries = new vector<Country*>();
	mapContinents = new vector<Continent*>();
	startingCountry = nullptr;
}

void Map::print() const
{
	//go through all continents and print their containedCountries
	for (auto i : *mapContinents)
	{
		cout << "\'" << i->name->c_str() << "\'" << " has the countries: " << endl;
		for (auto j : *i->containedCountries)
		{
			cout << "\t" << "\'" << j->name->c_str() << "\'";
			if (*j->isStartingCountry)
				cout << " (the starting country)";
				
			cout << endl;

			if (!j->occupyingArmies->empty())
			{
				cout << "\t\tThe occupying armies in " << j->name->c_str() << " are: " << endl;
				for (auto k : *j->occupyingArmies)
				{
					cout << "\t\t\t#" << k+1 << " owned by " << *k->player->name << endl;
				}
			}
			if (!j->cities->empty())
			{
				cout << "\t\tThe cities in " << j->name->c_str() << " are: " << endl;
				for (auto k : *j->cities)
				{
					cout << "\t\t\t#" << k+1 << " owned by " << *k->player->name << endl;
				}
			}
		}
	}
	
	//go through all countries and print their adjCountries as well
	for (auto i : *mapCountries)
	{
		if (!i->adjCountries->empty())
		{
			cout << "\'" << i->name->c_str() << "\'" << " is connected to the countries: " << endl;
			for (auto j : *i->adjCountries)
			{
				cout << "\t" <<  "\'"<< j->name->c_str() << "\'" << endl;
			}
		}
	}
}

Map::~Map()
{
	for (auto i : *mapCountries)
	{
		delete i;
		i = nullptr;
	}
	for (auto i : *mapContinents)
	{
		delete i;
		i = nullptr;
	}
	delete mapCountries, mapContinents;
	mapContinents = nullptr;
	mapCountries = nullptr;
}

//check if their is already a country in the map by the same name and return a pointer to it
Country* Map::getCountry(const string& str) const
{
	for (auto i : *mapCountries)
	{
		if (*i->name == str)
		{
			return i;
		}
	}
	return nullptr;
}

//check if their is already a continent in the map by the same name and return a pointer to it
Continent* Map::getContinent(const string& str) const
{
	for (auto i : *mapContinents)
	{
		if (*i->name == str)
			return i;
	}
	return nullptr;
}

//create a country and add it to the map
Country* Map::createCountry(const string &inputName, Continent* cont)
{
	//check if country already exists in map
	for (auto j : *mapCountries)
	{
		if (inputName == *j->name)
		{
			cout << '\"' << inputName << '\"' << " already exists in the map; it will not be added again." << endl;			
			return nullptr;
		}
	}
	return new Country(inputName, cont, this);
}

//create a continent and add it to the map
Continent* Map::createContinent(const string &inputName)
{
	//check if continent already exists in map
	for (auto j : *mapContinents)
	{
		if (inputName == *j->name)
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

Country::Country(const string &inputName, Continent* cont, Map* map)
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
	name = nullptr;
	parentContinent = nullptr;
	adjCountries = nullptr;
	occupyingArmies = nullptr;
	cities = nullptr;
	owningPlayer = nullptr;
}

Army* Country::getArmy(Player* ofPlayer) const
{
	for (auto i : *occupyingArmies)
	{
		if (i->player == ofPlayer)
		{
			return i;
		}
	}
	return nullptr;
}

//not meant to be directly called
Continent::Continent()
{
	name = new string("");
	containedCountries = new vector<Country*>();
}

Continent::Continent(const string &inputName, Map* map)
{
	name = new string(inputName);
	map->mapContinents->push_back(this); //add to map
	containedCountries = new vector<Country*>();
}

Continent::~Continent()
{
	delete name, containedCountries;
	name = nullptr;
	containedCountries = nullptr;
}

bool Country::removeArmy(Army* army) const
{
	for (int i = 0; i < occupyingArmies->size(); i++)
	{
		if (occupyingArmies->at(i) == army)
		{
			occupyingArmies->erase(occupyingArmies->begin() + i);
			return true;
		}
	}
	return false;
}

Map* Map::instance()
{
	if (!m_instance)
		m_instance = new Map;
	return m_instance;
}