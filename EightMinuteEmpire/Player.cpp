#include "Player.h"
#include "Map.h"

Army::Army(Player* newPlayer, int newId)
	: player(newPlayer), id(new int(newId)), occupiedCountry() {}

Army::~Army() {}

void Army::setOccupiedCountry(Country* country)
{
	country = country;
}

City::City(Player* newPlayer, int newId)
	: player(newPlayer), id(new int(newId)), occupiedCountry() {}

City::~City() {}

void City::setOccupiedCountry(Country* country)
{
	country = country;
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
	// Add city to a country (assign country to city obj)
}

void Player::destroyArmy(Country* country)
{
	// Remove army from a country (remove country ref)
}

void Player::moveArmies()
{
	// Change country ref of army
}

void Player::moveOverLand()
{
	// Change country ref of army
}

void Player::payCoin(int amount)
{
	// Decrease numCoin; add coin to supply?
}

void Player::placeNewArmies()
{
	// Ref country in army obj, add army to country 
}
