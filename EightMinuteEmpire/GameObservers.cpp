#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <set>
#include "GameObservers.h"
#include "Player.h"
#include "cards.h"
#include <string>
#include "Map.h"
#include "Actions.h"


using namespace std;

Observer::Observer()
{/*Intentionally Empty*/}

Observer::~Observer()
{/*Intentionally Empty*/}

Subject::Subject()
	: observers(new list<Observer*>()) {}

Subject::~Subject()
{
	delete observers;
}

void Subject::Attach(Observer* ob)
{
	observers->push_back(ob);
}

void Subject::Detach(Observer* ob)
{
	observers->remove(ob);
}

void Subject::Notify()
{
	list<Observer*>::iterator i = observers->begin();
	for (i; i != observers->end(); i++)
	{
		(*i)->Update();
	}
}

//PlayerObserver check whose turn it is
PlayerObserver::PlayerObserver():_playerSubject(nullptr), _index(nullptr)
{//Empty
}

PlayerObserver::PlayerObserver(Player* player, int* index)
{
	_playerSubject = player;
	_playerSubject->Attach(this);
	_index = index;
}

PlayerObserver::~PlayerObserver()
{
	_playerSubject->Detach(this);
	delete _index;
	_index = NULL;
}

void PlayerObserver::Update()
{
	display();
}

void PlayerObserver::display()
{
	cout << "**********Player "<<*this->_index  <<" " 
		<< *_playerSubject->name << "'s turn.**********" << endl;
}

//CurrentPOb is an to track the chosen card and the person's turn
CurrentPOb::CurrentPOb()
{
	_playerSubject= nullptr;
	_index= nullptr;
	_cardChosen=nullptr;
	position=nullptr;
	_supply = nullptr;
	_cost = nullptr;
}

CurrentPOb::CurrentPOb(Player* player, Cards* chosen, int* position, int* supply)
{
	_playerSubject = player;
	_playerSubject->Attach(this);
	_cardChosen = chosen;
	this->position = position;
	_supply = supply;
	_cost = nullptr;
}

CurrentPOb::~CurrentPOb()
{
	_playerSubject->Detach(this);
	_supply = nullptr;
	delete _cost;
	_cost = nullptr;
}

void CurrentPOb::Update()
{
	display();
}

void CurrentPOb::display()
{
	cout << "Player " << *this->_playerSubject->name
		<< " selects the " << *this->position + 1
		<< "th card from the left. The card is : ";
	this->_cardChosen->print();

	cout << "Player " << *(_playerSubject->name) << " needs to pay " << *_cost << " coins." << endl;
	cout << "Player " << *(_playerSubject->name) << " now has " << *(_playerSubject->numCoins) << " coins." << endl;
	cout << "The Game Supply now has : " << *_supply << " coins." << endl;
}

void CurrentPOb::setCost(int* cost)
{
	_cost =cost;
}

void CurrentPOb::setSupply(int* supply)
{
	_supply = supply;
}

ActionOb::ActionOb()
{
	_playerSubject = nullptr;
	_cardChosen = nullptr;
	_action = new vector<string*>();
	_amount = new vector<int*>();
}

ActionOb::ActionOb(Player* player, Cards* card)
{
	_playerSubject = player;
	_cardChosen = card;
	card->Attach(this);
	_action = new vector<string*>();
	_amount = new vector<int*>();

}

ActionOb::~ActionOb()
{
	_cardChosen->Detach(this);
}

void ActionOb::setAction(string* action)
{
	this->_action->push_back(action);
}

void ActionOb::setAmount(int* amount)
{
	_amount->push_back(amount);
}

