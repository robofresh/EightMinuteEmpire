#pragma once
#include <string>

class Player;

using namespace std;

class Strategy {
public:
	/**
	* Method whose implementation varies depending on the strategy adopted.
	*/
	virtual void execute(Player&) = 0;
	string* type;
	Strategy() = default;
	virtual ~Strategy() = default;
};

class Human : public Strategy
{
public:
	Human();
	~Human();
	void execute(Player&) override;
};

class Greedy : public Strategy
{
public:
	string* type;
	Greedy();
	~Greedy();
	void execute(Player&) override;
};

class Moderate : public Strategy
{
public:
	string* type;
	Moderate();
	~Moderate();
	void execute(Player&) override;
};