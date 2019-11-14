#include <string>
#include "GameObservers.h"
#include "Player.h"
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

