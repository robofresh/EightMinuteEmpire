#pragma once

#include "Map.h"
#include "Player.h"


class Strategy {
public:
	/**
	* Method whose implementation varies depending on the strategy adopted.
	*/
	virtual void execute(Player*, Map*);
};

class Human : public Strategy
{
public:
	void execute(Player*, Map*) override;
};

class Greedy : public Strategy
{
public:
	void execute(Player*, Map*) override;
};

class Moderate : public Strategy
{
public:
	void execute(Player*, Map*) override;
};