void ActionOb::display()
{
	cout << endl;
	cout << endl;
	for (int i = 0; i < _action->size(); i++)
	{

		if (*_action->at(i) == "Ignore")
		{
			cout << "~ACTION TAKEN : Player " << *this->_playerSubject->name
				<< " choose to ignore the card.~" << endl;
			return;
		}

		if ("placeArmies" == *_action->at(i))
		{
			if (*_amount->at(i) > 1)
			{
				cout << "~ACTION TAKEN : Place " << *_amount->at(i) << " armies"<<endl;
				return;
			}
			cout << "~ACTION TAKEN : Place " << *_amount->at(i) << " army" << endl;;
		}

		if ("move" == *_action->at(i))
		{
			if (*_amount->at(i) > 1)
			{
				cout << "~ACTION TAKEN : Move " << *_amount->at(i) << " armies~" << endl;
				return;
			}
			cout << "~ACTION TAKEN : Move " << *_amount->at(i) << " army~"<<endl;
		}
		if ("createCity" == *_action->at(i))
		{
			if (*_amount->at(i) > 1)
			{
				cout << "~ACTION TAKEN :Create " << *_amount->at(i) << " cities~" << endl;;
				return;
			}
			cout << "~ACTION TAKEN :Create " << *_amount->at(i) << " city~" << endl;
		}
		if ("waterMove" == *_action->at(i))
		{
			if (*_amount->at(i) > 1)
			{
				cout << "~ACTION TAKEN : Move " << *_amount->at(i) << " armies across water/land~"<< endl;
				return;
			}
			cout << "~ACTION TAKEN : Move " << *_amount->at(i) << " army across water/land~" << endl;
		}
		if ("destroyArmies" == *_action->at(i))
		{
			if (*_amount->at(i) > 1)
			{
				cout << "~ACTION TAKEN :Destroy " << *_amount->at(i) << " armies~" << endl;
				return;
			}
			cout << "~ACTION TAKEN :Destroy " << *_amount->at(i) << " army~"<<endl;
		}
	}
}

void ActionOb::Update()
{
	display();
}

ProcessActOb::ProcessActOb() : aObject(nullptr), _playerSubject(nullptr), _initCountry(nullptr)
, _finalCountry(nullptr), _playerTarget(nullptr), _numArmy(nullptr) {}

ProcessActOb::ProcessActOb(Actions* aObject, Player* player) : _playerSubject(player), _initCountry(nullptr)
, _finalCountry(nullptr), _playerTarget(nullptr), _numArmy(nullptr) 
{
	this->aObject = aObject;
	aObject->Attach(this);
}

ProcessActOb::ProcessActOb(Actions* aObject, Player* player, Country* country, int num) : _playerSubject(player)
, _initCountry(country), _finalCountry(nullptr), _playerTarget(nullptr) 
{
	_numArmy =new int(num);
	this->aObject = aObject;
	aObject->Attach(this);
}

ProcessActOb::ProcessActOb(Actions* aObject, Player* player, Country* initialCountry, Country* finalCountry):
	_playerSubject(player)	, _initCountry(initialCountry), _finalCountry(finalCountry)
	, _playerTarget(nullptr), _numArmy(nullptr)
{
	this->aObject = aObject;
	aObject->Attach(this);
}

ProcessActOb::ProcessActOb(Actions* aObject, Player* player, Country* initialCountry):
	_playerSubject(player), _initCountry(initialCountry)
	, _finalCountry(nullptr), _playerTarget(nullptr), _numArmy(nullptr)
{
	this->aObject = aObject;
	aObject->Attach(this);
}

ProcessActOb::ProcessActOb(Actions* aObject, Player* player, Country* initialCountry, Player* target)
	: _playerSubject(player), _initCountry(initialCountry)
	, _finalCountry(nullptr), _playerTarget(target), _numArmy(nullptr)
{
	this->aObject = aObject;
	aObject->Attach(this);
}

ProcessActOb::~ProcessActOb()
{
	aObject->Detach(this);
	_playerSubject = nullptr;
	_initCountry = nullptr;
	_finalCountry = nullptr;
	_playerTarget = nullptr;
	delete _numArmy;
	_numArmy = nullptr;
}

