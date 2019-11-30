#pragma once
#include <string>
#include <vector>
#include "cards.h"
#include "Player.h"
#include "Map.h"
#include "MapLoader.h"
#include "Actions.h"
#include "computeScore.h"
#include "GameStrategy.h"


using namespace std;

class StrategyG;

class GameEngine 
{
	enum class mode { single, tournament };
private:
	mode mode;
	Map* map;
	Deck* deck;
	int* supply;
	vector<Player*>* players;
	Country* startingCountry;
	int* NUM_PLAYERS;
	int* NUM_COINS_PER_PLAYER;
	StrategyG* strategy;//strategy is the mode of the game

public:
	const string COLORS[5] = { "Red", "Blue", "Green", "Yellow", "White" };//TODO: mght need to move this to Global
	GameEngine();
	GameEngine(string);
	~GameEngine();
	void setMode(string);
	int getMode();
	void setStartingCountry(Country*);
	Country* getStartingCountry();
	void chooseMap();//Prompt user to choose map
	void choosePlayers();//Prompt user to select num of players and set their strategy
	void setNumOfPlayers();
	int* getNumOfPlayers();
	Deck* getDeck();
	void setSupply();
	int* getSupply();
	void setNumCoinsPerPlayer(const int);
	int* getNumCoinsPerPlayer();
	void createPlayers();
	void set_strategy(StrategyG* strat);
	void execute_strategy();
	StrategyG* get_strategy();


};