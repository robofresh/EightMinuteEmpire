#include "Player.h"
#include "Map.h"
#include "BidingFacility.h"
#include "cards.h"

struct InsufficientCoinsException : public exception
{
	const char* what() const throw()
	{
		return "Player does not have enough coins.";
	}
};


Army::Army()
	: player(nullptr), occupiedCountry(nullptr) {}

Army::Army(Player* newPlayer)
	: player(newPlayer), occupiedCountry(nullptr) {}

Army::~Army()
{
	player = NULL;
	occupiedCountry = NULL;
}

void Army::setOccupiedCountry(Country* country)
{
	Army::occupiedCountry = country;
}

City::City()
	: player(nullptr), occupiedCountry(nullptr) {}

City::City(Player* newPlayer)
	: player(newPlayer), occupiedCountry(nullptr) {}

City::~City()
{
	player = NULL;
	occupiedCountry = NULL;
}

void City::setOccupiedCountry(Country* country)
{
	City::occupiedCountry = country;
}

Player::Player()
{
	name = new string("");
	age = new int(0);
	numCoins = new int(0);
	color = new string("");
	armies = new vector<Army*>();
	cities = new vector<City*>();
	ownedCountries = new vector<Country*>();
	hand = new Hand();
	goods = new vector<string*>();
	bidFacObj = new BidingFacility(this);
}

Player::Player(string inputName, int inputAge, int coinAmount, string selectedColor, Deck* mainDeck)
{
	name = new string(inputName);
	age = new int(inputAge);
	numCoins = new int(coinAmount);
	color = new string(selectedColor);
	armies = new vector<Army*>();
	cities = new vector<City*>();
	ownedCountries = new vector<Country*>();
	hand = new Hand(mainDeck);
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
		armies->at(i) = NULL;
	}
	for (int i = 0; i < cities->size(); i++)
	{
		delete cities->at(i);
		cities->at(i) = NULL;
	}
	delete name, age, numCoins, color, armies, cities, ownedCountries, hand, goods, bidFacObj;
	name = NULL;
	age = NULL;
	numCoins = NULL;
	color = NULL;
	armies = NULL;
	cities = NULL;
	ownedCountries = NULL;
	hand = NULL;
	goods = NULL;
	bidFacObj = NULL;
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

void Player::printPlayer()
{
	cout << "Player: " << *(this->name) << ", age " << *(this->age) << ", color " << *(this->color) << endl;
	cout << "\t" << *(this->name) << " holds " << *(this->numCoins) << " coins." << endl;
	cout << "\t" << *(this->name) << " has " << this->armies->size() << " " << *(this->color) << " army cubes and " << this->cities->size() << " " << *(this->color) << " city discs." << endl;
	for (int i = 0; i < armies->size(); i++)
	{
		if (armies->at(i)->occupiedCountry == nullptr)
		{
			cout << "\t\t\t" << "Army " << i+1 << " has not been placed." << endl;
		} 
		else
		{
			cout << "\t\t\t" << "Army " << i+1 << " is in " << *armies->at(i)->occupiedCountry->name << endl;
		}

	}
	cout << "\t\t" << this->cities->size() << " cities (discs)." << endl;
	for (int i = 0; i < cities->size(); i++)
	{
		if (cities->at(i)->occupiedCountry == nullptr)
		{
			cout << "\t\t\t" << "City " << i + 1 << " has not been placed." << endl;
		}
		else
		{
			cout << "\t\t\t" << "City " << i + 1 << " is in " << *cities->at(i)->occupiedCountry->name << endl;
		}

	}
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
	try
	{
		if ((*(this->numCoins) - amount) < 0)
			throw InsufficientCoinsException();
		else
		{
			*(this->numCoins) = *(this->numCoins) - amount;
			*supply = *supply + amount;
		}
	}
	catch (InsufficientCoinsException e)
	{
		cout << e.what();
		return ;
	}

	cout << *(this->name) << " is paying " << amount << " coins." << endl;
	cout << *(this->name) << " now has " << *(this->numCoins) << " coins." << endl;

}

void Player::placeNewArmies(Country* country, int amount)
{
	for (amount; amount > 0; amount--)
	{
		Army* availableArmy = this->getAvailableArmy();
		availableArmy->occupiedCountry = country;
		country->occupyingArmies->push_back(availableArmy);
		cout << *(this->name) << " placed an army in " << *(country->name) << endl;
	}

}

void Player::ignore(Cards* card)
{
	this->hand->faceupcards->push_back(card);
	cout << "Player takes the card and ignore the action." << endl;
}

void Player::payCard(Cards* card,int position, int* supply)
{
	switch (position)
	{
	case 0:
		this->payCoin(0,supply);
		break;
	case 1:
	case 2:
		this->payCoin(1,supply);
		break;
	case 3:
	case 4:
		this->payCoin(2,supply);
		break;
	case 5:
		this->payCoin(3,supply);
		break;
	default:
		cout << "Invalid input" << endl;
		break;
	}
	
}

// References
// [1] https://thispointer.com/c-how-to-find-an-element-in-vector-and-get-its-index/