void ProcessActOb::display()
{
	if (_initCountry!=nullptr && _finalCountry!= nullptr)
	{
		 cout <<"~ACTION OCCURING: " << *(this->_playerSubject->name) 
			 << " moved an army from " << *(_initCountry->name) << " to " << *(_finalCountry->name) << endl;	
		 return;
	}

	if (_initCountry != nullptr && _playerTarget != nullptr)
	{
		cout << "~ACTION OCCURING: " << *(this->_playerSubject->name) 
			<< " destroyed an army of " << *(_playerTarget->name) << "'s in " << *(_initCountry->name) << endl;
		return;
	}

	if (_initCountry != nullptr && _numArmy != nullptr)
	{
		cout << "~ACTION OCCURING: " << *(this->_playerSubject->name) 
			<< " placed an army in " << *(_initCountry->name) << endl;
		return;
	}
	if(_initCountry!=nullptr)
	{
		cout << "~ACTION OCCURING: " << *(this->_playerSubject->name) 
			<< " now has a city built in " << *(_initCountry->name) << endl;
	}
}

void ProcessActOb::Update()
{
	display();
}

GameStatistics::GameStatistics()
	: mapSubject(nullptr), players(new vector<Player*>)
{/*Intentionally Empty*/}

GameStatistics::GameStatistics(Map* map, vector<Player*>* gamePlayers)
{
	mapSubject = map;
	players = gamePlayers;
	mapSubject->Attach(this);
}

GameStatistics::~GameStatistics()
{
	mapSubject->Detach(this);
}

void GameStatistics::Update()
{
	this->display();
}

void GameStatistics::display()
{
	cout << fixed << showpoint;
	cout << setprecision(2);
	const int COL_WIDTH_CONTINENTS = 56;
	cout << endl;
	cout << string(200, '#') << endl;
	cout << string(80, ' ') << "Game Statistics" << endl;
	cout << string(200, '-') << endl;
	cout << "| Players  | Victory Pts | Coins | Owned Continents" << string(COL_WIDTH_CONTINENTS - 16, ' ') << "| Owned Countries" << endl;
	cout << string(200, '-') << endl;
	for (int i = 0; i < players->size(); i++)
	{
		string ownedContinents = "";
		cout << "| Player " << (i)+1 << " | ";
		cout << *players->at(i)->victoryPoint << string(9, ' ');
		if (*players->at(i)->victoryPoint < 10) {
			cout << " ";
		}
		cout << " | ";
		cout << *players->at(i)->numCoins << string(3, ' ');
		if (*players->at(i)->numCoins < 10) {
			cout << " ";
		}
		for (int j = 0; j < players->at(i)->ownedContinents->size(); j++)
		{
			ownedContinents.append(*players->at(i)->ownedContinents->at(j)->name);
			ownedContinents.append(" ");
		}
		cout << " | " << ownedContinents << string(COL_WIDTH_CONTINENTS - ownedContinents.size(), ' ') << "| ";
		for (int j = 0; j < players->at(i)->ownedCountries->size(); j++)
		{
			cout << *players->at(i)->ownedCountries->at(j)->name << " ";
		}
		cout << endl;
	}
	cout << string(200, '-') << endl;
	cout << endl;

	cout << string(80, ' ') << "Occupied Countries Stats" << endl;
	cout << string(200, '-') << endl;
	set<Country*> allOccupiedCountries;
	for (int i = 0; i < players->size(); i++)
	{
		for (int j = 0; j < players->at(i)->armies->size(); j++)
		{
			Country* country = players->at(i)->armies->at(j)->occupiedCountry;
			if (country != nullptr) {
				allOccupiedCountries.insert(country);
			}
		}
		for (int j = 0; j < players->at(i)->cities->size(); j++)
		{
			Country* country = players->at(i)->cities->at(j)->occupiedCountry;
			if (country != nullptr) {
				allOccupiedCountries.insert(country);
			}
		}
	}
	const int COL_WIDTH_COUNTRY_NAME = 12;
	if (allOccupiedCountries.size() != 0) {
		cout << "| Players ";
		for (set<Country*>::iterator it = allOccupiedCountries.begin(); it != allOccupiedCountries.end(); it++) {
			const Country* country = *it;
			cout << " | "  << *(country->name) << string(COL_WIDTH_COUNTRY_NAME - country->name->size(), ' ');
		}
		cout << endl;
		cout << string(200, '-') << endl;
		for (int i = 0; i < players->size(); i++)
		{
			cout << "| Player " << (i)+1 << " | ";
			for (set<Country*>::iterator it = allOccupiedCountries.begin(); it != allOccupiedCountries.end(); it++) {
				const Country* country = *it;
				int armies = 0;
				int cities = 0;
				for (int j = 0; j < country->occupyingArmies->size(); j++) {
					if (country->occupyingArmies->at(j)->player == players->at(i)) {
						armies++;
					}
				}
				for (int j = 0; j < country->cities->size(); j++) {
					if (country->cities->at(j)->player == players->at(i)) {
						cities++;
					}
				}
				cout << "A: ";
				if (armies < 10) cout << " ";
				cout << armies << ", C: ";
				if (armies < 10) cout << " ";
				cout << cities;
				if (cities < 10) cout << " ";
				cout << "| ";
			}
			cout << endl;
			cout << "|" << string(10, ' ') << "| ";
			for (set<Country*>::iterator it = allOccupiedCountries.begin(); it != allOccupiedCountries.end(); it++) {
				const Country* country = *it;
				double totalArmiesAndCities = country->occupyingArmies->size() + country->cities->size();
				int armies = 0;
				int cities = 0;
				for (int j = 0; j < country->occupyingArmies->size(); j++) {
					if (country->occupyingArmies->at(j)->player == players->at(i)) {
						armies++;
					}
				}
				for (int j = 0; j < country->cities->size(); j++) {
					if (country->cities->at(j)->player == players->at(i)) {
						cities++;
					}
				}
				cout << "own: ";
				double ownPercentage = (armies + cities) / totalArmiesAndCities * 100;
				if (ownPercentage < 100.00) cout << " ";
				if (ownPercentage < 10.00) cout << " ";
				cout << ownPercentage << "% | ";
			}
			cout << endl;
		}
	}
	cout << string(200, '-') << endl;
	cout << endl;

	cout << string(200, '#') << endl;
	cout << endl;
}

