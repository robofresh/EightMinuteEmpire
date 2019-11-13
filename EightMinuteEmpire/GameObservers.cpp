#pragma once
#include "GameObservers.h"
#include "Player.h"
#include "cards.h"


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
		<< " selects the " << *this->position 
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

//ActionOb::ActionOb(){}
//
//ActionOb::ActionOb(Player* player, Cards* card, string* action, int* amount)
//{
//	_playerSubject = player;
//	_cardChosen = card;
//	card->Attach(this);
//	_action = action;
//	_amount = amount;
//
//
//}
//
//ActionOb::~ActionOb()
//{
//
//}
//
//void ActionOb::display()
//{
//	if ("placeArmies" == *_action)
//	{
//		if (*_amount > 1)
//		{
//			cout << "Place " << *_amount << " armies";
//			return;
//		}
//		cout << "Place " << *_amount << " army";
//	}
//	if ("move" == *_action)
//	{
//		if (*_amount > 1)
//		{
//			cout << "Move " << *_amount << " armies";
//			return;
//		}
//		cout << "Move " << *_amount << " army";
//	}
//	if ("createCity" == *_action)
//	{
//		if (*_amount > 1)
//		{
//			cout << "Create " << *_amount << " cities";
//			return;
//		}
//		cout << "Create " << *_amount << " city";
//	}
//	if ("waterMove" == *_action)
//	{
//		if (*_amount > 1)
//		{
//			cout << "Move " << *_amount << " armies across water/land";
//			return;
//		}
//		cout << "Move " << *_amount << " army across water/land";
//	}
//	if ("destroyArmies" == *_action)
//	{
//		if (*_amount > 1)
//		{
//			cout << "Destroy " << *_amount << " armies";
//			return;
//		}
//		cout << "Destroy " << *_amount << " army";
//	}
//
//}
//
//void ActionOb::Update()
//{
//	display();
//}