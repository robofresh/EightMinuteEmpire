#pragma once
#include <list>
#include <string>
#include <vector>


using namespace std;

//Only way I found to actually avoid the circular referencing header files....
class Cards;
class Player;
//To avoid compiler crash....

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
	PlayerObserver(Player*, int* );
	~PlayerObserver();
	void Update();
	void display();
protected:
	Player* _playerSubject;
	int* _index;
};

class CurrentPOb : public PlayerObserver
{
public:
	CurrentPOb();
	CurrentPOb(Player*, Cards*, int*, int*);
	~CurrentPOb();
	void Update();
	void display();
protected:
	//Player* _currentSubject;
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

class ActionOb : public CurrentPOb
{
public:
	ActionOb();
	ActionOb(Player*, Cards*);
	ActionOb(Player*, Cards*, string*);
	ActionOb(Player*, Cards*, string*, int*);
	~ActionOb();
	void Update();
	void display();
	void setAction(string*);
	void setAmount(int*);

private:
	vector<string*>* _action;
	vector<int*>* _amount;
	
};
