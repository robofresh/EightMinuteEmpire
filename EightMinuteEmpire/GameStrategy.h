#pragma once
#include <string>
#include "cards.h"
#include "Player.h"
#include "Actions.h"
#include "GameEngine.h"

class GameEngine;

using namespace std;


class StrategyG {
public:
	/**
	* Method whose implementation varies depending on the strategy adopted.
	*/
	virtual void execute(GameEngine&) = 0;
	string* type;
	StrategyG() = default;
	virtual ~StrategyG() = default;
};

class SingleMode : public StrategyG
{
public:
	SingleMode();
	~SingleMode();
	void execute(GameEngine&) override;

};

class TournamentMode : public StrategyG
{
public:
	TournamentMode();
	~TournamentMode();
	void execute(GameEngine&) override;

};