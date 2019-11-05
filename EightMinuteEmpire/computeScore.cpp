#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>
#include <exception>
#include "Player.h"
#include "Cards.h"
#include "computeScore.h"

Player* getOwnerOfCountry(Country* country,vector<Player*>* players)
{
	Player* owningPlayer = nullptr;

	vector<int> playerArmyCount = vector<int>(players->size());

	if (country->occupyingArmies->size() > 0)
	{
		for (int j = 0; j < country->occupyingArmies->size(); j++)
		{
			for (int k = 0; k < players->size(); k++)
			{
				if (country->occupyingArmies->at(j)->player == players->at(k))
					playerArmyCount.at(k)++;
			}
		}
	}

	if (country->cities->size() > 0)
	{
		for (int j = 0; j < country->cities->size(); j++)
		{
			for (int k = 0; k < players->size(); k++)
			{
				if (country->cities->at(j)->player == players->at(k))
					playerArmyCount.at(k)++;
			}
		}
	}

	int max = 0;
	for (int i = 0; i < playerArmyCount.size(); i++)
	{
		if (playerArmyCount.at(i) > max)
		{
			max = playerArmyCount.at(i);
			owningPlayer = players->at(i);
		}
	}

	*owningPlayer->victoryPoint++;

	return owningPlayer;

}


void computeScore::continentScore(Map* map, vector<Player*>* players)
{

	vector<int> playerCountryCount = vector<int>(players->size());


	for (int i = 0; i < map->mapContinents->size(); i++)
	{

		for (int j = 0; j < map->mapContinents->at(i)->containedCountries->size(); j++)
		{
			for (int k = 0; k < players->size(); k++)
			{
				if (getOwnerOfCountry(map->mapContinents->at(i)->containedCountries->at(j), players) == players->at(k))
					playerCountryCount.at(k)++;
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

}


