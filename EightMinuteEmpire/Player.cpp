#include "Player.h"
#include "Map.h"

Army::Army(Player* newPlayer, int newId)
{
	player = newPlayer;
	id = new int(newId);
}

Army::~Army()
{
}

void Army::setOccupiedCountry(Country* country)
{
	country = country;
}

City::City(Player* newPlayer, int newId)
{
	player = newPlayer;
	id = new int(newId);
}

City::~City()
{
}

void City::setOccupiedCountry(Country* country)
{
	country = country;
}

//Player::Player(string inputName, int coinAmount, string selectedColor)
//{
//	name = new string(inputName);
//	numCoins = new int(coinAmount);
//	color = new string(selectedColor);
//	armies = new vector<Army*>();
//	cities = new vector<City*>();
//	ownedCountries = new vector<Country*>();
//	 hand = new vector<Card*>()				// Part 4
//	 goods = new vector<Good*>()				// Part 4
//	 biddingFacility = new BidingFacility()	// Part 5
//}

//Constructor for Biding Facility testing purpose
Player::Player(string inputName, int coinAmount, int playerAge)
{
	name = new string(inputName);
	numCoins = new int(coinAmount);
	age = new int(playerAge);
}

Player::~Player()
{
}

void Player::createArmies()
{
	for (int i = 0; i < 14; i++) {
		Army* army = new Army(this, i);
		// Find solution to pushing new Army pointer to armies vector
	}
}

void Player::createCities()
{
	for (int i = 0; i < 3; i++) {
		City* city = new City(this, i);
		// Find solution to pushing new City pointer to cities vector
	}
}

void Player::BuildCity(Country* country)
{
	// Add city to a country (assign country to city obj)
}

void Player::DestroyArmy(Country* country)
{
	// Remove army from a country (remove country ref)
}

void Player::MoveArmies()
{
	// Change country ref of army
}

void Player::MoveOverLand()
{
	// Change country ref of army
}

void Player::PayCoin(int amount)
{
	// Decrease numCoin; add coin to supply?
}

void Player::PlaceNewArmies()
{
	// Ref country in army obj, add army to country 
}
