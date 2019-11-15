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
		if (playerArmyCount.at(i) == max && players->at(i) != owningPlayer)
		{
			owningPlayer = nullptr;
		}
	}

	if (owningPlayer != nullptr)
	{
		*owningPlayer->victoryPoint = *owningPlayer->victoryPoint + 1;
		owningPlayer->ownedCountries->push_back(country);
	}

	return owningPlayer;

}


void computeScore::continentScore(Map* map, vector<Player*>* players)
{

	for (int i = 0; i < map->mapContinents->size(); i++)
	{
		vector<int> playerCountryCount = vector<int>(players->size());

		for (int j = 0; j < map->mapContinents->at(i)->containedCountries->size(); j++)
		{
			getOwnerOfCountry(map->mapContinents->at(i)->containedCountries->at(j), players);
			for (int k = 0; k < players->size(); k++)
			{
				for (int t = 0; t < players->at(k)->ownedCountries->size(); t++)
				{
					if (map->mapContinents->at(i)->containedCountries->at(j) == players->at(k)->ownedCountries->at(t))
						playerCountryCount.at(k)++;
				}
			}
		}

		int maxCount = 0;
		Player* winningPlayer = nullptr;
		for (int i = 0; i < playerCountryCount.size(); i++)
		{
			if (playerCountryCount.at(i) > maxCount)
			{
				maxCount = playerCountryCount.at(i);
				winningPlayer = players->at(i);
			}
		}


		for (int i = 0; i < playerCountryCount.size(); i++)
		{
			if (playerCountryCount.at(i) == maxCount && players->at(i) != winningPlayer)
			{
				winningPlayer = nullptr;
			}
		}

		if (winningPlayer != nullptr)
		{
			winningPlayer->ownedContinents->push_back(map->mapContinents->at(i));
			*winningPlayer->victoryPoint = *winningPlayer->victoryPoint + 1;
		}

	}

}

Player* computeScore::determineWinner(vector<Player*>* players) {
	Player* winner = players->at(0);//Winner initialize to the first player at first

	for (auto i : *players)
	{
		i->computeScore();
		if (*i->victoryPoint > * winner->victoryPoint)//Update Winner by comparing Points
		{
			winner = i;
			continue;
		}
		if (*i->victoryPoint == *winner->victoryPoint && i != winner)//If points are equals, compare number of coins
		{
			if (*i->numCoins > * winner->numCoins)
			{
				winner = i;
				continue;
			}
			if (*i->numCoins == *winner->numCoins && i != winner)//If Points and coins are equals, check armies
			{
				if ((14 - i->availableArmies()) > 14 - winner->availableArmies())
				{
					winner = i;
					continue;
				}
				if ((14 - i->availableArmies()) == 14 - winner->availableArmies() && i != winner)//If everything before equals, check ownedCountries
				{
					if (i->ownedCountries->size() > winner->ownedCountries->size())
					{
						winner = i;
					}
				}
			}
		}
	}
	return winner;
}
