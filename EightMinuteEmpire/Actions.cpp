#include "Actions.h"



Actions::Actions()
{
}

void actionProcess(string, int, Player* player, Map* map, vector<Player*>*);
void actionPrint(string, int);

void Actions::processAction(Player* player, Cards *card, Map *map, vector<Player*>* playerVector)
{

	/*

	format of actions:

	string = "action" + # + ("AND" or "OR") + "action2" + #
	- # and "AND/OR" are optional, but if there is "AND/OR" there must be an "action2"
	- at least one action is required

	*/

	//process action(s)

	cout << "card: " << card << endl;
	
	//if there is more than one action
	if (card->actions->size() > 2)
	{
		
		int selection = 0;

		if ((string("AND").compare(*card->actions->at(2)) == 0))
		{
			cout << "Select one: " << endl;
			cout << "\t1: ";  actionPrint(*card->actions->at(0), stoi(*card->actions->at(1)));
			cout << " and ";  actionPrint(*card->actions->at(3), stoi(*card->actions->at(4))); cout << endl;
			cout << "\tor" << endl;
			cout << "\t2: take no action " << endl;

			while (selection != 1 && selection != 2)
			{
				cout << "Please enter a valid choice: ";
				cin >> selection;
			}

			if (selection == 1)
			{
				actionProcess(*card->actions->at(0), stoi(*card->actions->at(1)), player, map, playerVector);
				actionProcess(*card->actions->at(3), stoi(*card->actions->at(4)), player, map, playerVector);
			}
			else if (selection == 2)
			{
				cout << "No action was taken." << endl;
				return;
			}
		}

		if ((string("OR").compare(*card->actions->at(2)) == 0))
		{
			cout << "Select one: " << endl;
			cout << "\t1: ";  actionPrint(*card->actions->at(0), stoi(*card->actions->at(1))); cout << endl;
			cout << "\tor" << endl;
			cout << "\t2: ";  actionPrint(*card->actions->at(3), stoi(*card->actions->at(4))); cout << endl;
			cout << "\tor" << endl;
			cout << "\t3: take no action " << endl;

			while (selection != 1 && selection != 2 && selection != 3)
			{
				cout << "Please enter a valid choice: ";
				cin >> selection;
			}

			if (selection == 1)
			{
				actionProcess(*card->actions->at(0), stoi(*card->actions->at(1)), player, map, playerVector);
			}
			else if (selection == 2)
			{
				actionProcess(*card->actions->at(3), stoi(*card->actions->at(4)), player, map, playerVector);
			}
			else if (selection == 3)
			{
				cout << "No action was taken." << endl;
				return;
			}

		}




	}
	else
	{
		int selection = 0;

		cout << "Select one: " << endl;
		cout << "\t1: ";  actionPrint(*card->actions->at(0), stoi(*card->actions->at(1))); cout << endl;
		cout << "\tor" << endl;
		cout << "\t2: take no action " << endl;

		while (selection != 1 && selection != 2)
		{
			cout << "Please enter a valid choice: ";
			cin >> selection;
		}

		if (selection == 1)
		{
			actionProcess(*card->actions->at(0), stoi(*card->actions->at(1)), player, map, playerVector);
		}
		else if (selection == 2)
		{
			cout << "No action was taken." << endl;
			return;
		}
		
	}
}


