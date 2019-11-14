#pragma once

#include "Player.h"

class Strategy {
public:
	/**
	* Method whose implementation varies depending on the strategy adopted.
	*/
	virtual void execute(const Player&) = 0;

	static void computer_action(const Cards&);
	
	Strategy() = default;
	virtual ~Strategy() = default;
};

class Human : public Strategy
{
public:
	Human() = default;
	~Human() = default;
	void execute(const Player&) override;
};

class Greedy : public Strategy
{
public:
	Greedy() = default;
	~Greedy() = default;
	void execute(const Player&) override;
};

class Moderate : public Strategy
{
public:
	Moderate() = default;
	~Moderate() = default;
	void execute(const Player&) override;
};