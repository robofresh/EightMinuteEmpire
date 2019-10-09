#include "Player.h"
#include "Map.h"

Army::Army(Player* newPlayer, int newId)
	: player(newPlayer), id(new int(newId)), occupiedCountry(nullptr) {}

Army::~Army() {}

void Army::setOccupiedCountry(Country* country)
{
	country = country;
}

City::City(Player* newPlayer, int newId)
	: player(newPlayer), id(new int(newId)), occupiedCountry(nullptr) {}

City::~City() {}

void City::setOccupiedCountry(Country* country)
{
	country = country;
}

int Player::availableCities()
{
	int numCities = 0;
	for (int i = 0; i < cities->size(); i++)
	{
		if (cities->at(i)->occupiedCountry == nullptr)
		{
			numCities++;
		}
	}
	return numCities;
}

City* Player::getAvailableCity()
{
	for (int j = 0; j < cities->size(); j++)
	{
		if (cities->at(j)->occupiedCountry == nullptr)
		{
			return cities->at(j);
		}
	}
	return nullptr;
}

int Player::availableArmies()
{
	int numArmies = 0;
	for (int i = 0; i < armies->size(); i++)
	{
		if (armies->at(i)->occupiedCountry == nullptr)
		{
			numArmies++;
		}
	}
	return numArmies;
}

Army* Player::getAvailableArmy()
{
	for (int j = 0; j < armies->size(); j++)
	{
		if (armies->at(j)->occupiedCountry == nullptr)
		{
			return armies->at(j);
		}
	}
	return nullptr;
}

Player::Player(string inputName, int inputAge, int coinAmount, string selectedColor)
{
	name = new string(inputName);
	age = new int(inputAge);
	numCoins = new int(coinAmount);
	color = new string(selectedColor);
	armies = new vector<Army*>();
	cities = new vector<City*>();
	ownedCountries = new vector<Country*>();
	// hand = new Hand()				// Part 4
	// goods = new vector<Good*>()				// Part 4
	// biddingFacility = new BidingFacility()	// Part 5
}

Player::~Player() {}

void Player::createArmies()
{
	for (int i = 0; i < 14; i++) {
		Army* army = new Army(this, i);
		this->armies->push_back(army);
	}
}

void Player::createCities()
{
	for (int i = 0; i < 3; i++) {
		City* city = new City(this, i);
		this->cities->push_back(city);
	}
}

void Player::printPlayer()
{
	cout << "Player: " << *(this->name) << ", age " << *(this->age) << ", color " << *(this->color) << endl;
	cout << "\tWith:" << endl;
	cout << "\t\t" << *(this->numCoins) << " coins." << endl;
	cout << "\t\t" << this->armies->size() << " armies (wooden cubes)." << endl;
	cout << "\t\t" << this->cities->size() << " cities (discs)." << endl;
	cout << "\t\t" << this->ownedCountries->size() << " countries owned.\n" << endl;
}

void Player::buildCity(Country* country)
{
	City* availableCity = this->getAvailableCity();
	availableCity->occupiedCountry = country;
	country->cities->push_back(availableCity);
}

void Player::destroyArmy(Country* country, Player* otherPlayer)
{
	Army* selectedArmy = country->getArmy(otherPlayer);
	selectedArmy->occupiedCountry = nullptr;
	auto it = find(country->occupyingArmies->begin(), country->occupyingArmies->end(), selectedArmy);
	if (it != country->occupyingArmies->end()) { country->occupyingArmies->erase(it); }	
}

void Player::moveArmies(Country* initCountry, Country* finalCountry, int amount)
{
	for (amount; amount > 0; amount--)
	{
		Army* selectedArmy = initCountry->getArmy(this);
		selectedArmy->occupiedCountry = finalCountry;
		finalCountry->occupyingArmies->push_back(selectedArmy);
		auto it = find(initCountry->occupyingArmies->begin(), initCountry->occupyingArmies->end(), selectedArmy);
		if (it != initCountry->occupyingArmies->end()) { initCountry->occupyingArmies->erase(it); }
	}
}

void Player::moveOverLand(Country* initCountry, Country* finalCountry)
{
	Army* selectedArmy = initCountry->getArmy(this);
	selectedArmy->occupiedCountry = finalCountry;
	finalCountry->occupyingArmies->push_back(selectedArmy);
	auto it = find(initCountry->occupyingArmies->begin(), initCountry->occupyingArmies->end(), selectedArmy);
	if (it != initCountry->occupyingArmies->end()) { initCountry->occupyingArmies->erase(it); }
}

void Player::payCoin(int amount, int* supply)
{
	*(this->numCoins) = *(this->numCoins) - amount;
	*supply = *supply + amount;
}

void Player::placeNewArmies(Country* country, int amount)
{
	for (amount; amount > 0; amount--)
	{
		Army* availableArmy = this->getAvailableArmy();
		availableArmy->occupiedCountry = country;
		country->occupyingArmies->push_back(availableArmy);
	}
}
