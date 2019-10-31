#include "Actions.h"



Actions::Actions()
{
}

void actionString(string);

void Actions::processAction(Player* player, Cards *card)
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
		if ((string("AND").compare(*card->actions->at(2)) == 0))
		{
			//both actions
		}

		if ((string("OR").compare(*card->actions->at(2)) == 0))
		{
			//one action
		}

		//first action
		if (string("createArmies").compare(*card->actions->at(0)) == 0)
		{
			if (card->actions->at(1) != nullptr)
			{
				for (int i = 0; i < stoi(*card->actions->at(1)); i++)
				{
					cout << "createArmies action " << i + 1 << endl;
				}
			}
			else
			{
				cout << "createArmies action" << endl;
			}
		}


	}
	else
	{
		//first action
		if (string("createArmies").compare(*card->actions->at(0)) == 0)
		{
			//if actions should be more than once
			if (card->actions->at(1) != nullptr)
			{
				for (int i = 0; i < stoi(*card->actions->at(1)); i++)
				{
					cout << "createArmies action " << i+1 << endl;
				}
			}
			else
			{
				cout << "createArmies action" << endl;
			}
		}
	}
}


void actionString(string action)
{
	if (string("createArmies").compare(action) == 0)
	{

	}
	if (string("createCity").compare(action) == 0)
	{

	}
	if (string("landMove").compare(action) == 0)
	{

	}
	if (string("waterMove").compare(action) == 0)
	{

	}
	if (string("destroyArmies").compare(action) == 0)
	{

	}
}

Actions::~Actions()
{
}