GameWinningScores::GameWinningScores()
	: mapSubject(nullptr), players(new vector<Player*>), winningPlayer(nullptr)
{/*Intentionally Empty*/
}

GameWinningScores::GameWinningScores(Map* map, vector<Player*>* gamePlayers, Player* winner)
{
	mapSubject = map;
	players = gamePlayers;
	winningPlayer = winner;
	mapSubject->Attach(this);
}

GameWinningScores::~GameWinningScores()
{
	mapSubject->Detach(this);
}

void GameWinningScores::Update()
{
	this->display();
}

void GameWinningScores::display()
{
	cout << endl;
	cout << string(80, '#') << endl;
	cout << "\t\tPlayers and scores" << endl;
	cout << string(80, '-') << endl;
	cout << "| Players  | Victory Pts | Coins | Armies on Board | Owned Countries" << endl;
	cout << string(80, '-') << endl;
	for (int i = 0; i < players->size(); i++)
	{
		cout << "| Player " << (i)+1 << " | ";
		cout << *players->at(i)->victoryPoint << string(9, ' ');
		if (*players->at(i)->victoryPoint < 10) {
			cout << " ";
		}
		cout << " | ";
		cout << *players->at(i)->numCoins << string(3, ' ');
		if (*players->at(i)->numCoins < 10) {
			cout << " ";
		}
		cout << " | ";
		cout << 14 - players->at(i)->availableArmies() << string(14, ' ');
		if (14 - players->at(i)->availableArmies() < 10) {
			cout << " ";
		}
		cout << " | ";
		cout << players->at(i)->ownedCountries->size() << string(14, ' ');
		if (players->at(i)->ownedCountries->size() < 10) {
			cout << " ";
		}
		cout << endl;
	}
	cout << string(80, '-') << endl;
	cout << endl;
	cout << "The winner is " << *winningPlayer->name << "!" << endl;
	cout << string(80, '#') << endl;
}

