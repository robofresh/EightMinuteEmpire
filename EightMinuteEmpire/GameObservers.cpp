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
	cout << _playerSubject->name << endl;
	cout << "display from observer" << endl;
}

