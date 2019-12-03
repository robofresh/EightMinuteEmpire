//#include <iostream>
//#include <limits>
//#include <vector>
//#include "cards.h"
//#include "Player.h"
//#include "Map.h"
//#include "MapLoader.h"
//#include "Actions.h"
//#include "computeScore.h"
//#include "GameObservers.h"
//#include "global.h"
//
//int main()
//{
//	// #########################################################
//	//		Setup map, deck, players, and other values
//	// #########################################################
//	Map* map = Map::getInstance();
//	MapLoader* mapLoader = new MapLoader("map1.map", map);
//	Country* startingCountry = map->startingCountry;
//	global::main_deck = new Deck();
//	global::players = new vector<Player*>();
//	const int NUM_COINS_PER_PLAYER = 20;
//	const int NUM_PLAYERS = 2;
//	Player* player1 = new Player("Alice", 25, NUM_COINS_PER_PLAYER, "Red", global::main_deck);
//	global::players->push_back(player1);
//	Player* player2 = new Player("Bob", 25, NUM_COINS_PER_PLAYER, "Blue", global::main_deck);
//	global::players->push_back(player2);
//
//	//Other details for setting up the game
//	bool endGame = false;
//	const int MAX_CARDS = 5;
//	global::action = new Actions();
//	int supplyVal = 44 - (NUM_COINS_PER_PLAYER * NUM_PLAYERS);
//	int* supply = &supplyVal;
//
//	// Place 3 armies of each player on the starting country.
//	for (int i = 0; i < global::players->size(); i++)
//	{
//		global::players->at(i)->placeNewArmies(startingCountry, 3);
//	}
//	global::main_deck->initialDraw();
//
//	Player* currentPlayer = player1;
//	int* currentPlayerIndex = new int(0);
//	Player* lastPlayer;
//	int lastIndex = (*currentPlayerIndex + NUM_PLAYERS - 1) % NUM_PLAYERS;
//	lastPlayer = global::players->at(lastIndex);
//
//	GameStatistics* gameStats = new GameStatistics(map, global::players);
//
//	cout << endl;
//	cout << "****************END OF GAME****************" << endl;
//
//	computeScore score = computeScore();
//	Player* winner = score.determineWinner(global::players);
//	GameWinningScores* gameWin = new GameWinningScores(map, global::players, winner);
//	map->Notify();
//
//	// #################################################
//	//						Cleanup
//	// #################################################
//
//	for (int i = 0; i < NUM_PLAYERS; i++)
//	{
//		delete global::players->at(i);
//	}
//	delete global::players;
//	global::players = NULL;
//	delete global::main_deck;
//	global::main_deck = NULL;
//	delete mapLoader;
//	mapLoader = NULL;
//	startingCountry = NULL;
//	supply = NULL;
//	currentPlayer = NULL;
//	delete currentPlayerIndex;
//	currentPlayerIndex = NULL;
//	lastPlayer = NULL;
//	delete global::action;
//	global::action = NULL;
//	winner = NULL;
//	delete gameWin;
//	gameWin = NULL;
//	delete gameStats;
//	gameStats = NULL;
//	delete map;
//	map = NULL;
//}
