#include "PlayerStrategies.h"
#include "global.h"

using namespace std;

//Exception struct of Wrong input type
struct InputException : public exception
{
	const char* what() const throw()
	{
		return "Your input is invalid.";
	}
};

//Exception struct if insufficient Coins
struct InsufficientCoinsException : public exception
{
	const char* what() const throw()
	{
		return "Player does not have enough coins.";
	}
};

void Human::execute(Player& p)
{
	//Current user takes one face-up card & pay the cost of the card
	Cards* chosenCard;
	int cardPosition;
	bool enoughCoins;

	do
	{
		enoughCoins = true;
		try
		{
			global::main_deck->cardsSpace->print();
			cout << *p.name;
			cout << "! Select one of the face-up cards" << endl;
			cin >> cardPosition;
			if (std::cin.fail())
				throw InputException();

			//Situations when player's ownCoins are limited
			if (*p.numCoins <= 3)
			{
				if (*p.numCoins == 0 && cardPosition != 1)
					throw InsufficientCoinsException();
				if (*p.numCoins == 1 &&
					(cardPosition == 6 || cardPosition == 5 || cardPosition == 4))
					throw InsufficientCoinsException();
				if (*p.numCoins == 2 &&
					(cardPosition == 6))
					throw InsufficientCoinsException();
			}
		}
		catch (InputException e)
		{
			cout << e.what() << endl;
			cout << "Game will close down!" << endl;
			exit(0);

		}
		catch (InsufficientCoinsException e)
		{
			cout << e.what() << endl;
			enoughCoins = false;
		}

	} while (!(cardPosition >= 1 && cardPosition <= 6) || !enoughCoins);
	//Continue loop if not enough Coins to pay for the card 
	//OR if the Card position chosen is NOT between 1 and 6

	cardPosition = cardPosition - 1;
	chosenCard = global::main_deck->cardsSpace->faceupcards->at(cardPosition);

	chosenCard->print();

	p.hand->faceupcards->push_back(chosenCard);//Push address 
	p.payCard(chosenCard, global::supply);//Pay the correct amount of coins

	global::action->processAction(&p, chosenCard, Map::getInstance(), global::players);
	
	//Update face-ups cards
	global::main_deck->updateCardsSpace(global::main_deck, global::main_deck->cardsSpace->faceupcards->at(cardPosition));
}

void Greedy::execute(Player& p)
{
	global::main_deck->cardsSpace->print();


	cout << "\tThe greedy computer will try to destroy armies or create cities." << endl;

	//go through all face-up cards
	for(auto i : *global::main_deck->cardsSpace->faceupcards)
	{
		//go through all actions of face-up cards
		for(auto j : *i->actions)
		{
			//do action if any card has them
			if (*j == "destroyArmies")
			{
				cout << "\tSelected card: " << endl;
				i->print();

				p.hand->faceupcards->push_back(i);//Push address 
				p.payCard(i, global::supply);//Pay the correct amount of coins

				global::action->computer_action(p, *i);
				
				//Update face-ups cards
				global::main_deck->updateCardsSpace(global::main_deck, i);
				return;
			}
			if (*j == "createCity")
			{
				cout << "\tSelected card: " << endl;
				i->print();

				p.hand->faceupcards->push_back(i);//Push address 
				p.payCard(i, global::supply);//Pay the correct amount of coins

				global::action->computer_action(p, *i);
				
				//Update face-ups cards
				global::main_deck->updateCardsSpace(global::main_deck, i);
				return;
			}
		}
	}
	//if no face-up card has destroyArmies or createCity, choose the first one (cheapest) and do it's action
	cout << "\tThe greedy computer did not find any destroy armies or create city cards." << endl;
	cout << "\tIt will take the cheapest one." << endl;
	global::main_deck->cardsSpace->faceupcards->at(0)->print();



	p.hand->faceupcards->push_back(global::main_deck->cardsSpace->faceupcards->at(0));//Push address 
	p.payCard(global::main_deck->cardsSpace->faceupcards->at(0), global::supply);//Pay the correct amount of coins
	global::action->computer_action(p, *global::main_deck->cardsSpace->faceupcards->at(0));

	//Update face-ups cards
	global::main_deck->updateCardsSpace(global::main_deck, global::main_deck->cardsSpace->faceupcards->at(0));
}

void Moderate::execute(Player& p)
{
	global::main_deck->cardsSpace->print();

	
	cout << "\tThe moderate computer will try to place armies to control regions." << endl;

	//go through all face-up cards
	for (auto i : *global::main_deck->cardsSpace->faceupcards)
	{
		//go through all actions of face-up cards
		for (auto j : *i->actions)
		{
			//do action if any card has them
			if (*j == "placeArmies" && Map::getInstance()->startingCountry->owningPlayer != &p)
			{
				cout << "\tSelected card: " << endl;
				i->print();

				p.hand->faceupcards->push_back(i);//Push address 
				p.payCard(i, global::supply);//Pay the correct amount of coins

				global::action->computer_action(p, *i);
				
				global::main_deck->updateCardsSpace(global::main_deck, i);
				return;
			}
		}
	}
	//if no face-up card has destroyArmies or createCity, choose the first one (cheapest) and do it's action
	cout << "\tThe moderate computer did not find any place army cards or already owns the starting country." << endl;
	cout << "\tIt will take the cheapest card." << endl;
	global::main_deck->cardsSpace->faceupcards->at(0)->print();

	p.hand->faceupcards->push_back(global::main_deck->cardsSpace->faceupcards->at(0));//Push address 
	p.payCard(global::main_deck->cardsSpace->faceupcards->at(0), global::supply);//Pay the correct amount of coins
	global::action->computer_action(p, *global::main_deck->cardsSpace->faceupcards->at(0));

	//Update face-ups cards
	global::main_deck->updateCardsSpace(global::main_deck, global::main_deck->cardsSpace->faceupcards->at(0));
}






Human::Human()
{
	Strategy::type = new string("human");
}

Greedy::Greedy()
{
	Strategy::type = new string("greedy");
}

Moderate::Moderate()
{
	Strategy::type = new string("moderate");
}

Human::~Human()
{
	delete Strategy::type;
}

Greedy::~Greedy()
{
	delete Strategy::type;
}

Moderate::~Moderate()
{
	delete Strategy::type;
}




