#pragma once
#include <list>
#include <string>
#include <vector>

using namespace std;

class Cards;
class Observer;
class Subject;
class GameStatistics;
class Player;
class Map;

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
	virtual void Update();
	virtual void display();
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
	virtual void Update();
	virtual void display();
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
	virtual void Update();
	virtual void display();

private:
	int* cost;
	int* supply;
};

class ActionOb:public Observer
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
	Player* _playerSubject;
	Cards* _cardChosen;
	int* position;
	int* _supply;
	vector<string*>* _action;
	vector<int*>* _amount;
};
	
class GameStatistics : public Observer
{
public:
	GameStatistics();
	GameStatistics(Map*, vector<Player*>*);
	~GameStatistics();
	void Update();
	void display();
protected:
	Map* mapSubject;
	vector<Player*>* players;
};


class GameWinningScores : public Observer
{
public:
	GameWinningScores();
	GameWinningScores(Map*, vector<Player*>*, Player*);
	~GameWinningScores();
	void Update();
	void display();
protected:
	Map* mapSubject;
	vector<Player*>* players;
	Player* winningPlayer;
};
