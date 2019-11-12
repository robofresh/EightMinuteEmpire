#pragma once
#include <list>
#include "Map.h"
#include "cards.h"

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

class CurrentPOb : public Observer
{
public:
	CurrentPOb();
	CurrentPOb(Player*, Cards*, int*, int*);
	~CurrentPOb();
	void Update();
	void display();
protected:
	Player* _currentSubject;
	Cards* _cardChosen;
	int* position;
	int* _supply;
};

class PayOb : public CurrentPOb
{
public:
	PayOb();
	PayOb(Player*, int*, int*);
	~PayOb();
	void Update();
	void display();

private:
	int* cost;
	int* supply;
};


