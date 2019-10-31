#include "Actions.h"



Actions::Actions()
{
}

void actionProcess(string, int, Player* player, Map* map);
void actionPrint(string, int);

void Actions::processAction(Player* player, Cards *card, Map *map)
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
			cout << " and ";  actionPrint(*card->actions->at(3), stoi(*card->actions->at(4)));
			cout << "\tor" << endl;
			cout << "\t2: take no action " << endl;

			while (selection != 1 && selection != 2)
			{
				cout << "Please enter a valid choice: ";
				cin >> selection;
			}

			if (selection == 1)
			{
				actionProcess(*card->actions->at(0), stoi(*card->actions->at(1)), player, map);
				actionProcess(*card->actions->at(3), stoi(*card->actions->at(4)), player, map);
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
			cout << "\t1: ";  actionPrint(*card->actions->at(0), stoi(*card->actions->at(1)));
			cout << "\tor" << endl;
			cout << "\t2: ";  actionPrint(*card->actions->at(3), stoi(*card->actions->at(4)));
			cout << "\tor" << endl;
			cout << "\t3: take no action " << endl;

			while (selection != 1 && selection != 2 && selection != 3)
			{
				cout << "Please enter a valid choice: ";
				cin >> selection;
			}

			if (selection == 1)
			{
				actionProcess(*card->actions->at(0), stoi(*card->actions->at(1)), player, map);
			}
			else if (selection == 2)
			{
				actionProcess(*card->actions->at(3), stoi(*card->actions->at(4)), player, map);
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
		cout << "\t1: ";  actionPrint(*card->actions->at(0), stoi(*card->actions->at(1)));
		cout << "\tor" << endl;
		cout << "\t2: take no action " << endl;

		while (selection != 1 && selection != 2)
		{
			cout << "Please enter a valid choice: ";
			cin >> selection;
		}

		if (selection == 1)
		{
			actionProcess(*card->actions->at(0), stoi(*card->actions->at(1)), player, map);
		}
		else if (selection == 2)
		{
			cout << "No action was taken." << endl;
			return;
		}
		
	}
}


void actionProcess(string action, int amount, Player *player, Map* map)
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
				while (country == nullptr)
				{
					cout << "Please give a valid country\'s name for the army " << i+1 << " to be placed in: ";
					cin >> countryName;
					//cout << *country->name << endl;
					country = map->getCountry(countryName);
				}
				country->occupyingArmies->push_back(newArmy);
				newArmy->setOccupiedCountry(country);
				cout << "Army " << i+1 << " has been placed in " << *newArmy->occupiedCountry->name << endl;
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
				while (country == nullptr)
				{
					cout << "Please give a valid country\'s name for the city to be placed in: ";
					cin >> countryName;
					//cout << *country->name << endl;
					country = map->getCountry(countryName);
				}
				country->cities->push_back(newCity);
				newCity->setOccupiedCountry(country);
				cout << "Army " << i + 1 << " has been placed in " << *newCity->occupiedCountry->name << endl;
			}
			else
			{
				cout << "You have no more armies to place. " << endl;
				break;
			}
		}
		return;
	}
	if (string("move").compare(action) == 0)
	{

		vector<int> armiesAlreadyMoved;

		for (int j = 0; j < amount; j++)
		{

			if (player->availableArmies() == 14)
			{
				cout << "No armies have been placed." << endl;
				return;
			}

			Army* army = nullptr;
			int armyID;

			player->printPlayer();

			while (army == nullptr)
			{
				cout << "Please give a valid placed army number: ";
				cin >> armyID;

				armyID--;

				for (int i = 0; i < armiesAlreadyMoved.size(); i++)
				{
					if (armyID+1 == armiesAlreadyMoved.at(i))
						continue;
				}

				if (armyID < 14 && armyID > -1)
				{
					if (player->armies->at(armyID)->occupiedCountry != nullptr)
						army = player->armies->at(armyID);
				}
			}

			armiesAlreadyMoved.push_back(armyID+1);

			if (player->armies->at(armyID)->occupiedCountry != nullptr)
			{
				Country* country = nullptr;
				bool isValid = false;
				while (!isValid)
				{
					string countryName;
					cout << "Please give a valid name for a country in " << *army->occupiedCountry->parentContinent->name << " to move army " << armyID+1 << " to: ";
					cin >> countryName;
					country = map->getCountry(countryName);
					if (country != nullptr && country->parentContinent == army->occupiedCountry->parentContinent)
						isValid = true;
				}
				country->removeArmy(army);
				army->setOccupiedCountry(country);
			}
		}
	}
	if (string("waterMove").compare(action) == 0)
	{

	}
	if (string("destroyArmies").compare(action) == 0)
	{

	}
}


void actionPrint(string action, int amount)
{
	if (string("placeArmies").compare(action) == 0)
	{
		if (amount > 1)
		{
			cout << "Place " << amount << " armies" << endl;
			return;
		}
		cout << "Place " << amount << " army" << endl;
	}
	if (string("move").compare(action) == 0)
	{
		if (amount > 1)
		{
			cout << "Move " << amount << " armies" << endl;
			return;
		}
		cout << "Move " << amount << " army" << endl;
	}
	if (string("createCity").compare(action) == 0)
	{
		if (amount > 1)
		{
			cout << "Create " << amount << " cities" << endl;
			return;
		}
		cout << "Create " << amount << " city" << endl;
	}
	if (string("waterMove").compare(action) == 0)
	{
		if (amount > 1)
		{
			cout << "Move " << amount << " armies transcontinentally" << endl;
			return;
		}
		cout << "Move " << amount << " army transcontinentally" << endl;
	}
	if (string("destroyArmies").compare(action) == 0)
	{
		if (amount > 1)
		{
			cout << "Destroy " << amount << " armies" << endl;
			return;
		}
		cout << "Destroy " << amount << " army" << endl;
	}
}


Actions::~Actions()
{
}
