#pragma once
#include "GameObservers.h"
#include "Player.h"
#include "cards.h"
#include <string>
#include "Map.h"


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

PlayerObserver::PlayerObserver()
{}

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

CurrentPOb::CurrentPOb()
{}

CurrentPOb::CurrentPOb(Player* player, Cards* chosen, int* position, int* supply)
{
	_playerSubject = player;
	_playerSubject->Attach(this);
	_cardChosen = chosen;
	this->position = position;
	_supply = supply;
}

CurrentPOb::~CurrentPOb()
{
	_playerSubject->Detach(this);
}

void CurrentPOb::Update()
{
	display();
}

//void CurrentPOb::display()
//{
//	cout << "dislay observer from currentPOb" << endl;
//	this->_cardChosen->print();
//}

void CurrentPOb::display()
{
	cout << "*************dislay observer from currentPOb************" << endl;
	cout<< "Player " <<*this->_playerSubject->name
		<< " selects the " << *this->position+1 
		<< "th card from the left." <<endl;
	this->_cardChosen->print();
}

PayOb::PayOb()
{}

PayOb::PayOb(Player* player, int* cost, int*supply)
{
	_playerSubject = player;
	_playerSubject->Attach(this);
	this->cost = cost;
	this->supply = supply;

}

PayOb::~PayOb()
{
	_playerSubject->Detach(this);
}
void PayOb::display()
{
	cout << "************Inside payOb display***************" << endl;
	cout << *(_playerSubject->name) << " is paying " << *cost << " coins." << endl;
	cout << *(_playerSubject->name) << " now has " << *(_playerSubject->numCoins) << " coins." << endl;
	cout << "The Game Supply now has : " << *supply << " coins." << endl;
}

void PayOb::Update()
{
	display();
}

ActionOb::ActionOb(){}

ActionOb::ActionOb(Player* player, Cards* card)
{
	_playerSubject = player;
	_cardChosen = card;
	card->Attach(this);
	_action = new vector<string*>();
	_amount = new vector<int*>();

}

ActionOb::ActionOb(Player* player, Cards* card, string* action)
{
	_playerSubject = player;
	_cardChosen = card;
	card->Attach(this);
	_action = new vector<string*>();

	for (int i = 0; i < _cardChosen->actions->size(); i++)
	{
		_action->push_back(_cardChosen->actions->at(i));
	}
	_amount = new vector<int*>();;


}

//TODO: Modify args
ActionOb::ActionOb(Player* player, Cards* card, string* action, int* amount)
{
	_playerSubject = player;
	_cardChosen = card;
	card->Attach(this);
	_action = new vector<string*>();
	for (int i = 0; i < _cardChosen->actions->size(); i++)
	{
		_action->push_back(_cardChosen->actions->at(i));
	}
	_amount = new vector<int*>();


}

ActionOb::~ActionOb()
{

}

void ActionOb::setAction(string* action)
{
	//for (int i = 0; i < _cardChosen->actions->size(); i++)
	//{
	//	_action->push_back(_cardChosen->actions->at(i));
	//}
	this->_action->push_back(action);

}

void ActionOb::setAmount(int* amount)
{
	_amount->push_back(amount);
}

void ActionOb::display()
{
	cout << "****** INSIDE ACTION OB******" << endl;
	cout << "Chosen card is : " << endl;

	cout << "[Good is : " << *_cardChosen->good;
	cout << ", Action is : ";
	const int temp = _cardChosen->actions->size();

	if (temp != 0)
	{
		for (int j = 0; j < temp; j++)
		{
			cout << *_cardChosen->actions->at(j) << " ";
		}
		cout << "]";

	}
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
				cout << "~ACTION TAKEN :Create " << *_amount->at(i) << " cities~";
				return;
			}
			cout << "~ACTION TAKEN :Create " << *_amount->at(i) << " city~";
		}
		if ("waterMove" == *_action->at(i))
		{
			if (*_amount->at(i) > 1)
			{
				cout << "~ACTION TAKEN : Move " << *_amount->at(i) << " armies across water/land"<< endl;
				return;
			}
			cout << "~ACTION TAKEN : Move " << *_amount->at(i) << " army across water/land" << endl;
		}
		if ("destroyArmies" == *_action->at(i))
		{
			if (*_amount->at(i) > 1)
			{
				cout << "~ACTION TAKEN :Destroy " << *_amount->at(i) << " armies" << endl;
				return;
			}
			cout << "~ACTION TAKEN :Destroy " << *_amount->at(i) << " army"<<endl;
		}
	}
}

