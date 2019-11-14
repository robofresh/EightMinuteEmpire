#include <iostream>
#include <limits>
#include <vector>
#include "cards.h"
#include "Player.h"
#include "Map.h"
#include "MapLoader.h"
#include "Actions.h"
#include "computeScore.h"
#include "GameObservers.h"

int main()
{
	// #########################################################
	//		Setup map, deck, players, and other values
	// #########################################################
	Map* map = Map::getInstance();
	MapLoader* mapLoader = new MapLoader("map1.map", map);
	Country* startingCountry = map->startingCountry; 
	Deck* deck = new Deck();
	vector<Player*>* players = new vector<Player*>();
	const int NUM_COINS_PER_PLAYER = 20;
	const int NUM_PLAYERS = 2;
	Player* player1 = new Player("Alice", 23, NUM_COINS_PER_PLAYER, "Red", deck);
	players->push_back(player1);
	Player* player2 = new Player("Bob", 25, NUM_COINS_PER_PLAYER, "Blue", deck);
	players->push_back(player2);

	//Other details for setting up the game
	bool endGame = false;
	const int MAX_CARDS = 5;
	Actions* action = new Actions();
	int supplyVal = 44 - (NUM_COINS_PER_PLAYER * NUM_PLAYERS);
	int* supply = &supplyVal;

	// Place 3 armies of each player on the starting country.
	for (int i = 0; i < players->size(); i++)
	{
		players->at(i)->placeNewArmies(startingCountry, 3);
	}
	deck->initialDraw();

	Player* currentPlayer = player1;
	int* currentPlayerIndex = new int(0);
	Player* lastPlayer;
	int lastIndex = (*currentPlayerIndex + NUM_PLAYERS - 1) % NUM_PLAYERS;
	lastPlayer = players->at(lastIndex);

	GameStatistics* gameStats = new GameStatistics(map, players);

	int newIndex;
	do {
		Cards* chosenCard;
		int cardPosition;

		deck->cardsSpace->print();
		cout << *currentPlayer->name << "! Select one of the face-up cards" << endl;
		cin >> cardPosition;

		cardPosition = cardPosition - 1;
		chosenCard = deck->cardsSpace->faceupcards->at(cardPosition);

		chosenCard->print();

		currentPlayer->hand->faceupcards->push_back(chosenCard);//Push address 
		currentPlayer->payCard(chosenCard, cardPosition, supply);//Pay the correct amount of coins

		action->processAction(currentPlayer, chosenCard, map, players);

		cout << *(currentPlayer->name) << " now has " << currentPlayer->hand->faceupcards->size() << " cards" << endl;

		deck->updateCardsSpace(deck, cardPosition);

		//Loop to the next player
		newIndex = *currentPlayerIndex + 1;//Increasing the index position is clockwise 
		*currentPlayerIndex = newIndex % NUM_PLAYERS;
		currentPlayer = players->at(*currentPlayerIndex);//update current player

		cout << endl;
		cout << "************************************************************" << endl;
		cout << endl;
		cout << "Current player is " << *(currentPlayer->name) << ", now with " << *(currentPlayer->numCoins) << " coins." << endl;

		if (lastPlayer->hand->faceupcards->size() >= MAX_CARDS)
		{
			cout << "Every Players has ";
			cout << currentPlayer->hand->faceupcards->size() << " cards. " << endl;
			cout << "Max cards each player can own has been reach. " << endl;
			endGame = true;
		}

	} while (!endGame);
}