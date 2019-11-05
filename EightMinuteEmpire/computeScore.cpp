#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>
#include <exception>
#include "Player.h"
#include "Cards.h"
#include "computeScore.h"

void computeScore::continentScore(Map* map, vector<Player*>* players)
{
	vector<int> playerCountryCount = vector<int>(players->size());

	for (int k = 0; k < players->size(); k++)
	{
		for (int i = 0; i < map->mapContinents->size(); i++)
		{
			for (int j = 0; j < map->mapContinents->at(i)->containedCountries->size(); j++)
			{
				if (map->mapContinents->at(i)->containedCountries->at(j)->owningPlayer == players->at(k))
					playerCountryCount.at(k)++;
			}
		}
	}

	int maxCount = 0;
	int winningPlayer = -1;
	for (int i = 0; i < playerCountryCount.size(); i++)
	{
		if (playerCountryCount.at(i) > maxCount)
		{
			maxCount = playerCountryCount.at(i);
			winningPlayer = i;
		}
	}

	for (int i = 0; i < playerCountryCount.size(); i++)
	{
		if (playerCountryCount.at(i) == maxCount)
		{
			winningPlayer = -1;
		}
	}

	if (winningPlayer != -1)
	{
		*players->at(winningPlayer)->victoryPoint = *players->at(winningPlayer)->victoryPoint + 1;
	}

}


