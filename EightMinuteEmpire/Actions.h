#pragma once
#include "Player.h"
#include "cards.h"

class Actions
{
public:
	Actions();
	~Actions();

	void processAction(Player*, Cards*);

};

