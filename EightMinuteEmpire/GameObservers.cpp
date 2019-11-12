#pragma once
#include "GameObservers.h"
#include "Player.h"


Observer::Observer()
{/*Intentionally Empty*/
}

Observer::~Observer()
{/*Intentionally Empty*/
}

Subject::Subject()
{
	observers = new list<Observer*>;
}


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
	for (; i != observers->end(); i++)
	{
		
		(*i)->Update();
	}
}

PlayerObserver::PlayerObserver()
{}

PlayerObserver::PlayerObserver(Player* player)
{
	_playerSubject = player;
	_playerSubject->Attach(this);
}

PlayerObserver::~PlayerObserver()
{
	_playerSubject->Detach(this);
}

void PlayerObserver::Update()
{
	display();
}

void PlayerObserver::display()
{
	cout << *_playerSubject->name << endl;
	cout << "display from observer" << endl;
}

CurrentPOb::CurrentPOb()
{}

CurrentPOb::CurrentPOb(Player* player, Cards* chosen, int* position, int* supply)
{
	_currentSubject = player;
	_currentSubject->Attach(this);
	_cardChosen = chosen;
	this->position = position;
	_supply = supply;
}

CurrentPOb::~CurrentPOb()
{
	_currentSubject->Detach(this);
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
	cout << "dislay observer from currentPOb" << endl;
	cout<< "Player " <<*this->_currentSubject->name
		<< " selects the " << *this->position 
		<< "th card from the left." <<endl;
	this->_cardChosen->print();
}

PayOb::PayOb()
{}

PayOb::PayOb(Player* player, int* cost, int*supply)
{
	_currentSubject = player;
	_currentSubject->Attach(this);
	this->cost = cost;
	this->supply = supply;

}

PayOb::~PayOb()
{
	_currentSubject->Detach(this);
}
void PayOb::display()
{
	cout << "Inside payOb display" << endl;
	cout << *(_currentSubject->name) << " is paying " << cost << " coins." << endl;
	cout << *(_currentSubject->name) << " now has " << *(_currentSubject->numCoins) << " coins." << endl;
}

void PayOb::Update()
{
	display();
}

