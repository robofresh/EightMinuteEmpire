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
	// hand = new vector<Card*>()				// Part 4
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

void Player::buildCity(Country* country)
{
	City* availableCity = this->getAvailableCity();
	availableCity->occupiedCountry = country;		// Assigns country to the city's occupiedCountry var
	// Country should be updated with the new city ref (Part 1?)
}

void Player::destroyArmy(Country* country, Player* otherPlayer)
{
	// Find army in Country where player === otherPlayer 
	// Country should be updated with the new city ref (Part 1?)
}

void Player::moveArmies(Country* country)
{
	// Change country ref of army
}

void Player::moveOverLand()
{
	// Change country ref of army
}

void Player::payCoin(int amount, int* supply)
{
	*(this->numCoins) = *(this->numCoins) - amount;	// Decrease numCoin by amount
	*supply = *supply + amount;						// Increase supply by amount
}

void Player::placeNewArmies(Country* country, int amount)
{
	for (amount; amount > 0; amount--)
	{
		Army* availableArmy = this->getAvailableArmy();
		availableArmy->occupiedCountry = country;		// Assigns country to the army's occupiedCountry var
		// Country should be updated with the new army ref (Part 1?)
	}
}