void ActionOb::Update()
{
	display();
}

ProcessActOb::ProcessActOb()
{
	_playerSubject = nullptr;
	_initCountry = nullptr;
	_finalCountry = nullptr;
	_playerTarget = nullptr;
	_numArmy = nullptr;
}

ProcessActOb::ProcessActOb(Player* player)
{
	_playerSubject = player;
	_initCountry = nullptr;
	_finalCountry = nullptr;
	_playerTarget = nullptr;
	_numArmy = nullptr;
}

ProcessActOb::~ProcessActOb()
{
	delete _playerSubject;
	delete _initCountry;
	delete _finalCountry;
	delete _playerTarget;
	delete _numArmy;
	_playerSubject = nullptr;
	_initCountry = nullptr;
	_finalCountry = nullptr;
	_playerTarget = nullptr;
	_numArmy = nullptr;
}

void ProcessActOb::setInitCountry(Country* country)
{
	_initCountry= country; 
}

void ProcessActOb::setFinalCountry(Country* country) 
{
	_finalCountry = country;
}

void ProcessActOb::setNumArmy(int num)
{
	*_numArmy = num;
}

void ProcessActOb::setPlayerTarget(Player* target)
{
	_playerTarget = target;
}

void ProcessActOb::display()
{
	if (_initCountry!=nullptr && _finalCountry!= nullptr)
	{
		 cout << *(this->_playerSubject->name) << " moved an army from " << *(_initCountry->name) << " to " << *(_finalCountry->name) << endl;	
		 return;
	}

	if (_initCountry != nullptr && _playerTarget != nullptr)
	{
		cout << *(this->_playerSubject->name) << " destroyed an army of " << *(_playerTarget->name) << "'s in " << *(_initCountry->name) << endl;
		return;
	}

	if (_initCountry != nullptr && _numArmy != nullptr)
	{
		cout << *(this->_playerSubject->name) << " placed an army in " << *(_initCountry->name) << endl;
		return;
	}
	if(_initCountry!=nullptr)
	{
		cout << *(this->_playerSubject->name) << " now has a city built in " << *(_initCountry->name) << endl;
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
	const int COL_WIDTH_CONTINENTS = 56;
	cout << endl;
	cout << string(150, '#') << endl;
	cout << "\t\t Game Statistics" << endl;
	cout << string(150, '-') << endl;
	cout << "| Players  | Victory Pts | Owned Continents" << string(COL_WIDTH_CONTINENTS - 16, ' ') << "| Owned Countries" << endl;
	cout << string(150, '-') << endl;

	for (int i = 0; i < players->size(); i++)
	{
		string ownedContinents = "";
		cout << "| Player " << (i)+1 << " | ";
		cout << *players->at(i)->victoryPoint << string(9, ' ');
		if (*players->at(i)->victoryPoint < 10) {
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
	cout << string(150, '-') << endl;
	cout << endl;
	cout << string(150, '#') << endl;
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
	cout << string(30, '#') << endl;
	cout << "\t\tPlayers and scores" << endl;
	cout << string(30, '-') << endl;

	for (int i = 0; i < players->size(); i++)
	{
		cout << "| Player " << (i)+1 << ":  " << *(players->at(i)->name) << " with " ;
		cout << *players->at(i)->victoryPoint << " victory points, ";
		cout << *players->at(i)->numCoins << " coins, ";
		cout << 14 - players->at(i)->availableArmies() << " armies on the board, and ";
		cout << players->at(i)->ownedCountries->size() << " owned countries." << endl;

	}
	cout << endl;
	cout << "The winner is " << *winningPlayer->name << "!" << endl;
	cout << string(100, '-') << endl;
	cout << endl;
	cout << string(100, '#') << endl;
	cout << endl;
}

