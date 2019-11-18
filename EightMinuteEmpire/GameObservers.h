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
class Country;

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
	void setCost(int*);
	void setSupply(int*);

protected:
	Cards* _cardChosen;
	int* position;
	int* _supply;
	int* _cost;
};

class ActionOb:public Observer
{
public:
	ActionOb();
	ActionOb(Player*, Cards*);
	~ActionOb();
	void Update();
	void display();
	void setAction(string*);
	void setAmount(int*);

private:
	Player* _playerSubject;
	Cards* _cardChosen;
	vector<string*>* _action;
	vector<int*>* _amount;
};

class ProcessActOb :public Observer
{
public:
	ProcessActOb();
	ProcessActOb(Player*);
	ProcessActOb(Player*, Country*, int);
	ProcessActOb(Player*, Country*, Country*);
	ProcessActOb(Player*, Country*);
	ProcessActOb(Player*, Country*, Player*);
	~ProcessActOb();
	void Update();
	void display();

private:
	Player* _playerSubject;
	Country* _initCountry;
	Country* _finalCountry;
	Player* _playerTarget;
	int* _numArmy;
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
