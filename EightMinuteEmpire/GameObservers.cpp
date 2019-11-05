#include "GameObservers.h"

Observer::Observer()
{/*Intentionally Empty*/}

Observer::~Observer()
{/*Intentionally Empty*/}

Subject::Subject()
	: observers(new list<Observer*>) {}

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

GameStatistics::GameStatistics()
{/*Intentionally Empty*/}

GameStatistics::GameStatistics(Map* map)
{
	mapSubject = map;
	mapSubject->Attach(this);
}

GameStatistics::~GameStatistics()
{
	mapSubject->Detach(this);
}

void GameStatistics::Update()
{
	display();
}

void GameStatistics::display()
{
	cout << "GameStat Display!" << endl;
}

