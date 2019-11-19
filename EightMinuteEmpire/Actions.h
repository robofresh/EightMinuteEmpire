#pragma once
#include "Player.h"
#include "cards.h"
#include "GameObservers.h"

class Actions: public Subject
{
public:
	Actions() = default;
	~Actions() = default;

	void processAction(Player*, Cards*, Map*, vector<Player*>*) const;

};

