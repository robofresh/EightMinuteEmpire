#include "Player.h"
#include "Map.h"
#include "BidingFacility.h"

Army::Army(Player* newPlayer)
	: player(newPlayer), occupiedCountry(nullptr) {}

Army::~Army()
{
	player = NULL;
	occupiedCountry = NULL;
	delete player, occupiedCountry;
}

void Army::setOccupiedCountry(Country* country)
{
	country = country;
}

City::City(Player* newPlayer)
	: player(newPlayer), occupiedCountry(nullptr) {}

City::~City() 
{
	player = NULL;
	occupiedCountry = NULL;
	delete player, occupiedCountry;
}

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
	hand = nullptr;
	goods = new vector<string*>();
	bidFacObj = new BidingFacility(this);

	this->createArmies();
	this->createCities();
}

Player::~Player()
{
	for (int i = 0; i < armies->size(); i++)
	{
		delete armies->at(i);
	}
	for (int i = 0; i < cities->size(); i++)
	{
		delete cities->at(i);
	}
	delete name, age, numCoins, color, armies, cities, ownedCountries, hand, goods, bidFacObj;
}

void Player::createArmies()
{
	for (int i = 0; i < 14; i++) {
		Army* army = new Army(this);
		this->armies->push_back(army);
	}
}

void Player::createCities()
{
	for (int i = 0; i < 3; i++) {
		City* city = new City(this);
		this->cities->push_back(city);
	}
}

void Player::initializeHand(Deck* deck)
{
	this->hand = new Hand(deck);
}

void Player::printPlayer()
{
	cout << "Player: " << *(this->name) << ", age " << *(this->age) << ", color " << *(this->color) << endl;
	cout << "\t" << *(this->name) << " holds " << *(this->numCoins) << " coins." << endl;
	cout << "\t" << *(this->name) << " has " << this->armies->size() << " " << *(this->color) << " army cubes and " << this->cities->size() << " " << *(this->color) << " city discs." << endl;
	cout << "\t" << *(this->name) << " owns " << this->ownedCountries->size() << " countries, and has " << this->goods->size() << " goods collected." << endl;
	cout << "\t" << *(this->name) << " has " << this->hand->faceupcards->size() << " cards in hand." << endl;
	cout << "\t" << *(this->name) << " has their own bidding facility.\n" << endl;
}

void Player::buildCity(Country* country)
{
	City* availableCity = this->getAvailableCity();
	availableCity->occupiedCountry = country;
	country->cities->push_back(availableCity);
	cout << *(this->name) << " now has a city built in " << *(country->name) << endl;
}

void Player::destroyArmy(Country* country, Player* otherPlayer)
{
	Army* selectedArmy = country->getArmy(otherPlayer);
	selectedArmy->occupiedCountry = nullptr;
	// Reference for following lines [1]
	auto it = find(country->occupyingArmies->begin(), country->occupyingArmies->end(), selectedArmy);
	if (it != country->occupyingArmies->end()) { country->occupyingArmies->erase(it); }	
	cout << *(this->name) << " destroyed an army of " << *(otherPlayer->name) << "'s in " << *(country->name) << endl;
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
	cout << *(this->name) << " moved an army from " << *(initCountry->name) << " to " << *(finalCountry->name) << endl;
}

void Player::moveOverLand(Country* initCountry, Country* finalCountry)
{
	Army* selectedArmy = initCountry->getArmy(this);
	selectedArmy->occupiedCountry = finalCountry;
	finalCountry->occupyingArmies->push_back(selectedArmy);
	auto it = find(initCountry->occupyingArmies->begin(), initCountry->occupyingArmies->end(), selectedArmy);
	if (it != initCountry->occupyingArmies->end()) { initCountry->occupyingArmies->erase(it); }
	cout << *(this->name) << " moved an army from " << *(initCountry->name) << " to " << *(finalCountry->name) << endl;
}

void Player::payCoin(int amount, int* supply)
{
	*(this->numCoins) = *(this->numCoins) - amount;
	*supply = *supply + amount;
	cout << *(this->name) << " now has " << *(this->numCoins) << " coins." << endl;
}

void Player::placeNewArmies(Country* country, int amount)
{
	for (amount; amount > 0; amount--)
	{
		Army* availableArmy = this->getAvailableArmy();
		availableArmy->occupiedCountry = country;
		country->occupyingArmies->push_back(availableArmy);
		cout << *(this->name) << " now has an army in " << *(country->name) << endl;
	}
}

// References
// [1] https://thispointer.com/c-how-to-find-an-element-in-vector-and-get-its-index/
