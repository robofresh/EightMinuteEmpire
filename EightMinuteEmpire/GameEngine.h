#pragma once
#include <string>
#include <vector>

#include "cards.h"
#include "Player.h"
#include "Map.h"
#include "MapLoader.h"
#include "Actions.h"
#include "computeScore.h"


using namespace std;


class GameEngine 
{
	enum class mode { single, tournament };
private:
	mode mode;
	Map* map;
	MapLoader mapLoader;//TODO: Will need to change this to a ptr since 
	//all member of a class needs to be ptr
	Deck* deck;
	int* supply;
	vector<Player*>* players;
	Country* startingCountry;
	int* NUM_PLAYERS;
	int* NUM_COINS_PER_PLAYER;
	const string COLORS[5] = { "Red", "Blue", "Green", "Yellow", "White" };


public:
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
	void startGame();// Depending on the mode it will loop differentely
	void setSupply();
	int* getSupply();
	void setNumCoinsPerPlayer(const int);
	int* getNumCoinsPerPlayer();
	void createPlayers();

};