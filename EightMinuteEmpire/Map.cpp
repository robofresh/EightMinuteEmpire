#include <map>
#include "Map.h"
#include "Player.h"

Map* Map::m_instance = nullptr;

//with each country as a class, our map nodes will be pointers to those classes on the heap
Map::Map()
{
	mapCountries = new vector<Country*>();
	mapContinents = new vector<Continent*>();
	startingCountry = nullptr;
}

Map* Map::getInstance()
{
	if (m_instance == 0) {
		m_instance = new Map();
	}
	return m_instance;
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
	if (0 != m_instance)
	{
		Map* pTemp = m_instance;
		m_instance = 0;

		delete pTemp;
	}
	
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

Player* Country::findCountryOwner() const
{
	Player* owningPlayer = nullptr;
	map<Player*, int> playerCount;

	if (this->occupyingArmies->size() > 0)
	{
		for (int j = 0; j < this->occupyingArmies->size(); j++)
		{
			auto search = playerCount.find(this->occupyingArmies->at(j)->player);
			if (search != playerCount.end())
			{
				search->second++;
			}
			else
			{
				playerCount.insert(pair<Player*, int>(this->occupyingArmies->at(j)->player, 1));
			}
		}
	}

	if (this->cities->size() > 0)
	{
		for (int j = 0; j < this->cities->size(); j++)
		{
			auto search = playerCount.find(this->cities->at(j)->player);
			if (search != playerCount.end())
			{
				search->second++;
			}
			else
			{
				playerCount.insert(pair<Player*, int>(this->cities->at(j)->player, 1));
			}
		}
	}

	int max = 0;
	for (auto it = playerCount.begin(); it != playerCount.end(); it++)
	{
		if (it->second > max)
		{
			max = it->second;
			owningPlayer = it->first;
		}
		if (it->second == max && it->first != owningPlayer)
		{
			owningPlayer = nullptr;
		}
	}

	return owningPlayer;
}

Player* Continent::findContinentOwner() const
{
	Player* owningPlayer = nullptr;
	map<Player*, int> playerCount;

	for (int j = 0; j < this->containedCountries->size(); j++)
	{
		Player* countryOwningPlayer = this->containedCountries->at(j)->findCountryOwner();
		auto search = playerCount.find(countryOwningPlayer);
		if (search != playerCount.end())
		{
			search->second++;
		}
		else
		{
			playerCount.insert(pair<Player*, int>(countryOwningPlayer, 1));
		}
	}

	int max = 0;
	for (auto it = playerCount.begin(); it != playerCount.end(); it++)
	{
		if (it->second > max && it->first != nullptr)
		{
			max = it->second;
			owningPlayer = it->first;
		}
		if (it->second == max && it->first != owningPlayer)
		{
			owningPlayer = nullptr;
		}
	}
	
	return owningPlayer;
}

bool Country::updateCountryOwner()
{
	Player* countryOwner = this->findCountryOwner();
	if (this->owningPlayer != countryOwner) {
		this->changeOwner(countryOwner);
		if (countryOwner != nullptr) {
			countryOwner->addOwnedCountry(this);
		}
		this->parentContinent->updateContinentOwner();
		Map* map = Map::getInstance();
		map->Notify();
		return true;
	}
	return false;
}

bool Continent::updateContinentOwner()
{
	Player* continentOwner = this->findContinentOwner();
	if (this->owningPlayer != continentOwner) {
		this->changeOwner(continentOwner);
		if (continentOwner != nullptr) {
			*continentOwner->victoryPoint = *continentOwner->victoryPoint + 1;
			continentOwner->addOwnedContinent(this);
		}
		return true;
	}
	return false;
}

void Country::addCity(City* city)
{
	this->cities->push_back(city);
	bool ownerChanged = this->updateCountryOwner();
	if (!ownerChanged)
	{
		Map* map = Map::getInstance();
		map->Notify();
	}
}

void Country::addArmy(Army* army)
{
	this->occupyingArmies->push_back(army);
	bool ownerChanged = this->updateCountryOwner();
	if (!ownerChanged)
	{
		Map* map = Map::getInstance();
		map->Notify();
	}
}

void Country::moveArmy(Country* newCountry, Army* army)
{
	newCountry->addArmy(army);
	this->removeArmy(army); // Country owning update would be done in removeArmy fucntion.
}

bool Country::removeArmy(Army* army)
{
	for (int i = 0; i < occupyingArmies->size(); i++)
	{
		if (occupyingArmies->at(i) == army)
		{
			occupyingArmies->erase(occupyingArmies->begin() + i);
			bool ownerChanged = this->updateCountryOwner();
			if (!ownerChanged)
			{
				Map* map = Map::getInstance();
				map->Notify();
			}
			return true;
		}
	}
	return false;
}

//not meant to be directly called
Continent::Continent()
{
	name = new string("");
	containedCountries = new vector<Country*>();
	owningPlayer = nullptr;
}

Continent::Continent(const string &inputName, Map* map)
{
	name = new string(inputName);
	map->mapContinents->push_back(this); //add to map
	containedCountries = new vector<Country*>();
	owningPlayer = nullptr;
}

Continent::~Continent()
{
	delete name, containedCountries;
	name = nullptr;
	containedCountries = nullptr;
}

void Country::changeOwner(Player* new_owner)
{
	if(owningPlayer == nullptr)
	{
		owningPlayer = new_owner;
	} else
	{
		owningPlayer->removeOwnedCountry(this);
		owningPlayer = new_owner;
	}
}

void Continent::changeOwner(Player* new_owner)
{
	if (owningPlayer == nullptr)
	{
		owningPlayer = new_owner;
	}
	else
	{
		owningPlayer->removeOwnedContinent(this);
		owningPlayer = new_owner;
	}
}
