#pragma once

#include <list>
#include <vector>

using namespace std;

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

class GameStatistics : public Observer
{
public:
	GameStatistics();
	GameStatistics(Map*, vector<Player*>*);
	~GameStatistics();
	void Update();
	void display();
private:
	Map* mapSubject;
	vector<Player*>* players;
};
