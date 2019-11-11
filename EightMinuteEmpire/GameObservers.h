#pragma once
#include <list>
#include "Map.h"

using namespace std;

class Observer
{
public:
	~Observer();
	virtual void Update() = 0;
protected:
	Observer();
};

class Subject
{
public:
	Subject();
	~Subject();
	virtual void Attach(Observer* ob);
	virtual void Detach(Observer* ob);
	virtual void Notify();
private:
	list<Observer*>* observers;
};

class PlayerObserver : public Observer
{
public:
	PlayerObserver();
	PlayerObserver(Player* player);
	~PlayerObserver();
	void Update();
	void display();
private:
	Player* _playerSubject;
};



