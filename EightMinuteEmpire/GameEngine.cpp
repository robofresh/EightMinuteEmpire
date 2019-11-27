#pragma once
#include "GameEngine.h"

using namespace std;

//getMapFileName returns the name of the file
string getMapFileName()
{
	string mapFileName = "";
	int fileSelectInput;

	cout << "The following map choices exist for the game:" << endl;
	cout << "\t[1] map1.map" << endl;
	cout << "\t[2] invalidMap.map" << endl;
	cout << "\t[3] nonexistantMap.map" << endl;
	while (true)
	{
		cout << "Enter the number of the map to use for the game: ";
		cin >> fileSelectInput;
		if (fileSelectInput < 1 || fileSelectInput > 3)
		{
			cout << "You've entered a number outside of the correct range. Try again." << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // See [1]
		}
		else
		{
			cout << endl;
			break;
		}
	}
	switch (fileSelectInput)
	{
	case 1:
		mapFileName = "map1.map";
		break;
	case 2:
		mapFileName = "invalidMap.map";
		break;
	case 3:
		mapFileName = "nonexistantMap.map";
		break;
	default:
		break;
	}
	return mapFileName;
}

GameEngine::GameEngine() 
{
	mode= ( GameEngine::mode::single);
	map = nullptr;
	//mapLoader = NULL;
	deck = nullptr;
	supply = nullptr;
	players = new vector<Player*>();
	startingCountry = nullptr;

}

GameEngine::GameEngine(string modeChosen) 
{
	mode = (modeChosen == "tournament" ? GameEngine::mode::tournament: GameEngine::mode::single);//default mode will be single game
	map = nullptr;
	//mapLoader = NULL;
	deck = nullptr;
	supply = nullptr;
	players = new vector<Player*>();
	startingCountry = nullptr;
}

GameEngine::~GameEngine()
{
	delete map, /*mapLoader,*/ deck, supply, players;
	map = NULL;
	//mapLoader = NULL;
	deck = NULL;
	supply = NULL;
	players = NULL;
}

void GameEngine::setMode(string modeChosen)
{
	if (modeChosen == "tournament")
		mode =GameEngine::mode:: tournament;
	if (modeChosen == "single")
		mode = GameEngine::mode::single;
	else
		cout << "Mode invalid" << endl;// TODO: Need to handle this exception
}

int GameEngine::getMode()
{
	return static_cast<int>(this->mode);
}

void GameEngine::setStartingCountry(Country* country)
{
	startingCountry = country;

}

void GameEngine::chooseMap()
{
	// Select map from list of files.
	map = Map::getInstance();
	MapLoader* mapLoader = nullptr;
	while (true)
	{
		string mapFileName = getMapFileName();
		try
		{
			mapLoader = new MapLoader(mapFileName, map);
			break;
		}
		catch (const MapLoaderException & e)
		{
			cout << e.message << endl;
			cout << "Try again." << endl;
			cout << endl;
			delete mapLoader;
		}
	}
	cout << "You've selected the following map: " << endl;
	map->print();
	cout << endl;
	setStartingCountry(map->startingCountry); //Starting country is loaded from map
}
//Retrieve numbers of players for the game
 void GameEngine::getNumOfPlayers()
{
	int playerInput;
	while (true)
	{
		cout << "Enter the number of players [2-5] who will be playing this game: ";
		cin >> playerInput;
		if (cin.fail() || playerInput < 2 || playerInput > 5)
		{
			cout << "You've entered a number outside of the correct range. Try again." << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // See [1]
		}
		else
		{
			cout << endl;
			break;
		}
	}
	NUM_PLAYERS = playerInput;
}

 void GameEngine::getNumCoinsPerPlayer(const int numPlayers)
 {
	 int numCoinsPerPlayer = 0;
	 switch (numPlayers)
	 {
	 case 2:
		 numCoinsPerPlayer = 14;
		 break;
	 case 3:
		 numCoinsPerPlayer = 11;
		 break;
	 case 4:
		 numCoinsPerPlayer = 9;
		 break;
	 case 5:
		 numCoinsPerPlayer = 8;
		 break;
	 default:
		 break;
	 }
	NUM_COINS_PER_PLAYER= numCoinsPerPlayer;
 }
//Will need to implement Strategy pattern here to handle choosePlayer
//According to the mode
//Old choosePlayers
//void GameEngine::choosePlayers()
//{
//******TODO: Call createPlayers() from the driver;****
//}

//New choosePlayers
 void GameEngine::choosePlayers()
{
	 getNumOfPlayers();

	 //TODO: Create CPU player
	 for (int i = 0; i < NUM_PLAYERS; i++)
	 {
		 string name;
		 int age;
		 cout << "New player, enter your name: ";
		 cin >> name;
		 cout << "Enter your age: ";
		 cin >> age;
		 Player* player = new Player(name, age, NUM_COINS_PER_PLAYER, COLORS[i], deck);
		 players->push_back(player);
		 player->printPlayer();
	 }
	 
	 //TODO: Foreach CPU player choose a strategy
	
	 //TODO: Choose the first player

}