void actionProcess(string action, int amount, Player *player, Map* map, vector<Player*>* playersVector)
{
	if (string("placeArmies").compare(action) == 0)
	{
		string countryName;
		for (int i = 0; i < amount; i++)
		{
			if (player->availableArmies() > 0)
			{
				Army* newArmy = player->getAvailableArmy();
				
				Country* country = nullptr;
				bool isValid = false;

				while (country == nullptr || !isValid)
				{
					cout << i + 1 << ": Please give a valid country\'s name for the army to be placed in (-1 to exit): ";
					cin >> countryName;
					if (countryName.compare("-1") == 0)
					{
						return;
					}
					//cout << *country->name << endl;
					country = map->getCountry(countryName);

					if (country != nullptr)
					{
						//if the country is the starting country
						if (*country->isStartingCountry)
						{
							isValid = true;
						}
						else
						{
							//if the player has a city in that country
							for (int j = 0; j < country->cities->size(); j++)
							{
								if (country->cities->at(j)->player == player)
								{
									isValid = true;
									break;
								}
							}
							if (!isValid)
								cout << *country->name << " is either not the starting country or the player does not own a city there. " << endl;
						}
					}
				}
				player->placeNewArmies(country, 1);
			}
			else
			{
				cout << "You have no more armies to place. " << endl;
				break;
			}
		}
		return;
	}
	if (string("createCity").compare(action) == 0)
	{
		string countryName;
		for (int i = 0; i < amount; i++)
		{
			if (player->availableCities() > 0)
			{
				City* newCity = player->getAvailableCity();

				Country* country = nullptr;

				bool isValid = false;
				while (country == nullptr || !isValid)
				{
					cout << "Please give a valid country\'s name for the city to be placed in (-1 to exit): ";
					cin >> countryName;
					if (countryName.compare("-1") == 0)
					{
						return;
					}
					//cout << *country->name << endl;
					country = map->getCountry(countryName);

					if (country != nullptr)
					{
						//if the player has amn army in that country
						for (int k = 0; k < country->occupyingArmies->size(); k++)
						{
							if (*country->occupyingArmies->at(k)->player->name == *player->name)
							{
								isValid = true;
								break;
							}
						}
						if(!isValid)
							cout << *player->name << " does not have an army in " << *country->name << endl;
					}
				}
				player->buildCity(country);
			}
			else
			{
				cout << "You have no more cities to place. " << endl;
				break;
			}
		}
		return;
	}
	if (string("move").compare(action) == 0 || string("moveWater").compare(action) == 0)
	{

		vector<int> armiesAlreadyMoved;

		for (int j = 0; j < amount; j++)
		{

			if (player->availableArmies() == 14)
			{
				cout << "No armies have been placed." << endl;
				return;
			}

			//if the card's amount of armies to move is greater than the player's placed armies
			if (armiesAlreadyMoved.size() >= 14 - player->availableArmies())
			{
				return;
			}

			Army* army = nullptr;
			int armyID;


			player->printPlayer();

			bool newArmy = false;
			while (army == nullptr || newArmy == false)
			{
				cout << "Please give a valid placed army number (-1 to exit): ";
				cin >> armyID;

				if (armyID == -1)
				{
					return;
				}

				armyID--;

				newArmy = true;
				for (int i = 0; i < armiesAlreadyMoved.size(); i++)
				{
					if (armyID+1 == armiesAlreadyMoved.at(i))
						newArmy = false;
				}

				if (armyID < 14 && armyID > -1)
				{
					if (player->armies->at(armyID)->occupiedCountry != nullptr)
						army = player->armies->at(armyID);
				}
			}


			if (string("moveWater").compare(action) == 0)
			{
				if (player->armies->at(armyID)->occupiedCountry != nullptr)
				{
					Country* country = nullptr;
					bool isValid = false;
					bool goBack = false;
					while (!isValid)
					{
						string countryName;
						cout << "Please give a valid name for a country to move army " << armyID + 1 << " across land or water to; ";
						cout << "the possible adjacent countries are (-1 to change army selection): " << endl;
						for (int j = 0; j < player->armies->at(armyID)->occupiedCountry->adjCountries->size(); j++)
						{
							cout << "\t" << *player->armies->at(armyID)->occupiedCountry->adjCountries->at(j)->name << endl;
						}
						cin >> countryName;
						if (countryName.compare("-1") == 0)
						{
							goBack = true;
							break;
						}
						country = map->getCountry(countryName);
						if (country != nullptr)
						{
							for (int j = 0; j < country->adjCountries->size(); j++)
							{
								//if the army's country is adjacent to the selected country
								if (*army->occupiedCountry->name == *country->adjCountries->at(j)->name)
									isValid = true;
							}
						}
					}

					if (goBack)
					{
						j--;
						continue;
					}
					armiesAlreadyMoved.push_back(armyID + 1);

					player->moveArmies(army->occupiedCountry, country, 1);
				}
			}
			else
			{
				if (player->armies->at(armyID)->occupiedCountry != nullptr)
				{
					Country* country = nullptr;
					bool isValid = false;
					bool isIsland = false;
					bool goBack = false;
					while (!isValid)
					{
						string countryName;
						int countryCheck = 0;
						for (int j = 0; j < player->armies->at(armyID)->occupiedCountry->adjCountries->size(); j++)
						{
							//if the army's country is adjacent to the selected country and if they are in the same continent
							if (*army->occupiedCountry->parentContinent->name == *player->armies->at(armyID)->occupiedCountry->adjCountries->at(j)->parentContinent->name)
								countryCheck++;
						}
						if (countryCheck == 0)
						{
							goBack = true;
							break;
						}

						cout << "Please give a valid name for a country in " << *army->occupiedCountry->parentContinent->name << " to move army " << armyID + 1 << " to; ";
						cout << "the possible adjacent countries are (-1 to change army selection): " << endl;
						for (int j = 0; j < player->armies->at(armyID)->occupiedCountry->adjCountries->size(); j++)
						{
							//if the army's country is adjacent to the selected country and if they are in the same continent
							if (*army->occupiedCountry->parentContinent->name == *player->armies->at(armyID)->occupiedCountry->adjCountries->at(j)->parentContinent->name)
								cout << "\t" << *player->armies->at(armyID)->occupiedCountry->adjCountries->at(j)->name << endl;
						}
						cin >> countryName;
						if (countryName.compare("-1") == 0)
						{
							isIsland = true;
							break;
						}
						country = map->getCountry(countryName);
						if (country != nullptr)
						{
							for (int j = 0; j < country->adjCountries->size(); j++)
							{
								//if the army's country is adjacent to the selected country and if they are in the same continent
								if (*army->occupiedCountry->name == *country->adjCountries->at(j)->name && *army->occupiedCountry->parentContinent->name == *country->parentContinent->name)
									isValid = true;
							}
						}
					}
					if (isIsland)
					{
						cout << "Invalid: this country is an island" << endl;
						j--;
						continue;
					}
					if (goBack)
					{
						j--;
						continue;
					}
					armiesAlreadyMoved.push_back(armyID + 1);

					player->moveOverLand(army->occupiedCountry, country);
				}
			}
		}
	}
	if (string("destroyArmies").compare(action) == 0)
	{
		Country* country = nullptr;
		Player* enemyPlayer = nullptr;
		while (country == nullptr || enemyPlayer == nullptr)
		{
			string enemyName;
			cout << "Give a valid player name (-1 to exit): ";
			cin >> enemyName;
			if (enemyName.compare("-1") == 0)
			{
				return;
			}
			for (int i = 0; i < playersVector->size(); i++)
			{
				if (enemyName.compare(*playersVector->at(i)->name) == 0)
					enemyPlayer = playersVector->at(i);
			}

			string countryName;
			while (true)
			{
				cout << "Give a valid country name (-1 to exit): ";
				cin >> countryName;
				if (countryName.compare("-1") == 0)
				{
					return;
				}
				country = map->getCountry(countryName);
				if (country != nullptr)
				{
					for (int i = 0; i < country->occupyingArmies->size(); i++)
					{
						if (enemyName.compare(*country->occupyingArmies->at(i)->player->name) == 0)
						{
							country = enemyPlayer->armies->at(i)->occupiedCountry;
							player->destroyArmy(country, enemyPlayer);
							return;
						}
					}
					cout << enemyName << " does not have an army in " << countryName << endl;
				}
			}
		}
	}
}


void actionPrint(string action, int amount)
{
	if (string("placeArmies").compare(action) == 0)
	{
		if (amount > 1)
		{
			cout << "Place " << amount << " armies";
			return;
		}
		cout << "Place " << amount << " army";
	}
	if (string("move").compare(action) == 0)
	{
		if (amount > 1)
		{
			cout << "Move " << amount << " armies";
			return;
		}
		cout << "Move " << amount << " army";
	}
	if (string("createCity").compare(action) == 0)
	{
		if (amount > 1)
		{
			cout << "Create " << amount << " cities";
			return;
		}
		cout << "Create " << amount << " city";
	}
	if (string("moveWater").compare(action) == 0)
	{
		if (amount > 1)
		{
			cout << "Move " << amount << " armies across water/land";
			return;
		}
		cout << "Move " << amount << " army across water/land";
	}
	if (string("destroyArmies").compare(action) == 0)
	{
		if (amount > 1)
		{
			cout << "Destroy " << amount << " armies";
			return;
		}
		cout << "Destroy " << amount << " army";
	}
}


Actions::~Actions()
{
}
