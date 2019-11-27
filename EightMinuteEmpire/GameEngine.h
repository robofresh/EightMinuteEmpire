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
	enum mode { single, tournament };
private:
	mode* mode;
	Map* map;
	MapLoader mapLoader;
	Deck* deck;
	int* supply;
	vector<Player*>* players;
	Country* startingCountry;


public:
	GameEngine();
	GameEngine(mode);
	~GameEngine();
	void setMode(mode);
	void setStartingCountry(Country*);
	void chooseMap();//Prompt user to choose map
	void choosePlayers();//Prompt user to select num of players and set their strategy

};