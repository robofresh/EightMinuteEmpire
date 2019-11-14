#pragma once
#include "Player.h"
#include "cards.h"

class Actions
{
public:
	Actions() = default;
	~Actions() = default;

	void processAction(Player*, Cards*, Map*, vector<Player*>*) const;
	void computer_action(Player&, Cards& c) const;
};

