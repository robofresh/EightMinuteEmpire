#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include "Map.h"
#include "Player.h"

class computeScore;

class computeScore
{
	public:
		void continentScore(Map*, vector<Player*>*);
		Player* determineWinner(vector<Player*>*);
};